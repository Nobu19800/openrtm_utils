/*!
* @file  GaitBase.cpp
* @brief 歩容基本クラス
*
*/


#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "GaitBase.h"



#define DEFAULT_SAMPLING_TIME 0.1
#define DEFAULT_MIN_MARGIN 0.01


/**
*@brief コンストラクタ
*@param ls 脚のリスト
*/
GaitBase::GaitBase(Leg_Object *ls, Body_Object *bo)
{
	legs = ls;
	body = bo;

	sampling_time = DEFAULT_SAMPLING_TIME;

	current_time = 0;

	state = UP_FRONT_RIGHT_LEG;
	dir = WALK_STOP;

	min_margin = DEFAULT_MIN_MARGIN;
}

/**
*@brief 刻み幅設定
* @param st サンプリング時間
*/
void GaitBase::setSamplingTime(double st)
{
	sampling_time = st;
}

/**
*@brief 歩行更新
* @param vx 速度(X)
* @param vy 速度(Y)
* @param dthe 回転速度
* @param sd 歩幅
*/
void GaitBase::walk(double vx, double vy, double dthe, double sd)
{

}

/**
*@brief 最低安定の設定
* @param msm 安定余裕
*/
void GaitBase::set_Min_Margin(double msm)
{
	min_margin = msm;
}

/**
*@brief 最低安定を満たしているかの判定
* 満たしていない場合は重心を移動させる
* @param mc 移動にかかるステップ数
*/
void GaitBase::judge_Stability(int mc)
{
	Stability_Margin sm = Stability_Margin::calc_stability_margin(legs);
	//std::cout << sm.distance << std::endl;
	if (sm.distance > min_margin)
	{
		return;
	}
	else
	{
		next_state = state;
		state = MOVE_STABILITY;
		/*for (int i = 0; i < 4; i++)
		{
		std::cout << legs[i].onGround() << std::endl;
		}*/
		double d = (-sm.distance + min_margin)* 1.2;
		Vector3d dp;
		dp(2) = 0;
		if (sm.stb_dir == STB_X_PLUS)
		{
			dp(0) = sqrt(d*d / (sm.slope*sm.slope + 1));
			dp(1) = -sm.slope*dp(0);
		}
		else if (sm.stb_dir == STB_X_MINUS)
		{
			dp(0) = -sqrt(d*d / (sm.slope*sm.slope + 1));
			dp(1) = -sm.slope*dp(0);
		}
		else if (sm.stb_dir == STB_Y_PLUS)
		{
			dp(0) = sqrt(d*d*sm.slope*sm.slope / (sm.slope*sm.slope + 1));
			dp(1) = -1.0 / sm.slope*dp(1);

		}
		else if (sm.stb_dir == STB_Y_MINUS)
		{
			dp(0) = -sqrt(d*d*sm.slope*sm.slope / (sm.slope*sm.slope + 1));
			dp(1) = -1.0 / sm.slope*dp(1);
		}
		//std::cout << dx << "\t" << dy << "\t" << sm.distance << "\t" << sm.slope << "\t" << sm.stb_dir << std::endl;

		//std::cout << legs[2].current_pos(0) << std::endl;
		for (int i = 0; i < 4; i++)
		{
			legs[i].set_state(ON_GROUND_MOVE_TARGET);
			legs[i].start_pos = legs[i].current_pos;
			legs[i].target_pos = legs[i].current_pos - dp;
			//std::cout << "move: " << dp(0) << "\t" << dp(1) << std::endl;
			//legs[i].next_stability_x_offset = 0;
			//legs[i].next_stability_y_offset = 0;
			legs[i].next_stability_x_offset = legs[i].stability_x_offset - dp(0);
			legs[i].next_stability_y_offset = legs[i].stability_y_offset - dp(1);
			//std::cout << legs[i].next_stability_x_offset << "\t" << legs[i].next_stability_y_offset << std::endl;
			legs[i].max_count = mc;////(int)(1.0/sampling_time);
		}
		body->set_state(ON_GROUND_MOVE_TARGET);
		body->start_pos = body->current_pos;
		body->target_pos = body->current_pos + dp;
		body->max_count = mc;

	}
}