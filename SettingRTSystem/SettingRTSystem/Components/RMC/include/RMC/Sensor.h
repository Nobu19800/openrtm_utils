
#ifndef SensorItem_H
#define SensorItem_H


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



class SensorItem : public QGraphicsPixmapItem
{

public:


	SensorItem(SensorData *sd, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

	void setData(SensorData *sd);	//パラメータ設定
	void setParam(SensorParam cp);
	void setName(QString Name);	//名前の設定
	int returnType();	//種類を返す
	SensorData* ReturnParam();	//パラメータを返す
	int ReturnID();	//IDを返す
	BodyData* ReturnBodyNUM();	//接続するボディの番号を返す
	QString ReturnName();	//名前を返す
	int returnGeom();
	void setBodyNum(BodyData* bd); //番号を設定
	int NUM;	//番号

	SensorData *m_param;
	QGraphicsLineItem* m_line;
	QGraphicsTextItem *m_text;


private:


};


#endif
