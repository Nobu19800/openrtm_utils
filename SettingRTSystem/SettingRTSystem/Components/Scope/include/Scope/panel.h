/*!
* @file  panel.h
* @brief ����p�l��
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
*@brief ����p�l��
*/
class Panel: public QTabWidget
{
    Q_OBJECT

public:
	/**
	*@brief �R���X�g���N�^
	* @param parent �e�E�B�W�F�b�g
	*/
	Panel( QWidget *parent = NULL );
	/**
	*@brief �ݒ�擾
	* @return �ݒ�I�u�W�F�N�g
	*/
    Settings settings() const;
	/**
	*@brief �ݒ蔽�f
	* @param s �ݒ�I�u�W�F�N�g
	*/
	void setSettings(const Settings &s);
	/**
	*@brief ���x���t�E�B�W�F�b�g�쐬
	* @param wd �E�B�W�F�b�g
	* @param layout �E�B�W�F�b�g��ǉ����郌�C�A�E�g
	* @param name �\�����镶����
	*/
	void addWidgetWithLabel(QWidget *wd, QBoxLayout *layout, const char* name);

Q_SIGNALS:
	/**
	*@brief �ݒ�ύX���̃V�O�i��
	* @param settings �ݒ�I�u�W�F�N�g
	*/
    void settingsChanged( const Settings &settings );

private Q_SLOTS:
	/**
	*@brief �ݒ�ύX���̃X���b�g
	*/
    void edited();

protected:
	//void timerEvent(QTimerEvent * e);

private:
	/**
	*@brief �e��ݒ�p�^�u�𐶐�
	* @param parent �e�E�B�W�F�b�g
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
