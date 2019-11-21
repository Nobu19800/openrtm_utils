#include <QtWidgets>
#include <QtGui>
#include <qtextcodec.h>
#include "JointMenu.h"


ActDialog::ActDialog(QWidget *parent)
    : QDialog(parent)
{
	tc = QTextCodec::codecForLocale();
	createButtons();

	Flag = false;

    createComboBoxes();
    createLabels();
    createLayout();

    JointComboBox->addItem("hinge");
	JointComboBox->addItem("slider");
	JointComboBox->addItem("fix");

	


    setWindowTitle(tc->toUnicode("Joint Menu"));

}


bool ActDialog::ReturnFLAG()
{

	return Flag;

}

void ActDialog::createButtons()
{
    buttonBox = new QDialogButtonBox;

    closeButton = buttonBox->addButton(QDialogButtonBox::Close);
    helpButton = buttonBox->addButton(QDialogButtonBox::Help);
    createButton = buttonBox->addButton(tc->toUnicode("作成"),
                                               QDialogButtonBox::ActionRole);

    connect(createButton, SIGNAL(clicked()), this, SLOT(createitems()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

}

void ActDialog::createitems()
{
	if(myGeom == Hinge)
	{
		m_jp = hingepage->returnParam();
		if(m_jp.m_axisx==0&&m_jp.m_axisy==0&&m_jp.m_axisz==0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("軸が設定されてません."));
		}
		else if(m_jp.NAME == tc->toUnicode(""))
		{
			QMessageBox::about(this, "Error", 
				            tc->toUnicode("名前がありません"));
		}
		else
		{
			Flag = true;
			this->close();
		}
	}
	else if(myGeom == Slider)
	{
		m_jp = sliderpage->returnParam();
		if(m_jp.m_axisx==0&&m_jp.m_axisy==0&&m_jp.m_axisz==0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("軸が設定されてません."));
		}
		else if(m_jp.NAME == tc->toUnicode(""))
		{
			QMessageBox::about(this, "Error", 
				            tc->toUnicode("名前がありません"));
		}
		else
		{
			Flag = true;
			this->close();
		}
	}
	else if(myGeom == Fix)
	{
		m_jp = fixpage->returnParam();
		if(m_jp.NAME == tc->toUnicode(""))
		{
			QMessageBox::about(this, "Error", 
				            tc->toUnicode("名前がありません"));
		}
		else
		{
			Flag = true;
			this->close();
		}
	}

	
}


void ActDialog::help()
{

}


JointParam ActDialog::returnParam()
{
	JointParam jp;
	if(myGeom == Hinge)
	{
		jp = hingepage->returnParam();
	}
	else if(myGeom == Slider)
	{
		jp = sliderpage->returnParam();
	}
	else if(myGeom == Fix)
	{
		jp = fixpage->returnParam();
	}

	return jp;
}



void ActDialog::update()
{
	
	if(JointComboBox->currentText() == "hinge")
	{
		myGeom = Hinge;
		pagesWidget->setCurrentIndex(Hinge);
	}

	else if(JointComboBox->currentText() == "slider")
	{
		myGeom = Slider;
		pagesWidget->setCurrentIndex(Slider);
	}

	else if(JointComboBox->currentText() == "fix")
	{
		myGeom = Fix;
		pagesWidget->setCurrentIndex(Fix);
	}


	
}




void ActDialog::createComboBoxes()
{
    JointComboBox = new QComboBox;



    JointComboBox->setMinimumContentsLength(30);
    JointComboBox->setSizeAdjustPolicy(
            QComboBox::AdjustToMinimumContentsLength);
    JointComboBox->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Preferred);


    connect(JointComboBox, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(update()));
}


void ActDialog::createLabels()
{
    JointLabel = new QLabel(tc->toUnicode("Joint:"));
    fileNameLabel = new QLabel(tc->toUnicode(""));
}

void ActDialog::createLayout()
{
    fileLayout = new QHBoxLayout;
    fileLayout->addWidget(fileNameLabel);


    QHBoxLayout *directoryLayout = new QHBoxLayout;
    directoryLayout->addWidget(JointLabel);
    directoryLayout->addWidget(JointComboBox);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(fileLayout);
    mainLayout->addLayout(directoryLayout);
    mainLayout->addStretch();

	pagesWidget = new QStackedWidget;


	hingepage = new HingePage;
	QWidget *HingeWidget = hingepage;
    pagesWidget->addWidget(HingeWidget);

	
	sliderpage = new SliderPage;
	QWidget *SliderWidget = sliderpage;
    pagesWidget->addWidget(SliderWidget);

	
	fixpage = new FixPage;
	QWidget *FixWidget = fixpage;
    pagesWidget->addWidget(FixWidget);

	mainLayout->addWidget(buttonBox);
	mainLayout->addWidget(pagesWidget, 1);
    setLayout(mainLayout);
}

void ActDialog::SetParam(JointParam jp)
{

	if (jp.m_type == Hinge)
		JointComboBox->setCurrentIndex(Hinge);


	hingepage->setParam(jp);
	
	if (jp.m_type == Slider)
		JointComboBox->setCurrentIndex(Slider);

	sliderpage->setParam(jp);
	
	if (jp.m_type == Fix)
		JointComboBox->setCurrentIndex(Fix);

	fixpage->setParam(jp);

} 
