
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
	enum JointType { Hinge, Slider, Fix};	//�W���C���g�̎��
	int returnJoint();	//�W���C���g�̎�ނ�Ԃ�
	void setJoint(JointData *jd);
	void setParam(JointParam jp);
	ItemDataBase*  returnNUM1();	//���{���ɐڑ����Ă���{�f�B�̔ԍ�
	ItemDataBase*  returnNUM2();	//��[���ɐڑ����Ă���{�f�B�̔ԍ�
	JointData* ReturnParam();	//�p�����[�^��Ԃ�
	void setBody(BodyData* i1, BodyData* i2);	//�ڑ�����{�f�B��ݒ�
	bool FLAG;	//���̂���������Ă��Ȃ����True,�����ς݂Ȃ�False
	void setName(QString Name);	//���O��ݒ�
	QString ReturnName();	//���O��Ԃ�
	int NUM;	//�ԍ�
	QGraphicsLineItem* m_line;
	QGraphicsTextItem *m_text;
	JointData *m_param;


private:
	Control_Mode myMode;	//�G�f�B�^��ł̏��
	void open();	//�p�����[�^�ݒ�̃_�C�A���O�\��





};


#endif
