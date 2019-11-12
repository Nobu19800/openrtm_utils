/*!
* @file  Four_legged_Robot.h
* @brief 四足歩行ロボット制御クラス
*
*/


#ifndef Four_legged_Robot_H
#define Four_legged_Robot_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

using namespace Eigen;



#include "Leg_Object.h"
#include "Direction_Object.h"
#include "Stability_Margin.h"
#include "GaitBase.h"
#include "CrawlGait.h"
#include "IntermittentCrawlGait.h"
#include "TrotGait.h"
#include "Body_Object.h"


/**
* @class Four_legged_Robot
*@brief 四足歩行ロボット制御クラス
*/
class Four_legged_Robot
{
public:
	/**
	*@brief コンストラクタ
	*/
	Four_legged_Robot();
	/**
	*@brief デストラクタ
	*/
	~Four_legged_Robot();
	/**
	*@brief 脚先位置から関節角度取得
	*@param the 脚先位置
	* @return 関節角度
	*/
	std::vector<double> inverseKinematics(Vector3d pos, int num);
	/**
	*@brief 脚先位置取得
	*@param the 関節角度
	* @return 脚先位置
	*/
	Vector3d calcKinematics(std::vector<double> the, int num);
	/**
	*@brief 関節角度を入力
	* @param the 関節角度
	*/
	void setAngle(std::vector<double> the[4]);
	/**
	*@brief 脚先速度から関節角速度を取得
	* @param v 脚先速度
	* @return 関節角速度
	*/
	Vector3d calcJointVel(std::vector<double> the[4]);
	/**
	*@brief 関節角速度の入力から関節角度を更新
	* @param the 関節角速度
	*/
	void updatePos(std::vector<double> the[4]);
	/**
	*@brief 未実装
	*/
	void update();
	/**
	*@brief クロール歩容の足先位置計算
	* @param vx 速度(X軸方向)
	* @param vy 速度(Y軸方向)
	* @param dthe 回転速度
	* @param stride 歩幅
	*/
	void crawl_gait(double vx, double vy, double dthe, double stride);
	/**
	*@brief 間歇クロール歩容の足先位置計算
	* @param vx 速度(X軸方向)
	* @param vy 速度(Y軸方向)
	* @param dthe 回転速度
	* @param stride 歩幅
	*/
	void intermittent_crawl_gait(double vx, double vy, double dthe, double stride);
	/**
	*@brief トロット歩容の足先位置計算
	* @param vx 速度(X軸方向)
	* @param vy 速度(Y軸方向)
	* @param dthe 回転速度
	* @param stride 歩幅
	*/
	void trot_gait(double vx, double vy, double dthe, double stride);
	/**
	*@brief 刻み幅設定
	* @param st サンプリング時間
	*/
	void setSamplingTime(double st);
	/**
	*@brief 足先基準位置設定
	* @param pos_x 位置(X)
	* @param pos_y 位置(Y)
	* @param pos_z 位置(Z)
	*/
	void setCenterPosition(double pos_x, double pos_y, double pos_z);
	/**
	*@brief 最低安定余裕設定
	* @param msm 安定余裕
	*/
	void setMinMargin(double msm);

	/**
	*@brief 遊脚高さ設定設定
	* @param h 高さ
	*/
	void setLiftHeight(double h);
	/**
	*@brief ロボットの現在位置設定
	* @param pos 現在位置
	* @param rot 現在の姿勢
	*/
	void setCurrentPosition(Vector3d pos, Vector3d rot);

	/**
	*@brief 安定余裕取得
	*@return 安定余裕
	*/
	double getStabilityMargin();
	/**
	*@brief NE安定余裕取得
	*@return NE安定余裕
	*/
	double getNEStabilityMargin();

	/**
	*@brief ボディのパラメータ設定
	*@param size 寸法
	*@param pos 中心位置
	*@param mass 重量
	*/
	void setBodyParam(Vector3d size, Vector3d pos, double mass);
	/**
	*@brief リンクのパラメータ設定
	*@param size 寸法
	*@param offset オフセット
	*@param mass 重量
	*@param num 番号
	*/
	void setLinkParam(Vector3d size, Vector3d offset, double mass, int num);
	/**
	*@brief リンク0のパラメータ設定
	*@param size 寸法
	*@param offset オフセット
	*@param mass 重量
	*/
	void setLink0Param(Vector3d size, Vector3d offset, double mass);
	/**
	*@brief リンク1のパラメータ設定
	*@param size 寸法
	*@param offset オフセット
	*@param mass 重量
	*/
	void setLink1Param(Vector3d size, Vector3d offset, double mass);
	/**
	*@brief リンク2のパラメータ設定
	*@param size 寸法
	*@param offset オフセット
	*@param mass 重量
	*/
	void setLink2Param(Vector3d size, Vector3d offset, double mass);
	/**
	*@brief 足裏のパラメータ設定
	*@param size 寸法
	*@param offset オフセット
	*@param mass 重量
	*/
	void setFootParam(Vector3d size, Vector3d offset, double mass);
	/**
	*@brief 設定したリンクパラメータから位置、姿勢を再計算
	*/
	void setPose();
	
	Leg_Object legs[4];
	Body_Object body;
	


	CrawlGait *cw_obj;
	IntermittentCrawlGait *icw_obj;
	TrotGait *trot_obj;
};



#endif