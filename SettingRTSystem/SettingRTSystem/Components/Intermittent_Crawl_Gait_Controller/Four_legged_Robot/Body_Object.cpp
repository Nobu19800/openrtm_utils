/*!
* @file  Body_Object.cpp
* @brief 重心制御クラス
*
*/

#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "Body_Object.h"

#define DEFAULT_SAMPLING_TIME 0.1


/**
*@brief コンストラクタ
*/
Body_Object::Body_Object()
{
	state = MOVE_STOP;

	sampling_time = DEFAULT_SAMPLING_TIME;

	max_count = 10000;
	count = 0;
	offset_count = 0;

	intermittent_x_offset = 0;
	intermittent_y_offset = 0;



	set_position(Vector3d(0, 0, 0));
	set_orientation(Vector3d(0, 0, 0));
	
}







/**
*@brief 更新
*/
void Body_Object::update()
{
	if (state == ON_GROUND_CRAWL)
	{
		double diff_x = -rotete_vel*rotate_len*sin(offset_angle)*sampling_time;
		double diff_y = rotete_vel*rotate_len*cos(offset_angle)*sampling_time;
		//std::cout << offset_angle << "\t" << diff_x << "\t" << diff_y << std::endl;
		current_pos(0) = current_pos(0) + diff_x*cos(current_rot(2)) - diff_y*sin(current_rot(2));
		current_pos(1) = current_pos(1) + diff_x*sin(current_rot(2)) + diff_y*cos(current_rot(2));


		current_rot(2) = current_rot(2) + rotete_vel*sampling_time;

		count++;
	}
	else if (state == ON_GROUND_INTERMITTENT_CRAWL)
	{
		double diff_x = (-rotete_vel*rotate_len*sin(offset_angle) + intermittent_x_offset)*sampling_time;
		double diff_y = (rotete_vel*rotate_len*cos(offset_angle) + intermittent_y_offset)*sampling_time;
		
		current_pos(0) = current_pos(0) + diff_x*cos(current_rot(2)) - diff_y*sin(current_rot(2));
		current_pos(1) = current_pos(1) + diff_x*sin(current_rot(2)) + diff_y*cos(current_rot(2));

		//std::cout << "test\t" << diff_x << "\t" << diff_y << "\t" << current_rot(2) << "\t" << current_pos(1) << std::endl;
		current_rot(2) = current_rot(2) + rotete_vel*sampling_time;

		count++;
	}
	else if (state == ON_GROUND_MOVE_TARGET)
	{
		double diff_x = (target_pos(0) - start_pos(0)) / (double)max_count;
		double diff_y = (target_pos(1) - start_pos(1)) / (double)max_count;
		//std::cout << diff_x << "\t" << diff_y << std::endl;
		current_pos(0) = current_pos(0) + diff_x*cos(current_rot(2)) - diff_y*sin(current_rot(2));
		current_pos(1) = current_pos(1) + diff_x*sin(current_rot(2)) + diff_y*cos(current_rot(2));
		

		count++;
	}

	if (count > max_count)
	{


		count = 0;
		set_state(MOVE_PAUSE);
	}
}

void Body_Object::set_state(FootState s)
{
	last_state = state;
	state = s;

}



/**
*@brief 回転中心位置、回転速度などの設定
*@param p 回転中心位置
*@param rv 回転速度
*@param mc ステップ数
*@param sampling サンプリング時間
*@param target_position_update trueの場合は目標位置を再設定する
*/
void Body_Object::setRotateStatus(Vector3d p, double rv, int mc, double sampling, bool target_position_update)
{
	rotate_pos = p;
	rotete_vel = rv;
	sampling_time = sampling;

	rotate_len = sqrt(p(0)*p(0) + p(1)*p(1));
	offset_angle = atan2(-p(1), -p(0));

	max_count = mc;


}





/**
*@brief 回転速度、ステップ数の再設定
*@param rv 回転速度
*@param len 回転中心までの長さ
*@param mc ステップ数
*/
void Body_Object::update_status(double rv, int mc)
{
	
	count = count * mc / max_count;
	
	offset_count = offset_count * mc / max_count;
	
	rotete_vel = rotete_vel * max_count / mc;

	max_count = mc;
	/*if (rv*rotete_vel >= 0)rotete_vel = rv;
	else rotete_vel = -rv;*/
	//rotate_len = len;
}

/**
*@brief 初期位置設定
*@param p 位置
*/
void Body_Object::set_position(Vector3d p)
{
	pos = p;
	current_pos = p;
}

/**
*@brief 初期姿勢設定
*@param p 位置
*/
void Body_Object::set_orientation(Vector3d r)
{
	rot = r;
	current_rot = r;
}