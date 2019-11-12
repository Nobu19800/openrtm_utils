/*!
* @file  Direction_Object.cpp
* @brief 進行方向制御クラス
*
*/


#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "Direction_Object.h"



/**
*@brief コンストラクタ
*@param vx 速度(X)
*@param vy 速度(Y)
*@param dthe 回転速度
*@param legs 脚のリスト
*/
Direction_Object::Direction_Object(double vx, double vy, double dthe, Leg_Object *legs)
{

	L = sqrt((vx*vx + vy*vy) / (dthe*dthe));
	phi = atan2(vy, vx);

	alpha = atan2(vy, vx);
	if (dthe > 0)alpha += M_PI / 2.0;
	else alpha -= M_PI / 2.0;
	pos(0) = L*cos(alpha);
	pos(1) = L*sin(alpha);

	offset_angle = atan2(pos(1), pos(0));
	double leg_angle[4];
	leg_angle[0] = atan2(legs[0].center_pos(1), legs[0].center_pos(0));
	leg_angle[1] = atan2(legs[1].center_pos(1), legs[1].center_pos(0));
	leg_angle[2] = atan2(legs[2].center_pos(1), legs[2].center_pos(0));
	leg_angle[3] = atan2(legs[3].center_pos(1), legs[3].center_pos(0));
	for (int i = 0; i < 4; i++)
	{
		if (leg_angle[i] < 0)leg_angle[i] = 2 * M_PI + leg_angle[i];
	}
	if (offset_angle < 0)offset_angle = 2 * M_PI + offset_angle;

	pos_distance = sqrt(pos(0)*pos(0) + pos(1)*pos(1));
	leg_distance = sqrt(legs[0].center_pos(0)*legs[0].center_pos(0) + legs[0].center_pos(1)*legs[0].center_pos(1));
	//std::cout << vx << "\t" << dthe << "\t" << leg_distance << "\t" << pos_distance << std::endl;
	//if (dir == WALK_STOP)
	{
		if (leg_distance > pos_distance)
		{
			if (dthe > 0)dir = WALK_ROT_PLUS;
			else dir = WALK_ROT_MINUS;
		}
		else if (offset_angle > leg_angle[0] && offset_angle < leg_angle[1])
		{
			if (dthe > 0)dir = WALK_FORWORD;
			else dir = WALK_BACK;
		}
		else if (offset_angle > leg_angle[1] && offset_angle < leg_angle[2])
		{
			if (dthe > 0)dir = WALK_LEFT;
			else dir = WALK_RIGHT;
		}
		else if (offset_angle > leg_angle[2] && offset_angle < leg_angle[3])
		{
			if (dthe > 0)dir = WALK_BACK;
			else dir = WALK_FORWORD;
		}
		else
		{
			if (dthe > 0)dir = WALK_RIGHT;
			else dir = WALK_LEFT;
		}
		//else if ((offset_angle > leg_angle1 && offset_angle < leg_angle1))dir = WALK_FORWORD;
	}
	//std::cout << dir << std::endl;
}
