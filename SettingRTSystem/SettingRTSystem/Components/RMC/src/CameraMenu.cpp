#include <QtWidgets> 
#include <QtGui>
#include "CameraMenu.h"



CameraDialog::CameraDialog(QWidget *parent)
    : QDialog(parent)
{

	tc = QTextCodec::codecForLocale();
	createButtons();

	Flag = false;

    createComboBoxes();
    createLabels();
    createLayout();

    BodyComboBox->addItem("Camera");

    setWindowTitle(tc->toUnicode("Camera menu"));

}


bool CameraDialog::ReturnFLAG()
{

	return Flag;

}

void CameraDialog::createButtons()
{
    buttonBox = new QDialogButtonBox;

    closeButton = buttonBox->addButton(QDialogButtonBox::Close);
    helpButton = buttonBox->addButton(QDialogButtonBox::Help);
    createButton = buttonBox->addButton(tc->toUnicode("作成"),
                                               QDialogButtonBox::ActionRole);


    connect(createButton, SIGNAL(clicked()), this, SLOT(createitems()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

}

CameraParam CameraDialog::returnParam()
{

	return camerapage->returnParam();
}

void CameraDialog::createitems()
{
        if(camerapage->returnParam().NAME == tc->toUnicode(""))
        {
            QMessageBox::about(this, "Error", tc->toUnicode("名前がありません"));
        }
        else
        {
            Flag = true;
            this->close();
        }
}

void CameraDialog::help()
{

}




void CameraDialog::update()
{
	if(BodyComboBox->currentText() == "Camera")
	{
		myCamera = Camera;
	}
	
}




void CameraDialog::createComboBoxes()
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


void CameraDialog::createLabels()
{
    BodyLabel = new QLabel(tc->toUnicode("Camera:"));
    fileNameLabel = new QLabel(tc->toUnicode(""));
}

void CameraDialog::createLayout()
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
	camerapage = new CameraPage;
	QWidget *CameraWidget = camerapage;
    pagesWidget->addWidget(CameraWidget);
	mainLayout->addWidget(buttonBox);
	mainLayout->addWidget(pagesWidget, 1);
    setLayout(mainLayout);
}

void CameraDialog::SetParam(CameraParam cp)
{
	if(cp.m_type == Camera)
		BodyComboBox->setCurrentIndex(Camera);


	camerapage->setParam(cp);

}

