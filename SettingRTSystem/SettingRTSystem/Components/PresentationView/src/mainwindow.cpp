// -*- C++ -*-
/*!
 * @file  mainwindow.cpp
 * @brief メインウインドウ
 */

#include "mainwindow.h"
#include "PresentationView.h"


#include <QAction>
#include <QLayout>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>
#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <qdebug.h>
#include <QtWidgets>


extern PresentationView* comp;


MainWindow::MainWindow()
{
    tc = QTextCodec::codecForLocale();
    setWindowTitle("Presentation View Component");

    QHBoxLayout *layout = new QHBoxLayout;

	QWidget *widget = new QWidget;
    widget->setLayout(layout);

	setCentralWidget(widget);

	menuBar()->addMenu(tr("&File"));

	gv = new GraphicsView(this);
	
	layout->addWidget(gv);

	QVBoxLayout *b_layout = new QVBoxLayout;
	pageGB = new QPushButton(tc->toUnicode("ページを進める"));
	b_layout->addWidget(pageGB);
	connect(pageGB, SIGNAL(clicked()), this, SLOT(pageGclickedSlot()));
	pageRB = new QPushButton(tc->toUnicode("ページを戻す"));
	b_layout->addWidget(pageRB);
	connect(pageRB, SIGNAL(clicked()), this, SLOT(pageRclickedSlot()));
	effGB = new QPushButton(tc->toUnicode("アニメーションを実行"));
	b_layout->addWidget(effGB);
	connect(effGB, SIGNAL(clicked()), this, SLOT(effGclickedSlot()));
	effRB = new QPushButton(tc->toUnicode("アニメーションを戻す"));
	b_layout->addWidget(effRB);
	connect(effRB, SIGNAL(clicked()), this, SLOT(effRclickedSlot()));

	saveSB = new QPushButton(tc->toUnicode("動画を保存を開始"));
	b_layout->addWidget(saveSB);
	connect(saveSB, SIGNAL(clicked()), this, SLOT(saveSclickedSlot()));

	saveEB = new QPushButton(tc->toUnicode("動画の保存を終了"));
	b_layout->addWidget(saveEB);
	connect(saveEB, SIGNAL(clicked()), this, SLOT(saveEclickedSlot()));

	

	QVBoxLayout *scaleLayout = new QVBoxLayout();
	QLabel *scaleLabel = new QLabel(tc->toUnicode("拡大率(％)"));
	scaleLayout->addWidget(scaleLabel);
	scaleSB = new QSpinBox();
	scaleSB->setMaximum(1000);
	scaleSB->setMinimum(1);
	scaleSB->setValue(100);
	scaleLayout->addWidget(scaleSB);
	connect(scaleSB, SIGNAL(valueChanged(int)), this, SLOT(scalevalueChangedSlot(int)));
	b_layout->addLayout(scaleLayout);
	

	QVBoxLayout *fpsLayout = new QVBoxLayout();
	QLabel *fpsLabel = new QLabel(tc->toUnicode("FPS"));
	fpsLayout->addWidget(fpsLabel);
	fpsSB = new QSpinBox();
	fpsSB->setMaximum(1000);
	fpsSB->setMinimum(1);
	fpsSB->setValue(30);
	fpsLayout->addWidget(fpsSB);
	b_layout->addLayout(fpsLayout);


	layout->addLayout(b_layout);


	

	grtcTable = new QTableWidget();
	
	/*QTableWidgetItem *iName = new QTableWidgetItem(tc->toUnicode("FPS"));
	//grtcTable->insertRow(0);
	grtcTable->setColumnCount( 1 );
	grtcTable->setRowCount( 1 );
	grtcTable->setItem(0, 0, iName);
	grtcTable->setRowCount( 2 );
	QList<QTableWidgetItem*> twis = grtcTable->selectedItems();
	grtcTable->clear();*/

	b_layout->addWidget(grtcTable);

	updateB = new QPushButton(tc->toUnicode("更新"));
	b_layout->addWidget(updateB);
	connect(updateB, SIGNAL(clicked()), this, SLOT(updateclickedSlot()));

	connectB = new QPushButton(tc->toUnicode("接続"));
	b_layout->addWidget(connectB);
	connect(connectB, SIGNAL(clicked()), this, SLOT(connectclickedSlot()));

	

}

void MainWindow::pageGclickedSlot()
{
	if(comp != NULL)
	{
		comp->writeSlideNumberOut(1);
	}
}

void MainWindow::pageRclickedSlot()
{
	if(comp != NULL)
	{
		comp->writeSlideNumberOut(-1);
	}
}

void MainWindow::effGclickedSlot()
{
	if(comp != NULL)
	{
		comp->writeEffectNumberOut(1);
	}
}

void MainWindow::effRclickedSlot()
{
	if(comp != NULL)
	{
		comp->writeEffectNumberOut(-1);
	}
}


void MainWindow::saveSclickedSlot()
{
	if(!gv->saveVideo)
	{
		QString fileName = QFileDialog::getSaveFileName(this,
								tc->toUnicode("保存"), "",
								tr("AVI File (*.avi);;All Files (*)"));
		if (fileName.isEmpty())
			return;

		QByteArray ba = fileName.toLocal8Bit();
		gv->startSaveVideo(fpsSB->value(), ba);
	}
}

void MainWindow::saveEclickedSlot()
{
	if(gv->saveVideo)
	{
		gv->saveVideo = false;
		QMessageBox msgBox(this);
		msgBox.setText(tc->toUnicode("動画の保存を完了しました。"));
		msgBox.exec();
	}
}

void MainWindow::updateclickedSlot()
{
	grtcTable->clear();
	
	if(comp)
	{
		m_result = comp->getList();
		grtcTable->setRowCount( m_result.size() );
		grtcTable->setColumnCount( 1 );

		for(int i=0;i < m_result.size();i++)
		{
			if(m_result[i].size() >= 2)
			{
				QTableWidgetItem *iName = new QTableWidgetItem(tc->toUnicode(m_result[i][0].c_str()));
				grtcTable->setItem(i, 0, iName);
			}
		}
	}

}

void MainWindow::connectclickedSlot()
{
	if(comp)
	{
		QList<QTableWidgetItem*> twis = grtcTable->selectedItems();
		if(twis.size() > 0)
		{
			QTableWidgetItem *twi = twis[0];
			QByteArray ba = twi->text().toLocal8Bit();
			
			if(!comp->connectDPort(ba, m_result))
			{
				QMessageBox msgBox(this);
				msgBox.setText(tc->toUnicode("接続に失敗しました"));
				msgBox.exec();
			}
		}
		else
		{
			QMessageBox msgBox(this);
			msgBox.setText(tc->toUnicode("RTCが選択されていません"));
			msgBox.exec();
		}
	}
}

void MainWindow::scalevalueChangedSlot(int v)
{
	gv->m_scale = (float)v/100.0;
	
}