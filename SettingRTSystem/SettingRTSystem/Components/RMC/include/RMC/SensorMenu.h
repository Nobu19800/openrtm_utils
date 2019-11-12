
#ifndef SENSORDIALOG_H
#define SENSORDIALOG_H


#include <QDialog>
#include <QtGui>
#include "Sensorpages.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QTextEdit;
class QToolButton;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE




/*センサーパラメータ設定のダイアログ*/

class SensorDialog : public QDialog
{
    Q_OBJECT

public:
    SensorDialog(QWidget *parent = 0);
	bool ReturnFLAG();
	SensorParam returnParam();
	void SetParam(SensorParam sp);


private slots:
    void help();
    void update();
	void createitems();

private:
	SensorType mySensor;

    void createButtons();
    void createComboBoxes();
    void createLabels();
    void createLayout();
	QVBoxLayout *mainLayout;


    QComboBox *BodyComboBox;
    QComboBox *fileNameComboBox;

    QLabel *BodyLabel;
    QLabel *fileNameLabel;

    QDialogButtonBox *buttonBox;

	QPushButton *closeButton;
    QPushButton *helpButton;
    QPushButton *createButton;
	QHBoxLayout *fileLayout;
	QStackedWidget *pagesWidget;
	SensorPage *sensorpage;
	bool Flag;
	SensorParam m_sp;
	QTextCodec* tc;

};


#endif
