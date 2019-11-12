
#ifndef CAMERAPAGES_H
#define CAMERAPAGES_H

#include <QWidget>
#include "ObjectData.h"

/*カメラのパラメータ設定のページ*/

class CameraPage : public QWidget
{
public:
	CameraPage(int def_num = 0, QWidget *parent = 0);
	CameraParam returnParam();
	void setParam(CameraParam cp);

private:
	QComboBox *geomNameComboBox;
	QLabel *geomNameLabel;
	QSpinBox *NumComboBox;
	QSpinBox *IDComboBox;
	QLabel *NumLabel;
	QGroupBox *NumGroup;
	QLabel *posxLabel;
	QLabel *posyLabel;
	QLabel *poszLabel;
	QLabel *slxLabel;
	QLabel *slyLabel;
	QLabel *slzLabel;
	QLabel *fieldOfViewLabel;
	QLabel *frontClipDistanceLabel;
	QLabel *backClipDistanceLabel;
	QLabel *typeLabel;
	QLabel *widthLabel;
	QLabel *heightLabel;
	QLabel *IDLabel;
	QGroupBox *NameGroup;
	QGroupBox *posGroup;
	QGroupBox *geomGroup;
	QGroupBox *anotherGroup;
	QDoubleSpinBox *posxCombo;
	QDoubleSpinBox *posyCombo;
	QDoubleSpinBox *poszCombo;
	QDoubleSpinBox *slxCombo;
	QDoubleSpinBox *slyCombo;
	QDoubleSpinBox *slzCombo;
	QDoubleSpinBox *fieldOfViewCombo;
	QDoubleSpinBox *frontClipDistanceCombo;
	QDoubleSpinBox *backClipDistanceCombo;
	QComboBox *typeCombo;
	QDoubleSpinBox *widthCombo;
	QDoubleSpinBox *heightCombo;
	
	QTextCodec* tc;


};




#endif
