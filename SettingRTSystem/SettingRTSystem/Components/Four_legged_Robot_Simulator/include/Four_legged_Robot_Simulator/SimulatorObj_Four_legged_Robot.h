/*!
* @file  SimulatorObj.h
* @brief シミュレーション関連のクラス
*
*/

#ifndef SIMULATOROBJ_Four_legged_Robot_H
#define SIMULATOROBJ_Four_legged_Robot_H

//#define dDOUBLE

#include <coil/Mutex.h>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>
#include <ode/ode.h>
#include <vector>

#include "Four_legged_Robot.h"




#ifdef _MSC_VER
#pragma warning(disable:4244 4305)  // for VC++, no precision loss complaints
#endif





/**
* @struct MyLink
*@brief ボディオブジェクト
*接続するジョイントも含む
*/
typedef struct {
  dBodyID  body;
  dGeomID  geom;
  dJointID joint;
  int  dir;
  float  red, green, blue;
  dReal    m,r,x,y,z,lx,ly,lz, the, dthe, ddthe, axisx, axisy, axisz, Tthe, Tdthe, Tddthe, tau, jx,jy,jz;
} MyLink;


/**
* @class SimulatorObj_Four_legged_Robot
*@brief シミュレーションの操作をするためのクラス
*/
class SimulatorObj_Four_legged_Robot
{
public:
	/**
	*@brief コンストラクタ
	*/
	SimulatorObj_Four_legged_Robot();
	/**
	*@brief デストラクタ
	*/
	~SimulatorObj_Four_legged_Robot();
	coil::Mutex mu;
	std::vector<std::vector<MyLink>> legs;
	MyLink body;
	Four_legged_Robot *rb;
	double st;
	double gravity;
	bool pause;
	dWorldID      world;       
	dSpaceID      space;       
	dGeomID       ground;       
	dJointGroupID contactgroup;
	bool foot_exist;

	
	
	/**
	*@brief 各パラメータの初期化を行う
	*/
	void makeParam();
	/**
	*@brief 直方体作成
	* @param body ボディオブジェクト
	*/
	void setBox(MyLink *body);
	/**
	*@brief 円柱作成
	* @param body ボディオブジェクト
	*/
	void setCylinder(MyLink *body);
	/**
	*@brief ヒンジジョイント作成
	* @param body1 ボディ1
	* @param body2 ボディ2
	*/
	void setHinge(MyLink *body1, MyLink *body2);
	/**
	*@brief スライダージョイント作成
	* @param body1 ボディ1
	* @param body2 ボディ2
	*/
	void setSlider(MyLink *body1, MyLink *body2);
	/**
	*@brief 固定ジョイント作成
	* @param body1 ボディ1
	* @param body2 ボディ2
	*/
	void setFixed(MyLink *body1, MyLink *body2);
	/**
	*@brief 全ボディ、接続する全ジョイント生成
	*/
	void makeRobot();
	/**
	*@brief ヒンジジョイント制御
	* @param body ボディオブジェクト
	* @param theta ヒンジジョイントの位置
	*/
	void controlHinge(MyLink *body, dReal theta);
	/**
	*@brief スライダージョイント制御
	* @param body ボディオブジェクト
	* @param length スライダージョイントの位置
	*/
	void controlSlider(MyLink *body, dReal length);
	/**
	*@brief 全ジョイント制御
	*/
	void control();
	/**
	*@brief 更新
	*/
	void update();
	/**
	*@brief 全ボディ、接続する全ジョイント消去
	*/
	void destroyRobot();

	/**
	*@brief 接触コールバック
	* @param o1 ジオメトリ1
	* @param o2 ジオメトリ2
	*/
	void m_nearCallback(dGeomID o1, dGeomID o2);
	/**
	*@brief 刻み幅設定
	* @param s サンプリング時間
	*/
	void setSamplingTime(double s);
	/**
	*@brief 足裏を作成するかを設定
	*@param fe trueで足裏作成
	*/
	void setFoot(bool fe);



};



#endif
