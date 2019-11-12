
#ifndef BODYDIALOG_H
#define BODYDIALOG_H


#include <QDialog>
#include <QtGui>
#include "ObjectData.h"
#include "Bodypages.h"

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QTextEdit;
class QToolButton;
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE



/*ボディのパラメータ設定ダイアログ*/


class BodyDialog : public QDialog
{
    Q_OBJECT

public:
    BodyDialog(QWidget *parent = 0);
	bool ReturnFLAG();
	BodyParam returnParam();
	int ReturnGeom();
	void SetParam(BodyParam bd);
	PolygonData m_Polygon;
	int BT;

private slots:
    void help();
    void update();
	void createitems();
	void FileLoad();

private:
	GeomType myGeom;

    void createButtons();
    void createComboBoxes();
    void createLabels();
    void createLayout();
	QVBoxLayout *mainLayout;
	void loadFile(const QString &fileName);


    QComboBox *BodyComboBox;
    QComboBox *fileNameComboBox;

    QLabel *BodyLabel;
	QLabel *BTLabel;
    QLabel *fileNameLabel;

	QComboBox *BTComboBox;

    QDialogButtonBox *buttonBox;

	QPushButton *closeButton;
    QPushButton *helpButton;
    QPushButton *createButton;
	QPushButton *LoadButton;
	QHBoxLayout *fileLayout;
	QStackedWidget *pagesWidget;
	BoxPage *boxpage;
	SpherePage *spherepage;
	CylinderPage *cylinderpage;
	ConePage *conepage;
	PolygonPage *polygonpage;
	bool Flag;
	GLBox *GraBox;
	void Judge();
	double TempTrans[3];
	int TempRotNum[3];
	double TempRotation[3];

	BodyParam m_bp;
	QTextCodec* tc;

};


#endif
