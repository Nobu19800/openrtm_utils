/*!
* @file  plot.h
* @brief プロット操作のクラス
*
*/

#ifndef _PLOT_H_
#define _PLOT_H_ 1

#include <qwt_plot.h>
#include <qwt_system_clock.h>
#include "settings.h"

class QwtPlotGrid;
class QwtPlotCurve;


/**
* @class Plot
*@brief プロット操作のクラス
*/
class Plot: public QwtPlot
{
    Q_OBJECT

public:
	/**
	*@brief コンストラクタ
	* @param parent 親ウィジェット
	*/
    Plot( QWidget* = NULL );

public Q_SLOTS:
	/**
	*@brief 設定変更時のスロット
	*/
    void setSettings( const Settings & );

protected:
	/**
	*@brief タイマーイベント
	* @param e イベントオブジェクト
	*/
    virtual void timerEvent( QTimerEvent *e );

private:
	/**
	*@brief 描画するデータ追加
	* @param num データ数
	* @param id データ名
	*/
	void setPlotCurve(int num, std::string id);
    QwtPlotGrid *d_grid;
    std::vector<QwtPlotCurve*> d_curve;

    QwtSystemClock d_clock;
    double d_interval;

    int d_timerId;
	double valueRange_low;
	double valueRange_high;
	double timeRange;
	std::string XAxisLabel;
	std::string YAxisLabel;
};

#endif
