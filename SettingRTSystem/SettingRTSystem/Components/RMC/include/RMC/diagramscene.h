
#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include "Joint.h"
#include "Body.h"
#include "Sensor.h"
#include "Camera.h"
#include "JointMenu.h"
#include "BodyMenu.h"
#include "SensorMenu.h"
#include "CameraMenu.h"

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE



/*エディタ*/

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:

    DiagramScene(QMenu *itemMenu, QObject *parent = 0);

	int ReturnItemCount();
	BodyData* ReturnParam(int num);
	void deleteItem();
	JointData* ReturnactParam(int num);
	SensorData* ReturnsenParam(int num);
	CameraData* ReturncamParam(int num);
	int ReturnactCount();
	int ReturnsenCount();
	int ReturncamCount();
	bool returnTip(int num);
	int CHECK();
	int RotNum;
	int GeoNum;
	int SSNum;
	int returnActNum(int i);
	int returnBodyNum(int i);
	int returnSenNum(int i);
	int returnCamNum(int i);
	int LoadFile(const QString &fileName);
	int SaveFile(const QString &fileName);
	int SaveFileVRML(const QString &fileName);
	enum BTType { BTFree, BTFix};
	BodyItem * getBodyItem(ItemDataBase *bd);
	JointItem * getJointItem(JointData *jd);
	BodyItem * getBodyItem(int num);
	JointItem * getJointItem(int num);
	void updateJoint();
	void writeJointData(const QString &fileName, QTextStream &out, JointData *jd, float *trans);
	void deleteBody(BodyItem *bi);
	void deleteJoint(JointItem *ji);
	void deleteSensor(SensorItem *si);
	void deleteCamera(CameraItem *ci);

	BodyItem* createBody(BodyParam bp, QPointF p);
	JointItem* createJoint(JointParam jp, BodyItem *bi1, BodyItem *bi2);
	SensorItem* createSensor(SensorParam sp, QPointF p, BodyData *bd);
	CameraItem* createCamera(CameraParam cp, QPointF p, JointData *jd);

	std::vector<BodyItem*> textItem;
	std::vector<JointItem*> actItem;	
	std::vector<SensorItem*> senItem;
	std::vector<CameraItem*> camItem;

	bool DoubleFlag;





signals:
    void textInserted(BodyItem *item);
	void actInserted(JointItem *item);
	void senInserted(SensorItem *item);
	void camInserted(CameraItem *item);
	void lineInserted(QGraphicsLineItem *line);
	void renew();
	void setRotNum();
	void setGeoNum();
	void setSSNum();
	void delTab();


public slots:
	void setMode(Control_Mode mode);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void dropEvent(QGraphicsSceneDragDropEvent *mouseEvent);
	void contextMenuEvent(QContextMenuEvent *event);
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:

	void createActions();
	QAction *cutAct;

    QMenu *myItemMenu;
    bool leftButtonDown;
    QPointF startPoint;
   //std::vector<QGraphicsLineItem*> line;
	QGraphicsLineItem* templine;
	QGraphicsLineItem* templine2;
	QGraphicsLineItem* camlin;
	QGraphicsLineItem* senlin;
	QGraphicsItem* tempItem;
	QGraphicsItem* tempItem2;
	//std::vector<QGraphicsLineItem*> Senline;
	//std::vector<QGraphicsLineItem*> Camline;
    QFont myFont;
	Control_Mode myMode;
	
    QColor myTextColor;
    QColor myItemColor;
    QColor myLineColor;
	void loadFile(const QString &fileName, PolygonData *P1, double Tr[3], double Ro[3]);
	/*QGraphicsItem *Senlin1[100];
	QGraphicsItem *Senlin2[100];
	QGraphicsItem *lin1[100];
	QGraphicsItem *lin2[100];
	QGraphicsItem *camlin[100];*/
	QGraphicsPixmapItem *BackG;
	void savePolygon(const QString &fileName, BodyData *bd);
	double *dot3X3(double *T1, double *T2);
	double *Silde(double x, double y, double z, double *T1);
	double *RotX(double rad, double *T1);
	double *RotY(double rad, double *T1);
	double *RotZ(double rad, double *T1);
	double *RotTSL(double roll, double pitch, double yaw, double x, double y, double z, double *R);
	int BType;


	QTextCodec* tc;


};


#endif
