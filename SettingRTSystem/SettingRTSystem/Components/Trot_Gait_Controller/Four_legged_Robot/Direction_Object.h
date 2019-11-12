/*!
* @file  Direction_Object.h
* @brief 進行方向制御クラス
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
*@brief 進行方向制御クラス
*/
class Direction_Object
{
public:
	/**
	*@brief コンストラクタ
	*@param vx 速度(X)
	*@param vy 速度(Y)
	*@param dthe 回転速度
	*@param legs 脚のリスト
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