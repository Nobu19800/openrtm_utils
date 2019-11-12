/*!
* @file  Leg_Object.h
* @brief 脚制御クラス
*
*/


#ifndef Leg_Object_H
#define Leg_Object_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

using namespace Eigen;



enum FootState
{
	ON_GROUND_CRAWL = 0,
	NOT_ON_GROUND_CRAWL = 1,
	MOVE_STOP = 2,
	MOVE_PAUSE = 3,
	ON_GROUND_INTERMITTENT_CRAWL = 4,
	NOT_ON_GROUND_INTERMITTENT_CRAWL = 5,
	ON_GROUND_MOVE_TARGET = 6,
	ON_GROUND_TROT = 7,
	NOT_ON_GROUND_TROT = 8,
};



/**
* @class Leg_Object
*@brief 脚制御クラス
*/
class Leg_Object
{
public:
	/**
	*@brief コンストラクタ
	*/
	Leg_Object();
	/**
	*@brief 脚が全て停止しているかを判定
	*@param legs 脚のリスト
	*@param len 脚のリストのサイズ
	*@return 停止していない脚の数、全て停止している場合は0
	*/
	static int LegsStop(Leg_Object *legs, int len);

	/**
	*@brief 回転中心位置、回転速度などの設定
	*@param p 回転中心位置
	*@param rv 回転速度
	*@param mc ステップ数
	*@param sampling サンプリング時間
	*@param target_position_update trueの場合は目標位置を再設定する
	*@param targetpos_rate 再設定する目標位置
	*/
	void setRotateStatus(Vector3d p, double rv, int mc, double sampling, bool target_position_update = true, double targetpos_rate = 1);
	/**
	*@brief 更新
	*/
	void update();
	/**
	*@brief 足先基準位置設定
	*@param cs 基準位置
	*/
	void set_center_pos(Vector3d cs);
	/**
	*@brief 状態設定
	*@param s 状態
	*/
	void set_state(FootState s);
	/**
	*@brief 目標位置設定
	*@param tp 目標位置
	*@param mc ステップ数
	*/
	void setTargetPos(Vector3d tp, int mc);
	/**
	*@brief オフセットを0にする
	*/
	void reset_offset();
	/**
	*@brief 回転速度、ステップ数の再設定
	*@param rv 回転速度
	*@param len 回転中心までの長さ
	*@param mc ステップ数
	*/
	void update_status(double rv, int mc);
	/**
	*@brief 接地しているかの判定
	*@return 接地している場合はtrue
	*/
	bool onGround();
	/**
	*@brief 逆運動学により関節角度を計算
	*@param pos 脚先位置
	*@return 関節角度
	*/
	std::vector<double> inverseKinematics(Vector3d pos);
	/**
	*@brief 順運動学により脚先位置を計算
	*@param the 関節角度
	*@return 脚先位置
	*/
	Vector3d calcKinematics(std::vector<double> the);
	/**
	*@brief 遊脚高さの設定
	*@param lh 高さ
	*/
	void setLiftHeight(double lh);
	/**
	*@brief ジョイントのオフセット設定
	*@param o1 ジョイント0のオフセット
	*@param o1 ジョイント1のオフセット
	*@param o1 ジョイント2のオフセット
	*/
	void setJointOffset(double o0, double o1, double o2);
	/**
	*@brief ジョイントの可動範囲上限の設定
	*@param o1 ジョイント0の可動範囲上限値
	*@param o1 ジョイント1の可動範囲上限値
	*@param o1 ジョイント2の可動範囲上限値
	*/
	void setUpperLimitJoint(double l0, double l1, double l2);
	/**
	*@brief ジョイントの可動範囲下限の設定
	*@param o1 ジョイント0の可動範囲下限値
	*@param o1 ジョイント1の可動範囲下限値
	*@param o1 ジョイント2の可動範囲下限値
	*/
	void setLowerLimitJoint(double l0, double l1, double l2);
	/**
	*@brief 関節角度の設定
	*@param t 関節角度
	*@return trueの場合は可動範囲外
	*/
	bool setAngle(std::vector<double> t);

	Vector3d pos[3];
	Vector3d pos_offset[3];
	Vector3d joint_pos[3];
	double foot_mass;
	double foot_width;
	double foot_len;
	double foot_height;
	Vector3d foot_pos;
	Vector3d foot_joint_pos;
	double theta[3];
	double leg_len[3], leg_width[3], leg_height[3];
	double leg_mass[3];
	double jointOffset[3];
	double UpperLimitJoint[3];
	double LowerLimitJoint[3];
	Vector3d center_pos;	
	double offset_angle;
	Vector3d rotate_pos;
	double rotate_len;
	double rotete_vel;
	FootState state;
	FootState last_state;
	double sampling_time;
	double step_time;
	int max_count;
	int count;
	Vector3d current_pos;
	double start_angle;
	int offset_count;
	Vector3d start_pos;
	Vector3d target_pos;
	double x_offset;
	double y_offset;
	//double move_rate;

	double stability_x_offset;
	double stability_y_offset;
	double next_stability_x_offset;
	double next_stability_y_offset;
	//int current_offset_count;

	double intermittent_x_offset;
	double intermittent_y_offset;
	double next_intermittent_x_offset;
	double next_intermittent_y_offset;

	double trot_offset;

	double lift_height;

};




#endif