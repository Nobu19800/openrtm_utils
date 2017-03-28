



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

	/*void setBox(BodyBase *Param);	//�����̂ɐݒ�
	void setSphere(BodyBase *Param);	//���ɐݒ�
	void setCone(BodyBase *Param);	//�~���ɐݒ�
	void setCylinder(BodyBase *Param);	//�~���ɐݒ�
	void setPolygon(BodyBase *Param);	//�|���S���ɐݒ�*/
	void setName(QString Name);	//���O��ݒ�
	void setGeom(BodyData *bd);
	void setParam(BodyParam bp);
	int returnGeom();	//�`��̎�ނ�Ԃ�
	BodyData *ReturnParam();	//�p�����[�^��Ԃ�
	//double Param1[26];
	QString ReturnName();	//���O��Ԃ�
	//bool Flag;	//���̂���������Ă��Ȃ����True,�����ς݂Ȃ�False
	void SetTip(bool Tip);	//�擪���ǂ�����ݒ�
	//int NUM;	//�ԍ�
	BodyData *m_param;
	QGraphicsTextItem *m_text;



private:
	Control_Mode myMode;	//�G�f�B�^�ł̏��
	void open();	//�p�����[�^�ݒ�̃_�C�A���O�\��
	
	

};


#endif
