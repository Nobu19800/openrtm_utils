
#ifndef CameraItem_H
#define CameraItem_H


#include "ObjectData.h"
#include <QtGui>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPen>

QT_BEGIN_NAMESPACE
class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QPolygonF;
class QTimeLine;
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE



class CameraItem : public QGraphicsPixmapItem
{

public:

    CameraItem(CameraData *cd, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

	void setData(CameraData *cd);	//パラメータを設定
	void setParam(CameraParam cd);
	void setName(QString Name);	//名前を設定
	int returnType();	//取得する情報の種類を返す
	CameraData *ReturnParam();	//パラメータを返す
	int ReturnID();	//IDを返す
	JointData* ReturnJointNUM();	//接続するジョイントの番号を返す
	QString ReturnName();	//名前を返す
	int returnGeom();	//カメラの種類を返す
	void setJointNum(JointData* jd);	//番号を設定
	int NUM;	//番号
	CameraData *m_param;
	QGraphicsTextItem *m_text;
	QGraphicsLineItem* m_line;

private:

};


#endif
