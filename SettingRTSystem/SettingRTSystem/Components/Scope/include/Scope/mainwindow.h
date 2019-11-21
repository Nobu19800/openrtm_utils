/*!
* @file  mainwindow.h
* @brief メインウインドウ
*
*/

#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <qmainwindow.h>
#include "settings.h"

class Plot;
class Panel;
class QLabel;
//class Settings;

/**
* @class MainWindow
*@brief メインウインドウ
*/
class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
	/**
	*@brief コンストラクタ
	* @param parent 親ウィジェット
	*/
    MainWindow( QWidget *parent = NULL );
    //virtual bool eventFilter( QObject *, QEvent * );

private Q_SLOTS:
	/**
	*@brief 設定反映時のスロット
	* @param settings 設定オブジェクト
	*/
	void applySettings(const Settings &settings);

private:
    Plot *d_plot;
    Panel *d_panel;
    QLabel *d_frameCount;
};

#endif
