
#ifndef JOINTITEM_H
#define JOINTITEM_H

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


class JointItem : public QGraphicsPixmapItem
{

public:

    JointItem(JointData *jd, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
	enum JointType { Hinge, Slider, Fix};	//ジョイントの種類
	int returnJoint();	//ジョイントの種類を返す
	void setJoint(JointData *jd);
	void setParam(JointParam jp);
	ItemDataBase*  returnNUM1();	//根本側に接続しているボディの番号
	ItemDataBase*  returnNUM2();	//先端側に接続しているボディの番号
	JointData* ReturnParam();	//パラメータを返す
	void setBody(BodyData* i1, BodyData* i2);	//接続するボディを設定
	bool FLAG;	//物体が消去されていなければTrue,消去済みならFalse
	void setName(QString Name);	//名前を設定
	QString ReturnName();	//名前を返す
	int NUM;	//番号
	QGraphicsLineItem* m_line;
	QGraphicsTextItem *m_text;
	JointData *m_param;


private:
	Control_Mode myMode;	//エディタ上での状態
	void open();	//パラメータ設定のダイアログ表示





};


#endif
