/*!
* @file  plot.cpp
* @brief プロット操作のクラス
*
*/

#include <qglobal.h>
#include <qwt_painter.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_grid.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_layout.h>
#include <qwt_scale_widget.h>
#include <qwt_scale_draw.h>

#include <coil/stringutil.h>

#include <iostream>
#include <stdio.h>
#include <time.h>
#include "plot.h"


#include "Scope.h"


/**
*@brief プロット操作のクラスのコンストラクタ
* @param parent 親ウィジェット
*/
Plot::Plot( QWidget *parent ):
    QwtPlot( parent ),
    d_interval( 10.0 ), // seconds
    d_timerId( -1 )
{
    // Assign a title
    //setTitle( "Testing Refresh Rates" );

    QwtPlotCanvas *canvas = new QwtPlotCanvas();
    canvas->setFrameStyle( QFrame::Box | QFrame::Plain );
    canvas->setLineWidth( 1 );
    canvas->setPalette( Qt::white );

    setCanvas( canvas );

    //alignScales();

    //QPen pen = Qt::black;
    // Insert grid
    d_grid = new QwtPlotGrid();
    d_grid->attach( this );
	
	srand((unsigned int)time(NULL));

   

    // Axis
    //setAxisTitle( QwtPlot::xBottom, "Seconds" );
    setAxisScale( QwtPlot::xBottom, -d_interval, 0.0 );

    //setAxisTitle( QwtPlot::yLeft, "Values" );
    setAxisScale( QwtPlot::yLeft, -1.0, 1.0 );

    d_clock.start();
    d_timerId = startTimer( 10 );
    	

    //d_grid->setVisible( s.grid.pen.style() != Qt::NoPen );
	QwtScaleDiv x(0.0, 10.0);
	QwtScaleDiv y(0.0, 10.0);
	d_grid->setXDiv(x);
	d_grid->setYDiv(x);

	this->setAxisScale(QwtPlot::yLeft, -5, 5);
	this->setAxisScale(QwtPlot::xBottom, 0, 10);
	

 }


void Plot::setPlotCurve(int num, std::string id)
{
	if (num > d_curve.size())
	{
		for (int i = d_curve.size(); i < num; i++)
		{
			std::string name = id + coil::otos<int>(i);

			QwtPlotCurve *t_curve = new QwtPlotCurve(name.c_str());
			if (i % 4 == 0)
			{
				t_curve->setPen(QColor(255, i * 10, i * 10));
			}
			else if (i % 4 == 1)
			{
				t_curve->setPen(QColor(i * 10, 255, i * 10));
			}
			else if (i % 4 == 2)
			{
				t_curve->setPen(QColor(i * 10, i * 10, 255));
			}
			else
			{
				t_curve->setPen(QColor(i * 10, i * 10, i * 10));
			}

			t_curve->attach(this);
			d_curve.push_back(t_curve);
		}

	}
	else if (num < d_curve.size())
	{
		for (std::vector<QwtPlotCurve*>::iterator it = d_curve.begin() + num; it != d_curve.end();)
		{
			delete *it;
			it = d_curve.erase(it);
		}
	}
	//coil::otos<int>(i);


	//d_curve->setData( new CircularBuffer( d_interval, 10 ) );


}



/**
*@brief 設定変更時のスロット
*/
void Plot::setSettings( const Settings &s )
{
	if (Scope::obj)
	{
		const char *name = s.dataType.toLocal8Bit();
		//Scope::obj->setDataPort(name);
		Scope::obj->setConfigParam_Name("dataType", name);
		//Scope::obj->setMaxPointNum(s.max_pointNum);
		//Scope::obj->setSamplingNum(s.samplingNum);
		Scope::obj->setConfigParam_Name("max_pointNum", coil::otos<int>(s.max_pointNum));
		Scope::obj->setConfigParam_Name("samplingNum", coil::otos<int>(s.samplingNum));

		//setAxisTitle(QwtPlot::xBottom, s.XAxis);
		//setAxisTitle(QwtPlot::yLeft, s.YAxis);

		Scope::obj->setConfigParam_Name("XAxis", (const char*)s.XAxis.toLocal8Bit());
		Scope::obj->setConfigParam_Name("YAxis", (const char*)s.YAxis.toLocal8Bit());

		valueRange_low = s.valueRange_low;
		valueRange_high = s.valueRange_high;

		Scope::obj->setConfigParam_Name("valueRange_low", coil::otos<double>(s.valueRange_low));
		Scope::obj->setConfigParam_Name("valueRange_high", coil::otos<double>(s.valueRange_high));

		timeRange = s.timeRange;
		this->setAxisScale(QwtPlot::xBottom, 0, timeRange);
		Scope::obj->setConfigParam_Name("timeRange", coil::otos<double>(s.timeRange));

		Scope::obj->setConfigParam_Name("samplingTime", coil::otos<double>(s.samplingTime));
		if (s.realTime)
		{
			Scope::obj->setConfigParam_Name("realTime", "ON");
		}
		else
		{
			Scope::obj->setConfigParam_Name("realTime", "OFF");
		}
		

		this->setAxisScale(QwtPlot::yLeft, valueRange_low, valueRange_high);
	}
}

/**
*@brief タイマーイベント
* @param e イベントオブジェクト
*/
void Plot::timerEvent( QTimerEvent * )
{
	double maxXValue = timeRange;
	double maxYValue = valueRange_high;
	double minYValue = valueRange_low;
	if (Scope::obj)
	{
		maxXValue = Scope::obj->getTimeRange();
		timeRange = Scope::obj->getTimeRange();
		maxYValue = Scope::obj->getValueRange_high();
		valueRange_high = Scope::obj->getValueRange_high();
		minYValue = Scope::obj->getValueRange_low();
		valueRange_low = Scope::obj->getValueRange_low();
		if (XAxisLabel != Scope::obj->getXAxis())
		{
			XAxisLabel = Scope::obj->getXAxis();
			setAxisTitle(QwtPlot::xBottom, XAxisLabel.c_str());
		}
		if (YAxisLabel != Scope::obj->getYAxis())
		{
			YAxisLabel = Scope::obj->getYAxis();
			setAxisTitle(QwtPlot::yLeft, YAxisLabel.c_str());
		}
		if (Scope::obj->update())
		{
			std::vector<QVector<QPointF>> vlist = Scope::obj->getPointList();
			setPlotCurve((int)vlist.size(),"data");
			for (int i = 0; i < d_curve.size(); i++)
			{
				d_curve[i]->setSamples(vlist[i]);
				for (QVector<QPointF>::iterator it = vlist[i].begin(); it != vlist[i].end(); ++it)
				{
					//std::cout << (double)(*it).x() << std::endl;
					if (maxXValue < (double)(*it).x())
						maxXValue = (double)(*it).x();
					if (maxYValue < (double)(*it).y())
						maxYValue = (double)(*it).y();
					if (minYValue > (double)(*it).y())
						minYValue = (double)(*it).y();
				}
			}
			//std::cout << maxXValue << std::endl;
			this->setAxisScale(QwtPlot::xBottom, maxXValue - timeRange, maxXValue);
			this->setAxisScale(QwtPlot::yLeft, minYValue, maxYValue);
		}
	}
	
	

	replot();
}
