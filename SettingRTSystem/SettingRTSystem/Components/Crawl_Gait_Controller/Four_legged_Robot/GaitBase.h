/*!
* @file  CrawlGait.h
* @brief ���e��{�N���X
*
*/


#ifndef GaitBase_H
#define GaitBase_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

#include "Body_Object.h"
#include "Leg_Object.h"
#include "Direction_Object.h"
#include "Stability_Margin.h"


using namespace Eigen;


enum GaitState
{
	UP_FRONT_LEFT_LEG = 0,
	UP_BACK_LEFT_LEG = 1,
	UP_BACK_RIGHT_LEG = 2,
	UP_FRONT_RIGHT_LEG = 3,
	ON_GROUND_FOUR_LEGS_1 = 4,
	ON_GROUND_FOUR_LEGS_2 = 5,
	MOVE_STABILITY = 6,
	UP_FRONT_LEFT_LEG_AND_BACK_RIGHT_LEG = 7,
	UP_FRONT_RIGHT_LEG_AND_BACK_LEFT_LEG = 8,
	WALK_PAUSE = 9,
};


/**
* @class GaitBase
*@brief ���e��{�N���X
*/
class GaitBase
{
public:
	/**
	*@brief �R���X�g���N�^
	*@param ls �r�̃��X�g
	*/
	GaitBase(Leg_Object *ls, Body_Object *bo);
	/**
	*@brief ���s�X�V
	* @param vx ���x(X)
	* @param vy ���x(Y)
	* @param dthe ��]���x
	* @param sd ����
	*/
	virtual void walk(double vx, double vy, double dthe, double sd);
	/**
	*@brief ���ݕ��ݒ�
	* @param st �T���v�����O����
	*/
	virtual void setSamplingTime(double st);
	/**
	*@brief �Œ����𖞂����Ă��邩�̔���
	* �������Ă��Ȃ��ꍇ�͏d�S���ړ�������
	* @param mc �ړ��ɂ�����X�e�b�v��
	*/
	virtual void judge_Stability(int mc);
	/**
	*@brief �Œ����̐ݒ�
	* @param msm ����]�T
	*/
	virtual void set_Min_Margin(double msm);
	double sampling_time;
	double current_time;
	double stride;


	GaitState state;
	CrawlGaitDir dir;
	GaitState next_state;

	Leg_Object *legs;
	Body_Object *body;
	double min_margin;
};





#endif