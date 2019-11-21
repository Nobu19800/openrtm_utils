/*!
* @file  Body_Object.h
* @brief 重心制御クラス
*
*/


#ifndef Body_Object_H
#define Body_Object_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

#include "Leg_Object.h"

using namespace Eigen;




/**
* @class Body_Object
*@brief 胴体制御クラス
*/
class Body_Object
{
public:
	/**
	*@brief コンストラクタ
	*/
	Body_Object();


	/**
	*@brief 回転中心位置、回転速度などの設定
	*@param p 回転中心位置
	*@param rv 回転速度
	*@param mc ステップ数
	*@param sampling サンプリング時間
	*@param target_position_update trueの場合は目標位置を再設定する
	*/
	void setRotateStatus(Vector3d p, double rv, int mc, double sampling, bool target_position_update = true);
	/**
	*@brief 更新
	*/
	void update();

	/**
	*@brief 状態設定
	*@param s 状態
	*/
	void set_state(FootState s);


	/**
	*@brief 回転速度、ステップ数の再設定
	*@param rv 回転速度
	*@param mc ステップ数
	*/
	void update_status(double rv, int mc);

	/**
	*@brief 初期位置設定
	*@param p 位置
	*/
	void set_position(Vector3d p);

	/**
	*@brief 初期姿勢設定
	*@param r 姿勢
	*/
	void set_orientation(Vector3d r);

	double sampling_time;
	int count;
	int max_count;
	int offset_count;
	double rotete_vel;
	Vector3d pos;
	Vector3d rot;
	double lx, ly, lz;
	double mass;
	FootState state;
	FootState last_state;

	Vector3d start_pos;
	Vector3d current_pos;
	Vector3d current_rot;
	Vector3d target_pos;

	Vector3d rotate_pos;
	double rotate_len;
	double offset_angle;

	double intermittent_x_offset;
	double intermittent_y_offset;



};




#endif