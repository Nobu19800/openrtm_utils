#include <QtWidgets>
#include <QtGui>
#include <qtextcodec.h>
#include "Bodypages.h"


BoxPage::BoxPage(int def_num, QWidget *parent)
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

	
	
        geomGroup = new QGroupBox(tc->toUnicode("形状・姿勢"));

        lengthLabel = new QLabel(tc->toUnicode("長さ(X)[m]:"));
    lengthCombo = new QDoubleSpinBox;
    lengthCombo->setValue(1.0);

        widthLabel = new QLabel(tc->toUnicode("幅(Y)[m]:"));
    widthCombo = new QDoubleSpinBox;
    widthCombo->setValue(1.0);


        heightLabel = new QLabel(tc->toUnicode("高さ(Z)[m]:"));
    heightCombo = new QDoubleSpinBox;
    heightCombo->setValue(1.0);


	QHBoxLayout *lengthLayout = new QHBoxLayout;
    lengthLayout->addWidget(lengthLabel);
    lengthLayout->addWidget(lengthCombo);

	QHBoxLayout *widthLayout = new QHBoxLayout;
    widthLayout->addWidget(widthLabel);
    widthLayout->addWidget(widthCombo);

	QHBoxLayout *heightLayout = new QHBoxLayout;
    heightLayout->addWidget(heightLabel);
    heightLayout->addWidget(heightCombo);

	QHBoxLayout *LWHLayout = new QHBoxLayout;
	LWHLayout->addLayout(lengthLayout);
	LWHLayout->addLayout(widthLayout);
	LWHLayout->addLayout(heightLayout);

        slxLabel = new QLabel(tc->toUnicode("傾き(X)[rad]:"));
    slxCombo = new QDoubleSpinBox;
    slxCombo->setValue(0.0);
	slxCombo->setMaximum(3.14);
	slxCombo->setMinimum(-3.14);


        slyLabel = new QLabel(tc->toUnicode("傾き(Y)[rad]:"));
    slyCombo = new QDoubleSpinBox;
    slyCombo->setValue(0.0);
	slyCombo->setMaximum(3.14);
	slyCombo->setMinimum(-3.14);


        slzLabel = new QLabel(tc->toUnicode("傾き(Z)[rad]:"));
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

        MassLabel = new QLabel(tc->toUnicode("質量[kg]:"));
    MassCombo = new QDoubleSpinBox;
    MassCombo->setValue(1.0);


	QHBoxLayout *MassLayout = new QHBoxLayout;
    MassLayout->addWidget(MassLabel);
    MassLayout->addWidget(MassCombo);



	QVBoxLayout *geomLayout = new QVBoxLayout;
	geomLayout->addLayout(LWHLayout);
	geomLayout->addLayout(SlLayout);
	geomLayout->addLayout(MassLayout);


	geomGroup->setLayout(geomLayout);


	

        ColorGroup = new QGroupBox(tc->toUnicode("色"));

        RedLabel = new QLabel(tc->toUnicode("赤:"));
    RedCombo = new QDoubleSpinBox;
    RedCombo->setValue(0.0);




        GreenLabel = new QLabel(tc->toUnicode("緑:"));
    GreenCombo = new QDoubleSpinBox;
    GreenCombo->setValue(0.0);

        BlueLabel = new QLabel(tc->toUnicode("青:"));
    BlueCombo = new QDoubleSpinBox;
    BlueCombo->setValue(0.0);


	QHBoxLayout *RedLayout = new QHBoxLayout;
    RedLayout->addWidget(RedLabel);
    RedLayout->addWidget(RedCombo);

	QHBoxLayout *GreenLayout = new QHBoxLayout;
    GreenLayout->addWidget(GreenLabel);
    GreenLayout->addWidget(GreenCombo);

	QHBoxLayout *BlueLayout = new QHBoxLayout;
    BlueLayout->addWidget(BlueLabel);
    BlueLayout->addWidget(BlueCombo);



	QHBoxLayout *ColorLayout = new QHBoxLayout;
	ColorLayout->addLayout(RedLayout);
	ColorLayout->addLayout(GreenLayout);
	ColorLayout->addLayout(BlueLayout);

	ColorGroup->setLayout(ColorLayout);



        IGroup = new QGroupBox(tc->toUnicode("慣性テンソル"));

    I1Combo = new QDoubleSpinBox;
    I1Combo->setValue(1.0);

	I2Combo = new QDoubleSpinBox;
    I2Combo->setValue(0.0);

	I3Combo = new QDoubleSpinBox;
    I3Combo->setValue(0.0);

	I4Combo = new QDoubleSpinBox;
    I4Combo->setValue(0.0);

	I5Combo = new QDoubleSpinBox;
    I5Combo->setValue(1.0);

	I6Combo = new QDoubleSpinBox;
    I6Combo->setValue(0.0);

	I7Combo = new QDoubleSpinBox;
    I7Combo->setValue(0.0);

	I8Combo = new QDoubleSpinBox;
    I8Combo->setValue(0.0);

	I9Combo = new QDoubleSpinBox;
    I9Combo->setValue(1.0);





	QVBoxLayout *I1Layout = new QVBoxLayout;
    I1Layout->addWidget(I1Combo);
    I1Layout->addWidget(I4Combo);
	I1Layout->addWidget(I7Combo);

        QVBoxLayout *I2Layout = new QVBoxLayout;
    I2Layout->addWidget(I2Combo);
    I2Layout->addWidget(I5Combo);
	I2Layout->addWidget(I8Combo);

	QVBoxLayout *I3Layout = new QVBoxLayout;
    I3Layout->addWidget(I3Combo);
    I3Layout->addWidget(I6Combo);
	I3Layout->addWidget(I9Combo);



	QHBoxLayout *ILayout = new QHBoxLayout;
	ILayout->addLayout(I1Layout);
	ILayout->addLayout(I2Layout);
	ILayout->addLayout(I3Layout);

	IGroup->setLayout(ILayout);




    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(NumGroup);
	mainLayout->addWidget(NameGroup);
    mainLayout->addWidget(posGroup);
	mainLayout->addWidget(geomGroup);
	mainLayout->addWidget(IGroup);
	mainLayout->addWidget(ColorGroup);
	mainLayout->addStretch(1);
    setLayout(mainLayout);
}
void BoxPage::setParam(BodyParam bp)
{
	posxCombo->setValue(bp.m_px);
	posyCombo->setValue(bp.m_py);
	poszCombo->setValue(bp.m_pz);
	lengthCombo->setValue(bp.m_length);
	widthCombo->setValue(bp.m_width);
	heightCombo->setValue(bp.m_height);
	slxCombo->setValue(bp.m_slx);
	slyCombo->setValue(bp.m_sly);
	slzCombo->setValue(bp.m_slz);
	MassCombo->setValue(bp.m_mass);
	RedCombo->setValue(bp.m_red);
	BlueCombo->setValue(bp.m_blue);
	GreenCombo->setValue(bp.m_green);
	I1Combo->setValue(bp.I[0]);
	I2Combo->setValue(bp.I[1]);
	I3Combo->setValue(bp.I[2]);
	I4Combo->setValue(bp.I[3]);
	I5Combo->setValue(bp.I[4]);
	I6Combo->setValue(bp.I[5]);
	I7Combo->setValue(bp.I[6]);
	I8Combo->setValue(bp.I[7]);
	I9Combo->setValue(bp.I[8]);
	NumComboBox->setValue(bp.NUM);
	const QString TEMP = bp.NAME;
	geomNameComboBox->addItem(TEMP);



}

BodyParam BoxPage::returnParam()
{
	BodyParam bp;
	bp.m_px = posxCombo->value();
	bp.m_py = posyCombo->value();
	bp.m_pz = poszCombo->value();
	bp.m_length = lengthCombo->value();
	bp.m_width = widthCombo->value();
	bp.m_height = heightCombo->value();
	bp.m_slx = slxCombo->value();
	bp.m_sly = slyCombo->value();
	bp.m_slz = slzCombo->value();
	bp.m_mass = MassCombo->value();
	bp.m_red = RedCombo->value();
	bp.m_blue = BlueCombo->value();
	bp.m_green = GreenCombo->value();
	bp.I[0] = I1Combo->value();
	bp.I[1] = I2Combo->value();
	bp.I[2] = I3Combo->value();
	bp.I[3] = I4Combo->value();
	bp.I[4] = I5Combo->value();
	bp.I[5] = I6Combo->value();
	bp.I[6] = I7Combo->value();
	bp.I[7] = I8Combo->value();
	bp.I[8] = I9Combo->value();

	bp.NAME = geomNameComboBox->currentText();
	bp.NUM = NumComboBox->value();
	bp.m_type = Body_Box;

	return bp;
}





CylinderPage::CylinderPage(int def_num, QWidget *parent)
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

	
	
        geomGroup = new QGroupBox(tc->toUnicode("形状・姿勢"));

        lengthLabel = new QLabel(tc->toUnicode("長さ[m]:"));
    lengthCombo = new QDoubleSpinBox;
    lengthCombo->setValue(1.0);


        radLabel = new QLabel(tc->toUnicode("半径[m]:"));
    radCombo = new QDoubleSpinBox;
    radCombo->setValue(1.0);


        axisLabel = new QLabel(tc->toUnicode("軸:"));
    axisCombo = new QComboBox;
	axisCombo->addItem(tc->toUnicode("x"));
	axisCombo->addItem(tc->toUnicode("y"));
	axisCombo->addItem(tc->toUnicode("z"));


	QHBoxLayout *lengthLayout = new QHBoxLayout;
    lengthLayout->addWidget(lengthLabel);
    lengthLayout->addWidget(lengthCombo);

	QHBoxLayout *radLayout = new QHBoxLayout;
    radLayout->addWidget(radLabel);
    radLayout->addWidget(radCombo);

	QHBoxLayout *axisLayout = new QHBoxLayout;
    axisLayout->addWidget(axisLabel);
    axisLayout->addWidget(axisCombo);

	QHBoxLayout *LWHLayout = new QHBoxLayout;
	LWHLayout->addLayout(lengthLayout);
	LWHLayout->addLayout(radLayout);
	LWHLayout->addLayout(axisLayout);

        slxLabel = new QLabel(tc->toUnicode("傾き(X)[rad]:"));
    slxCombo = new QDoubleSpinBox;
    slxCombo->setValue(0.0);
	slxCombo->setMaximum(3.14);
	slxCombo->setMinimum(-3.14);


        slyLabel = new QLabel(tc->toUnicode("傾き(Y)[rad]:"));
    slyCombo = new QDoubleSpinBox;
    slyCombo->setValue(0.0);
	slyCombo->setMaximum(3.14);
	slyCombo->setMinimum(-3.14);


        slzLabel = new QLabel(tc->toUnicode("傾き(Z)[rad]:"));
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

        MassLabel = new QLabel(tc->toUnicode("質量[kg]:"));
    MassCombo = new QDoubleSpinBox;
    MassCombo->setValue(1.0);


	QHBoxLayout *MassLayout = new QHBoxLayout;
    MassLayout->addWidget(MassLabel);
    MassLayout->addWidget(MassCombo);



	QVBoxLayout *geomLayout = new QVBoxLayout;
	geomLayout->addLayout(LWHLayout);
	geomLayout->addLayout(SlLayout);
	geomLayout->addLayout(MassLayout);


	geomGroup->setLayout(geomLayout);


	

        ColorGroup = new QGroupBox(tc->toUnicode("色"));

        RedLabel = new QLabel(tc->toUnicode("赤:"));
    RedCombo = new QDoubleSpinBox;
    RedCombo->setValue(0.0);


        BlueLabel = new QLabel(tc->toUnicode("青:"));
    BlueCombo = new QDoubleSpinBox;
    BlueCombo->setValue(0.0);


        GreenLabel = new QLabel(tc->toUnicode("緑:"));
    GreenCombo = new QDoubleSpinBox;
    GreenCombo->setValue(0.0);


	QHBoxLayout *RedLayout = new QHBoxLayout;
    RedLayout->addWidget(RedLabel);
    RedLayout->addWidget(RedCombo);

	QHBoxLayout *BlueLayout = new QHBoxLayout;
    BlueLayout->addWidget(BlueLabel);
    BlueLayout->addWidget(BlueCombo);

	QHBoxLayout *GreenLayout = new QHBoxLayout;
    GreenLayout->addWidget(GreenLabel);
    GreenLayout->addWidget(GreenCombo);

	QHBoxLayout *ColorLayout = new QHBoxLayout;
	ColorLayout->addLayout(RedLayout);
	ColorLayout->addLayout(GreenLayout);
	ColorLayout->addLayout(BlueLayout);

	ColorGroup->setLayout(ColorLayout);

        IGroup = new QGroupBox(tc->toUnicode("慣性テンソル"));

    I1Combo = new QDoubleSpinBox;
    I1Combo->setValue(1.0);

	I2Combo = new QDoubleSpinBox;
    I2Combo->setValue(0.0);

	I3Combo = new QDoubleSpinBox;
    I3Combo->setValue(0.0);

	I4Combo = new QDoubleSpinBox;
    I4Combo->setValue(0.0);

	I5Combo = new QDoubleSpinBox;
    I5Combo->setValue(1.0);

	I6Combo = new QDoubleSpinBox;
    I6Combo->setValue(0.0);

	I7Combo = new QDoubleSpinBox;
    I7Combo->setValue(0.0);

	I8Combo = new QDoubleSpinBox;
    I8Combo->setValue(0.0);

	I9Combo = new QDoubleSpinBox;
    I9Combo->setValue(1.0);





	QVBoxLayout *I1Layout = new QVBoxLayout;
    I1Layout->addWidget(I1Combo);
    I1Layout->addWidget(I4Combo);
	I1Layout->addWidget(I7Combo);

	QVBoxLayout *I2Layout = new QVBoxLayout;
    I2Layout->addWidget(I2Combo);
    I2Layout->addWidget(I5Combo);
	I2Layout->addWidget(I8Combo);

	QVBoxLayout *I3Layout = new QVBoxLayout;
    I3Layout->addWidget(I3Combo);
    I3Layout->addWidget(I6Combo);
	I3Layout->addWidget(I9Combo);



	QHBoxLayout *ILayout = new QHBoxLayout;
	ILayout->addLayout(I1Layout);
	ILayout->addLayout(I2Layout);
	ILayout->addLayout(I3Layout);

	IGroup->setLayout(ILayout);



    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(NumGroup);
	mainLayout->addWidget(NameGroup);
    mainLayout->addWidget(posGroup);
	mainLayout->addWidget(geomGroup);
	mainLayout->addWidget(IGroup);
	mainLayout->addWidget(ColorGroup);
	mainLayout->addStretch(1);
    setLayout(mainLayout);

}

void CylinderPage::setParam(BodyParam bp)
{
	
	posxCombo->setValue(bp.m_px);
	posyCombo->setValue(bp.m_py);
	poszCombo->setValue(bp.m_pz);
	lengthCombo->setValue(bp.m_length);
	radCombo->setValue(bp.m_rad);
	slxCombo->setValue(bp.m_slx);
	slyCombo->setValue(bp.m_sly);
	slzCombo->setValue(bp.m_slz);
	MassCombo->setValue(bp.m_mass);
	RedCombo->setValue(bp.m_red);
	BlueCombo->setValue(bp.m_blue);
	GreenCombo->setValue(bp.m_green);
	I1Combo->setValue(bp.I[0]);
	I2Combo->setValue(bp.I[1]);
	I3Combo->setValue(bp.I[2]);
	I4Combo->setValue(bp.I[3]);
	I5Combo->setValue(bp.I[4]);
	I6Combo->setValue(bp.I[5]);
	I7Combo->setValue(bp.I[6]);
	I8Combo->setValue(bp.I[7]);
	I9Combo->setValue(bp.I[8]);
	NumComboBox->setValue(bp.NUM);
	
	const QString TEMP = bp.NAME;
	geomNameComboBox->addItem(TEMP);

}

BodyParam CylinderPage::returnParam()
{
	BodyParam bp;
	bp.m_px = posxCombo->value();
	bp.m_py = posyCombo->value();
	bp.m_pz = poszCombo->value();
	bp.m_length = lengthCombo->value();
	bp.m_rad = radCombo->value();
	if(axisCombo->currentText() == "x")
		bp.axis = 0;
	else if(axisCombo->currentText() == "y")
		bp.axis = 1;
	else if(axisCombo->currentText() == "z")
		bp.axis = 2;
	bp.m_slx = slxCombo->value();
	bp.m_sly = slyCombo->value();
	bp.m_slz = slzCombo->value();
	bp.m_mass = MassCombo->value();
	bp.m_red = RedCombo->value();
	bp.m_blue = BlueCombo->value();
	bp.m_green = GreenCombo->value();
	bp.I[0] = I1Combo->value();
	bp.I[1] = I2Combo->value();
	bp.I[2] = I3Combo->value();
	bp.I[3] = I4Combo->value();
	bp.I[4] = I5Combo->value();
	bp.I[5] = I6Combo->value();
	bp.I[6] = I7Combo->value();
	bp.I[7] = I8Combo->value();
	bp.I[8] = I9Combo->value();

	bp.NAME = geomNameComboBox->currentText();

	bp.NUM = NumComboBox->value();
	bp.m_type = Body_Cylinder;

	return bp;
}




SpherePage::SpherePage(int def_num, QWidget *parent)
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

	
	
        geomGroup = new QGroupBox(tc->toUnicode("形状・姿勢"));



        radLabel = new QLabel(tc->toUnicode("半径(Y)[m]:"));
    radCombo = new QDoubleSpinBox;
    radCombo->setValue(1.0);




	QHBoxLayout *radLayout = new QHBoxLayout;
    radLayout->addWidget(radLabel);
    radLayout->addWidget(radCombo);



	QHBoxLayout *LWHLayout = new QHBoxLayout;
	LWHLayout->addLayout(radLayout);



        MassLabel = new QLabel(tc->toUnicode("質量[kg]:"));
    MassCombo = new QDoubleSpinBox;
    MassCombo->setValue(1.0);


	QHBoxLayout *MassLayout = new QHBoxLayout;
    MassLayout->addWidget(MassLabel);
    MassLayout->addWidget(MassCombo);



	QVBoxLayout *geomLayout = new QVBoxLayout;
	geomLayout->addLayout(LWHLayout);
	geomLayout->addLayout(MassLayout);


	geomGroup->setLayout(geomLayout);


	

        ColorGroup = new QGroupBox(tc->toUnicode("色"));

        RedLabel = new QLabel(tc->toUnicode("赤:"));
    RedCombo = new QDoubleSpinBox;
    RedCombo->setValue(0.0);


        BlueLabel = new QLabel(tc->toUnicode("青:"));
    BlueCombo = new QDoubleSpinBox;
    BlueCombo->setValue(0.0);


        GreenLabel = new QLabel(tc->toUnicode("緑:"));
    GreenCombo = new QDoubleSpinBox;
    GreenCombo->setValue(0.0);


	QHBoxLayout *RedLayout = new QHBoxLayout;
    RedLayout->addWidget(RedLabel);
    RedLayout->addWidget(RedCombo);

	QHBoxLayout *BlueLayout = new QHBoxLayout;
    BlueLayout->addWidget(BlueLabel);
    BlueLayout->addWidget(BlueCombo);

	QHBoxLayout *GreenLayout = new QHBoxLayout;
    GreenLayout->addWidget(GreenLabel);
    GreenLayout->addWidget(GreenCombo);

	QHBoxLayout *ColorLayout = new QHBoxLayout;
	ColorLayout->addLayout(RedLayout);
	ColorLayout->addLayout(GreenLayout);
	ColorLayout->addLayout(BlueLayout);
	

	ColorGroup->setLayout(ColorLayout);

        IGroup = new QGroupBox(tc->toUnicode("慣性テンソル"));

    I1Combo = new QDoubleSpinBox;
    I1Combo->setValue(1.0);

	I2Combo = new QDoubleSpinBox;
    I2Combo->setValue(0.0);

	I3Combo = new QDoubleSpinBox;
    I3Combo->setValue(0.0);

	I4Combo = new QDoubleSpinBox;
    I4Combo->setValue(0.0);

	I5Combo = new QDoubleSpinBox;
    I5Combo->setValue(1.0);

	I6Combo = new QDoubleSpinBox;
    I6Combo->setValue(0.0);

	I7Combo = new QDoubleSpinBox;
    I7Combo->setValue(0.0);

	I8Combo = new QDoubleSpinBox;
    I8Combo->setValue(0.0);

	I9Combo = new QDoubleSpinBox;
    I9Combo->setValue(1.0);





	QVBoxLayout *I1Layout = new QVBoxLayout;
    I1Layout->addWidget(I1Combo);
    I1Layout->addWidget(I4Combo);
	I1Layout->addWidget(I7Combo);

	QVBoxLayout *I2Layout = new QVBoxLayout;
    I2Layout->addWidget(I2Combo);
    I2Layout->addWidget(I5Combo);
	I2Layout->addWidget(I8Combo);

	QVBoxLayout *I3Layout = new QVBoxLayout;
    I3Layout->addWidget(I3Combo);
    I3Layout->addWidget(I6Combo);
	I3Layout->addWidget(I9Combo);



	QHBoxLayout *ILayout = new QHBoxLayout;
	ILayout->addLayout(I1Layout);
	ILayout->addLayout(I2Layout);
	ILayout->addLayout(I3Layout);

	IGroup->setLayout(ILayout);



    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(NumGroup);
	mainLayout->addWidget(NameGroup);
    mainLayout->addWidget(posGroup);
	mainLayout->addWidget(geomGroup);
	mainLayout->addWidget(IGroup);
	mainLayout->addWidget(ColorGroup);
	mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void SpherePage::setParam(BodyParam bp)
{
	posxCombo->setValue(bp.m_px);
	posyCombo->setValue(bp.m_py);
	poszCombo->setValue(bp.m_pz);
	radCombo->setValue(bp.m_rad);
	MassCombo->setValue(bp.m_mass);
	RedCombo->setValue(bp.m_red);
	BlueCombo->setValue(bp.m_blue);
	GreenCombo->setValue(bp.m_green);
	I1Combo->setValue(bp.I[0]);
	I2Combo->setValue(bp.I[1]);
	I3Combo->setValue(bp.I[2]);
	I4Combo->setValue(bp.I[3]);
	I5Combo->setValue(bp.I[4]);
	I6Combo->setValue(bp.I[5]);
	I7Combo->setValue(bp.I[6]);
	I8Combo->setValue(bp.I[7]);
	I9Combo->setValue(bp.I[8]);
	NumComboBox->setValue(bp.NUM);
	
	const QString TEMP = bp.NAME;
	geomNameComboBox->addItem(TEMP);

}




BodyParam SpherePage::returnParam()
{
	BodyParam bp;
	bp.m_px = posxCombo->value();
	bp.m_py = posyCombo->value();
	bp.m_pz = poszCombo->value();
	bp.m_rad = radCombo->value();
	bp.m_mass = MassCombo->value();
	bp.m_red = RedCombo->value();
	bp.m_blue = BlueCombo->value();
	bp.m_green = GreenCombo->value();
	bp.I[0] = I1Combo->value();
	bp.I[1] = I2Combo->value();
	bp.I[2] = I3Combo->value();
	bp.I[3] = I4Combo->value();
	bp.I[4] = I5Combo->value();
	bp.I[5] = I6Combo->value();
	bp.I[6] = I7Combo->value();
	bp.I[7] = I8Combo->value();
	bp.I[8] = I9Combo->value();

	bp.NAME = geomNameComboBox->currentText();

	bp.NUM = NumComboBox->value();
	bp.m_type = Body_Sphere;

	return bp;
}



ConePage::ConePage(int def_num, QWidget *parent)
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

	
	
        geomGroup = new QGroupBox(tc->toUnicode("形状・姿勢"));

        lengthLabel = new QLabel(tc->toUnicode("長さ(X)[m]:"));
    lengthCombo = new QDoubleSpinBox;
    lengthCombo->setValue(1.0);


        radLabel = new QLabel(tc->toUnicode("半径(Y)[m]:"));
    radCombo = new QDoubleSpinBox;
    radCombo->setValue(1.0);


        axisLabel = new QLabel(tc->toUnicode("軸(Z)[m]:"));
    axisCombo = new QComboBox;
	axisCombo->addItem(tc->toUnicode("x"));
	axisCombo->addItem(tc->toUnicode("y"));
	axisCombo->addItem(tc->toUnicode("z"));


	QHBoxLayout *lengthLayout = new QHBoxLayout;
    lengthLayout->addWidget(lengthLabel);
    lengthLayout->addWidget(lengthCombo);

	QHBoxLayout *radLayout = new QHBoxLayout;
    radLayout->addWidget(radLabel);
    radLayout->addWidget(radCombo);

	QHBoxLayout *axisLayout = new QHBoxLayout;
    axisLayout->addWidget(axisLabel);
    axisLayout->addWidget(axisCombo);

	QHBoxLayout *LWHLayout = new QHBoxLayout;
	LWHLayout->addLayout(lengthLayout);
	LWHLayout->addLayout(radLayout);
	LWHLayout->addLayout(axisLayout);

        slxLabel = new QLabel(tc->toUnicode("傾き(X)[rad]:"));
    slxCombo = new QDoubleSpinBox;
    slxCombo->setValue(0.0);
	slxCombo->setMaximum(3.14);
	slxCombo->setMinimum(-3.14);


        slyLabel = new QLabel(tc->toUnicode("傾き(Y)[rad]:"));
    slyCombo = new QDoubleSpinBox;
    slyCombo->setValue(0.0);
	slyCombo->setMaximum(3.14);
	slyCombo->setMinimum(-3.14);


        slzLabel = new QLabel(tc->toUnicode("傾き(Z)[rad]:"));
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

        MassLabel = new QLabel(tc->toUnicode("質量[kg]:"));
    MassCombo = new QDoubleSpinBox;
    MassCombo->setValue(1.0);


	QHBoxLayout *MassLayout = new QHBoxLayout;
    MassLayout->addWidget(MassLabel);
    MassLayout->addWidget(MassCombo);



	QVBoxLayout *geomLayout = new QVBoxLayout;
	geomLayout->addLayout(LWHLayout);
	geomLayout->addLayout(SlLayout);
	geomLayout->addLayout(MassLayout);


	geomGroup->setLayout(geomLayout);


	

        ColorGroup = new QGroupBox(tc->toUnicode("色"));

        RedLabel = new QLabel(tc->toUnicode("赤:"));
    RedCombo = new QDoubleSpinBox;
    RedCombo->setValue(0.0);


        BlueLabel = new QLabel(tc->toUnicode("青:"));
    BlueCombo = new QDoubleSpinBox;
	BlueCombo->setValue(0.0);


        GreenLabel = new QLabel(tc->toUnicode("緑:"));
    GreenCombo = new QDoubleSpinBox;
    GreenCombo->setValue(0.0);


	QHBoxLayout *RedLayout = new QHBoxLayout;
    RedLayout->addWidget(RedLabel);
    RedLayout->addWidget(RedCombo);

	QHBoxLayout *BlueLayout = new QHBoxLayout;
    BlueLayout->addWidget(BlueLabel);
    BlueLayout->addWidget(BlueCombo);

	QHBoxLayout *GreenLayout = new QHBoxLayout;
    GreenLayout->addWidget(GreenLabel);
    GreenLayout->addWidget(GreenCombo);

	QHBoxLayout *ColorLayout = new QHBoxLayout;
	ColorLayout->addLayout(RedLayout);
	ColorLayout->addLayout(GreenLayout);
	ColorLayout->addLayout(BlueLayout);
	

	ColorGroup->setLayout(ColorLayout);

        IGroup = new QGroupBox(tc->toUnicode("慣性テンソル"));

    I1Combo = new QDoubleSpinBox;
    I1Combo->setValue(1.0);

	I2Combo = new QDoubleSpinBox;
    I2Combo->setValue(0.0);

	I3Combo = new QDoubleSpinBox;
    I3Combo->setValue(0.0);

	I4Combo = new QDoubleSpinBox;
    I4Combo->setValue(0.0);

	I5Combo = new QDoubleSpinBox;
    I5Combo->setValue(1.0);

	I6Combo = new QDoubleSpinBox;
    I6Combo->setValue(0.0);

	I7Combo = new QDoubleSpinBox;
    I7Combo->setValue(0.0);

	I8Combo = new QDoubleSpinBox;
    I8Combo->setValue(0.0);

	I9Combo = new QDoubleSpinBox;
    I9Combo->setValue(1.0);





	QVBoxLayout *I1Layout = new QVBoxLayout;
    I1Layout->addWidget(I1Combo);
    I1Layout->addWidget(I4Combo);
	I1Layout->addWidget(I7Combo);

	QVBoxLayout *I2Layout = new QVBoxLayout;
    I2Layout->addWidget(I2Combo);
    I2Layout->addWidget(I5Combo);
	I2Layout->addWidget(I8Combo);

	QVBoxLayout *I3Layout = new QVBoxLayout;
    I3Layout->addWidget(I3Combo);
    I3Layout->addWidget(I6Combo);
	I3Layout->addWidget(I9Combo);



	QHBoxLayout *ILayout = new QHBoxLayout;
	ILayout->addLayout(I1Layout);
	ILayout->addLayout(I2Layout);
	ILayout->addLayout(I3Layout);

	IGroup->setLayout(ILayout);



    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(NumGroup);
	mainLayout->addWidget(NameGroup);
    mainLayout->addWidget(posGroup);
	mainLayout->addWidget(geomGroup);
	mainLayout->addWidget(IGroup);
	mainLayout->addWidget(ColorGroup);
	mainLayout->addStretch(1);
    setLayout(mainLayout);
}

void ConePage::setParam(BodyParam bp)
{
	posxCombo->setValue(bp.m_px);
	posyCombo->setValue(bp.m_py);
	poszCombo->setValue(bp.m_pz);
	lengthCombo->setValue(bp.m_length);
	radCombo->setValue(bp.m_rad);
	slxCombo->setValue(bp.m_slx);
	slyCombo->setValue(bp.m_sly);
	slzCombo->setValue(bp.m_slz);
	MassCombo->setValue(bp.m_mass);
	RedCombo->setValue(bp.m_red);
	BlueCombo->setValue(bp.m_blue);
	GreenCombo->setValue(bp.m_green);
	I1Combo->setValue(bp.I[0]);
	I2Combo->setValue(bp.I[1]);
	I3Combo->setValue(bp.I[2]);
	I4Combo->setValue(bp.I[3]);
	I5Combo->setValue(bp.I[4]);
	I6Combo->setValue(bp.I[5]);
	I7Combo->setValue(bp.I[6]);
	I8Combo->setValue(bp.I[7]);
	I9Combo->setValue(bp.I[8]);
	NumComboBox->setValue(bp.NUM);
	
	const QString TEMP = bp.NAME;
	geomNameComboBox->addItem(TEMP);

}

BodyParam ConePage::returnParam()
{

	BodyParam bp;
	bp.m_px = posxCombo->value();
	bp.m_py = posyCombo->value();
	bp.m_pz = poszCombo->value();
	bp.m_length = lengthCombo->value();
	bp.m_rad = radCombo->value();
	if(axisCombo->currentText() == "x")
		bp.axis = 0;
	else if(axisCombo->currentText() == "y")
		bp.axis = 1;
	else if(axisCombo->currentText() == "z")
		bp.axis = 2;
	bp.m_slx = slxCombo->value();
	bp.m_sly = slyCombo->value();
	bp.m_slz = slzCombo->value();
	bp.m_mass = MassCombo->value();
	bp.m_red = RedCombo->value();
	bp.m_blue = BlueCombo->value();
	bp.m_green = GreenCombo->value();
	bp.I[0] = I1Combo->value();
	bp.I[1] = I2Combo->value();
	bp.I[2] = I3Combo->value();
	bp.I[3] = I4Combo->value();
	bp.I[4] = I5Combo->value();
	bp.I[5] = I6Combo->value();
	bp.I[6] = I7Combo->value();
	bp.I[7] = I8Combo->value();
	bp.I[8] = I9Combo->value();

	bp.NAME = geomNameComboBox->currentText();

	bp.NUM = NumComboBox->value();
	bp.m_type = Body_Cone;
	
	return bp;
}





PolygonPage::PolygonPage(int def_num, QWidget *parent)
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

	
	
        geomGroup = new QGroupBox(tc->toUnicode("姿勢"));



        slxLabel = new QLabel(tc->toUnicode("傾き(X)[rad]:"));
    slxCombo = new QDoubleSpinBox;
    slxCombo->setValue(0.0);
	slxCombo->setMaximum(3.14);
	slxCombo->setMinimum(-3.14);


        slyLabel = new QLabel(tc->toUnicode("傾き(Y)[rad]:"));
    slyCombo = new QDoubleSpinBox;
    slyCombo->setValue(0.0);
	slyCombo->setMaximum(3.14);
	slyCombo->setMinimum(-3.14);


        slzLabel = new QLabel(tc->toUnicode("傾き(Z)[rad]:"));
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

        MassLabel = new QLabel(tc->toUnicode("質量[kg]:"));
    MassCombo = new QDoubleSpinBox;
    MassCombo->setValue(1.0);


	QHBoxLayout *MassLayout = new QHBoxLayout;
    MassLayout->addWidget(MassLabel);
    MassLayout->addWidget(MassCombo);



	QVBoxLayout *geomLayout = new QVBoxLayout;
	geomLayout->addLayout(SlLayout);
	geomLayout->addLayout(MassLayout);


	geomGroup->setLayout(geomLayout);

        IGroup = new QGroupBox(tc->toUnicode("慣性テンソル"));

    I1Combo = new QDoubleSpinBox;
    I1Combo->setValue(1.0);

	I2Combo = new QDoubleSpinBox;
    I2Combo->setValue(0.0);

	I3Combo = new QDoubleSpinBox;
    I3Combo->setValue(0.0);

	I4Combo = new QDoubleSpinBox;
    I4Combo->setValue(0.0);

	I5Combo = new QDoubleSpinBox;
    I5Combo->setValue(1.0);

	I6Combo = new QDoubleSpinBox;
    I6Combo->setValue(0.0);

	I7Combo = new QDoubleSpinBox;
    I7Combo->setValue(0.0);

	I8Combo = new QDoubleSpinBox;
    I8Combo->setValue(0.0);

	I9Combo = new QDoubleSpinBox;
    I9Combo->setValue(1.0);





	QVBoxLayout *I1Layout = new QVBoxLayout;
    I1Layout->addWidget(I1Combo);
    I1Layout->addWidget(I4Combo);
	I1Layout->addWidget(I7Combo);

	QVBoxLayout *I2Layout = new QVBoxLayout;
    I2Layout->addWidget(I2Combo);
    I2Layout->addWidget(I5Combo);
	I2Layout->addWidget(I8Combo);

	QVBoxLayout *I3Layout = new QVBoxLayout;
    I3Layout->addWidget(I3Combo);
    I3Layout->addWidget(I6Combo);
	I3Layout->addWidget(I9Combo);



	QHBoxLayout *ILayout = new QHBoxLayout;
	ILayout->addLayout(I1Layout);
	ILayout->addLayout(I2Layout);
	ILayout->addLayout(I3Layout);

	IGroup->setLayout(ILayout);




    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(NumGroup);
	mainLayout->addWidget(NameGroup);
    mainLayout->addWidget(posGroup);
	mainLayout->addWidget(geomGroup);
	mainLayout->addWidget(IGroup);
	mainLayout->addStretch(1);
    setLayout(mainLayout);

}

void PolygonPage::setParam(BodyParam bp)
{
	posxCombo->setValue(bp.m_px);
	posyCombo->setValue(bp.m_py);
	poszCombo->setValue(bp.m_pz);
	slxCombo->setValue(bp.m_slx);
	slyCombo->setValue(bp.m_sly);
	slzCombo->setValue(bp.m_slz);
	MassCombo->setValue(bp.m_mass);
	I1Combo->setValue(bp.I[0]);
	I2Combo->setValue(bp.I[1]);
	I3Combo->setValue(bp.I[2]);
	I4Combo->setValue(bp.I[3]);
	I5Combo->setValue(bp.I[4]);
	I6Combo->setValue(bp.I[5]);
	I7Combo->setValue(bp.I[6]);
	I8Combo->setValue(bp.I[7]);
	I9Combo->setValue(bp.I[8]);
	NumComboBox->setValue(bp.NUM);
	m_pd = bp.m_pd;
	
	const QString TEMP = bp.NAME;
	geomNameComboBox->addItem(TEMP);



}

BodyParam PolygonPage::returnParam()
{

	BodyParam bp;
	bp.m_px = posxCombo->value();
	bp.m_py = posyCombo->value();
	bp.m_pz = poszCombo->value();
	bp.m_length = 0.0;
	bp.m_width = 0.0;
	bp.m_height = 0.0;
	bp.m_slx = slxCombo->value();
	bp.m_sly = slyCombo->value();
	bp.m_slz = slzCombo->value();
	bp.m_mass = MassCombo->value();
	bp.m_red = 0.0;
	bp.m_blue = 0.0;
	bp.m_green = 0.0;
	bp.I[0] = I1Combo->value();
	bp.I[1] = I2Combo->value();
	bp.I[2] = I3Combo->value();
	bp.I[3] = I4Combo->value();
	bp.I[4] = I5Combo->value();
	bp.I[5] = I6Combo->value();
	bp.I[6] = I7Combo->value();
	bp.I[7] = I8Combo->value();
	bp.I[8] = I9Combo->value();

	bp.NAME = geomNameComboBox->currentText();

	bp.NUM = NumComboBox->value();

	bp.m_type = Body_Polygon;
	bp.m_pd = m_pd;

	return bp;

}


