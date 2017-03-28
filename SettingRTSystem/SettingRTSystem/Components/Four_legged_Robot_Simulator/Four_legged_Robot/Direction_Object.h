/*!
* @file  Direction_Object.h
* @brief �i�s��������N���X
*
*/


#ifndef Direction_Object_H
#define Direction_Object_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "Leg_Object.h"



enum CrawlGaitDir
{
	WALK_FORWORD = 0,
	WALK_BACK = 1,
	WALK_RIGHT = 2,
	WALK_LEFT = 3,
	WALK_ROT_PLUS = 4,
	WALK_ROT_MINUS = 5,
	WALK_STOP = 6,
};




/**
* @class Direction_Object
*@brief �i�s��������N���X
*/
class Direction_Object
{
public:
	/**
	*@brief �R���X�g���N�^
	*@param vx ���x(X)
	*@param vy ���x(Y)
	*@param dthe ��]���x
	*@param legs �r�̃��X�g
	*/
	Direction_Object(double vx, double vy, double dthe, Leg_Object *legs);
	Vector3d pos;
	double L;
	double phi;
	double alpha;
	double offset_angle;
	double pos_distance;
	double leg_distance;
	CrawlGaitDir dir;
};






#endif