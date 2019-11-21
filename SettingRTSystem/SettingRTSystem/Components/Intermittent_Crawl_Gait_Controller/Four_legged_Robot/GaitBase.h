/*!
* @file  CrawlGait.h
* @brief 歩容基本クラス
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
*@brief 歩容基本クラス
*/
class GaitBase
{
public:
	/**
	*@brief コンストラクタ
	*@param ls 脚のリスト
	*/
	GaitBase(Leg_Object *ls, Body_Object *bo);
	/**
	*@brief 歩行更新
	* @param vx 速度(X)
	* @param vy 速度(Y)
	* @param dthe 回転速度
	* @param sd 歩幅
	*/
	virtual void walk(double vx, double vy, double dthe, double sd);
	/**
	*@brief 刻み幅設定
	* @param st サンプリング時間
	*/
	virtual void setSamplingTime(double st);
	/**
	*@brief 最低安定を満たしているかの判定
	* 満たしていない場合は重心を移動させる
	* @param mc 移動にかかるステップ数
	*/
	virtual void judge_Stability(int mc);
	/**
	*@brief 最低安定の設定
	* @param msm 安定余裕
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