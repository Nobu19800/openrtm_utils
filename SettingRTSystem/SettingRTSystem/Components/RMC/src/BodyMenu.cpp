 
#include <QtWidgets>
#include <QtGui>
#include "BodyMenu.h"
#include <qtextcodec.h>
#include <iostream>



BodyDialog::BodyDialog(QWidget *parent)
    : QDialog(parent)
{

	tc = QTextCodec::codecForLocale();
	createButtons();





	Flag = false;

    createComboBoxes();
    createLabels();
    createLayout();

    BodyComboBox->addItem("box");
	BodyComboBox->addItem("sphere");
	BodyComboBox->addItem("cylinder");
	BodyComboBox->addItem("cone");
	BodyComboBox->addItem("polygon");

	BTComboBox->addItem("Free");
	BTComboBox->addItem("Fix");

    setWindowTitle(tc->toUnicode("Body menu"));

	connect(boxpage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->lengthCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->widthCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->heightCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->slxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->slyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->slzCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->MassCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->RedCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->BlueCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(boxpage->GreenCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));

	connect(cylinderpage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->lengthCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->radCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->slxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->slyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->slzCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->MassCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->RedCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->BlueCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(cylinderpage->GreenCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));

	connect(conepage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->lengthCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->radCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->slxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->slyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->slzCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->MassCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->RedCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->BlueCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(conepage->GreenCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));

	connect(spherepage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(spherepage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(spherepage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(spherepage->radCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(spherepage->MassCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(spherepage->RedCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(spherepage->BlueCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(spherepage->GreenCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));

	
	connect(polygonpage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(polygonpage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(polygonpage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(polygonpage->slxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(polygonpage->slyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(polygonpage->slzCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
	connect(polygonpage->MassCombo, SIGNAL(valueChanged(double)),
        this, SLOT(update()));
 


}


bool BodyDialog::ReturnFLAG()
{

	return Flag;

}

void BodyDialog::createButtons()
{

    buttonBox = new QDialogButtonBox;

    closeButton = buttonBox->addButton(QDialogButtonBox::Close);
    helpButton = buttonBox->addButton(QDialogButtonBox::Help);
    createButton = buttonBox->addButton(tc->toUnicode("作成"),
                                               QDialogButtonBox::ActionRole);
	LoadButton = buttonBox->addButton(tc->toUnicode("Load VRML"),
                                               QDialogButtonBox::ActionRole);


    connect(createButton, SIGNAL(clicked()), this, SLOT(createitems()));
	connect(LoadButton, SIGNAL(clicked()), this, SLOT(FileLoad()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

}

void BodyDialog::createitems()
{
	if(myGeom == Body_Box)
	{
		m_bp = boxpage->returnParam();
	
		if(m_bp.m_length<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("立方体の長さは0以上にする必要があります．"));
		}
		else if(m_bp.m_width<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("立方体の幅は0以上にする必要があります．"));
		}
		else if(m_bp.m_height<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("立方体の高さは0以上にする必要があります．"));
		}
		else if(m_bp.m_mass<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("質量は0以上にする必要があります．"));
		}
		else if(m_bp.NAME == tc->toUnicode(""))
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
	else if (myGeom == Body_Sphere)
	{
		m_bp = spherepage->returnParam();
		if(m_bp.m_rad<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("球の半径は0以上にする必要があります．"));
		}
		else if(m_bp.m_mass<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("質量は0以上にする必要があります．"));
		}
		else if(m_bp.NAME == tc->toUnicode(""))
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
	else if (myGeom == Body_Cylinder)
	{
		m_bp = cylinderpage->returnParam();
		if(m_bp.m_length<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("円柱の長さは0以上にする必要があります．"));
		}
		else if(m_bp.m_rad<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("円柱の半径は0以上にする必要があります．"));
		}
		else if(m_bp.m_mass<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("質量は0以上にする必要があります．"));
		}
		else if(m_bp.NAME == tc->toUnicode(""))
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
	else if (myGeom == Body_Cone)
	{
		m_bp = conepage->returnParam();
		if(m_bp.m_length<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("円錐の長さは0以上にする必要があります．"));
		}
		else if(m_bp.m_rad<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("円錐の半径は0以上にする必要があります．"));
		}
		else if(m_bp.m_mass<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("質量は0以上にする必要があります．"));
		}
		else if(m_bp.NAME == tc->toUnicode(""))
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
	else if (myGeom == Body_Polygon)
	{
		m_bp = polygonpage->returnParam();
		
		if(m_bp.m_mass<=0)
		{
			QMessageBox::about(this, "Error", 
                        tc->toUnicode("質量は0以上にする必要があります．"));
		}
		else if(m_bp.NAME == tc->toUnicode(""))
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

void BodyDialog::help()
{

}


BodyParam BodyDialog::returnParam()
{

	if(myGeom == Body_Box)
	{
		return boxpage->returnParam();
	}
	else if (myGeom == Body_Sphere)
	{
		return spherepage->returnParam();
	}
	else if (myGeom == Body_Cylinder)
	{
		return cylinderpage->returnParam();
	}
	else if (myGeom == Body_Cone)
	{
		return conepage->returnParam();
	}
	else if (myGeom == Body_Polygon)
	{
		return polygonpage->returnParam();
	}
	return BodyParam();
}





void BodyDialog::update()
{
	if(BodyComboBox->currentText() == "box")
	{
		
		myGeom = Body_Box;
		pagesWidget->setCurrentIndex(Body_Box);
		BodyParam bp = boxpage->returnParam();
		GraBox->setBodyParam(&bp,0);
		GraBox->updateGL();
	}

	else if(BodyComboBox->currentText() == "sphere")
	{
		myGeom = Body_Sphere;
		pagesWidget->setCurrentIndex(Body_Sphere);
		BodyParam bp = spherepage->returnParam();
		GraBox->setBodyParam(&bp, 0);
		GraBox->updateGL();
	}

	else if(BodyComboBox->currentText() == "cylinder")
	{
		myGeom = Body_Cylinder;
		pagesWidget->setCurrentIndex(Body_Cylinder);
		BodyParam bp = cylinderpage->returnParam();
		GraBox->setBodyParam(&bp, 0);
		GraBox->updateGL();
	}

	else if(BodyComboBox->currentText() == "cone")
	{
		myGeom = Body_Cone;
		pagesWidget->setCurrentIndex(Body_Cone);
		BodyParam bp = conepage->returnParam();
		GraBox->setBodyParam(&bp, 0);
		GraBox->updateGL();
	}

	else if(BodyComboBox->currentText() == "polygon")
	{
		myGeom = Body_Polygon;
		pagesWidget->setCurrentIndex(Body_Polygon);
			BodyParam bp = polygonpage->returnParam();
			GraBox->setBodyParam(&bp, 0);
			GraBox->updateGL();
		
	}

	if(BTComboBox->currentText() == "Free")
	{
		BT = BTFree;
		
	}
	if(BTComboBox->currentText() == "Fix")
	{
		BT = BTFix;
		
	}


	
}




void BodyDialog::createComboBoxes()
{
    BodyComboBox = new QComboBox;
    
    BodyComboBox->setMinimumContentsLength(30);
    BodyComboBox->setSizeAdjustPolicy(
            QComboBox::AdjustToMinimumContentsLength);
    BodyComboBox->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Preferred);


    connect(BodyComboBox, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(update()));

	BTComboBox = new QComboBox;
	BTComboBox->setMinimumContentsLength(30);
    BTComboBox->setSizeAdjustPolicy(
            QComboBox::AdjustToMinimumContentsLength);
    BTComboBox->setSizePolicy(QSizePolicy::Expanding,
                                     QSizePolicy::Preferred);

	connect(BTComboBox, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(update()));

}


void BodyDialog::createLabels()
{

    BodyLabel = new QLabel(tc->toUnicode("Body:"));
	BTLabel = new QLabel(tc->toUnicode("Type:"));
    fileNameLabel = new QLabel(tc->toUnicode(""));
}

void BodyDialog::createLayout()
{
    fileLayout = new QHBoxLayout;
    fileLayout->addWidget(fileNameLabel);


    QHBoxLayout *directoryLayout = new QHBoxLayout;
    directoryLayout->addWidget(BodyLabel);
    directoryLayout->addWidget(BodyComboBox);

	directoryLayout->addWidget(BTLabel);
	directoryLayout->addWidget(BTComboBox);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(fileLayout);
    mainLayout->addLayout(directoryLayout);
    mainLayout->addStretch();
	pagesWidget = new QStackedWidget;
	boxpage = new BoxPage;
	spherepage = new SpherePage;
	cylinderpage = new CylinderPage;
	conepage = new ConePage;
	polygonpage = new PolygonPage;
	QWidget *BoxWidget = boxpage;
	QWidget *SphereWidget = spherepage;
	QWidget *CylinderWidget = cylinderpage;
	QWidget *ConeWidget = conepage;
	QWidget *PolygonWidget = polygonpage;
    pagesWidget->addWidget(BoxWidget);
	pagesWidget->addWidget(SphereWidget);
    pagesWidget->addWidget(CylinderWidget);
	pagesWidget->addWidget(ConeWidget);
	pagesWidget->addWidget(PolygonWidget);
	mainLayout->addWidget(buttonBox);
	QFrame* f = new QFrame;
    f->setFrameStyle( QFrame::Sunken | QFrame::Panel );
    f->setLineWidth( 2 );

    GraBox = new GLBox( f, "glbox");

	QHBoxLayout* flayout = new QHBoxLayout(f);
    flayout->setMargin(0);
    flayout->addWidget( GraBox, 0 );



	f->resize(1000, 1000);

	f->setMinimumSize(QSize(300, 300));
	f->setMaximumSize(QSize(300, 300));

	mainLayout->addWidget(pagesWidget, 1);

	QHBoxLayout *mainlayout2;
	mainlayout2 = new QHBoxLayout;
	mainlayout2->addLayout(mainLayout, 1);
	mainlayout2->addWidget(f, 1);



    setLayout(mainlayout2);
}

void BodyDialog::SetParam(BodyParam bp)
{

	if (bp.m_type == Body_Box)
		BodyComboBox->setCurrentIndex(Body_Box);
	boxpage->setParam(bp);
	
	if (bp.m_type == Body_Sphere)
		BodyComboBox->setCurrentIndex(Body_Sphere);
	spherepage->setParam(bp);
	
	if (bp.m_type == Body_Cylinder)
		BodyComboBox->setCurrentIndex(Body_Cylinder);
	cylinderpage->setParam(bp);
	
	if (bp.m_type == Body_Cone)
		BodyComboBox->setCurrentIndex(Body_Cone);
	conepage->setParam(bp);
	
	if (bp.m_type == Body_Polygon)
		BodyComboBox->setCurrentIndex(Body_Polygon);
	polygonpage->setParam(bp);

}

void BodyDialog::FileLoad()
{
    QString fileName = QFileDialog::getOpenFileName(this, tc->toUnicode("Choose a VRML file"),
                                                "", "VRML Files(*.wrl)");
    if (fileName.isEmpty())
        return;


    loadFile(fileName);
}


void BodyDialog::loadFile(const QString &fileName)
{


	PolygonData pd;
	pd.loadFile(fileName, this);
	polygonpage->m_pd = pd;

	if(BodyComboBox->currentText() == "polygon")
	{
		myGeom = Body_Polygon;
		pagesWidget->setCurrentIndex(Body_Polygon);
		BodyParam bp = polygonpage->returnParam();
		bp.m_pd = pd;
		GraBox->setBody(new BodyData(bp),0);

		GraBox->updateGL();

		
		
	}
}



void BodyDialog::Judge()
{

	BodyParam bp = polygonpage->returnParam();
	GraBox->setBodyParam(&bp,0);
	
	

}
