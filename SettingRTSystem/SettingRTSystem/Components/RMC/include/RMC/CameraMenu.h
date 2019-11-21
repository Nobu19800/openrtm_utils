
#ifndef CAMERADIALOG_H
#define CAMERADIALOG_H


#include <QDialog>
#include <QtGui>
#include "Camera.h"
#include "Camerapages.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QTextEdit;
class QToolButton;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE



/*カメラのパラメータ設定ダイアログ*/


class CameraDialog : public QDialog
{
    Q_OBJECT

public:
    CameraDialog(QWidget *parent = 0);
	bool ReturnFLAG();
	CameraParam returnParam();
	void SetParam(CameraParam cp);

private slots:
    void help();
    void update();
	void createitems();

private:
	CameraType myCamera;

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
	CameraPage *camerapage;
	bool Flag;

	QTextCodec* tc;
	CameraParam m_cp;
};


#endif
