#include <QtWidgets>
#include <QtGui>
#include <QLabel>
#include <iostream>

#include "mainwindow.h"
#include "Joint.h"
#include "diagramscene.h"
#include "Body.h"
#include "Sensor.h"
#include "Camera.h"

const int InsertTextButton = 10;
const int InsertactButton = 9;
const int InsertsenButton = 11;
const int InsertcamButton = 12;




MainWindow::MainWindow()
{
        tc = QTextCodec::codecForLocale();

	createParamWidget();
	
	
	QTextCodec* tc = QTextCodec::codecForLocale();
	CHECK = false;

	createToolBox();
	
	createActions();
	createMenus();





	QFrame* f = new QFrame;
    f->setFrameStyle( QFrame::Sunken | QFrame::Panel );
    f->setLineWidth( 2 );

	QFrame* f2 = new QFrame;
    f2->setFrameStyle( QFrame::Sunken | QFrame::Panel );
    f2->setLineWidth( 2 );

    c = new GLBox( f, "glbox");

	QHBoxLayout* flayout = new QHBoxLayout(f);
    flayout->setMargin(0);
    flayout->addWidget( c, 0 );

	createSliderWidget();
	createSliderArrowWidget();



	f->resize(1000, 1000);

	f->setMinimumSize(QSize(400, 100));


    scene = new DiagramScene(itemMenu);
	scene->setSceneRect(QRectF(0, 0, 2000, 2000));

    connect(scene, SIGNAL(textInserted(BodyItem *)),
        this, SLOT(textInserted(BodyItem *)));
	
	connect(scene, SIGNAL(actInserted(JointItem *)),
        this, SLOT(actInserted(JointItem *)));

	connect(scene, SIGNAL(senInserted(SensorItem *)),
        this, SLOT(senInserted(SensorItem *)));

	connect(scene, SIGNAL(camInserted(CameraItem *)),
        this, SLOT(camInserted(CameraItem *)));

	connect(scene, SIGNAL(renew()),
        this, SLOT(renew()));
	
	connect(scene, SIGNAL(setRotNum()),
        this, SLOT(setRotNum()));

	connect(scene, SIGNAL(setGeoNum()),
        this, SLOT(setGeoNum()));

	connect(scene, SIGNAL(setSSNum()),
        this, SLOT(setSSNum()));




	createToolbars();

	QHBoxLayout *hlayout = new QHBoxLayout(f2);

    QHBoxLayout *layout = new QHBoxLayout;

	tabWidget = new QTabWidget;
	
	tabWidget->addTab(SliderWidget, tc->toUnicode("パーツ選択ボタン"));
	tabWidget->addTab(SliderArrowWidget, tc->toUnicode("スケール調整(センサ・ジョイントのサイズ)"));
	//QHBoxLayout *layout = new QHBoxLayout;
	//ParamWidget = new QWidget;
	
	//tabWidget->addTab(ParamWidget, tc->toUnicode("パラメータ"));


	layout->addWidget(tabWidget);

    view = new QGraphicsView(scene);
    hlayout->addWidget(view);
	view->setMinimumSize(400, 100);

	layout->addWidget( f2 );

	layout->addWidget( f);
	
	QFrame* f3 = new QFrame;
    f->setFrameStyle( QFrame::Sunken | QFrame::Panel );
    f->setLineWidth( 2 );

	QHBoxLayout *WLayout = new QHBoxLayout(f3);


	RotSlider = new QSlider(Qt::Vertical, this);
    RotSlider->setMaximum(360);
	RotSlider->setValue(180);
    RotSlider->setPageStep(60);
    RotSlider->setTickPosition( QSlider::TicksRight );
	connect( RotSlider, SIGNAL(valueChanged(int)),c,SLOT(setRotation(int)) );



	WLayout->addWidget(RotSlider);
	layout->addWidget( f3);



	

    QWidget *widget = new QWidget;
    widget->setLayout(layout);


    setCentralWidget(widget);
    setWindowTitle(tc->toUnicode("Robot Model Creator"));
    setUnifiedTitleAndToolBarOnMac(true);


	if (RMC::obj)
	{
		if (RMC::obj->getFileName() != "")
		{
			//std::cout << RMC::obj->getFileName() << std::endl;
			loadFile(RMC::obj->getFileName().c_str());
		}
	}
}

void MainWindow::createParamWidget()
{

	boxpage = new BoxPage;
	spherepage = new SpherePage;
	cylinderpage = new CylinderPage;
	conepage = new ConePage;
	polygonpage = new PolygonPage;
	hingepage = new HingePage;
	sliderpage = new SliderPage;
	fixpage = new FixPage;
	sensorpage = new SensorPage;

	connect(boxpage->geomNameComboBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setBox()));
	connect(boxpage->NumComboBox, SIGNAL(valueChanged(int)),
		this, SLOT(setBox()));
	connect(boxpage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->lengthCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->widthCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->heightCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->slxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->slyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->slzCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->MassCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->RedCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->BlueCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->GreenCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->I1Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->I2Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->I3Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->I4Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->I5Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->I6Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->I7Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->I8Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));
	connect(boxpage->I9Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setBox()));

	connect(cylinderpage->geomNameComboBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setCylinder()));
	connect(cylinderpage->NumComboBox, SIGNAL(valueChanged(int)),
		this, SLOT(setCylinder()));
	connect(cylinderpage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->lengthCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->radCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->slxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->slyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->slzCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->MassCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->RedCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->BlueCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->GreenCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->I1Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->I2Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->I3Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->I4Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->I5Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->I6Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->I7Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->I8Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));
	connect(cylinderpage->I9Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCylinder()));

	connect(conepage->geomNameComboBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setCone()));
	connect(conepage->NumComboBox, SIGNAL(valueChanged(int)),
		this, SLOT(setCone()));
	connect(conepage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->lengthCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->radCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->slxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->slyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->slzCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->MassCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->RedCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->BlueCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->GreenCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->I1Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->I2Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->I3Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->I4Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->I5Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->I6Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->I7Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->I8Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));
	connect(conepage->I9Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setCone()));

	connect(spherepage->geomNameComboBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setSphere()));
	connect(spherepage->NumComboBox, SIGNAL(valueChanged(int)),
		this, SLOT(setSphere()));
	connect(spherepage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->radCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->MassCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->RedCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->BlueCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->GreenCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->I1Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->I2Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->I3Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->I4Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->I5Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->I6Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->I7Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->I8Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));
	connect(spherepage->I9Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setSphere()));

	connect(polygonpage->geomNameComboBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setPolygon()));
	connect(polygonpage->NumComboBox, SIGNAL(valueChanged(int)),
		this, SLOT(setPolygon()));
	connect(polygonpage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->slxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->slyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->slzCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->MassCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->I1Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->I2Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->I3Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->I4Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->I5Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->I6Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->I7Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->I8Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));
	connect(polygonpage->I9Combo, SIGNAL(valueChanged(double)),
        this, SLOT(setPolygon()));

	connect(hingepage->geomNameComboBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setHinge()));
	connect(hingepage->NumComboBox, SIGNAL(valueChanged(int)),
		this, SLOT(setHinge()));
	connect(hingepage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->axisxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->axisyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->axiszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->ulimitHCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->ulimitLCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->uvlimitHCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->uvlimitLCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->rotorInertiaCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->rotorResistorCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->torqueConstCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));
	connect(hingepage->encoderPulseCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setHinge()));

	connect(sliderpage->geomNameComboBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setSlider()));
	connect(sliderpage->NumComboBox, SIGNAL(valueChanged(int)),
		this, SLOT(setSlider()));
	connect(sliderpage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->axisxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->axisyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->axiszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->ulimitHCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->ulimitLCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->uvlimitHCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->uvlimitLCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->rotorInertiaCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->rotorResistorCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->torqueConstCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));
	connect(sliderpage->encoderPulseCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSlider()));

	connect(fixpage->geomNameComboBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setFix()));
	connect(fixpage->NumComboBox, SIGNAL(valueChanged(int)),
		this, SLOT(setFix()));
	connect(fixpage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setFix()));
	connect(fixpage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setFix()));
	connect(fixpage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setFix()));

	connect(sensorpage->geomNameComboBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setSensor()));
	connect(sensorpage->NumComboBox, SIGNAL(valueChanged(int)),
		this, SLOT(setSensor()));
	connect(sensorpage->posxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSensor()));
	connect(sensorpage->posyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSensor()));
	connect(sensorpage->poszCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSensor()));
	connect(sensorpage->slxCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSensor()));
	connect(sensorpage->slyCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSensor()));
	connect(sensorpage->slzCombo, SIGNAL(valueChanged(double)),
        this, SLOT(setSensor()));
}

void MainWindow::createSliderArrowWidget()
{
	SliderArrowWidget = new QWidget;

	QFrame* f = new QFrame;
    f->setFrameStyle( QFrame::Sunken | QFrame::Panel );
    f->setLineWidth( 2 );

	
	QHBoxLayout* flayout = new QHBoxLayout(f);
    flayout->setMargin(0);
    


	ArrowForceSlider = new QSlider(Qt::Vertical, this);
    ArrowForceSlider->setMaximum(800);
	ArrowForceSlider->setValue(80);
    ArrowForceSlider->setPageStep(1);
    ArrowForceSlider->setTickPosition( QSlider::TicksRight );
	connect( ArrowForceSlider, SIGNAL(valueChanged(int)),c,SLOT(setForceArrowScale(int)) );

	
	QGroupBox *ArrowForceGroup = new QGroupBox(tc->toUnicode("力センサ"));

	
	QVBoxLayout* ArrowForcelayout = new QVBoxLayout();
	ArrowForcelayout->addWidget(ArrowForceSlider);
	ArrowForceGroup->setLayout(ArrowForcelayout);

	flayout->addWidget( ArrowForceGroup, 0 );

	ArrowGyroSlider = new QSlider(Qt::Vertical, this);
    ArrowGyroSlider->setMaximum(800);
	ArrowGyroSlider->setValue(80);
    ArrowGyroSlider->setPageStep(1);
    ArrowGyroSlider->setTickPosition( QSlider::TicksRight );
	connect( ArrowGyroSlider, SIGNAL(valueChanged(int)),c,SLOT(setGyroArrowScale(int)) );

	
	QGroupBox *ArrowGyroGroup = new QGroupBox(tc->toUnicode("ジャイロセンサ"));

	
	QVBoxLayout* ArrowGyrolayout = new QVBoxLayout();
	ArrowGyrolayout->addWidget(ArrowGyroSlider);
	ArrowGyroGroup->setLayout(ArrowGyrolayout);

	flayout->addWidget( ArrowGyroGroup, 1 );

	ArrowAccSlider = new QSlider(Qt::Vertical, this);
    ArrowAccSlider->setMaximum(800);
	ArrowAccSlider->setValue(80);
    ArrowAccSlider->setPageStep(1);
    ArrowAccSlider->setTickPosition( QSlider::TicksRight );
	connect( ArrowAccSlider, SIGNAL(valueChanged(int)),c,SLOT(setAccArrowScale(int)) );

	
	QGroupBox *ArrowAccGroup = new QGroupBox(tc->toUnicode("加速度センサ"));

	
	QVBoxLayout* ArrowAcclayout = new QVBoxLayout();
	ArrowAcclayout->addWidget(ArrowAccSlider);
	ArrowAccGroup->setLayout(ArrowAcclayout);

	flayout->addWidget( ArrowAccGroup, 2 );

	ArrowRangeSlider = new QSlider(Qt::Vertical, this);
    ArrowRangeSlider->setMaximum(800);
	ArrowRangeSlider->setValue(80);
    ArrowRangeSlider->setPageStep(1);
    ArrowRangeSlider->setTickPosition( QSlider::TicksRight );
	connect( ArrowRangeSlider, SIGNAL(valueChanged(int)),c,SLOT(setRangeArrowScale(int)) );

	
	QGroupBox *ArrowRangeGroup = new QGroupBox(tc->toUnicode("距離センサ"));

	
	QVBoxLayout* ArrowRangelayout = new QVBoxLayout();
	ArrowRangelayout->addWidget(ArrowRangeSlider);
	ArrowRangeGroup->setLayout(ArrowRangelayout);

	flayout->addWidget( ArrowRangeGroup, 3 );

	ArrowTorqueSlider = new QSlider(Qt::Vertical, this);
    ArrowTorqueSlider->setMaximum(800);
	ArrowTorqueSlider->setValue(80);
    ArrowTorqueSlider->setPageStep(1);
    ArrowTorqueSlider->setTickPosition( QSlider::TicksRight );
	connect( ArrowTorqueSlider, SIGNAL(valueChanged(int)),c,SLOT(setTorqueArrowScale(int)) );

	
	QGroupBox *ArrowTorqueGroup = new QGroupBox(tc->toUnicode("トルクセンサ"));

	
	QVBoxLayout* ArrowTorquelayout = new QVBoxLayout();
	ArrowTorquelayout->addWidget(ArrowTorqueSlider);
	ArrowTorqueGroup->setLayout(ArrowTorquelayout);

	flayout->addWidget( ArrowTorqueGroup, 4 );

	

	

	SliderArrowWidget->setLayout(flayout);

}

void MainWindow::createSliderWidget()
{
	SliderWidget = new QWidget;

	QFrame* f = new QFrame;
    f->setFrameStyle( QFrame::Sunken | QFrame::Panel );
    f->setLineWidth( 2 );

	
	QHBoxLayout* flayout = new QHBoxLayout(f);
    flayout->setMargin(0);
    

	JointSlider = new QSlider(Qt::Vertical, this);
    JointSlider->setMaximum(800);
	JointSlider->setValue(20);
    JointSlider->setPageStep(1);
    JointSlider->setTickPosition( QSlider::TicksRight );
	connect( JointSlider, SIGNAL(valueChanged(int)),c,SLOT(setJointScale(int)) );

	SensorSlider = new QSlider(Qt::Vertical, this);
    SensorSlider->setMaximum(800);
	SensorSlider->setValue(20);
    SensorSlider->setPageStep(1);
    SensorSlider->setTickPosition( QSlider::TicksRight );
	connect( SensorSlider, SIGNAL(valueChanged(int)),c,SLOT(setSensorScale(int)) );

	

	QGroupBox *JointGroup = new QGroupBox(tc->toUnicode("ジョイント"));
	QGroupBox *SensorGroup = new QGroupBox(tc->toUnicode("センサ"));

	QVBoxLayout* Jointlayout = new QVBoxLayout();
	Jointlayout->addWidget(JointSlider);
	JointGroup->setLayout(Jointlayout);
	QVBoxLayout* Sensorlayout = new QVBoxLayout();
	Sensorlayout->addWidget(SensorSlider);
	SensorGroup->setLayout(Sensorlayout);
	

	flayout->addWidget( JointGroup, 0 );
	flayout->addWidget( SensorGroup, 1 );
	flayout->addWidget( toolBox, 2 );
	


	

	

	SliderWidget->setLayout(flayout);

}


void MainWindow::setBox()
{
	
		scene->textItem[scene->GeoNum]->setParam(boxpage->returnParam());

		Judge();
	
}

void MainWindow::setSphere()
{
	
		scene->textItem[scene->GeoNum]->setParam(spherepage->returnParam());

		Judge();

	
}

void MainWindow::setCylinder()
{
	
		scene->textItem[scene->GeoNum]->setParam(cylinderpage->returnParam());

		Judge();
	
}

void MainWindow::setCone()
{
	
		scene->textItem[scene->GeoNum]->setParam(conepage->returnParam());

		Judge();
	
}

void MainWindow::setPolygon()
{
	
		
	
		scene->textItem[scene->GeoNum]->setParam(polygonpage->returnParam());

		Judge();
	
}

void MainWindow::setFix()
{
	
		
		scene->actItem[scene->RotNum]->setParam(fixpage->returnParam());
		Judge();
	
}

void MainWindow::setSlider()
{
	
	scene->actItem[scene->RotNum]->setParam(sliderpage->returnParam());
	Judge();
}

void MainWindow::setHinge()
{
	
	scene->actItem[scene->RotNum]->setParam(hingepage->returnParam());
	Judge();
}

void MainWindow::setSensor()
{
	scene->senItem[scene->SSNum]->setParam(sensorpage->returnParam());
	Judge();
}

void MainWindow::createToolBox()
{
        	buttonGroup = new QButtonGroup;
	buttonGroup->setExclusive(false);
	connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));
	QGridLayout *layout = new QGridLayout;

	QToolButton *textButton = new QToolButton;
	textButton->setCheckable(true);
	buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/link.png")
                        .scaled(30, 30)));

    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tc->toUnicode("リンク")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 1, 1);

	QToolButton *actButton = new QToolButton;
	actButton->setCheckable(true);
	buttonGroup->addButton(actButton, InsertactButton);
    actButton->setIcon(QIcon(QPixmap(":/images/joint.png")
                        .scaled(30, 30)));

    actButton->setIconSize(QSize(50, 50));
    QGridLayout *actLayout = new QGridLayout;
    actLayout->addWidget(actButton, 0, 0, Qt::AlignHCenter);
    actLayout->addWidget(new QLabel(tc->toUnicode("ジョイント")), 1, 0, Qt::AlignCenter);
    QWidget *actWidget = new QWidget;
    actWidget->setLayout(actLayout);
    layout->addWidget(actWidget, 2, 1);

	QToolButton *sensorButton = new QToolButton;
	sensorButton->setCheckable(true);
	buttonGroup->addButton(sensorButton, InsertsenButton);
    sensorButton->setIcon(QIcon(QPixmap(":/images/sensor.png")
                        .scaled(30, 30)));

    sensorButton->setIconSize(QSize(50, 50));
    QGridLayout *sensorLayout = new QGridLayout;
    sensorLayout->addWidget(sensorButton, 0, 0, Qt::AlignHCenter);
    sensorLayout->addWidget(new QLabel(tc->toUnicode("センサー")), 1, 0, Qt::AlignCenter);
    QWidget *sensorWidget = new QWidget;
    sensorWidget->setLayout(sensorLayout);
    layout->addWidget(sensorWidget, 2, 2);

	QToolButton *cameraButton = new QToolButton;
	cameraButton->setCheckable(true);
	buttonGroup->addButton(cameraButton, InsertcamButton);
    cameraButton->setIcon(QIcon(QPixmap(":/images/vision.png")
                        .scaled(30, 30)));

    cameraButton->setIconSize(QSize(50, 50));
    QGridLayout *cameraLayout = new QGridLayout;
    cameraLayout->addWidget(cameraButton, 0, 0, Qt::AlignHCenter);
    cameraLayout->addWidget(new QLabel(tc->toUnicode("カメラ")), 1, 0, Qt::AlignCenter);
    QWidget *cameraWidget = new QWidget;
    cameraWidget->setLayout(cameraLayout);
    layout->addWidget(cameraWidget, 1, 2);



    layout->setRowStretch(3, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemWidget = new QWidget;
    itemWidget->setLayout(layout);

    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemWidget->sizeHint().width());
    toolBox->addItem(itemWidget, tc->toUnicode(""));

}




void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
    if (buttonGroup->button(id) != button)
        button->setChecked(false);
    }
    if (id == InsertTextButton) {
        scene->setMode(InsertText);
    }
	else if(id == InsertactButton)
	{
		scene->setMode(MoveLink);
	}
	else if(id == InsertsenButton)
	{
		scene->setMode(CreateSensor);
	}

	else if(id == InsertcamButton)
	{
		scene->setMode(CreateCamera);
	}
	else {
        scene->setMode(InsertItem);
    }
}


void MainWindow::Judge()
{
	c->clearBody();
	for(int i=0;i<scene->ReturnItemCount();i++)
	{
		c->setBody(scene->ReturnParam(i),i);
	}
	c->clearJoint();
	for(int i=0;i<scene->ReturnactCount();i++)
	{
		c->setJoint(scene->ReturnactParam(i), i);
		
	}
	
	c->clearSensor();
	for(int i=0;i<scene->ReturnsenCount();i++)
	{
		c->setSensor(scene->ReturnsenParam(i), i);
	}

	c->clearCamera();
	for(int i=0;i<scene->ReturncamCount();i++)
	{
		c->setCamera(scene->ReturncamParam(i),i);



	}

	c->updateGL();

}



void MainWindow::textInserted(BodyItem *item)
{
	buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(MoveItem);
	c->CHECK = false;
	Judge();
	

}

void MainWindow::senInserted(SensorItem *item)
{
	buttonGroup->button(InsertsenButton)->setChecked(false);
    scene->setMode(MoveItem);
	c->CHECK = false;
	Judge();

}

void MainWindow::camInserted(CameraItem *item)
{
	buttonGroup->button(InsertcamButton)->setChecked(false);
    scene->setMode(MoveItem);
	c->CHECK = false;
	Judge();

}

void MainWindow::renew()
{
	Judge();
	c->CHECK = false;

}


void MainWindow::actInserted(JointItem *item)
{
	buttonGroup->button(InsertactButton)->setChecked(false);
    scene->setMode(MoveItem);
	Judge();
	c->CHECK = false;

		
	//c->LoadNode();
}



void MainWindow::pointerGroupClicked(int)
{
	scene->setMode(Control_Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::BorTGroupClicked(int)
{
	c->BorT = BorTGroup->checkedId();
}


void MainWindow::createToolbars()
{
    editToolBar = addToolBar(tc->toUnicode("Edit"));
    editToolBar->addAction(deleteAction);
    editToolBar->addAction(toFrontAction);
    editToolBar->addAction(sendBackAction);
	editToolBar->addAction(checkAction);
    editToolBar->addAction(BHAct);
	editToolBar->addAction(JHAct);


	QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));



    pointerTypeGroup = new QButtonGroup;
    pointerTypeGroup->addButton(pointerButton, int(MoveItem));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));




    pointerToolbar = addToolBar(tc->toUnicode("Pointer type"));
    pointerToolbar->addWidget(pointerButton);



	QToolButton *BanButton = new QToolButton;
    BanButton->setCheckable(true);

	QToolButton *TransButton = new QToolButton;
    TransButton->setCheckable(true);
    TransButton->setChecked(true);
    BanButton->setIcon(QIcon(":/images/ban.png"));
	TransButton->setIcon(QIcon(":/images/scale.png"));



    BorTGroup = new QButtonGroup;
    BorTGroup->addButton(BanButton, 1);
    connect(BorTGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(BorTGroupClicked(int)));
	BorTGroup->addButton(TransButton, 0);
    connect(BorTGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(BorTGroupClicked(int)));




    BorTToolbar = addToolBar(tc->toUnicode("Pointer type"));
    BorTToolbar->addWidget(BanButton);
	BorTToolbar->addWidget(TransButton);

}


void MainWindow::createActions()
{

    toFrontAction = new QAction(QIcon(":/images/bringtofront.png"),
                                tc->toUnicode("Bring to &Front"), this);
    toFrontAction->setShortcut(tc->toUnicode("Ctrl+F"));
    toFrontAction->setStatusTip(tc->toUnicode("Bring item to front"));
    connect(toFrontAction, SIGNAL(triggered()),
            this, SLOT(bringToFront()));


    sendBackAction = new QAction(QIcon(":/images/sendtoback.png"),
                                 tc->toUnicode("Send to &Back"), this);
    sendBackAction->setShortcut(tc->toUnicode("Ctrl+B"));
    sendBackAction->setStatusTip(tc->toUnicode("Send item to back"));
    connect(sendBackAction, SIGNAL(triggered()),
        this, SLOT(sendToBack()));

	checkAction = new QAction(QIcon(":/images/check.png"),
								tc->toUnicode("Check"), this);

	checkAction->setShortcut(tc->toUnicode("Ctrl+M"));
	checkAction->setStatusTip(tc->toUnicode("Check Model"));
    connect(checkAction, SIGNAL(triggered()),
        this, SLOT(check()));

	BHAct = new QAction(QIcon(":/images/BH.png"),
								tc->toUnicode("clear"), this);

	BHAct->setShortcut(tc->toUnicode("Ctrl+K"));
	BHAct->setStatusTip(tc->toUnicode("Clear Body"));
    connect(BHAct, SIGNAL(triggered()),
        this, SLOT(setBH()));

	JHAct = new QAction(QIcon(":/images/JH.png"),
								tc->toUnicode("not clear"), this);

	JHAct->setShortcut(tc->toUnicode("Ctrl+L"));
	JHAct->setStatusTip(tc->toUnicode("Not Clear Body"));

    connect(JHAct, SIGNAL(triggered()),
        this, SLOT(setJH()));

    deleteAction = new QAction(QIcon(":/images/delete.png"),
                               tc->toUnicode("&Delete"), this);
    deleteAction->setShortcut(tc->toUnicode("Delete"));
    deleteAction->setStatusTip(tc->toUnicode("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()),
        this, SLOT(deleteItem()));
	
	exitAction = new QAction(tc->toUnicode("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tc->toUnicode("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	aboutAction = new QAction(tc->toUnicode("A&bout"), this);
    aboutAction->setShortcut(tc->toUnicode("Ctrl+B"));
    connect(aboutAction, SIGNAL(triggered()),
            this, SLOT(about()));

	saveAct = new QAction(tc->toUnicode("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tc->toUnicode("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

	saveVRMLAct = new QAction(tc->toUnicode("&SaveVRML"), this);
	saveVRMLAct->setStatusTip(tc->toUnicode("Save the vrml to disk"));
	connect(saveVRMLAct, SIGNAL(triggered()), this, SLOT(saveVRML()));

	openAct = new QAction(tc->toUnicode("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tc->toUnicode("Open the document to disk"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAsAct = new QAction(tc->toUnicode("Save &As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tc->toUnicode("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));



}

void MainWindow::about()
{
    QMessageBox::about(this, tc->toUnicode("About Diagram Scene"),
                       tc->toUnicode("The <b>Diagram Scene</b> example shows "
                          "use of the graphics framework."));
}

void MainWindow::deleteItem()
{
   scene->deleteItem();
   	/*c->setNum(scene->ReturnItemCount());
	for(int i=0;i<scene->ReturnItemCount();i++)
	{
		c->setBody(i,scene->ReturnGeom(i),scene->ReturnParam(i),scene->returnFlag(i),scene->returnTip(i));
	}*/
    Judge();
	c->update();
	c->CHECK = false;
}

void MainWindow::bringToFront()
{

    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() >= zValue &&
            item->type() == JointItem::Type)
            zValue = item->zValue() + 0.1;
    }
    selectedItem->setZValue(zValue);
}


void MainWindow::sendToBack()
{
    if (scene->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue &&
            item->type() == JointItem::Type)
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}


void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tc->toUnicode("&File"));
	fileMenu->addAction(openAct);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(saveVRMLAct);
	
	fileMenu->addAction(saveAsAct);
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tc->toUnicode("&Item"));
    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();
    itemMenu->addAction(toFrontAction);
    itemMenu->addAction(sendBackAction);
	itemMenu->addAction(checkAction);
	itemMenu->addAction(BHAct);
	itemMenu->addAction(JHAct);

    aboutMenu = menuBar()->addMenu(tc->toUnicode("&Help"));
    aboutMenu->addAction(aboutAction);
}



void MainWindow::save()
{

        saveAs();

}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tc->toUnicode("Choose a VRML file"),
                                                "", "Model Files(*.rmc)");
    if (fileName.isEmpty())
        return;


    loadFile(fileName);
}

void MainWindow::saveVRML()
{
	QString fileName = QFileDialog::getSaveFileName(this, tc->toUnicode("VRML file"),
		"", "VRML Files(*.wrl)");
	if (fileName.isEmpty())
		return;


	int k = scene->SaveFileVRML(fileName);
	if (k != 0) {
		QMessageBox::warning(this, tc->toUnicode("Recent Files"),
			tc->toUnicode("Cannot write file %1:\n.")
			.arg(fileName));
		return;
	}
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tc->toUnicode("VRML file"),
                                                "", "MODEL Files(*.rmc)");
    if (fileName.isEmpty())
        return;


    saveFile(fileName);
}

void MainWindow::check()
{

	
	int ch = scene->CHECK();
	if(ch == 1){
		QMessageBox::about(this, "Error", 
                        tc->toUnicode("ボディの番号が順番通りではないです"));
	}
	if(ch == 2){
		QMessageBox::about(this, "Error", 
                        tc->toUnicode("ジョイントの番号が順番通りではないです"));
	}
	if(ch == 0){
		QMessageBox::about(this, "Sucsses", 
                tc->toUnicode("動作できます"));
		c->CHECK = true;
		Judge();
	}

}




bool MainWindow::ReturnCheck()
{
	return CHECK;
}




void MainWindow::saveFile(const QString &fileName)
{
    int k = scene->SaveFile(fileName);
    if (k != 0) {
        QMessageBox::warning(this, tc->toUnicode("Recent Files"),
                             tc->toUnicode("Cannot write file %1:\n.")
                             .arg(fileName));
        return;
    }

    
}


void MainWindow::loadFile(const QString &fileName)
{
	int JL = scene->LoadFile(fileName);

	if(JL == 1){
	 QMessageBox::warning(this, tc->toUnicode("Recent Files"),
                             tc->toUnicode("Cannot write file %1:\n.")
                             .arg(fileName));
	}
    
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowFilePath(curFile);

    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);

    foreach (QWidget *widget, QApplication::topLevelWidgets()) {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin)
            mainWin->updateRecentFileActions();
    }
}

void MainWindow::updateRecentFileActions()
{
    QSettings settings;
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i) {
        QString text = tc->toUnicode("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        recentFileActs[i]->setText(text);
        recentFileActs[i]->setData(files[i]);
        recentFileActs[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        recentFileActs[j]->setVisible(false);

    separatorAct->setVisible(numRecentFiles > 0);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::setRotNum()
{
	//std::cout << scene->RotNum << std::endl;
	if(c->CHECK)
	{
		if(scene->RotNum != 100){

			c->RotNum = scene->returnActNum(scene->RotNum);

		}
		else
			c->RotNum = scene->RotNum;
		
	}
	else
		c->RotNum = scene->RotNum;
	RotSlider->setValue(180);

	//createParamWidget();

	//std::cout << scene->RotNum << std::endl;
	
	if(scene->RotNum != 100)
	{
		for(int i=0;i<tabWidget->count()-2;i++)tabWidget->removeTab(2+i);
		JointParam jp = scene->ReturnactParam(scene->RotNum)->m_param;
		
		if(jp.m_type == Hinge)
		{
			
			hingepage->setParam(jp);
			ParamWidget = hingepage;

			tabWidget->addTab(ParamWidget, tc->toUnicode("パラメータ"));

			tabWidget->setCurrentIndex(2);

		}

		if (jp.m_type == Slider)
		{
			sliderpage->setParam(jp);
			ParamWidget = sliderpage;

			tabWidget->addTab(ParamWidget, tc->toUnicode("パラメータ"));

			tabWidget->setCurrentIndex(2);

		}

		if (jp.m_type == Fix)
		{
			fixpage->setParam(jp);
			ParamWidget = fixpage;

			tabWidget->addTab(ParamWidget, tc->toUnicode("パラメータ"));

			tabWidget->setCurrentIndex(2);
		}

		
	}
	c->updateGL();

}

void MainWindow::delTab()
{
	for(int i=0;i<tabWidget->count()-2;i++)tabWidget->removeTab(2+i);
	
}


void MainWindow::setGeoNum()
{


	if(c->CHECK)
	{
		if(scene->GeoNum != 100)
		{
			c->GeoNum = scene->returnBodyNum(scene->GeoNum);
		}
		else
		{
			c->GeoNum = scene->GeoNum;
		}
	}
	else
		c->GeoNum = scene->GeoNum;
	

	

	if(scene->GeoNum != 100)
	{
		for(int i=0;i<tabWidget->count()-2;i++)tabWidget->removeTab(2+i);
		
	
		scene->ReturnParam(scene->GeoNum);

		BodyParam bp = scene->ReturnParam(scene->GeoNum)->m_param;
		if(bp.m_type == Body_Box)
		{
			boxpage->setParam(bp);
			ParamWidget = boxpage;
			

			tabWidget->addTab(ParamWidget, tc->toUnicode("パラメータ"));

			tabWidget->setCurrentIndex(2);

		}

		if(bp.m_type == Body_Sphere)
		{


			spherepage->setParam(bp);
			ParamWidget = spherepage;
			

			tabWidget->addTab(ParamWidget, tc->toUnicode("パラメータ"));

			tabWidget->setCurrentIndex(2);

		}

		if (bp.m_type == Body_Cylinder)
		{
			cylinderpage->setParam(bp);
			ParamWidget = cylinderpage;
			

			tabWidget->addTab(ParamWidget, tc->toUnicode("パラメータ"));

			tabWidget->setCurrentIndex(2);

		}

		if (bp.m_type == Body_Cone)
		{
			conepage->setParam(bp);
			ParamWidget = conepage;
			

			tabWidget->addTab(ParamWidget, tc->toUnicode("パラメータ"));

			tabWidget->setCurrentIndex(2);

		}

		if (bp.m_type == Body_Cone)
		{
			polygonpage->setParam(bp);
			ParamWidget = polygonpage;
			

			tabWidget->addTab(ParamWidget, tc->toUnicode("パラメータ"));

			tabWidget->setCurrentIndex(2);
		}


		
	}

	c->updateGL();

	

}


void MainWindow::setSSNum()
{

	c->SSNum = scene->SSNum;
	

	if(scene->SSNum != 100)
	{
		for(int i=0;i<tabWidget->count()-2;i++)tabWidget->removeTab(2+i);

		
			
			sensorpage->setParam(scene->ReturnsenParam(scene->SSNum)->m_param);
			ParamWidget = sensorpage;

			tabWidget->addTab(ParamWidget, tc->toUnicode("パラメータ"));

			tabWidget->setCurrentIndex(2);

		

		
	}

	c->updateGL();

	//createParamWidget();

}
void MainWindow::updateParam()
{

}
void MainWindow::setBH()
{
	c->BCL = 1.0;
	c->updateGL();
}

void MainWindow::setJH()
{
	c->BCL = 0.4;
	c->updateGL();
}






