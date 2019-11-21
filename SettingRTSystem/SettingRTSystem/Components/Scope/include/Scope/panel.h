/*!
* @file  panel.h
* @brief 操作パネル
*
*/

#ifndef _PANEL_H_
#define _PANEL_H_ 1

//#include "settings.h"
#include "settings.h"
#include <QtWidgets>
#include <qtabwidget.h>

class QComboBox;
class QBoxLayout;
class QSpinBox;
class QDoubleSpinBox;
class QTextEdit;


/**
* @class Panel
*@brief 操作パネル
*/
class Panel: public QTabWidget
{
    Q_OBJECT

public:
	/**
	*@brief コンストラクタ
	* @param parent 親ウィジェット
	*/
	Panel( QWidget *parent = NULL );
	/**
	*@brief 設定取得
	* @return 設定オブジェクト
	*/
    Settings settings() const;
	/**
	*@brief 設定反映
	* @param s 設定オブジェクト
	*/
	void setSettings(const Settings &s);
	/**
	*@brief ラベル付ウィジェット作成
	* @param wd ウィジェット
	* @param layout ウィジェットを追加するレイアウト
	* @param name 表示する文字列
	*/
	void addWidgetWithLabel(QWidget *wd, QBoxLayout *layout, const char* name);

Q_SIGNALS:
	/**
	*@brief 設定変更時のシグナル
	* @param settings 設定オブジェクト
	*/
    void settingsChanged( const Settings &settings );

private Q_SLOTS:
	/**
	*@brief 設定変更時のスロット
	*/
    void edited();

protected:
	//void timerEvent(QTimerEvent * e);

private:
	/**
	*@brief 各種設定用タブを生成
	* @param parent 親ウィジェット
	*/
	QWidget *createPlotTab(QWidget *parent);


	QComboBox *d_dataType;
	QDoubleSpinBox *d_timeRange;
	QDoubleSpinBox *d_valueRange_low;
	QDoubleSpinBox *d_valueRange_high;
	QSpinBox *d_samplingNum;
	QLineEdit *d_XAxis;
	QLineEdit *d_YAxis;
	QSpinBox *d_max_pointNum;
	QDoubleSpinBox *d_samplingTime;
	QCheckBox *d_realTime;



	QTextCodec* tc;
};

#endif
