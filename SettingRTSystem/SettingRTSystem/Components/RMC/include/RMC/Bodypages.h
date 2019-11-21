
#ifndef BODYPAGES_H
#define BODYPAGES_H

#include <QWidget>

#include "ObjectData.h"
#include "glbox.h"


/*立方体のパラメータ設定ページ*/

class BoxPage : public QWidget
{
public:
    BoxPage(int def_num=0, QWidget *parent = 0);
	BodyParam returnParam();
	void setParam(BodyParam Param);


	QDoubleSpinBox *posxCombo;
	QDoubleSpinBox *posyCombo;
	QDoubleSpinBox *poszCombo;
	QDoubleSpinBox *lengthCombo;
	QDoubleSpinBox *widthCombo;
	QDoubleSpinBox *heightCombo;
	QDoubleSpinBox *MassCombo;
	QDoubleSpinBox *RedCombo;
	QDoubleSpinBox *BlueCombo;
	QDoubleSpinBox *GreenCombo;
	QDoubleSpinBox *slxCombo;
	QDoubleSpinBox *slyCombo;
	QDoubleSpinBox *slzCombo;
	QDoubleSpinBox *I1Combo;
	QDoubleSpinBox *I2Combo;
	QDoubleSpinBox *I3Combo;
	QDoubleSpinBox *I4Combo;
	QDoubleSpinBox *I5Combo;
	QDoubleSpinBox *I6Combo;
	QDoubleSpinBox *I7Combo;
	QDoubleSpinBox *I8Combo;
	QDoubleSpinBox *I9Combo;
	QComboBox *geomNameComboBox;
	QSpinBox *NumComboBox;

private:
	
	QLabel *geomNameLabel;
	
	QLabel *NumLabel;
	QGroupBox *NumGroup;
	QLabel *posxLabel;
	QLabel *posyLabel;
	QLabel *poszLabel;
	QLabel *lengthLabel;
	QLabel *widthLabel;
	QLabel *heightLabel;
	QLabel *slxLabel;
	QLabel *slyLabel;
	QLabel *slzLabel;
	QLabel *MassLabel;
	QLabel *RedLabel;
	QLabel *BlueLabel;
	QLabel *GreenLabel;
	QGroupBox *NameGroup;
	QGroupBox *posGroup;
	QGroupBox *geomGroup;
	QGroupBox *anotherGroup;
	QGroupBox *IGroup;
	QGroupBox *ColorGroup;

	
	QTextCodec* tc;


};


/*球のパラメータ設定ページ*/

class SpherePage : public QWidget
{
public:
	SpherePage(int def_num = 0, QWidget *parent = 0);
	BodyParam returnParam();
	void setParam(BodyParam bp);
	QDoubleSpinBox *posxCombo;
	QDoubleSpinBox *posyCombo;
	QDoubleSpinBox *poszCombo;
	QDoubleSpinBox *radCombo;
	QDoubleSpinBox *MassCombo;
	QDoubleSpinBox *RedCombo;
	QDoubleSpinBox *BlueCombo;
	QDoubleSpinBox *GreenCombo;
	QDoubleSpinBox *I1Combo;
	QDoubleSpinBox *I2Combo;
	QDoubleSpinBox *I3Combo;
	QDoubleSpinBox *I4Combo;
	QDoubleSpinBox *I5Combo;
	QDoubleSpinBox *I6Combo;
	QDoubleSpinBox *I7Combo;
	QDoubleSpinBox *I8Combo;
	QDoubleSpinBox *I9Combo;
	QComboBox *geomNameComboBox;
	QSpinBox *NumComboBox;

private:
	
	QLabel *geomNameLabel;
	
	QLabel *NumLabel;
	QGroupBox *NumGroup;
	QLabel *posxLabel;
	QLabel *posyLabel;
	QLabel *poszLabel;
	QLabel *radLabel;
	QLabel *MassLabel;
	QLabel *RedLabel;
	QLabel *BlueLabel;
	QLabel *GreenLabel;
	QGroupBox *NameGroup;
	QGroupBox *posGroup;
	QGroupBox *geomGroup;
	QGroupBox *anotherGroup;
	QGroupBox *ColorGroup;
	QGroupBox *IGroup;
	QTextCodec* tc;
};


/*円柱のパラメータ設定ページ*/

class CylinderPage : public QWidget
{
public:
	CylinderPage(int def_num = 0, QWidget *parent = 0);
	BodyParam returnParam();
	void setParam(BodyParam Param);
	QDoubleSpinBox *posxCombo;
	QDoubleSpinBox *posyCombo;
	QDoubleSpinBox *poszCombo;
	QDoubleSpinBox *lengthCombo;
	QDoubleSpinBox *radCombo;
	QComboBox *axisCombo;
	QDoubleSpinBox *MassCombo;
	QDoubleSpinBox *RedCombo;
	QDoubleSpinBox *BlueCombo;
	QDoubleSpinBox *GreenCombo;
	QDoubleSpinBox *slxCombo;
	QDoubleSpinBox *slyCombo;
	QDoubleSpinBox *slzCombo;
	QDoubleSpinBox *I1Combo;
	QDoubleSpinBox *I2Combo;
	QDoubleSpinBox *I3Combo;
	QDoubleSpinBox *I4Combo;
	QDoubleSpinBox *I5Combo;
	QDoubleSpinBox *I6Combo;
	QDoubleSpinBox *I7Combo;
	QDoubleSpinBox *I8Combo;
	QDoubleSpinBox *I9Combo;
	QComboBox *geomNameComboBox;
	QSpinBox *NumComboBox;

private:
	
	QLabel *geomNameLabel;
	
	QLabel *NumLabel;
	QGroupBox *NumGroup;
	QLabel *posxLabel;
	QLabel *posyLabel;
	QLabel *poszLabel;
	QLabel *radLabel;
	QLabel *lengthLabel;
	QLabel *axisLabel;
	QLabel *slxLabel;
	QLabel *slyLabel;
	QLabel *slzLabel;
	QLabel *MassLabel;
	QLabel *RedLabel;
	QLabel *BlueLabel;
	QLabel *GreenLabel;
	QGroupBox *NameGroup;
	QGroupBox *posGroup;
	QGroupBox *geomGroup;
	QGroupBox *anotherGroup;
	QGroupBox *IGroup;
	QGroupBox *ColorGroup;
	QTextCodec* tc;
};


/*円錐のパラメータ設定ページ*/

class ConePage : public QWidget
{
public:
	ConePage(int def_num = 0, QWidget *parent = 0);
	BodyParam returnParam();
	void setParam(BodyParam bp);
	QDoubleSpinBox *posxCombo;
	QDoubleSpinBox *posyCombo;
	QDoubleSpinBox *poszCombo;
	QDoubleSpinBox *lengthCombo;
	QDoubleSpinBox *radCombo;
	QComboBox *axisCombo;
	QDoubleSpinBox *MassCombo;
	QDoubleSpinBox *RedCombo;
	QDoubleSpinBox *BlueCombo;
	QDoubleSpinBox *GreenCombo;
	QDoubleSpinBox *slxCombo;
	QDoubleSpinBox *slyCombo;
	QDoubleSpinBox *slzCombo;
	QDoubleSpinBox *I1Combo;
	QDoubleSpinBox *I2Combo;
	QDoubleSpinBox *I3Combo;
	QDoubleSpinBox *I4Combo;
	QDoubleSpinBox *I5Combo;
	QDoubleSpinBox *I6Combo;
	QDoubleSpinBox *I7Combo;
	QDoubleSpinBox *I8Combo;
	QDoubleSpinBox *I9Combo;
	QComboBox *geomNameComboBox;
	QSpinBox *NumComboBox;


private:
	
	QLabel *geomNameLabel;

	QLabel *NumLabel;
	QGroupBox *NumGroup;
	QLabel *posxLabel;
	QLabel *posyLabel;
	QLabel *poszLabel;
	QLabel *radLabel;
	QLabel *lengthLabel;
	QLabel *axisLabel;
	QLabel *slxLabel;
	QLabel *slyLabel;
	QLabel *slzLabel;
	QLabel *MassLabel;
	QLabel *RedLabel;
	QLabel *BlueLabel;
	QLabel *GreenLabel;
	QGroupBox *NameGroup;
	QGroupBox *posGroup;
	QGroupBox *geomGroup;
	QGroupBox *anotherGroup;
	QGroupBox *IGroup;
	QGroupBox *ColorGroup;
	QTextCodec* tc;

};


/*ポリゴンのパラメータ設定ページ*/

class PolygonPage : public QWidget
{
public:
	PolygonPage(int def_num = 0, QWidget *parent = 0);
	BodyParam returnParam();
	void setParam(BodyParam bp);
	QDoubleSpinBox *posxCombo;
	QDoubleSpinBox *posyCombo;
	QDoubleSpinBox *poszCombo;
	QDoubleSpinBox *MassCombo;
	QDoubleSpinBox *slxCombo;
	QDoubleSpinBox *slyCombo;
	QDoubleSpinBox *slzCombo;
	QDoubleSpinBox *I1Combo;
	QDoubleSpinBox *I2Combo;
	QDoubleSpinBox *I3Combo;
	QDoubleSpinBox *I4Combo;
	QDoubleSpinBox *I5Combo;
	QDoubleSpinBox *I6Combo;
	QDoubleSpinBox *I7Combo;
	QDoubleSpinBox *I8Combo;
	QDoubleSpinBox *I9Combo;
	QComboBox *geomNameComboBox;
	QSpinBox *NumComboBox;
	PolygonData m_pd;

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
	QLabel *MassLabel;
	QGroupBox *NameGroup;
	QGroupBox *posGroup;
	QGroupBox *geomGroup;
	QGroupBox *anotherGroup;
	QGroupBox *IGroup;
	PolygonData m_polygon;
	QTextCodec* tc;




};

#endif
