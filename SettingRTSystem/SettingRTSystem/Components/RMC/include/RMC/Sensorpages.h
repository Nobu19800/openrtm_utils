
#ifndef SENSORPAGES_H
#define SENSORPAGES_H

#include <QWidget>
#include "ObjectData.h"


/*センサのパラメータ設定のページ*/

class SensorPage : public QWidget
{
public:
	SensorPage(int def_num = 0, QWidget *parent = 0);
	SensorParam returnParam();
	void setParam(SensorParam sp);
	QDoubleSpinBox *posxCombo;
	QDoubleSpinBox *posyCombo;
	QDoubleSpinBox *poszCombo;
	QDoubleSpinBox *slxCombo;
	QDoubleSpinBox *slyCombo;
	QDoubleSpinBox *slzCombo;
	QComboBox *geomNameComboBox;
	QSpinBox *NumComboBox;
	QSpinBox *IDComboBox;
	int m_type;

private:
	
	QLabel *geomNameLabel;
	QLabel *NumLabel;
	QGroupBox *NumGroup;
	QLabel *posxLabel;
	QLabel *posyLabel;
	QLabel *poszLabel;
	QLabel *slxLabel;
	QLabel *slyLabel;
	QLabel *slzLabel;
	QLabel *IDLabel;
	QGroupBox *NameGroup;
	QGroupBox *posGroup;
	QGroupBox *geomGroup;
	QGroupBox *anotherGroup;
	
	

	QTextCodec* tc;

};




#endif
