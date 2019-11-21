/*!
* @file  panel.cpp
* @brief 操作パネル
*
*/

#include "panel.h"

#include <qlabel.h>
#include <qcombobox.h>
#include <qspinbox.h>
#include <qcheckbox.h>
#include <qlayout.h>
#include <qwt_plot_curve.h>

#include <iostream>


/**
*@brief 操作パネルのコンストラクタ
* @param parent 親ウィジェット
*/
Panel::Panel( QWidget *parent ):
    QTabWidget( parent )
{
    setTabPosition( QTabWidget::West );
	tc = QTextCodec::codecForLocale();
    addTab( createPlotTab( this ), "Plot" );



    setSettings( Settings() );
	connect(d_dataType, SIGNAL(currentIndexChanged(int)), SLOT(edited()));
	connect(d_timeRange, SIGNAL(valueChanged(double)), SLOT(edited()));
	connect(d_valueRange_low, SIGNAL(valueChanged(double)), SLOT(edited()));
	connect(d_valueRange_high, SIGNAL(valueChanged(double)), SLOT(edited()));
	connect(d_samplingNum, SIGNAL(valueChanged(int)), SLOT(edited()));
	connect(d_max_pointNum, SIGNAL(valueChanged(int)), SLOT(edited()));
	connect(d_XAxis, SIGNAL(textChanged(QString)), SLOT(edited()));
	connect(d_YAxis, SIGNAL(textChanged(QString)), SLOT(edited()));
	connect(d_samplingTime, SIGNAL(valueChanged(double)), SLOT(edited()));
	connect(d_realTime, SIGNAL(toggled(bool)), SLOT(edited()));
	//startTimer(1000);

    /*connect( d_numPoints, SIGNAL( valueChanged( int ) ), SLOT( edited() ) );
    connect( d_updateInterval, SIGNAL( valueChanged( int ) ), SLOT( edited() ) );
    connect( d_curveWidth, SIGNAL( valueChanged( int ) ), SLOT( edited() ) );

    connect( d_paintCache, SIGNAL( stateChanged( int ) ), SLOT( edited() ) );
    connect( d_paintOnScreen, SIGNAL( stateChanged( int ) ), SLOT( edited() ) );
    connect( d_immediatePaint, SIGNAL( stateChanged( int ) ), SLOT( edited() ) );


    connect( d_curveAntialiasing, SIGNAL( stateChanged( int ) ), SLOT( edited() ) );
    connect( d_curveClipping, SIGNAL( stateChanged( int ) ), SLOT( edited() ) );
    connect( d_curveFiltering, SIGNAL( stateChanged( int ) ), SLOT( edited() ) );
    connect( d_lineSplitting, SIGNAL( stateChanged( int ) ), SLOT( edited() ) );
    connect( d_curveFilled, SIGNAL( stateChanged( int ) ), SLOT( edited() ) );

    connect( d_updateType, SIGNAL( currentIndexChanged( int ) ), SLOT( edited() ) );
    connect( d_gridStyle, SIGNAL( currentIndexChanged( int ) ), SLOT( edited() ) );
    connect( d_curveType, SIGNAL( currentIndexChanged( int ) ), SLOT( edited() ) );
    connect( d_curvePen, SIGNAL( currentIndexChanged( int ) ), SLOT( edited() ) );*/
}

/**
*@brief ラベル付ウィジェット作成
* @param wd ウィジェット
* @param layout ウィジェットを追加するレイアウト
* @param name 表示する文字列
*/
void Panel::addWidgetWithLabel(QWidget *wd, QBoxLayout *layout, const char* name)
{
	QHBoxLayout *subLayout = new QHBoxLayout();
	layout->addLayout(subLayout);
	subLayout->addWidget(new QLabel(tc->toUnicode(name)));
	subLayout->addWidget(wd);
};

/*void Panel::timerEvent(QTimerEvent * e)
{
	
}*/

/**
*@brief 各種設定用タブを生成
* @param parent 親ウィジェット
*/
QWidget *Panel::createPlotTab( QWidget *parent )
{
    QWidget *page = new QWidget( parent );

    /*d_updateInterval = new SpinBox( 0, 1000, 10, page );
    d_numPoints = new SpinBox( 10, 1000000, 1000, page );

    d_updateType = new QComboBox( page );
    d_updateType->addItem( "Repaint" );
    d_updateType->addItem( "Replot" );
	*/
    int row = 0;
	
	QVBoxLayout *layout = new QVBoxLayout(page);
	/*
    layout->addWidget( new QLabel( "Updates", page ), row, 0 );
    layout->addWidget( d_updateInterval, row, 1 );
    layout->addWidget( new QLabel( "ms", page ), row++, 2 );

    layout->addWidget( new QLabel( "Points", page ), row, 0 );
    layout->addWidget( d_numPoints, row++, 1 );

    layout->addWidget( new QLabel( "Update", page ), row, 0 );
    layout->addWidget( d_updateType, row++, 1 );

    layout->addLayout( new QHBoxLayout(), row++, 0 );
	*/
	
	d_dataType = new QComboBox(page);
	

	addWidgetWithLabel(d_dataType, layout, "データ型");

	d_dataType->addItem("TimedDouble");
	d_dataType->addItem("TimedLong");
	d_dataType->addItem("TimedFloat");
	d_dataType->addItem("TimedShort");
	d_dataType->addItem("TimedULong");
	d_dataType->addItem("TimedUShort");
	d_dataType->addItem("TimedDoubleSeq");
	d_dataType->addItem("TimedLongSeq");
	d_dataType->addItem("TimedFloatSeq");
	d_dataType->addItem("TimedShortSeq");
	d_dataType->addItem("TimedULongSeq");
	d_dataType->addItem("TimedUShortSeq");
    //layout->setColumnStretch( 1, 10 );
    //layout->setRowStretch( row, 10 );

	d_timeRange = new QDoubleSpinBox();
	addWidgetWithLabel(d_timeRange, layout, "X軸データ範囲");
	d_timeRange->setValue(10);
	d_timeRange->setRange(0.01, 1000);
	d_timeRange->setSingleStep(1);

	d_valueRange_high = new QDoubleSpinBox();
	addWidgetWithLabel(d_valueRange_high, layout, "Y軸データ範囲(上限)");
	d_valueRange_high->setValue(5);
	d_valueRange_high->setRange(-1000, 1000);
	d_valueRange_high->setSingleStep(1);

	d_valueRange_low = new QDoubleSpinBox();
	addWidgetWithLabel(d_valueRange_low, layout, "Y軸データ範囲(下限)");
	d_valueRange_low->setValue(-5);
	d_valueRange_low->setRange(-1000, 1000);
	d_valueRange_low->setSingleStep(1);

	d_samplingNum = new QSpinBox();
	addWidgetWithLabel(d_samplingNum, layout, "間引き");
	d_samplingNum->setValue(1);
	d_samplingNum->setRange(1, 1000);

	d_XAxis = new QLineEdit();
	addWidgetWithLabel(d_XAxis, layout, "X軸ラベル");

	d_YAxis = new QLineEdit();
	addWidgetWithLabel(d_YAxis, layout, "Y軸ラベル");
	
	d_max_pointNum = new QSpinBox();
	addWidgetWithLabel(d_max_pointNum, layout, "表示する点の最大の数");
	d_max_pointNum->setValue(100);
	d_max_pointNum->setRange(1, 10000);

	d_samplingTime = new QDoubleSpinBox();
	addWidgetWithLabel(d_samplingTime, layout, "ステップ幅[ms]");
	d_samplingTime->setValue(10);
	d_samplingTime->setRange(0, 10000);
	//d_samplingTime->setSingleStep(1);

	d_realTime = new QCheckBox();
	addWidgetWithLabel(d_realTime, layout, "実時間");
	d_realTime->setCheckable(true);

    return page;
}


/**
*@brief 設定変更時のスロット
*/
void Panel::edited()
{
    const Settings s = settings();
    Q_EMIT settingsChanged( s );
}

/**
*@brief 設定取得
* @return 設定オブジェクト
*/
Settings Panel::settings() const
{
    Settings s;

    
	s.dataType = d_dataType->itemText(d_dataType->currentIndex());
	s.valueRange_high = d_valueRange_high->value();
	s.valueRange_low = d_valueRange_low->value();
	s.timeRange = d_timeRange->value();
	s.samplingNum = d_samplingNum->value();
	s.XAxis = d_XAxis->text();
	s.YAxis = d_YAxis->text();
	s.max_pointNum = d_max_pointNum->value();
	s.samplingTime = d_samplingTime->value()/1000.0;
	s.realTime = d_realTime->isChecked();
    return s;
}

/**
*@brief 設定反映
* @param s 設定オブジェクト
*/
void Panel::setSettings( const Settings &s )
{
	d_dataType->setCurrentText(s.dataType);
	d_timeRange->setValue(s.timeRange);
	d_valueRange_high->setValue(s.valueRange_high);
	d_valueRange_low->setValue(s.valueRange_low);
	d_samplingNum->setValue(s.samplingNum);
	d_XAxis->setText(s.XAxis);
	d_YAxis->setText(s.YAxis);
	d_max_pointNum->setValue(s.max_pointNum);
	d_samplingTime->setValue(s.samplingTime*1000.0);
	d_realTime->setChecked(s.realTime);
	/*
    d_numPoints->setValue( s.curve.numPoints );
    d_updateInterval->setValue( s.updateInterval );
    d_updateType->setCurrentIndex( s.updateType );

    switch( s.grid.pen.style() )
    {
        case Qt::NoPen:
        {
            d_gridStyle->setCurrentIndex( 0 );
            break;
        }
        case Qt::DashLine:
        {
            d_gridStyle->setCurrentIndex( 2 );
            break;
        }
        default:
        {
            d_gridStyle->setCurrentIndex( 1 ); // Solid
        }
    }

    d_paintCache->setChecked( s.canvas.useBackingStore );
    d_paintOnScreen->setChecked( s.canvas.paintOnScreen );
    d_immediatePaint->setChecked( s.canvas.immediatePaint );


    d_curveType->setCurrentIndex( s.curve.functionType );
    d_curveAntialiasing->setChecked(
        s.curve.renderHint & QwtPlotCurve::RenderAntialiased );

    d_curveClipping->setChecked(
        s.curve.paintAttributes & QwtPlotCurve::ClipPolygons );
    d_curveFiltering->setChecked(
        s.curve.paintAttributes & QwtPlotCurve::FilterPoints );

    d_lineSplitting->setChecked( s.curve.lineSplitting );

    d_curveWidth->setValue( s.curve.pen.width() );
    d_curvePen->setCurrentIndex(
        s.curve.pen.style() == Qt::SolidLine ? 0 : 1 );
    d_curveFilled->setChecked( s.curve.brush.style() != Qt::NoBrush );
	*/
}
