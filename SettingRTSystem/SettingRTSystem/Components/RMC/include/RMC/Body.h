



#ifndef BODYITEM_H
#define BODYITEM_H


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



class BodyItem : public QGraphicsPixmapItem
{

public:


    BodyItem(BodyData *bd, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

	/*void setBox(BodyBase *Param);	//立方体に設定
	void setSphere(BodyBase *Param);	//球に設定
	void setCone(BodyBase *Param);	//円錐に設定
	void setCylinder(BodyBase *Param);	//円柱に設定
	void setPolygon(BodyBase *Param);	//ポリゴンに設定*/
	void setName(QString Name);	//名前を設定
	void setGeom(BodyData *bd);
	void setParam(BodyParam bp);
	int returnGeom();	//形状の種類を返す
	BodyData *ReturnParam();	//パラメータを返す
	//double Param1[26];
	QString ReturnName();	//名前を返す
	//bool Flag;	//物体が消去されていなければTrue,消去済みならFalse
	void SetTip(bool Tip);	//先頭かどうかを設定
	//int NUM;	//番号
	BodyData *m_param;
	QGraphicsTextItem *m_text;



private:
	Control_Mode myMode;	//エディタでの状態
	void open();	//パラメータ設定のダイアログ表示
	
	

};


#endif
