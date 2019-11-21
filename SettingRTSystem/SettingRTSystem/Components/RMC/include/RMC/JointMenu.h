
#ifndef JOINTMENU_H
#define JOINTMENU_H


#include <QDialog>
#include <QtGui>
#include "Jointpages.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QTextEdit;
class QToolButton;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE


/*ジョイントのパラメータ設定ダイアログ*/

class ActDialog : public QDialog
{
    Q_OBJECT

public:
    ActDialog(QWidget *parent = 0);
	bool ReturnFLAG();
	JointParam returnParam();
	void SetParam(JointParam jp);
	JointParam m_jp;

private slots:
    void help();
    void update();
	void createitems();

private:
	JointType myGeom;


    void createButtons();
    void createComboBoxes();

    void createLabels();
    void createLayout();
	QVBoxLayout *mainLayout;



    QComboBox *JointComboBox;
    QComboBox *fileNameComboBox;

    QLabel *JointLabel;
    QLabel *fileNameLabel;

    QDialogButtonBox *buttonBox;

	QPushButton *closeButton;
    QPushButton *helpButton;
    QPushButton *createButton;
	QHBoxLayout *fileLayout;
	QStackedWidget *pagesWidget;
	HingePage *hingepage;
	SliderPage *sliderpage;
	FixPage *fixpage;
	bool Flag;

	QTextCodec* tc;

};


#endif
