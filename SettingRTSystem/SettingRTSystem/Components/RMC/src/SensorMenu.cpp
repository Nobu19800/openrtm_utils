#include <QtWidgets>
#include <QtGui>
#include "SensorMenu.h"
#include <qtextcodec.h>



SensorDialog::SensorDialog(QWidget *parent)
    : QDialog(parent)
{
	tc = QTextCodec::codecForLocale();
	createButtons();

	Flag = false;

    createComboBoxes();
    createLabels();
    createLayout();

    BodyComboBox->addItem("Force");
	BodyComboBox->addItem("Gyro");
	BodyComboBox->addItem("Range");
	BodyComboBox->addItem("Acceleration");
	BodyComboBox->addItem("Torque");

    setWindowTitle(tc->toUnicode("Sensor menu"));

}


bool SensorDialog::ReturnFLAG()
{

	return Flag;

}

void SensorDialog::createButtons()
{

    buttonBox = new QDialogButtonBox;

    closeButton = buttonBox->addButton(QDialogButtonBox::Close);
    helpButton = buttonBox->addButton(QDialogButtonBox::Help);
	createButton = buttonBox->addButton(tc->toUnicode("作成"),QDialogButtonBox::ActionRole);
    connect(createButton, SIGNAL(clicked()), this, SLOT(createitems()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

}

void SensorDialog::createitems()
{
        if(sensorpage->returnParam().NAME == tc->toUnicode(""))
        {
            QMessageBox::about(this, "Error", tc->toUnicode("名前がありません"));
        }
        else
        {
            Flag = true;
            this->close();
        }
}

void SensorDialog::help()
{

}


SensorParam SensorDialog::returnParam()
{
	update();

	SensorParam sp = sensorpage->returnParam();
	sp.m_type = mySensor;
	return sp;

}


void SensorDialog::update()
{
	if(BodyComboBox->currentText() == "Force")
	{
		mySensor = Force;
	}

	else if(BodyComboBox->currentText() == "Gyro")
	{
		mySensor = Gyro;
	}

	else if(BodyComboBox->currentText() == "Range")
	{
		mySensor = Range;
	}

	else if(BodyComboBox->currentText() == "Acceleration")
	{
		mySensor = Acceleration;
	}
	else if(BodyComboBox->currentText() == "Torque")
	{
		mySensor = Torque;
	}

	


	
}




void SensorDialog::createComboBoxes()
{
    BodyComboBox = new QComboBox;
    
    BodyComboBox->setMinimumContentsLength(30);
    BodyComboBox->setSizeAdjustPolicy(
            QComboBox::AdjustToMinimumContentsLength);
    BodyComboBox->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Preferred);


    connect(BodyComboBox, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(update()));
}


void SensorDialog::createLabels()
{
    BodyLabel = new QLabel(tc->toUnicode("Sensor:"));
    fileNameLabel = new QLabel(tc->toUnicode(""));
}

void SensorDialog::createLayout()
{
    fileLayout = new QHBoxLayout;
    fileLayout->addWidget(fileNameLabel);


    QHBoxLayout *directoryLayout = new QHBoxLayout;
    directoryLayout->addWidget(BodyLabel);
    directoryLayout->addWidget(BodyComboBox);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(fileLayout);
    mainLayout->addLayout(directoryLayout);
    mainLayout->addStretch();
	pagesWidget = new QStackedWidget;
	sensorpage = new SensorPage;
	QWidget *SensorWidget = sensorpage;
    pagesWidget->addWidget(SensorWidget);
	mainLayout->addWidget(buttonBox);
	mainLayout->addWidget(pagesWidget, 1);
    setLayout(mainLayout);
}

void SensorDialog::SetParam(SensorParam sp)
{
	if(sp.m_type == Force)
		BodyComboBox->setCurrentIndex(Force);
	if (sp.m_type == Gyro)
		BodyComboBox->setCurrentIndex(Gyro);

	if (sp.m_type == Range)
		BodyComboBox->setCurrentIndex(Range);

	if (sp.m_type == Acceleration)
		BodyComboBox->setCurrentIndex(Acceleration);
	
	if (sp.m_type == Torque)
		BodyComboBox->setCurrentIndex(Torque);


	sensorpage->setParam(sp);

}

 