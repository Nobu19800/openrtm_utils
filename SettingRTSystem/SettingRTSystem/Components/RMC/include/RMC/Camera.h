
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

	void setData(CameraData *cd);	//�p�����[�^��ݒ�
	void setParam(CameraParam cd);
	void setName(QString Name);	//���O��ݒ�
	int returnType();	//�擾������̎�ނ�Ԃ�
	CameraData *ReturnParam();	//�p�����[�^��Ԃ�
	int ReturnID();	//ID��Ԃ�
	JointData* ReturnJointNUM();	//�ڑ�����W���C���g�̔ԍ���Ԃ�
	QString ReturnName();	//���O��Ԃ�
	int returnGeom();	//�J�����̎�ނ�Ԃ�
	void setJointNum(JointData* jd);	//�ԍ���ݒ�
	int NUM;	//�ԍ�
	CameraData *m_param;
	QGraphicsTextItem *m_text;
	QGraphicsLineItem* m_line;

private:

};


#endif
