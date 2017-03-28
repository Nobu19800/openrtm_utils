/*!
* @file  mainwindow.cpp
* @brief ���C���E�C���h�E
*
*/


#include <qstatusbar.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qevent.h>
#include <qdatetime.h>
#include <qwt_plot_canvas.h>
#include "panel.h"
#include "plot.h"
#include "mainwindow.h"


/**
*@brief ���C���E�C���h�E�̃R���X�g���N�^
* @param parent �e�E�B�W�F�b�g
*/
MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent )
{
    QWidget *w = new QWidget( this );

    d_panel = new Panel( w );

    d_plot = new Plot( w );

    QHBoxLayout *hLayout = new QHBoxLayout( w );
    hLayout->addWidget( d_panel );
    hLayout->addWidget( d_plot, 10 );

    setCentralWidget( w );

    d_frameCount = new QLabel( this );
    statusBar()->addWidget( d_frameCount, 10 );

    //applySettings( d_panel->settings() );

    connect( d_panel, SIGNAL( settingsChanged( const Settings & ) ),
        this, SLOT( applySettings( const Settings & ) ) );
}

/**
*@brief �ݒ蔽�f���̃X���b�g
* @param settings �ݒ�I�u�W�F�N�g
*/
void MainWindow::applySettings( const Settings &settings )
{
    d_plot->setSettings( settings );

    // the canvas might have been recreated
    d_plot->canvas()->removeEventFilter( this );
    d_plot->canvas()->installEventFilter( this );
}
