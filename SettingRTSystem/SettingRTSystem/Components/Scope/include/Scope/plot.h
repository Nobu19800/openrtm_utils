/*!
* @file  plot.h
* @brief �v���b�g����̃N���X
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
*@brief �v���b�g����̃N���X
*/
class Plot: public QwtPlot
{
    Q_OBJECT

public:
	/**
	*@brief �R���X�g���N�^
	* @param parent �e�E�B�W�F�b�g
	*/
    Plot( QWidget* = NULL );

public Q_SLOTS:
	/**
	*@brief �ݒ�ύX���̃X���b�g
	*/
    void setSettings( const Settings & );

protected:
	/**
	*@brief �^�C�}�[�C�x���g
	* @param e �C�x���g�I�u�W�F�N�g
	*/
    virtual void timerEvent( QTimerEvent *e );

private:
	/**
	*@brief �`�悷��f�[�^�ǉ�
	* @param num �f�[�^��
	* @param id �f�[�^��
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
