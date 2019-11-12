// -*- C++ -*-
/*!
 * @file  graphicsview.cpp
 * @brief 画像表示ウィジェット
 */

#include "graphicsview.h"
#include "PresentationView.h"
#include "ImageDataCom.h"


extern PresentationView* comp;

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



GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
	saveVideo = false;

	

	my_timer = new QTimer();
	connect(my_timer, SIGNAL(timeout()), this, SLOT(show_time()));
    //startTimer(10);
	m_rate = 30;
	file_path = "sample.avi";
	my_timer->start(m_rate);

	iplimage = NULL;
	resizeimage = NULL;
	vw = NULL;

	m_scale = 1.0;
	
}

GraphicsView::~GraphicsView()
{
	if(my_timer)delete my_timer;
}

void GraphicsView::show_time()
{
	
	//update();
	//repaint();
	if(comp != NULL)
	{
		
		if(comp->imageIsNew)
		{
			viewport()->update();
		}
	}

	if(vw != NULL && iplimage != NULL)
	{
		cvWriteFrame(vw, iplimage);

	}
}

void GraphicsView::paintEvent(QPaintEvent *)
{
	if(vw != NULL && !saveVideo)
	{
		cvReleaseVideoWriter(&vw);
	}
	
	if(comp != NULL)
	{
		
		if(comp->imageIsNew)
		{
			CameraImage *m_image = comp->getImage();
			comp->imageIsNew = false;
			if(iplimage != NULL)
			{
				if(saveVideo)
				{
					if(vw == NULL)
					{
						vw = cvCreateVideoWriter (file_path.c_str(), CV_FOURCC ('X', 'V', 'I', 'D'), m_rate, cvSize((int) iplimage->width, (int) iplimage->height));
					}
					


				}

				cvReleaseImage(&iplimage);
				
			}
			if(resizeimage != NULL)
				cvReleaseImage(&resizeimage);
			iplimage = GetCameraImage(m_image);
			int t_width = m_image->width*m_scale;
			int t_height = m_image->height*m_scale;
			resizeimage = cvCreateImage(cvSize(t_width, t_height), iplimage->depth, iplimage->nChannels);
			cvResize(iplimage, resizeimage);
			setMinimumSize(t_width, t_height);
			setMaximumSize(t_width, t_height);
			//setMinimumSize( m_image->width, m_image->height);
			//setMaximumSize( m_image->width, m_image->height);

		}
	}

	if(resizeimage != NULL)
	{
		cv::Mat src, dst;
		src = cv::cvarrToMat(resizeimage);
		//src = cv::imread("sample.jpg");
		cv::cvtColor(src, dst, CV_RGB2BGR);
		QImage img(dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888);

	

		QPainter qPainter(viewport());
		qPainter.drawImage(0, 0, img);

		
	}
		
    
}

void GraphicsView::startSaveVideo(int fps, const char* fn)
{
	m_rate = fps;
	file_path = fn;
	saveVideo = true;
	my_timer->start(m_rate);
}

void GraphicsView::mousePressEvent(QMouseEvent *e)
{
	
}

void GraphicsView::mouseReleaseEvent(QMouseEvent *e)
{
	
	if(e->button() == Qt::LeftButton)
	{
		if(comp != NULL)
		{
			
			comp->putPenData(&posList);
		}
		posList.clear();
	}
}

void GraphicsView::mouseMoveEvent(QMouseEvent *e)
{
	if(e->buttons() & Qt::LeftButton)
	{
		
		posList.push_back(e->pos().x()/m_scale);
		posList.push_back(e->pos().y()/m_scale);
	}
}