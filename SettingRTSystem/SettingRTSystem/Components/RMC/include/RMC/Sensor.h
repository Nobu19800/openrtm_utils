
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

	void setData(SensorData *sd);	//�p�����[�^�ݒ�
	void setParam(SensorParam cp);
	void setName(QString Name);	//���O�̐ݒ�
	int returnType();	//��ނ�Ԃ�
	SensorData* ReturnParam();	//�p�����[�^��Ԃ�
	int ReturnID();	//ID��Ԃ�
	BodyData* ReturnBodyNUM();	//�ڑ�����{�f�B�̔ԍ���Ԃ�
	QString ReturnName();	//���O��Ԃ�
	int returnGeom();
	void setBodyNum(BodyData* bd); //�ԍ���ݒ�
	int NUM;	//�ԍ�

	SensorData *m_param;
	QGraphicsLineItem* m_line;
	QGraphicsTextItem *m_text;


private:


};


#endif
