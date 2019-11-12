/*!
* @file  settings.h
* @brief プロット関連の設定
*
*/

#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <QWidget>


/**
* @class Settings
*@brief プロット関連の設定
*/
class Settings
{
public:
	/**
	*@brief コンストラクタ
	*/
	Settings()
	{
		timeRange = 10;
		valueRange_low = -5;
		valueRange_high = 5;
		samplingNum = 1;
		XAxis = "X";
		YAxis = "Y";
		dataType = "TimedDouble";
		max_pointNum = 100;
		samplingTime = 0.01;
		realTime = false;
	};
	double timeRange;
	double valueRange_low;
	double valueRange_high;
	int samplingNum;
	QString XAxis;
	QString YAxis;
	QString dataType;
	int max_pointNum;
	double samplingTime;
	bool realTime;
};

#endif
