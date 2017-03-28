/*!
* @file  IntermittentCrawlGait.h
* @brief �ԟ[�N���[�����e����N���X
*
*/


#ifndef IntermittentCrawlGait_H
#define IntermittentCrawlGait_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

#include "Leg_Object.h"
#include "Direction_Object.h"
#include "Stability_Margin.h"
#include "GaitBase.h"

using namespace Eigen;


/**
* @class CrawlGait
*@brief �ԟ[�N���[�����e����N���X
*/
class IntermittentCrawlGait : public GaitBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param ls �r�̃��X�g
	*/
	IntermittentCrawlGait(Leg_Object *ls, Body_Object *bo);
	/**
	*@brief ���s�X�V
	* @param vx ���x(X)
	* @param vy ���x(Y)
	* @param dthe ��]���x
	* @param sd ����
	*/
	virtual void walk(double vx, double vy, double dthe, double sd);
	/**
	*@brief �������ւ̈ړ������ݒ�
	* @param smd �ړ�����
	*/
	void setSideMoveDistance(double smd);
	double side_move_distance;

};

#endif