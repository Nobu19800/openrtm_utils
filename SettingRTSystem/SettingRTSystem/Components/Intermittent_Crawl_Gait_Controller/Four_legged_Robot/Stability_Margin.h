/*!
* @file  Stability_Margin.h
* @brief 安定余裕計算クラス
*
*/


#ifndef Stability_Margin_H
#define Stability_Margin_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

#include "Leg_Object.h"

using namespace Eigen;



enum Stability_Direction
{
	STB_X_PLUS = 0,
	STB_X_MINUS = 1,
	STB_Y_PLUS = 2,
	STB_Y_MINUS = 3,
};






/**
* @class Stability_Margin
*@brief 安定余裕計算クラス
*/
class Stability_Margin
{
public:
	/**
	*@brief コンストラクタ
	*/
	Stability_Margin();
	/**
	*@brief 全脚から安定余裕計算
	*@param legs 脚のリスト
	*@param ne trueの場合はNE安定余裕も計算
	*@param tf trueの場合は目標位置での安定余裕も計算
	*/
	static Stability_Margin calc_stability_margin(Leg_Object *legs,bool ne = false, bool tf = true);
	/**
	*@brief 重心位置と支持脚直線の距離を計算
	*@param pos0 脚0の位置
	*@param pos1 脚1の位置
	*@param dir 安定になる重心位置の方向
	*@param ne trueの場合はNE安定余裕も計算
	*/
	static Stability_Margin calc_distance(Vector3d pos0, Vector3d pos1, Stability_Direction dir, bool ne = false);
	/**
	*@brief 安定余裕を取得
	*@param ne trueの場合はNE安定余裕を取得
	*@return 安定余裕
	*/
	double getDistance(bool ne);
	double distance;
	double slope;
	double ne_distance;
	Stability_Direction stb_dir;
};





#endif