#include <QtWidgets> 
#include <QtGui>
#include <qtextcodec.h>

#include "Sensorpages.h"

SensorPage::SensorPage(int def_num, QWidget *parent)
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





	QVBoxLayout *geomLayout = new QVBoxLayout;
	geomLayout->addLayout(SlLayout);


	geomGroup->setLayout(geomLayout);


	





    QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(NumGroup);
	mainLayout->addWidget(NameGroup);
    mainLayout->addWidget(posGroup);
	mainLayout->addWidget(geomGroup);
	mainLayout->addStretch(1);
    setLayout(mainLayout);
}
void SensorPage::setParam(SensorParam sp)
{
	posxCombo->setValue(sp.m_px);
	posyCombo->setValue(sp.m_py);
	poszCombo->setValue(sp.m_pz);
	slxCombo->setValue(sp.m_slx);
	slyCombo->setValue(sp.m_sly);
	slzCombo->setValue(sp.m_slz);
	IDComboBox->setValue(sp.ID);
	NumComboBox->setValue(sp.NUM);
	const QString TEMP = sp.NAME;
	geomNameComboBox->addItem(TEMP);

	m_type = sp.m_type;

}

SensorParam SensorPage::returnParam()
{
	SensorParam sp;

	sp.m_px = posxCombo->value();
	sp.m_py = posyCombo->value();
	sp.m_pz = poszCombo->value();
	sp.m_slx = slxCombo->value();
	sp.m_sly = slyCombo->value();
	sp.m_slz = slzCombo->value();
	sp.ID = IDComboBox->value();
	sp.NUM = NumComboBox->value();
	sp.NAME = geomNameComboBox->currentText();
	sp.m_type = m_type;

	return sp;
}



