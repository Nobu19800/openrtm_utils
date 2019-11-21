/*!
* @file  DrawThread.h
* @brief シミュレーション描画関連のクラス
*
*/

#ifndef DrawThread_Four_legged_Robot_H
#define DrawThread_Four_legged_Robot_H


#include <coil/Task.h>

#include <stdio.h>
#include <stdlib.h>
#include <drawstuff/drawstuff.h>
#include "SimulatorObj_Four_legged_Robot.h"



/**
* @class DrawThread_Four_legged_Robot
*@brief シミュレーションの描画をするスレッド
*/
class DrawThread_Four_legged_Robot : public virtual coil::Task
{
public:
		/**
		*@brief コンストラクタ
		*/
		DrawThread_Four_legged_Robot(SimulatorObj_Four_legged_Robot *so);
		
		/**
		*@brief スレッド実行関数
		* @return 
		*/
		virtual int svc();
		/**
		*@brief DrawStuff初期化
		*/
		void setDrawStuff();
		/**
		*@brief 直方体描画
		* @param body ボディオブジェクト
		*/
		void drawBox(MyLink *body);
		/**
		*@brief 円柱描画
		* @param body ボディオブジェクト
		*/
		void drawCylinder(MyLink *body);
		/**
		*@brief 全ボディ描画
		*/
		void drawRobot();

		/**
		*@brief カメラ位置再設定
		*/
		void resetCameraPosition();
		/**
		*@brief カメラ位置再設定フラグを立てる
		*/
		void setRCPFlag();
		/**
		*@brief 描画を停止する
		*/
		void stop();


		double fps;
		bool RCP_flag;
		bool stop_flag;
		

		int m_pause;


private:
	SimulatorObj_Four_legged_Robot *m_so;
	dsFunctions   fn;
	

};

#endif