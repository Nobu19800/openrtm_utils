#include <QtWidgets> 
#include <QtGui>
#include <qtextcodec.h>

#include "Camerapages.h" 

CameraPage::CameraPage(int def_num, QWidget *parent)
    : QWidget(parent)
{
        tc = QTextCodec::codecForLocale();

        NameGroup = new QGroupBox(tc->toUnicode("名前"));

	geomNameComboBox = new QComboBox;

	geomNameComboBox->setEditable(true);
    geomNameComboBox->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Preferred);
	geomNameComboBox->lineEdit()->setText("test");
        geomNameLabel = new QLabel(tc->toUnicode("名前:"));

	QHBoxLayout *NameLayout = new QHBoxLayout;
    NameLayout->addWidget(geomNameLabel);
    NameLayout->addWidget(geomNameComboBox);

	NameGroup->setLayout(NameLayout);



	
        NumGroup = new QGroupBox(tc->toUnicode("番号"));
	
	NumComboBox = new QSpinBox;

	NumComboBox->setValue(def_num);
        NumLabel = new QLabel(tc->toUnicode("番号:"));

	QHBoxLayout *NumLayout = new QHBoxLayout;
    NumLayout->addWidget(NumLabel);
    NumLayout->addWidget(NumComboBox);

	IDComboBox = new QSpinBox;
	IDComboBox->setValue(0);

        IDLabel = new QLabel(tc->toUnicode("ID:"));

    NumLayout->addWidget(IDLabel);
    NumLayout->addWidget(IDComboBox);




	

	NumGroup->setLayout(NumLayout);



    posGroup = new QGroupBox(tc->toUnicode("位置"));

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

	
	
        geomGroup = new QGroupBox(tc->toUnicode("方向"));



        slxLabel = new QLabel(tc->toUnicode("X:"));
    slxCombo = new QDoubleSpinBox;
    slxCombo->setValue(0.0);
	slxCombo->setMaximum(3.14);
	slxCombo->setMinimum(-3.14);


        slyLabel = new QLabel(tc->toUnicode("Y:"));
    slyCombo = new QDoubleSpinBox;
    slyCombo->setValue(0.0);
	slyCombo->setMaximum(3.14);
	slyCombo->setMinimum(-3.14);


        slzLabel = new QLabel(tc->toUnicode("Z:"));
    slzCombo = new QDoubleSpinBox;
    slzCombo->setValue(0.0);
	slzCombo->setMaximum(3.14);
	slzCombo->setMinimum(-3.14);


	QHBoxLayout *slxLayout = new QHBoxLayout;
    slxLayout->addWidget(slxLabel);
    slxLayout->addWidget(slxCombo);

	QHBoxLayout *slyLayout = new QHBoxLayout;
    slyLayout->addWidget(slyLabel);
    slyLayout->addWidget(slyCombo);

	QHBoxLayout *slzLayout = new QHBoxLayout;
    slzLayout->addWidget(slzLabel);
    slzLayout->addWidget(slzCombo);

	QHBoxLayout *SlLayout = new QHBoxLayout;
	SlLayout->addLayout(slxLayout);
	SlLayout->addLayout(slyLayout);
	SlLayout->addLayout(slzLayout);



        fieldOfViewLabel = new QLabel(tc->toUnicode("視野角度[rad]:"));
    fieldOfViewCombo = new QDoubleSpinBox;
    fieldOfViewCombo->setValue(0.78);
	fieldOfViewCombo->setMaximum(3.14);
	fieldOfViewCombo->setMinimum(0.0);

        frontClipDistanceLabel = new QLabel(tc->toUnicode("前クリップ面までの距離[m]:"));
    frontClipDistanceCombo = new QDoubleSpinBox;
    frontClipDistanceCombo->setValue(0.01);
	frontClipDistanceCombo->setMinimum(0.0);

	backClipDistanceLabel = new QLabel(tc->toUnicode("後クリップ面までの距離[m]:"));
    backClipDistanceCombo = new QDoubleSpinBox;
    backClipDistanceCombo->setValue(10.0);
	backClipDistanceCombo->setMinimum(0.0);

        typeLabel = new QLabel(tc->toUnicode("情報の種類:"));

	typeCombo = new QComboBox;
        typeCombo->addItem(tc->toUnicode("色"));
        typeCombo->addItem(tc->toUnicode("深さ"));
        typeCombo->addItem(tc->toUnicode("色と深さ"));
        typeCombo->addItem(tc->toUnicode("取得しない"));

        widthLabel = new QLabel(tc->toUnicode("幅[m]:"));
    widthCombo = new QDoubleSpinBox;
    widthCombo->setValue(320);
	widthCombo->setMinimum(0.0);
	widthCombo->setMaximum(1000.0);

        heightLabel = new QLabel(tc->toUnicode("高さ[m]:"));
    heightCombo = new QDoubleSpinBox;
    heightCombo->setValue(240);
	heightCombo->setMinimum(0.0);
	heightCombo->setMaximum(1000.0);

	QHBoxLayout *fieldOfViewLayout = new QHBoxLayout;
    fieldOfViewLayout->addWidget(fieldOfViewLabel);
    fieldOfViewLayout->addWidget(fieldOfViewCombo);

	QHBoxLayout *ClipDistanceLayout = new QHBoxLayout;
    ClipDistanceLayout->addWidget(frontClipDistanceLabel);
    ClipDistanceLayout->addWidget(frontClipDistanceCombo);
	ClipDistanceLayout->addWidget(backClipDistanceLabel);
    ClipDistanceLayout->addWidget(backClipDistanceCombo);

	QHBoxLayout *TypeLayout = new QHBoxLayout;
    TypeLayout->addWidget(typeLabel);
    TypeLayout->addWidget(typeCombo);

	QHBoxLayout *RangeLayout = new QHBoxLayout;
    RangeLayout->addWidget(widthLabel);
    RangeLayout->addWidget(widthCombo);
	RangeLayout->addWidget(heightLabel);
    RangeLayout->addWidget(heightCombo);

	QVBoxLayout *ParamLayout = new QVBoxLayout;
	ParamLayout->addLayout(fieldOfViewLayout);
	ParamLayout->addLayout(ClipDistanceLayout);
	ParamLayout->addLayout(TypeLayout);
	ParamLayout->addLayout(RangeLayout);










	QVBoxLayout *geomLayout = new QVBoxLayout;
	geomLayout->addLayout(SlLayout);
	geomLayout->addLayout(ParamLayout);


	geomGroup->setLayout(geomLayout);


	





    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(NumGroup);
	mainLayout->addWidget(NameGroup);
    mainLayout->addWidget(posGroup);
	mainLayout->addWidget(geomGroup);
	mainLayout->addStretch(1);
    setLayout(mainLayout);
}


void CameraPage::setParam(CameraParam cp)
{
	posxCombo->setValue(cp.m_px);
	posyCombo->setValue(cp.m_py);
	poszCombo->setValue(cp.m_pz);
	slxCombo->setValue(cp.m_slx);
	slyCombo->setValue(cp.m_sly);
	slzCombo->setValue(cp.m_slz);
	fieldOfViewCombo->setValue(cp.fieldOfView);
	frontClipDistanceCombo->setValue(cp.frontClipDistance);
	backClipDistanceCombo->setValue(cp.backClipDistance);
	widthCombo->setValue(cp.m_width);
	heightCombo->setValue(cp.m_height);
	typeCombo->setCurrentIndex(cp.m_type);
	IDComboBox->setValue(cp.ID);
	NumComboBox->setValue(cp.NUM);
	const QString TEMP = cp.NAME;
	geomNameComboBox->addItem(TEMP);
	



}

CameraParam CameraPage::returnParam()
{


	CameraParam cp;

	cp.m_px = posxCombo->value();
	cp.m_py = posyCombo->value();
	cp.m_pz = poszCombo->value();
	cp.m_slx = slxCombo->value();
	cp.m_sly = slyCombo->value();
	cp.m_slz = slzCombo->value();
	cp.fieldOfView = fieldOfViewCombo->value();
	cp.frontClipDistance = frontClipDistanceCombo->value();
	cp.backClipDistance = backClipDistanceCombo->value();
	cp.m_width = widthCombo->value();
	cp.m_height = heightCombo->value();
	cp.ID = IDComboBox->value();
	cp.NUM = NumComboBox->value();
	cp.NAME = geomNameComboBox->currentText();
	

	if(typeCombo->currentText() == "COLOR")
		cp.m_type = COLOR;
	else if(typeCombo->currentText() == "DEPTH")
		cp.m_type = DEPTH;
	else if(typeCombo->currentText() == "COLOR_DEPTH")
		cp.m_type = COLOR_DEPTH;
	else if(typeCombo->currentText() == "NONE")
		cp.m_type = NONE;

	return cp;
}




