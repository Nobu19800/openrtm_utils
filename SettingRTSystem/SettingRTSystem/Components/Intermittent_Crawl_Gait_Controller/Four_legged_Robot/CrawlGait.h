/*!
* @file  CrawlGait.h
* @brief クロール歩容制御クラス
*
*/


#ifndef CrawlGait_H
#define CrawlGait_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

#include "Leg_Object.h"
#include "Body_Object.h"
#include "Direction_Object.h"
#include "Stability_Margin.h"
#include "GaitBase.h"

using namespace Eigen;




/**
* @class CrawlGait
*@brief クロール歩容制御クラス
*/
class CrawlGait : public GaitBase
{
public:
	/**
	*@brief コンストラクタ
	* @param ls 脚のリスト
	*/
	CrawlGait(Leg_Object *ls, Body_Object *bo);
	/**
	*@brief 歩行更新
	* @param vx 速度(X)
	* @param vy 速度(Y)
	* @param dthe 回転速度
	* @param sd 歩幅
	*/
	virtual void walk(double vx, double vy, double dthe, double sd);
};





#endif