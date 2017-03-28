/*!
* @file  TrotGait.h
* @brief �g���b�g���e����N���X
*
*/


#ifndef TrotGait_H
#define TrotGait_H

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
*@brief �g���b�g���e����N���X
*/
class TrotGait : public GaitBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param ls �r�̃��X�g
	*/
	TrotGait(Leg_Object *ls, Body_Object *bo);
	/**
	*@brief ���s�X�V
	* @param vx ���x(X)
	* @param vy ���x(Y)
	* @param dthe ��]���x
	* @param sd ����
	*/
	virtual void walk(double vx, double vy, double dthe, double sd);


};

#endif