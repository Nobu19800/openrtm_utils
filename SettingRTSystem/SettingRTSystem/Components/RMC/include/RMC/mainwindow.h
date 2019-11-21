
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QMainWindow>
#include <QSlider>

#include "Joint.h"
#include "Jointpages.h"
#include "Body.h"
#include "Bodypages.h"
#include "Camera.h"
#include "Sensor.h"
#include "Sensorpages.h"
#include "glbox.h"

class DiagramScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
QT_END_NAMESPACE

/*メインウィンドウ*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();
   bool ReturnCheck();

private slots:
	void about();
	void textInserted(BodyItem *item);
	void actInserted(JointItem *item);
	void senInserted(SensorItem *item);
	void camInserted(CameraItem *item);
    void pointerGroupClicked(int id);
	void BorTGroupClicked(int id);
    void bringToFront();
    void sendToBack();
    void deleteItem();
    void buttonGroupClicked(int id);
	void save();
	void open();
    void saveAs();
	void saveVRML();
	void check();
	void renew();
	void setRotNum();
	void setGeoNum();
	void setSSNum();
	void updateParam();
	void setJH();
	void setBH();
	void setBox();
	void setSphere();
	void setCylinder();
	void setCone();
	void setPolygon();
	void setHinge();
	void setSlider();
	void setFix();
	void setSensor();

	void delTab();


protected:


private:
	void saveFile(const QString &fileName);
	
	void loadFile(const QString &fileName);

    void createActions();
    void createToolBox();
	void createSliderWidget();
	void createSliderArrowWidget();
	void createParamWidget();
	
	void createToolbars();
	void createMenus();
    DiagramScene *scene;
    QGraphicsView *view;
	void Judge();

	GLBox* c;

	QAction *exitAction;
    QAction *addAction;
    QAction *deleteAction;

    QAction *toFrontAction;
    QAction *sendBackAction;
    QAction *aboutAction;

	QAction *testAction;
	

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

    QToolBar *textToolBar;
    QToolBar *editToolBar;
    QToolBar *colorToolBar;
    QToolBar *pointerToolbar;

	QToolBar *BorTToolbar;

    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;
    QComboBox *textColorCombo;
    QComboBox *fontSizeCombo;
    QFontComboBox *fontCombo;

	QSlider *RotSlider;
	QSlider *ArrowAccSlider;
	QSlider *ArrowGyroSlider;
	QSlider *ArrowForceSlider;
	QSlider *ArrowTorqueSlider;
	QSlider *ArrowRangeSlider;
	QSlider *SensorSlider;
	QSlider *JointSlider;
    QToolBox *toolBox;
	QWidget *SliderWidget;
	QWidget *SliderArrowWidget;
	QWidget *ParamWidget;
    QButtonGroup *buttonGroup;
    QButtonGroup *pointerTypeGroup;
	QButtonGroup *BorTGroup;
    QButtonGroup *backgroundButtonGroup;
	QPushButton *testButton;
    QToolButton *fontColorToolButton;
	QTabWidget *tabWidget;
	//QToolButton *BanButton;
	//QToolButton *TransButton;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *boldAction;
    QAction *underlineAction;
    QAction *italicAction;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;
	QAction *checkAction;
	QString curFile;
	QAction *openAct;
	QAction *saveAct;
	QAction *saveVRMLAct;
	QAction *saveAsAct;
	QAction *BHAct;
	QAction *JHAct;
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];
	QString strippedName(const QString &fullFileName);
	QAction *separatorAct;
	void setCurrentFile(const QString &fileName);
	void updateRecentFileActions();
	bool CHECK;
	BoxPage *boxpage;
	SpherePage *spherepage;
	CylinderPage *cylinderpage;
	ConePage *conepage;
	PolygonPage *polygonpage;
	HingePage *hingepage;
	SliderPage *sliderpage;
	FixPage *fixpage;
	SensorPage *sensorpage;

	QTextCodec* tc;

};

#endif
