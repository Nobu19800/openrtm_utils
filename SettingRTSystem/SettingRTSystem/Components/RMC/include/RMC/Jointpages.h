
#ifndef JOINTPAGES_H
#define JOINTPAGES_H

#include <QtWidgets>
#include <QWidget>
#include "ObjectData.h"

class QSpinBox;
class QDoubleSpinBox;

/*ヒンジジョイントのパラメータ設定のページ*/

class HingePage : public QWidget
{
public:
	HingePage(int def_num = 0, QWidget *parent = 0);
	JointParam returnParam();
	void setParam(JointParam jp);
	QDoubleSpinBox *posxCombo;
	QDoubleSpinBox *posyCombo;
	QDoubleSpinBox *poszCombo;
	QDoubleSpinBox *axisxCombo;
	QDoubleSpinBox *axisyCombo;
	QDoubleSpinBox *axiszCombo;
	QDoubleSpinBox *ulimitHCombo;
	QDoubleSpinBox *ulimitLCombo;
	QDoubleSpinBox *uvlimitHCombo;
	QDoubleSpinBox *uvlimitLCombo;
	QDoubleSpinBox *rotorInertiaCombo;
	QDoubleSpinBox *rotorResistorCombo;
	QDoubleSpinBox *torqueConstCombo;
	QDoubleSpinBox *encoderPulseCombo;
	QComboBox *geomNameComboBox;
	QSpinBox *NumComboBox;

private:
	
	QLabel *geomNameLabel;
	
	QLabel *NumLabel;
	QGroupBox *NumGroup;
	QLabel *posxLabel;
	QLabel *posyLabel;
	QLabel *poszLabel;
	QLabel *axisxLabel;
	QLabel *axisyLabel;
	QLabel *axiszLabel;
	QLabel *ulimitHLabel;
	QLabel *ulimitLLabel;
	QLabel *uvlimitHLabel;
	QLabel *uvlimitLLabel;
	QLabel *rotorInertiaLabel;
	QLabel *rotorResistorLabel;
	QLabel *torqueConstLabel;
	QLabel *encoderPulseLabel;
	QGroupBox *NameGroup;
	QGroupBox *posGroup;
	QGroupBox *axisGroup;
	QGroupBox *anotherGroup;

	QTextCodec* tc;
	



};

/*並進ジョイントのパラメータ設定のページ*/

class SliderPage : public QWidget
{
public:
	SliderPage(int def_num = 0, QWidget *parent = 0);
	JointParam returnParam();
	void setParam(JointParam jp);
	QDoubleSpinBox *posxCombo;
	QDoubleSpinBox *posyCombo;
	QDoubleSpinBox *poszCombo;
	QDoubleSpinBox *axisxCombo;
	QDoubleSpinBox *axisyCombo;
	QDoubleSpinBox *axiszCombo;
	QDoubleSpinBox *ulimitHCombo;
	QDoubleSpinBox *ulimitLCombo;
	QDoubleSpinBox *uvlimitHCombo;
	QDoubleSpinBox *uvlimitLCombo;
	QDoubleSpinBox *rotorInertiaCombo;
	QDoubleSpinBox *rotorResistorCombo;
	QDoubleSpinBox *torqueConstCombo;
	QDoubleSpinBox *encoderPulseCombo;
	QComboBox *geomNameComboBox;
	QSpinBox *NumComboBox;

private:
	
	QLabel *geomNameLabel;
	
	QLabel *NumLabel;
	QGroupBox *NumGroup;
	QLabel *posxLabel;
	QLabel *posyLabel;
	QLabel *poszLabel;
	QLabel *axisxLabel;
	QLabel *axisyLabel;
	QLabel *axiszLabel;
	QLabel *ulimitHLabel;
	QLabel *ulimitLLabel;
	QLabel *uvlimitHLabel;
	QLabel *uvlimitLLabel;
	QLabel *rotorInertiaLabel;
	QLabel *rotorResistorLabel;
	QLabel *torqueConstLabel;
	QLabel *encoderPulseLabel;
	QGroupBox *NameGroup;
	QGroupBox *posGroup;
	QGroupBox *axisGroup;
	QGroupBox *anotherGroup;

	QTextCodec* tc;
	



};


/*固定ジョイントのパラメータ設定のページ*/

class FixPage : public QWidget
{
public:
	FixPage(int def_num = 0, QWidget *parent = 0);
	JointParam returnParam();
	void setParam(JointParam jp);
	QDoubleSpinBox *posxCombo;
	QDoubleSpinBox *posyCombo;
	QDoubleSpinBox *poszCombo;
	QComboBox *geomNameComboBox;
	QSpinBox *NumComboBox;

private:
	
	QLabel *geomNameLabel;
	
	QLabel *NumLabel;
	QGroupBox *NumGroup;
	QLabel *posxLabel;
	QLabel *posyLabel;
	QLabel *poszLabel;
	QGroupBox *NameGroup;
	QGroupBox *posGroup;
	
	QTextCodec* tc;

};

#endif