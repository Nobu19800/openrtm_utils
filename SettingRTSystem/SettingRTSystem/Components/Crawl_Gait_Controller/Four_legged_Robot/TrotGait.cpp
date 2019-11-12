/*!
* @file  TrotGait.cpp
* @brief トロット歩容制御クラス
*
*/


#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "TrotGait.h"



#define DEFAULT_SAMPLING_TIME 0.1


#define MIN_VELOCITY_VX 0.0001
#define MIN_VELOCITY_VY 0.0001
#define MIN_VELOCITY_TH 0.0001




/**
*@brief コンストラクタ
* @param ls 脚のリスト
*/
TrotGait::TrotGait(Leg_Object *ls, Body_Object *bo) : GaitBase(ls, bo)
{
	legs = ls;

	sampling_time = DEFAULT_SAMPLING_TIME;

	current_time = 0;

	state = UP_FRONT_LEFT_LEG_AND_BACK_RIGHT_LEG;
	dir = WALK_STOP;


}




/**
*@brief 歩行更新
* @param vx 速度(X)
* @param vy 速度(Y)
* @param dthe 回転速度
* @param sd 歩幅
*/
void TrotGait::walk(double vx, double vy, double dthe, double sd)
{
	
	if (abs(vx) < MIN_VELOCITY_VX && abs(vy) < MIN_VELOCITY_VY && abs(dthe) < MIN_VELOCITY_TH)
	{
		return;
	}
	else if (abs(dthe) < MIN_VELOCITY_TH)
	{
		dthe = MIN_VELOCITY_TH;
	}

	for (int i = 0; i < 4; i++)
	{
		legs[i].update();
	}

	body->update();

	correctlyOnGroundPos();

	Direction_Object d = Direction_Object(vx, vy, dthe, legs);

	stride = sd;

	double L_max = 0;
	for (int i = 0; i < 4; i++)
	{
		double len_x = d.pos(0) - (legs[i].center_pos(0) + legs[i].stability_x_offset);
		double len_y = d.pos(1) - (legs[i].center_pos(1) + legs[i].stability_y_offset);
		double L_tmp = sqrt(len_x*len_x + len_y*len_y);
		if (L_tmp > L_max)L_max = L_tmp;
	}
	int mc = (int)((stride) / (L_max * abs(dthe) * sampling_time));
	
	for (int i = 0; i < 4; i++)
	{
		legs[i].update_status(dthe, mc);
		if (dir == d.dir)
		{

			legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, false);

		}

	}

	body->update_status(dthe, mc);

	if (dir == d.dir)
		body->setRotateStatus(d.pos, dthe, mc, sampling_time, false);

	for (int i = 0; i < 4; i++)
	{
		if (legs[i].state != MOVE_PAUSE && legs[i].state != MOVE_STOP)return;
	}

	if (dir != d.dir)
	{
		for (int i = 0; i < 4; i++)
		{
			legs[i].set_state(MOVE_STOP);
			legs[i].count = 0;
		}
		body->set_state(MOVE_STOP);
		body->count = 0;
	}
	dir = d.dir;



	if (state == UP_FRONT_LEFT_LEG_AND_BACK_RIGHT_LEG)state = UP_FRONT_RIGHT_LEG_AND_BACK_LEFT_LEG;
	else if (state == UP_FRONT_RIGHT_LEG_AND_BACK_LEFT_LEG)state = UP_FRONT_LEFT_LEG_AND_BACK_RIGHT_LEG;


	if (state == UP_FRONT_LEFT_LEG_AND_BACK_RIGHT_LEG)
	{

		
		legs[1].set_state(NOT_ON_GROUND_TROT);
		legs[3].set_state(NOT_ON_GROUND_TROT);
		

		if (Leg_Object::LegsStop(legs, 4) == 0)
		{
			legs[0].set_state(ON_GROUND_TROT);
			legs[2].set_state(ON_GROUND_TROT);
			body->set_state(ON_GROUND_TROT);
			body->setRotateStatus(d.pos, dthe, mc, sampling_time);
		}

		

		legs[0].offset_count = (int)((double)mc*(0.5));
		legs[1].offset_count = (int)((double)mc*(-0.5));
		legs[2].offset_count = (int)((double)mc*(0.5));
		legs[3].offset_count = (int)((double)mc*(-0.5));

		for (int i = 0; i < 4; i++)
		{
			legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
		}
		correctlyOffGroundPos();
	}
	else if (state == UP_FRONT_RIGHT_LEG_AND_BACK_LEFT_LEG)
	{
		
		legs[0].set_state(NOT_ON_GROUND_TROT);
		legs[2].set_state(NOT_ON_GROUND_TROT);

		if (Leg_Object::LegsStop(legs, 4) == 0)
		{
			legs[1].set_state(ON_GROUND_TROT);
			legs[3].set_state(ON_GROUND_TROT);
			body->set_state(ON_GROUND_TROT);
			body->setRotateStatus(d.pos, dthe, mc, sampling_time);
		}

		
		

		legs[0].offset_count = (int)((double)mc*(-0.5));
		legs[1].offset_count = (int)((double)mc*(0.5));
		legs[2].offset_count = (int)((double)mc*(-0.5));
		legs[3].offset_count = (int)((double)mc*(0.5));

		for (int i = 0; i < 4; i++)
		{
			legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
			//legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, true, 1.0 - (1.0 / 3.0*(double)(Leg_Object::LegsStop(legs, 4) - 1)));
		}
		correctlyOffGroundPos();
	}

}


/**
*@brief 補正方向計算
* @param pos0 脚0の位置
* @param pos1 脚1の位置
* @return 最短距離ベクトル
*/
Vector2d TrotGait::calcDistance(Vector2d &pos0, Vector2d &pos1)
{

	Vector2d vec1 = pos1 - pos0;
	vec1 = vec1.normalized();
	Vector2d vec2 = - pos0;
	Vector2d a = vec2.dot(vec1)*vec1;
	
	Vector2d b = vec2 - a;
	//std::cout << vec2.dot(vec1) << "\t" << pos0(0) << "\t" << pos0(1) << "\t" << pos1(0) << "\t" << pos1(1) << std::endl;
	
	return b;
}


/**
*@brief 重心位置が対角線上に乗るように脚先接地点を補正
* @param pos0 脚0の位置
* @param pos1 脚1の位置
*/
void TrotGait::correctlyOnGroundPos()
{
	if (state == UP_FRONT_LEFT_LEG_AND_BACK_RIGHT_LEG)
	{
		Vector2d pos0(legs[0].current_pos(0), legs[0].current_pos(1));
		Vector2d pos1(legs[2].current_pos(0), legs[2].current_pos(1));
		Vector2d diff = calcDistance(pos0, pos1);
		legs[0].current_pos(0) += diff(0);
		legs[0].current_pos(1) += diff(1);
		legs[2].current_pos(0) += diff(0);
		legs[2].current_pos(1) += diff(1);
		//std::cout << diff << std::endl;


	}
	else if (state == UP_FRONT_RIGHT_LEG_AND_BACK_LEFT_LEG)
	{
		Vector2d pos0(legs[1].current_pos(0), legs[1].current_pos(1));
		Vector2d pos1(legs[3].current_pos(0), legs[3].current_pos(1));
		//std::cout << calcDistance(pos0, pos1) << std::endl;
		Vector2d diff = calcDistance(pos0, pos1);
		legs[1].current_pos(0) += diff(0);
		legs[1].current_pos(1) += diff(1);
		legs[3].current_pos(0) += diff(0);
		legs[3].current_pos(1) += diff(1);
		//std::cout << diff << std::endl;

	}
}
/**
*@brief 重心位置が対角線上に乗るように目標着地点を補正
* @param pos0 脚0の位置
* @param pos1 脚1の位置
*/
void TrotGait::correctlyOffGroundPos()
{
	if (state == UP_FRONT_LEFT_LEG_AND_BACK_RIGHT_LEG)
	{
		Vector2d pos0(legs[1].target_pos(0), legs[1].target_pos(1));
		Vector2d pos1(legs[3].target_pos(0), legs[3].target_pos(1));
		//std::cout << calcDistance(pos0, pos1) << std::endl;
		Vector2d diff = calcDistance(pos0, pos1);
		legs[1].target_pos(0) += diff(0);
		legs[1].target_pos(1) += diff(1);
		legs[3].target_pos(0) += diff(0);
		legs[3].target_pos(1) += diff(1);
		//std::cout << diff << std::endl;


	}
	else if (state == UP_FRONT_RIGHT_LEG_AND_BACK_LEFT_LEG)
	{
		

		

		

		Vector2d pos0(legs[0].target_pos(0), legs[0].target_pos(1));
		Vector2d pos1(legs[2].target_pos(0), legs[2].target_pos(1));
		Vector2d diff = calcDistance(pos0, pos1);
		legs[0].target_pos(0) += diff(0);
		legs[0].target_pos(1) += diff(1);
		legs[2].target_pos(0) += diff(0);
		legs[2].target_pos(1) += diff(1);
		//std::cout << diff << std::endl;

	}
}