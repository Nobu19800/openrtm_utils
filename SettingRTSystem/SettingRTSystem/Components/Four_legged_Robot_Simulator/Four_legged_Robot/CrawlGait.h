/*!
* @file  CrawlGait.h
* @brief �N���[�����e����N���X
*
*/


#ifndef CrawlGait_H
#define CrawlGait_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

#include "Leg_Object.h"
#include "Body_Object.h"
#include "Direction_Object.h"
#include "Stability_Margin.h"
#include "GaitBase.h"

using namespace Eigen;




/**
* @class CrawlGait
*@brief �N���[�����e����N���X
*/
class CrawlGait : public GaitBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param ls �r�̃��X�g
	*/
	CrawlGait(Leg_Object *ls, Body_Object *bo);
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