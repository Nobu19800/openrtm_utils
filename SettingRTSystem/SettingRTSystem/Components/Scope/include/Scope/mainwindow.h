/*!
* @file  mainwindow.h
* @brief ���C���E�C���h�E
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
*@brief ���C���E�C���h�E
*/
class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
	/**
	*@brief �R���X�g���N�^
	* @param parent �e�E�B�W�F�b�g
	*/
    MainWindow( QWidget *parent = NULL );
    //virtual bool eventFilter( QObject *, QEvent * );

private Q_SLOTS:
	/**
	*@brief �ݒ蔽�f���̃X���b�g
	* @param settings �ݒ�I�u�W�F�N�g
	*/
	void applySettings(const Settings &settings);

private:
    Plot *d_plot;
    Panel *d_panel;
    QLabel *d_frameCount;
};

#endif
