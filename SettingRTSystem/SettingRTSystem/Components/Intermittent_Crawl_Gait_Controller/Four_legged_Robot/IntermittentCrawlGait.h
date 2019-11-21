/*!
* @file  IntermittentCrawlGait.h
* @brief 間歇クロール歩容制御クラス
*
*/


#ifndef IntermittentCrawlGait_H
#define IntermittentCrawlGait_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

#include "Leg_Object.h"
#include "Direction_Object.h"
#include "Stability_Margin.h"
#include "GaitBase.h"

using namespace Eigen;


/**
* @class CrawlGait
*@brief 間歇クロール歩容制御クラス
*/
class IntermittentCrawlGait : public GaitBase
{
public:
	/**
	*@brief コンストラクタ
	* @param ls 脚のリスト
	*/
	IntermittentCrawlGait(Leg_Object *ls, Body_Object *bo);
	/**
	*@brief 歩行更新
	* @param vx 速度(X)
	* @param vy 速度(Y)
	* @param dthe 回転速度
	* @param sd 歩幅
	*/
	virtual void walk(double vx, double vy, double dthe, double sd);
	/**
	*@brief 横方向への移動距離設定
	* @param smd 移動距離
	*/
	void setSideMoveDistance(double smd);
	double side_move_distance;

};

#endif