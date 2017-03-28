#include <QtWidgets>
#include <QtGui>
#include "Jointpages.h"

HingePage::HingePage(int def_num, QWidget *parent)
    : QWidget(parent)
{
        tc = QTextCodec::codecForLocale();

        NameGroup = new QGroupBox(tc->toUnicode("���O"));

	geomNameComboBox = new QComboBox;

	geomNameComboBox->setEditable(true);
    geomNameComboBox->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Preferred);
	geomNameComboBox->lineEdit()->setText("test");
        geomNameLabel = new QLabel(tc->toUnicode("���O:"));

	QHBoxLayout *NameLayout = new QHBoxLayout;
    NameLayout->addWidget(geomNameLabel);
    NameLayout->addWidget(geomNameComboBox);

	NameGroup->setLayout(NameLayout);

        NumGroup = new QGroupBox(tc->toUnicode("�ԍ�"));
	
	NumComboBox = new QSpinBox;

	NumComboBox->setValue(def_num);
        NumLabel = new QLabel(tc->toUnicode("�ԍ�:"));

	QHBoxLayout *NumLayout = new QHBoxLayout;
    NumLayout->addWidget(NumLabel);
    NumLayout->addWidget(NumComboBox);

	NumGroup->setLayout(NumLayout);


    posGroup = new QGroupBox(tc->toUnicode("�ʒu:"));

	posxLabel = new QLabel(tc->toUnicode("X[m]:"));
    posxCombo = new QDoubleSpinBox;
    posxCombo->setValue(0.0);
	posxCombo->setMaximum(100.0);
	posxCombo->setMinimum(-100.0);


	posyLabel = new QLabel(tc->toUnicode("Y[m]:"));
    posyCombo = new QDoubleSpinBox;
    posyCombo->setValue(0.0);
	posyCombo->setMaximum(100.0);
	posyCombo->setMinimum(-100.0);


	poszLabel = new QLabel(tc->toUnicode("Z[m]:"));
    poszCombo = new QDoubleSpinBox;
    poszCombo->setValue(0.0);
	poszCombo->setMaximum(100.0);
	poszCombo->setMinimum(-100.0);


	QHBoxLayout *posxLayout = new QHBoxLayout;
    posxLayout->addWidget(posxLabel);
    posxLayout->addWidget(posxCombo);

	QHBoxLayout *posyLayout = new QHBoxLayout;
    posyLayout->addWidget(posyLabel);
    posyLayout->addWidget(posyCombo);

	QHBoxLayout *poszLayout = new QHBoxLayout;
    poszLayout->addWidget(poszLabel);
    poszLayout->addWidget(poszCombo);

	QHBoxLayout *posLayout = new QHBoxLayout;
	posLayout->addLayout(posxLayout);
	posLayout->addLayout(posyLayout);
	posLayout->addLayout(poszLayout);

	posGroup->setLayout(posLayout);



        axisGroup = new QGroupBox(tc->toUnicode("��:"));

	axisxLabel = new QLabel(tc->toUnicode("X:"));
    axisxCombo = new QDoubleSpinBox;
    axisxCombo->setValue(1.0);


	axisyLabel = new QLabel(tc->toUnicode("Y:"));
    axisyCombo = new QDoubleSpinBox;
    axisyCombo->setValue(0.0);


	axiszLabel = new QLabel(tc->toUnicode("Z:"));
    axiszCombo = new QDoubleSpinBox;
    axiszCombo->setValue(0.0);


	QHBoxLayout *axisxLayout = new QHBoxLayout;
    axisxLayout->addWidget(axisxLabel);
    axisxLayout->addWidget(axisxCombo);

	QHBoxLayout *axisyLayout = new QHBoxLayout;
    axisyLayout->addWidget(axisyLabel);
    axisyLayout->addWidget(axisyCombo);

	QHBoxLayout *axiszLayout = new QHBoxLayout;
    axiszLayout->addWidget(axiszLabel);
    axiszLayout->addWidget(axiszCombo);

	QHBoxLayout *axisLayout = new QHBoxLayout;
	axisLayout->addLayout(axisxLayout);
	axisLayout->addLayout(axisyLayout);
	axisLayout->addLayout(axiszLayout);

	axisGroup->setLayout(axisLayout);

	
	
        anotherGroup = new QGroupBox(tc->toUnicode("���̑�:"));

        ulimitHLabel = new QLabel(tc->toUnicode("�p�x�ő�l[rad]:"));
    ulimitHCombo = new QDoubleSpinBox;
    ulimitHCombo->setValue(1000.0);


        ulimitLLabel = new QLabel(tc->toUnicode("�p�x�ŏ��l[rad]:"));
    ulimitLCombo = new QDoubleSpinBox;
    ulimitLCombo->setValue(-1000.0);



	QHBoxLayout *ulimitHLayout = new QHBoxLayout;
    ulimitHLayout->addWidget(ulimitHLabel);
    ulimitHLayout->addWidget(ulimitHCombo);

	QHBoxLayout *ulimitLLayout = new QHBoxLayout;
    ulimitLLayout->addWidget(ulimitLLabel);
    ulimitLLayout->addWidget(ulimitLCombo);


	QHBoxLayout *ulimitLayout = new QHBoxLayout;
	ulimitLayout->addLayout(ulimitHLayout);
	ulimitLayout->addLayout(ulimitLLayout);

        uvlimitHLabel = new QLabel(tc->toUnicode("�p���x�ŏ��l[rad/s]:"));
    uvlimitHCombo = new QDoubleSpinBox;
    uvlimitHCombo->setValue(1000.0);


        uvlimitLLabel = new QLabel(tc->toUnicode("�p���x�ő�l[rad/s]:"));
    uvlimitLCombo = new QDoubleSpinBox;
    uvlimitLCombo->setValue(-1000.0);

	
	QHBoxLayout *uvlimitHLayout = new QHBoxLayout;
    uvlimitHLayout->addWidget(uvlimitHLabel);
    uvlimitHLayout->addWidget(uvlimitHCombo);

	QHBoxLayout *uvlimitLLayout = new QHBoxLayout;
    uvlimitLLayout->addWidget(uvlimitLLabel);
    uvlimitLLayout->addWidget(uvlimitLCombo);



	QHBoxLayout *uvlimitLayout = new QHBoxLayout;
	uvlimitLayout->addLayout(uvlimitHLayout);
	uvlimitLayout->addLayout(uvlimitLLayout);


	
	
	
        rotorInertiaLabel = new QLabel(tc->toUnicode("�������[�����g[kgm^2]:"));
    rotorInertiaCombo = new QDoubleSpinBox;
    rotorInertiaCombo->setValue(0.0);


        rotorResistorLabel = new QLabel(tc->toUnicode("������R[Ohm]:"));
    rotorResistorCombo = new QDoubleSpinBox;
    rotorResistorCombo->setValue(0.0);



	QHBoxLayout *rotorInertiaLayout = new QHBoxLayout;
    rotorInertiaLayout->addWidget(rotorInertiaLabel);
    rotorInertiaLayout->addWidget(rotorInertiaCombo);

	QHBoxLayout *rotorResistorLayout = new QHBoxLayout;
    rotorResistorLayout->addWidget(rotorResistorLabel);
    rotorResistorLayout->addWidget(rotorResistorCombo);





        torqueConstLabel = new QLabel(tc->toUnicode("�g���N�萔[Nm/A]:"));
    torqueConstCombo = new QDoubleSpinBox;
    torqueConstCombo->setValue(0.0);


        encoderPulseLabel = new QLabel(tc->toUnicode("encoderPulse[pulse/rotate]:"));
    encoderPulseCombo = new QDoubleSpinBox;
    encoderPulseCombo->setValue(0.0);



	QHBoxLayout *torqueConstLayout = new QHBoxLayout;
    torqueConstLayout->addWidget(torqueConstLabel);
    torqueConstLayout->addWidget(torqueConstCombo);

	QHBoxLayout *encoderPulseLayout = new QHBoxLayout;
    encoderPulseLayout->addWidget(encoderPulseLabel);
    encoderPulseLayout->addWidget(encoderPulseCombo);


	QVBoxLayout *another2Layout = new QVBoxLayout;
	another2Layout->addLayout(rotorInertiaLayout);
	another2Layout->addLayout(rotorResistorLayout);
	another2Layout->addLayout(torqueConstLayout);
	another2Layout->addLayout(encoderPulseLayout);

	QVBoxLayout *anotherLayout = new QVBoxLayout;
	anotherLayout->addLayout(ulimitLayout);
	anotherLayout->addLayout(uvlimitLayout);
	anotherLayout->addLayout(another2Layout);







	anotherGroup->setLayout(anotherLayout);


	





    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(NumGroup);
	mainLayout->addWidget(NameGroup);
    mainLayout->addWidget(posGroup);
	mainLayout->addWidget(axisGroup);
	mainLayout->addWidget(anotherGroup);
	mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void HingePage::setParam(JointParam jp)
{
	posxCombo->setValue(jp.m_px);
	posyCombo->setValue(jp.m_py);
	poszCombo->setValue(jp.m_pz);
	axisxCombo->setValue(jp.m_axisx);
	axisyCombo->setValue(jp.m_axisy);
	axiszCombo->setValue(jp.m_axisz);
	ulimitHCombo->setValue(jp.ulimitH);
	ulimitLCombo->setValue(jp.ulimitL);
	uvlimitHCombo->setValue(jp.uvlimitH);
	uvlimitLCombo->setValue(jp.uvlimitL);
	rotorInertiaCombo->setValue(jp.rotorInertia);
	rotorResistorCombo->setValue(jp.rotorResistor);
	torqueConstCombo->setValue(jp.torqueConst);
	encoderPulseCombo->setValue(jp.encoder);
	NumComboBox->setValue(jp.NUM);

	const QString TEMP = jp.NAME;
	geomNameComboBox->addItem(TEMP);
}

JointParam HingePage::returnParam()
{
	JointParam jp;

	jp.m_px = posxCombo->value();
	jp.m_py = posyCombo->value();
	jp.m_pz = poszCombo->value();
	jp.m_axisx = axisxCombo->value();
	jp.m_axisy = axisyCombo->value();
	jp.m_axisz = axiszCombo->value();
	jp.ulimitH = ulimitHCombo->value();
	jp.ulimitL = ulimitLCombo->value();
	jp.uvlimitH = uvlimitHCombo->value();
	jp.uvlimitL = uvlimitLCombo->value();
	jp.rotorInertia = rotorInertiaCombo->value();
	jp.rotorResistor = rotorResistorCombo->value();
	jp.torqueConst = torqueConstCombo->value();
	jp.encoder = encoderPulseCombo->value();

	jp.NAME = geomNameComboBox->currentText();
	jp.NUM = NumComboBox->value();

	jp.m_type = Hinge;

	return jp;
}



SliderPage::SliderPage(int def_num, QWidget *parent)
    : QWidget(parent)
{
        tc = QTextCodec::codecForLocale();

        NameGroup = new QGroupBox(tc->toUnicode("���O"));

	geomNameComboBox = new QComboBox;

	geomNameComboBox->setEditable(true);
    geomNameComboBox->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Preferred);
	geomNameComboBox->lineEdit()->setText("test");
        geomNameLabel = new QLabel(tc->toUnicode("���O:"));

	QHBoxLayout *NameLayout = new QHBoxLayout;
    NameLayout->addWidget(geomNameLabel);
    NameLayout->addWidget(geomNameComboBox);

	NameGroup->setLayout(NameLayout);

        NumGroup = new QGroupBox(tc->toUnicode("�ԍ�"));
	
	NumComboBox = new QSpinBox;

	NumComboBox->setValue(def_num);
        NumLabel = new QLabel(tc->toUnicode("�ԍ�:"));

	QHBoxLayout *NumLayout = new QHBoxLayout;
    NumLayout->addWidget(NumLabel);
    NumLayout->addWidget(NumComboBox);

	NumGroup->setLayout(NumLayout);


    posGroup = new QGroupBox(tc->toUnicode("�ʒu"));

	posxLabel = new QLabel(tc->toUnicode("X[m]:"));
    posxCombo = new QDoubleSpinBox;
    posxCombo->setValue(0.0);
	posxCombo->setMaximum(100.0);
	posxCombo->setMinimum(-100.0);


	posyLabel = new QLabel(tc->toUnicode("Y[m]:"));
    posyCombo = new QDoubleSpinBox;
    posyCombo->setValue(0.0);
	posyCombo->setMaximum(100.0);
	posyCombo->setMinimum(-100.0);


	poszLabel = new QLabel(tc->toUnicode("Z[m]:"));
    poszCombo = new QDoubleSpinBox;
    poszCombo->setValue(0.0);
	poszCombo->setMaximum(100.0);
	poszCombo->setMinimum(-100.0);


	QHBoxLayout *posxLayout = new QHBoxLayout;
    posxLayout->addWidget(posxLabel);
    posxLayout->addWidget(posxCombo);

	QHBoxLayout *posyLayout = new QHBoxLayout;
    posyLayout->addWidget(posyLabel);
    posyLayout->addWidget(posyCombo);

	QHBoxLayout *poszLayout = new QHBoxLayout;
    poszLayout->addWidget(poszLabel);
    poszLayout->addWidget(poszCombo);

	QHBoxLayout *posLayout = new QHBoxLayout;
	posLayout->addLayout(posxLayout);
	posLayout->addLayout(posyLayout);
	posLayout->addLayout(poszLayout);

	posGroup->setLayout(posLayout);



        axisGroup = new QGroupBox(tc->toUnicode("��"));

	axisxLabel = new QLabel(tc->toUnicode("X:"));
    axisxCombo = new QDoubleSpinBox;
    axisxCombo->setValue(1.0);


	axisyLabel = new QLabel(tc->toUnicode("Y:"));
    axisyCombo = new QDoubleSpinBox;
    axisyCombo->setValue(0.0);


	axiszLabel = new QLabel(tc->toUnicode("Z:"));
    axiszCombo = new QDoubleSpinBox;
    axiszCombo->setValue(0.0);


	QHBoxLayout *axisxLayout = new QHBoxLayout;
    axisxLayout->addWidget(axisxLabel);
    axisxLayout->addWidget(axisxCombo);

	QHBoxLayout *axisyLayout = new QHBoxLayout;
    axisyLayout->addWidget(axisyLabel);
    axisyLayout->addWidget(axisyCombo);

	QHBoxLayout *axiszLayout = new QHBoxLayout;
    axiszLayout->addWidget(axiszLabel);
    axiszLayout->addWidget(axiszCombo);

	QHBoxLayout *axisLayout = new QHBoxLayout;
	axisLayout->addLayout(axisxLayout);
	axisLayout->addLayout(axisyLayout);
	axisLayout->addLayout(axiszLayout);

	axisGroup->setLayout(axisLayout);

	
	
        anotherGroup = new QGroupBox(tc->toUnicode("���̑�"));

        ulimitHLabel = new QLabel(tc->toUnicode("�ړ��ʍő�l[m]:"));
    ulimitHCombo = new QDoubleSpinBox;
    ulimitHCombo->setValue(0.0);


        ulimitLLabel = new QLabel(tc->toUnicode("�ړ��ʍŏ��l[m]:"));
    ulimitLCombo = new QDoubleSpinBox;
    ulimitLCombo->setValue(0.0);



	QHBoxLayout *ulimitHLayout = new QHBoxLayout;
    ulimitHLayout->addWidget(ulimitHLabel);
    ulimitHLayout->addWidget(ulimitHCombo);

	QHBoxLayout *ulimitLLayout = new QHBoxLayout;
    ulimitLLayout->addWidget(ulimitLLabel);
    ulimitLLayout->addWidget(ulimitLCombo);


	QHBoxLayout *ulimitLayout = new QHBoxLayout;
	ulimitLayout->addLayout(ulimitHLayout);
	ulimitLayout->addLayout(ulimitLLayout);

        uvlimitHLabel = new QLabel(tc->toUnicode("���x�ő�l[m/s]:"));
    uvlimitHCombo = new QDoubleSpinBox;
    uvlimitHCombo->setValue(0.0);


        uvlimitLLabel = new QLabel(tc->toUnicode("���x�ŏ��l[m/s]:"));
    uvlimitLCombo = new QDoubleSpinBox;
    uvlimitLCombo->setValue(0.0);

	
	QHBoxLayout *uvlimitHLayout = new QHBoxLayout;
    uvlimitHLayout->addWidget(uvlimitHLabel);
    uvlimitHLayout->addWidget(uvlimitHCombo);

	QHBoxLayout *uvlimitLLayout = new QHBoxLayout;
    uvlimitLLayout->addWidget(uvlimitLLabel);
    uvlimitLLayout->addWidget(uvlimitLCombo);



	QHBoxLayout *uvlimitLayout = new QHBoxLayout;
	uvlimitLayout->addLayout(uvlimitHLayout);
	uvlimitLayout->addLayout(uvlimitLLayout);


	
	
	
        rotorInertiaLabel = new QLabel(tc->toUnicode("�������[�����g[kgm^2]:"));
    rotorInertiaCombo = new QDoubleSpinBox;
    rotorInertiaCombo->setValue(0.0);


        rotorResistorLabel = new QLabel(tc->toUnicode("������R[Ohm]:"));
    rotorResistorCombo = new QDoubleSpinBox;
    rotorResistorCombo->setValue(0.0);



	QHBoxLayout *rotorInertiaLayout = new QHBoxLayout;
    rotorInertiaLayout->addWidget(rotorInertiaLabel);
    rotorInertiaLayout->addWidget(rotorInertiaCombo);

	QHBoxLayout *rotorResistorLayout = new QHBoxLayout;
    rotorResistorLayout->addWidget(rotorResistorLabel);
    rotorResistorLayout->addWidget(rotorResistorCombo);





        torqueConstLabel = new QLabel(tc->toUnicode("�g���N�萔[Nm/A]:"));
    torqueConstCombo = new QDoubleSpinBox;
    torqueConstCombo->setValue(0.0);


        encoderPulseLabel = new QLabel(tc->toUnicode("encoderPulse[pulse/rotate]:"));
    encoderPulseCombo = new QDoubleSpinBox;
    encoderPulseCombo->setValue(0.0);



	QHBoxLayout *torqueConstLayout = new QHBoxLayout;
    torqueConstLayout->addWidget(torqueConstLabel);
    torqueConstLayout->addWidget(torqueConstCombo);

	QHBoxLayout *encoderPulseLayout = new QHBoxLayout;
    encoderPulseLayout->addWidget(encoderPulseLabel);
    encoderPulseLayout->addWidget(encoderPulseCombo);


	QVBoxLayout *another2Layout = new QVBoxLayout;
	another2Layout->addLayout(rotorInertiaLayout);
	another2Layout->addLayout(rotorResistorLayout);
	another2Layout->addLayout(torqueConstLayout);
	another2Layout->addLayout(encoderPulseLayout);

	QVBoxLayout *anotherLayout = new QVBoxLayout;
	anotherLayout->addLayout(ulimitLayout);
	anotherLayout->addLayout(uvlimitLayout);
	anotherLayout->addLayout(another2Layout);


	

	anotherGroup->setLayout(anotherLayout);



    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(NumGroup);
	mainLayout->addWidget(NameGroup);
    mainLayout->addWidget(posGroup);
	mainLayout->addWidget(axisGroup);
	mainLayout->addWidget(anotherGroup);
	mainLayout->addStretch(1);
    setLayout(mainLayout);
}


void SliderPage::setParam(JointParam jp)
{
	posxCombo->setValue(jp.m_px);
	posyCombo->setValue(jp.m_py);
	poszCombo->setValue(jp.m_pz);
	axisxCombo->setValue(jp.m_axisx);
	axisyCombo->setValue(jp.m_axisy);
	axiszCombo->setValue(jp.m_axisz);
	ulimitHCombo->setValue(jp.ulimitH);
	ulimitLCombo->setValue(jp.ulimitL);
	uvlimitHCombo->setValue(jp.uvlimitH);
	uvlimitLCombo->setValue(jp.uvlimitL);
	rotorInertiaCombo->setValue(jp.rotorInertia);
	rotorResistorCombo->setValue(jp.rotorResistor);
	torqueConstCombo->setValue(jp.torqueConst);
	encoderPulseCombo->setValue(jp.encoder);
	NumComboBox->setValue(jp.NUM);

	const QString TEMP = jp.NAME;
	geomNameComboBox->addItem(TEMP);
}



JointParam SliderPage::returnParam()
{
	
	JointParam jp;

	jp.m_px = posxCombo->value();
	jp.m_py = posyCombo->value();
	jp.m_pz = poszCombo->value();
	jp.m_axisx = axisxCombo->value();
	jp.m_axisy = axisyCombo->value();
	jp.m_axisz = axiszCombo->value();
	jp.ulimitH = ulimitHCombo->value();
	jp.ulimitL = ulimitLCombo->value();
	jp.uvlimitH = uvlimitHCombo->value();
	jp.uvlimitL = uvlimitLCombo->value();
	jp.rotorInertia = rotorInertiaCombo->value();
	jp.rotorResistor = rotorResistorCombo->value();
	jp.torqueConst = torqueConstCombo->value();
	jp.encoder = encoderPulseCombo->value();

	jp.NAME = geomNameComboBox->currentText();
	jp.NUM = NumComboBox->value();

	jp.m_type = Slider;

	return jp;
}



FixPage::FixPage(int def_num, QWidget *parent)
    : QWidget(parent)
{
        tc = QTextCodec::codecForLocale();

        NameGroup = new QGroupBox(tc->toUnicode("���O"));

	geomNameComboBox = new QComboBox;

	geomNameComboBox->setEditable(true);
    geomNameComboBox->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Preferred);
	geomNameComboBox->lineEdit()->setText("test");
        geomNameLabel = new QLabel(tc->toUnicode("���O:"));

	QHBoxLayout *NameLayout = new QHBoxLayout;
    NameLayout->addWidget(geomNameLabel);
    NameLayout->addWidget(geomNameComboBox);

	NameGroup->setLayout(NameLayout);

        NumGroup = new QGroupBox(tc->toUnicode("�ԍ�"));
	
	NumComboBox = new QSpinBox;

	NumComboBox->setValue(def_num);
        NumLabel = new QLabel(tc->toUnicode("�ԍ�:"));

	QHBoxLayout *NumLayout = new QHBoxLayout;
    NumLayout->addWidget(NumLabel);
    NumLayout->addWidget(NumComboBox);

	NumGroup->setLayout(NumLayout);


    posGroup = new QGroupBox(tc->toUnicode("�ʒu"));

	posxLabel = new QLabel(tc->toUnicode("X[m]:"));
    posxCombo = new QDoubleSpinBox;
    posxCombo->setValue(0.0);
	posxCombo->setMaximum(100.0);
	posxCombo->setMinimum(-100.0);


	posyLabel = new QLabel(tc->toUnicode("Y[m]:"));
    posyCombo = new QDoubleSpinBox;
    posyCombo->setValue(0.0);
	posyCombo->setMaximum(100.0);
	posyCombo->setMinimum(-100.0);


	poszLabel = new QLabel(tc->toUnicode("Z[m]:"));
    poszCombo = new QDoubleSpinBox;
    poszCombo->setValue(0.0);
	poszCombo->setMaximum(100.0);
	poszCombo->setMinimum(-100.0);


	QHBoxLayout *posxLayout = new QHBoxLayout;
    posxLayout->addWidget(posxLabel);
    posxLayout->addWidget(posxCombo);

	QHBoxLayout *posyLayout = new QHBoxLayout;
    posyLayout->addWidget(posyLabel);
    posyLayout->addWidget(posyCombo);

	QHBoxLayout *poszLayout = new QHBoxLayout;
    poszLayout->addWidget(poszLabel);
    poszLayout->addWidget(poszCombo);

	QHBoxLayout *posLayout = new QHBoxLayout;
	posLayout->addLayout(posxLayout);
	posLayout->addLayout(posyLayout);
	posLayout->addLayout(poszLayout);

	posGroup->setLayout(posLayout);




    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(NumGroup);
	mainLayout->addWidget(NameGroup);
    mainLayout->addWidget(posGroup);
	mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void FixPage::setParam(JointParam jp)
{
	posxCombo->setValue(jp.m_px);
	posyCombo->setValue(jp.m_py);
	poszCombo->setValue(jp.m_pz);
	NumComboBox->setValue(jp.NUM);

	const QString TEMP = jp.NAME;
	geomNameComboBox->addItem(TEMP);
}

JointParam FixPage::returnParam()
{
	JointParam jp;

	jp.m_px = posxCombo->value();
	jp.m_py = posyCombo->value();
	jp.m_pz = poszCombo->value();

	jp.NAME = geomNameComboBox->currentText();
	jp.NUM = NumComboBox->value();

	jp.m_type = Fix;

	return jp;
}

