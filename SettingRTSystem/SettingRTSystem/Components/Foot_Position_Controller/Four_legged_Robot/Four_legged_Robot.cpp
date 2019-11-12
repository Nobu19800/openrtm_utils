/*!
* @file  Four_legged_Robot.cpp
* @brief 四足歩行ロボット制御クラス
*
*/


#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "Four_legged_Robot.h"

#define LegLength0 0.02
#define LegLength1 0.055
#define LegLength2 0.08

#define LegMath0 0.2
#define LegMath1 0.1
#define LegMath2 0.001

#define BodyLength 0.07
#define BodyWidth 0.07
#define BodyHeight 0.005

#define BodyMath 0.3



#define LegWidth0 0.02
#define LegWidth1 0.005
#define LegWidth2 0.005

#define LegHeight0 0.025
#define LegHeight1 0.01
#define LegHeight2 0.005


#define BodyPositon_X 0
#define BodyPositon_Y 0
#define BodyPositon_Z LegLength2 + LegHeight0 + BodyHeight + 0.005


#define MOTOR_UPPER__LIMIT_0 M_PI*90/180+0.001
#define MOTOR_UPPER__LIMIT_1 M_PI*90/180+0.001
#define MOTOR_UPPER__LIMIT_2 M_PI*90/180+0.001

#define MOTOR_LOWER__LIMIT_0 -M_PI*90/180-0.001
#define MOTOR_LOWER__LIMIT_1 -M_PI*90/180-0.001
#define MOTOR_LOWER__LIMIT_2 -M_PI*90/180-0.001


#define MOTOR_OFFSET_0 0
#define MOTOR_OFFSET_1 0
#define MOTOR_OFFSET_2 0


#define FOOT_LENGTH 0.16
#define FOOT_WIDTH 0.12
#define FOOT_HEIGHT 0.005
#define FOOT_MASS 0.1




/**
*@brief 四足歩行ロボット制御クラスのコンストラクタ
*/
Four_legged_Robot::Four_legged_Robot()
{

	setLink0Param(Vector3d(LegLength0, LegWidth0, LegHeight0), Vector3d(0, 0, 0), LegMath0);
	setLink1Param(Vector3d(LegLength1, LegWidth1, LegHeight1), Vector3d(0, 0, 0), LegMath1);
	setLink2Param(Vector3d(LegLength2, LegWidth2, LegHeight2), Vector3d(0, 0, 0), LegMath2);

	/*for (int i = 0; i < 4; i++)
	{
		

		legs[i].leg_len[0] = LegLength0;
		legs[i].leg_len[1] = LegLength1;
		legs[i].leg_len[2] = LegLength2;

		legs[i].leg_width[0] = LegWidth0;
		legs[i].leg_width[1] = LegWidth1;
		legs[i].leg_width[2] = LegWidth2;

		legs[i].leg_height[0] = LegHeight0;
		legs[i].leg_height[1] = LegHeight1;
		legs[i].leg_height[2] = LegHeight2;

		legs[i].leg_mass[0] = LegMath0;
		legs[i].leg_mass[1] = LegMath1;
		legs[i].leg_mass[2] = LegMath2;
	}
	*/
	setFootParam(Vector3d(FOOT_LENGTH,FOOT_WIDTH,FOOT_HEIGHT), Vector3d(0,0,0),FOOT_MASS);
	setBodyParam(Vector3d(BodyLength, BodyWidth, BodyHeight), Vector3d(BodyPositon_X, BodyPositon_Y, BodyPositon_Z), BodyMath);
	/*body.lx = BodyLength;
	body.ly = BodyWidth;
	body.lz = BodyHeight;
	body.mass = BodyMath;*/


	/*for(int i=0;i < 4;i++)
	{
		for(int j=0;j < 3;j++)
		{
			legs[i].theta[j] = 0;
		}
	}*/

	setMotorOffset(MOTOR_OFFSET_0, MOTOR_OFFSET_1, MOTOR_OFFSET_2);
	setMotorLimit(MOTOR_UPPER__LIMIT_0, MOTOR_UPPER__LIMIT_1, MOTOR_UPPER__LIMIT_2, MOTOR_LOWER__LIMIT_0, MOTOR_LOWER__LIMIT_1, MOTOR_LOWER__LIMIT_2);

	//body.set_position(Vector3d(BodyPositon_X, BodyPositon_Y, BodyPositon_Z));

	/*for (int i = 0; i < 4; i++)
	{
		legs[i].setJointOffset(MOTOR_OFFSET_0, MOTOR_OFFSET_1, MOTOR_OFFSET_2);
		legs[i].setUpperLimitJoint(MOTOR_UPPER__LIMIT_0, MOTOR_UPPER__LIMIT_1, MOTOR_UPPER__LIMIT_2);
		legs[i].setLowerLimitJoint(MOTOR_LOWER__LIMIT_0, MOTOR_LOWER__LIMIT_1, MOTOR_LOWER__LIMIT_2);
		/*legs[i].jointOffset[0] = MOTOR_OFFSET_0;
		legs[i].jointOffset[1] = MOTOR_OFFSET_1;
		legs[i].jointOffset[2] = MOTOR_OFFSET_2;
		legs[i].UpperLimitJoint[0] = MOTOR_UPPER__LIMIT_0;
		legs[i].UpperLimitJoint[1] = MOTOR_UPPER__LIMIT_1;
		legs[i].UpperLimitJoint[2] = MOTOR_UPPER__LIMIT_2;
		legs[i].LowerLimitJoint[0] = MOTOR_LOWER__LIMIT_0;
		legs[i].LowerLimitJoint[1] = MOTOR_LOWER__LIMIT_1;
		legs[i].LowerLimitJoint[2] = MOTOR_LOWER__LIMIT_2;*/
	//}



	

	setPose();


	
	//pos_rf.push_back(pos_rf2);

	//pos[3] = pos_rf;
	//joint_pos[3] = joint_pos_rf;
	double center_pos_offset_angle = 0.6;
	double center_pos_offset_x = (legs[0].leg_len[0] + legs[0].leg_len[1]) * sin(center_pos_offset_angle);
	double center_pos_offset_y = (legs[0].leg_len[0] + legs[0].leg_len[1]) * (cos(center_pos_offset_angle) - 1);
	
	Vector3d cs;
	cs(0) = legs[0].pos[2](0) - body.pos(0) + center_pos_offset_x;
	cs(1) = legs[0].pos[2](1) - body.pos(1) + center_pos_offset_y;
	cs(2) = (legs[0].pos[2](2) - legs[0].leg_len[2] / 2.0) - body.pos(2) + 0.016;
	//std::cout << cs << std::endl;
	setCenterPosition(cs(0), cs(1), cs(2));
	

	cw_obj = new CrawlGait(legs, &body);
	icw_obj = new IntermittentCrawlGait(legs, &body);
	trot_obj = new TrotGait(legs, &body);

	
}

/**
*@brief コピーコンストラクタ
*/
Four_legged_Robot::Four_legged_Robot(Four_legged_Robot &fo)
{
	for (int i = 0; i < 4; i++)
	{
		legs[i] = fo.legs[i];
	}
	body = fo.body;

	cw_obj = new CrawlGait(legs, &body);
	icw_obj = new IntermittentCrawlGait(legs, &body);
	trot_obj = new TrotGait(legs, &body);

	

}

/**
*@brief デストラクタ
*/
Four_legged_Robot::~Four_legged_Robot()
{
	delete cw_obj;
	delete icw_obj;
	delete trot_obj;
}


/**
*@brief 脚先位置から関節角度取得
*@param the 脚先位置
* @return 関節角度
*/
std::vector<double> Four_legged_Robot::inverseKinematics(Vector3d pos, int num)
{
	if (num == 0)
	{
		pos(0) = pos(0) - this->body.lx / 2.0;
		pos(1) = pos(1) - this->body.ly / 2.0;
	}
	else if (num == 1)
	{
		pos(0) = pos(0) + this->body.lx / 2.0;
		pos(1) = pos(1) - this->body.ly / 2.0;
	}
	else if (num == 2)
	{
		pos(0) = pos(0) + this->body.lx / 2.0;
		pos(1) = pos(1) + this->body.ly / 2.0;
	}
	else if (num == 3)
	{
		pos(0) = pos(0) - this->body.lx / 2.0;
		pos(1) = pos(1) + this->body.ly / 2.0;
	}

	std::vector<double> the;
	/*for (int i = 0; i < 3; i++)
	{
		the.push_back(0);
	}*/
	//pos(2) = -pos(2);
	pos(2) = pos(2) + body.lz / 2.0 + legs[num].leg_height[0] / 2.0 - legs[num].pos_offset[0](2);
	the = legs[num].inverseKinematics(pos);
	//the[0] = atan2(pos(1), pos(0));
	/*double ld_xy = sqrt(pos(0)*pos(0) + pos(1)*pos(1)) - leg_len[0];
	double ld = sqrt(pos(2)*pos(2) + ld_xy*ld_xy);
	double beta = acos((leg_len[1] * leg_len[1] + leg_len[2] * leg_len[2] - ld*ld) / (2 * leg_len[1] * leg_len[2]));
	double alpha = acos((leg_len[1] * leg_len[1] + ld*ld - leg_len[2] * leg_len[2]) / (2 * leg_len[1] * ld));
	double phi = atan2(ld_xy, pos(2));
	the[1] = -(M_PI / 2 - alpha - phi);
	
	the[2] = -(M_PI - beta);
	*/
	/*double ld_xy = sqrt(pos(0)*pos(0) + pos(1)*pos(1)) - legs[num].leg_len[0];
	double ld = sqrt(pos(2)*pos(2) + ld_xy*ld_xy);
	double c3 = (ld*ld - legs[num].leg_len[1] * legs[num].leg_len[1] - legs[num].leg_len[2] * legs[num].leg_len[2]) / (2 * legs[num].leg_len[1] * legs[num].leg_len[2]);
	double s3 = sqrt(1 - c3*c3);

	the[2] = atan2(s3, c3);
	
	double A = ld_xy;
	double M = legs[num].leg_len[1] + legs[num].leg_len[2] * c3;
	double B = pos[2];
	double N = legs[num].leg_len[2] * s3;
	the[1] = atan2(M*A-N*B,N*A+M*B);*/
	/*//if (num == 0)
	{
		Vector3d a = calcKinematics(the, num);
		//std::cout << num << "\t" << the[0] << "\t" << the[1] << "\t" << the[2] << std::endl;
		//std::cout << "p\t" << pos(0) << "\t" << pos(1) << "\t" << pos(2) << std::endl;
		//std::cout << "a\t" << a(0) << "\t" << a(1) << "\t" << a(2) << std::endl;
	}*/
	return the;
}

/**
*@brief 脚先位置取得
*@param the 関節角度
* @return 脚先位置
*/
Vector3d Four_legged_Robot::calcKinematics(std::vector<double> the, int num)
{
	Vector3d pos;
	/*if (the.size() < 3)return pos;
	pos(2) = legs[num].leg_len[1] * cos(the[1]) + legs[num].leg_len[2] * cos(the[1] + the[2]) - body_lz / 2.0 - legs[num].leg_height[0] / 2.0;
	double ld = legs[num].leg_len[1] * sin(the[1]) + legs[num].leg_len[2] * sin(the[1] + the[2]) + legs[num].leg_len[0];
	pos(0) = ld * cos(the[0]);
	pos(1) = ld * sin(the[0]);*/
	pos = legs[num].calcKinematics(the);
	pos(2) += -body.lz / 2.0 - legs[num].leg_height[0] / 2.0 + legs[num].pos_offset[0](2);

	if (num == 0)
	{
		pos(0) = pos(0) + this->body.lx / 2.0;
		pos(1) = pos(1) + this->body.ly / 2.0;
	}
	else if (num == 1)
	{
		pos(0) = pos(0) - this->body.lx / 2.0;
		pos(1) = pos(1) + this->body.ly / 2.0;
	}
	else if (num == 2)
	{
		pos(0) = pos(0) - this->body.lx / 2.0;
		pos(1) = pos(1) - this->body.ly / 2.0;
	}
	else if (num == 3)
	{
		pos(0) = pos(0) + this->body.lx / 2.0;
		pos(1) = pos(1) - this->body.ly / 2.0;
	}

	return pos;
}
/**
*@brief 関節角度を入力
* @param the 関節角度
*/
void Four_legged_Robot::setAngle(std::vector<double> the[4])
{


}
/**
*@brief 脚先速度から関節角速度を取得
* @param v 脚先速度
* @return 関節角速度
*/
Vector3d Four_legged_Robot::calcJointVel(std::vector<double> the[4])
{
	Vector3d vel;
	return vel;

}
/**
*@brief 関節角速度の入力から関節角度を更新
* @param the 関節角速度
*/
void Four_legged_Robot::updatePos(std::vector<double> the[4])
{

}

/**
*@brief 未実装
*/
void Four_legged_Robot::update()
{

}

/**
*@brief クロール歩容の足先位置計算
* @param vx 速度(X軸方向)
* @param vy 速度(Y軸方向)
* @param dthe 回転速度
* @param stride 歩幅
*/
void Four_legged_Robot::crawl_gait(double vx, double vy, double dthe, double stride)
{
	
	
	cw_obj->walk(vx, vy, dthe, stride);

}

/**
*@brief 間歇クロール歩容の足先位置計算
* @param vx 速度(X軸方向)
* @param vy 速度(Y軸方向)
* @param dthe 回転速度
* @param stride 歩幅
*/
void Four_legged_Robot::intermittent_crawl_gait(double vx, double vy, double dthe, double stride)
{
	icw_obj->walk(vx, vy, dthe, stride);
}

/**
*@brief トロット歩容の足先位置計算
* @param vx 速度(X軸方向)
* @param vy 速度(Y軸方向)
* @param dthe 回転速度
* @param stride 歩幅
*/
void Four_legged_Robot::trot_gait(double vx, double vy, double dthe, double stride)
{
	trot_obj->walk(vx, vy, dthe, stride);
}

/**
*@brief 刻み幅設定
* @param st サンプリング時間
*/
void Four_legged_Robot::setSamplingTime(double st)
{
	cw_obj->setSamplingTime(st);
	icw_obj->setSamplingTime(st);
	trot_obj->setSamplingTime(st);
}

/**
*@brief 足先基準位置設定
* @param pos_x 位置(X)
* @param pos_y 位置(Y)
* @param pos_z 位置(Z)
*/
void Four_legged_Robot::setCenterPosition(double pos_x, double pos_y, double pos_z)
{
	for (int i = 0; i < 4; i++)
	{
		Vector3d cs;
		//cs(0) = legs[i].pos[2](0) - body_pos(0);
		//cs(1) = legs[i].pos[2](1) - body_pos(1);
		//cs(2) = (legs[i].pos[2](2) - legs[i].leg_len[2] / 2.0) - body_pos(2);

		cs(2) = pos_z;


		if (i == 0)
		{
			cs(0) = pos_x;
			cs(1) = pos_y;
		}
		else if (i == 1)
		{
			cs(0) = -pos_x;
			cs(1) = pos_y;
		}
		else if (i == 2)
		{
			cs(0) = -pos_x;
			cs(1) = -pos_y;
		}
		else if (i == 3)
		{
			cs(0) = pos_x;
			cs(1) = -pos_y;
		}

		legs[i].set_center_pos(cs);
	}
}

/**
*@brief 最低安定余裕設定
* @param msm 安定余裕
*/
void Four_legged_Robot::setMinMargin(double msm)
{
	cw_obj->set_Min_Margin(msm);
	icw_obj->set_Min_Margin(msm);
	trot_obj->set_Min_Margin(msm);
}

/**
*@brief ロボットの現在位置設定
* @param pos 現在位置
* @param rot 現在の姿勢
*/
void Four_legged_Robot::setCurrentPosition(Vector3d pos, Vector3d rot)
{
	body.current_pos = pos;
	body.current_rot = rot;
}

/**
*@brief 安定余裕取得
*@return 安定余裕
*/
double Four_legged_Robot::getStabilityMargin()
{
	Stability_Margin sm = Stability_Margin::calc_stability_margin(legs, false, false);
	return sm.distance;
}
/**
*@brief NE安定余裕取得
*@return NE安定余裕
*/
double Four_legged_Robot::getNEStabilityMargin()
{
	Stability_Margin sm = Stability_Margin::calc_stability_margin(legs, true, false);
	return sm.ne_distance;
}


/**
*@brief 遊脚高さ設定設定
* @param h 高さ
*/
void Four_legged_Robot::setLiftHeight(double h)
{
	for (int i = 0; i < 4; i++)
	{
		legs[i].setLiftHeight(h);
	}
}




/**
*@brief ボディのパラメータ設定
*@param size 寸法
*@param pos 中心位置
*@param mass 重量
*/
void Four_legged_Robot::setBodyParam(Vector3d size, Vector3d pos, double mass)
{
	body.lx = size(0);
	body.ly = size(1);
	body.lz = size(2);
	body.mass = mass;

	body.set_position(pos);
}


/**
*@brief リンクのパラメータ設定
*@param size 寸法
*@param offset オフセット
*@param mass 重量
*@param num 番号
*/
void Four_legged_Robot::setLinkParam(Vector3d size, Vector3d offset, double mass, int num)
{
	for (int i = 0; i < 4; i++)
	{
		legs[i].leg_len[num] = size(0);
		legs[i].leg_width[num] = size(1);
		legs[i].leg_height[num] = size(2);
		legs[i].leg_mass[num] = mass;
		legs[i].pos_offset[num] = offset;
		if (num == 1)
		{
			legs[i].pos_offset[num](0) = -offset(0);
		}
		else if (num == 2)
		{
			legs[i].pos_offset[num](0) = -offset(0);
			legs[i].pos_offset[num](1) = -offset(1);
		}

	}
}


/**
*@brief 足裏のパラメータ設定
*@param size 寸法
*@param offset オフセット
*@param mass 重量
*/
void Four_legged_Robot::setFootParam(Vector3d size, Vector3d offset, double mass)
{
	for (int i = 0; i < 4; i++)
	{
		legs[i].foot_len = size(0);
		legs[i].foot_width = size(1);
		legs[i].foot_height = size(2);
		legs[i].foot_mass = mass;

	}
}

/**
*@brief リンク0のパラメータ設定
*@param size 寸法
*@param offset オフセット
*@param mass 重量
*/
void Four_legged_Robot::setLink0Param(Vector3d size, Vector3d offset, double mass)
{
	setLinkParam(size, offset, mass, 0);
}

/**
*@brief リンク1のパラメータ設定
*@param size 寸法
*@param offset オフセット
*@param mass 重量
*/
void Four_legged_Robot::setLink1Param(Vector3d size, Vector3d offset, double mass)
{
	setLinkParam(size, offset, mass, 1);
}

/**
*@brief リンク2のパラメータ設定
*@param size 寸法
*@param offset オフセット
*@param mass 重量
*/
void Four_legged_Robot::setLink2Param(Vector3d size, Vector3d offset, double mass)
{
	setLinkParam(size, offset, mass, 2);
}


/**
*@brief 設定したリンクパラメータから位置、姿勢を再計算
*/
void Four_legged_Robot::setPose()
{
	//std::vector<Vector3d> pos_lf, joint_pos_lf;



	legs[0].joint_pos[0](0) = body.pos(0) + body.lx / 2.0;
	legs[0].joint_pos[0](1) = body.pos(1) + body.ly / 2.0;
	legs[0].joint_pos[0](2) = body.pos(2) - body.lz / 2.0 - legs[0].leg_height[0] / 2.0;



	legs[0].joint_pos[0] += legs[0].pos_offset[0];

	//joint_pos_lf.push_back(joint_pos_lf0);


	legs[0].pos[0](0) = legs[0].joint_pos[0](0);
	legs[0].pos[0](1) = legs[0].joint_pos[0](1) + legs[0].leg_len[0] / 2.0;
	legs[0].pos[0](2) = legs[0].joint_pos[0](2);

	//pos_lf.push_back(pos_lf0);


	legs[0].joint_pos[1](0) = legs[0].pos[0](0);
	legs[0].joint_pos[1](1) = legs[0].pos[0](1) + legs[0].leg_len[0] / 2.0;
	legs[0].joint_pos[1](2) = legs[0].pos[0](2);

	legs[0].joint_pos[1] += legs[0].pos_offset[1];

	//joint_pos_lf.push_back(joint_pos_lf1);


	legs[0].pos[1](0) = legs[0].joint_pos[1](0);
	legs[0].pos[1](1) = legs[0].joint_pos[1](1) + legs[0].leg_len[1] / 2.0;
	legs[0].pos[1](2) = legs[0].joint_pos[1](2);

	//pos_lf.push_back(pos_lf1);


	legs[0].joint_pos[2](0) = legs[0].pos[1](0);
	legs[0].joint_pos[2](1) = legs[0].pos[1](1) + legs[0].leg_len[1] / 2.0;
	legs[0].joint_pos[2](2) = legs[0].pos[1](2);

	legs[0].joint_pos[2] += legs[0].pos_offset[2];

	//joint_pos_lf.push_back(joint_pos_lf2);


	legs[0].pos[2](0) = legs[0].joint_pos[2](0);
	legs[0].pos[2](1) = legs[0].joint_pos[2](1);
	legs[0].pos[2](2) = legs[0].joint_pos[2](2) - legs[0].leg_len[2] / 2.0;

	legs[0].foot_joint_pos(0) = legs[0].pos[2](0);
	legs[0].foot_joint_pos(1) = legs[0].pos[2](1);
	legs[0].foot_joint_pos(2) = legs[0].pos[2](2) - legs[0].leg_len[2] / 2.0 - legs[0].leg_width[2] / 2.0;;

	legs[0].foot_pos(0) = legs[0].foot_joint_pos(0);
	legs[0].foot_pos(1) = legs[0].foot_joint_pos(1);
	legs[0].foot_pos(2) = legs[0].foot_joint_pos(2) - legs[0].foot_height / 2.0;
	//pos_lf.push_back(pos_lf2);

	//legs[0].pos = pos_lf;
	//legs[0].joint_pos = joint_pos_lf;




	//std::vector<Vector3d> pos_lb, joint_pos_lb;



	legs[1].joint_pos[0](0) = body.pos(0) - body.lx / 2.0;
	legs[1].joint_pos[0](1) = body.pos(1) + body.ly / 2.0;
	legs[1].joint_pos[0](2) = body.pos(2) - body.lz / 2.0 - legs[1].leg_height[0] / 2.0;

	legs[1].joint_pos[0] += legs[1].pos_offset[0];

	//joint_pos_lb.push_back(joint_pos_lb0);


	legs[1].pos[0](0) = legs[1].joint_pos[0](0);
	legs[1].pos[0](1) = legs[1].joint_pos[0](1) + legs[1].leg_len[0] / 2.0;
	legs[1].pos[0](2) = legs[1].joint_pos[0](2);

	//pos_lb.push_back(pos_lb0);


	legs[1].joint_pos[1](0) = legs[1].pos[0](0);
	legs[1].joint_pos[1](1) = legs[1].pos[0](1) + legs[1].leg_len[0] / 2.0;
	legs[1].joint_pos[1](2) = legs[1].pos[0](2);


	legs[1].joint_pos[1] += legs[1].pos_offset[1];

	//joint_pos_lb.push_back(joint_pos_lb1);


	legs[1].pos[1](0) = legs[1].joint_pos[1](0);
	legs[1].pos[1](1) = legs[1].joint_pos[1](1) + legs[1].leg_len[1] / 2.0;
	legs[1].pos[1](2) = legs[1].joint_pos[1](2);

	//pos_lb.push_back(pos_lb1);


	legs[1].joint_pos[2](0) = legs[1].pos[1](0);
	legs[1].joint_pos[2](1) = legs[1].pos[1](1) + legs[1].leg_len[1] / 2.0;
	legs[1].joint_pos[2](2) = legs[1].pos[1](2);

	legs[1].joint_pos[2] += legs[1].pos_offset[2];
	//joint_pos_lb.push_back(joint_pos_lb2);


	legs[1].pos[2](0) = legs[1].joint_pos[2](0);
	legs[1].pos[2](1) = legs[1].joint_pos[2](1);
	legs[1].pos[2](2) = legs[1].joint_pos[2](2) - legs[1].leg_len[2] / 2.0;


	legs[1].foot_joint_pos(0) = legs[1].pos[2](0);
	legs[1].foot_joint_pos(1) = legs[1].pos[2](1);
	legs[1].foot_joint_pos(2) = legs[1].pos[2](2) - legs[1].leg_len[2] / 2.0 - legs[1].leg_width[2] / 2.0;;

	legs[1].foot_pos(0) = legs[1].foot_joint_pos(0);
	legs[1].foot_pos(1) = legs[1].foot_joint_pos(1);
	legs[1].foot_pos(2) = legs[1].foot_joint_pos(2) - legs[1].foot_height / 2.0;
	//pos_lb.push_back(pos_lb2);

	//pos[1] = pos_lb;
	//joint_pos[1] = joint_pos_lb;




	//std::vector<Vector3d> pos_rb, joint_pos_rb;



	legs[2].joint_pos[0](0) = body.pos(0) - body.lx / 2.0;
	legs[2].joint_pos[0](1) = body.pos(1) - body.ly / 2.0;
	legs[2].joint_pos[0](2) = body.pos(2) - body.lz / 2.0 - legs[2].leg_height[0] / 2.0;

	legs[2].joint_pos[0] += legs[2].pos_offset[0];
	//joint_pos_rb.push_back(joint_pos_rb0);


	legs[2].pos[0](0) = legs[2].joint_pos[0](0);
	legs[2].pos[0](1) = legs[2].joint_pos[0](1) - legs[2].leg_len[0] / 2.0;
	legs[2].pos[0](2) = legs[2].joint_pos[0](2);

	//pos_rb.push_back(pos_rb0);


	legs[2].joint_pos[1](0) = legs[2].pos[0](0);
	legs[2].joint_pos[1](1) = legs[2].pos[0](1) - legs[2].leg_len[0] / 2.0;
	legs[2].joint_pos[1](2) = legs[2].pos[0](2);

	legs[2].joint_pos[1] += legs[2].pos_offset[1];
	//joint_pos_rb.push_back(joint_pos_rb1);


	legs[2].pos[1](0) = legs[2].joint_pos[1](0);
	legs[2].pos[1](1) = legs[2].joint_pos[1](1) - legs[2].leg_len[1] / 2.0;
	legs[2].pos[1](2) = legs[2].joint_pos[1](2);

	//pos_rb.push_back(pos_rb1);


	legs[2].joint_pos[2](0) = legs[2].pos[1](0);
	legs[2].joint_pos[2](1) = legs[2].pos[1](1) - legs[2].leg_len[1] / 2.0;
	legs[2].joint_pos[2](2) = legs[2].pos[1](2);

	legs[2].joint_pos[2] += legs[2].pos_offset[2];

	//joint_pos_rb.push_back(joint_pos_rb2);


	legs[2].pos[2](0) = legs[2].joint_pos[2](0);
	legs[2].pos[2](1) = legs[2].joint_pos[2](1);
	legs[2].pos[2](2) = legs[2].joint_pos[2](2) - legs[2].leg_len[2] / 2.0;


	legs[2].foot_joint_pos(0) = legs[2].pos[2](0);
	legs[2].foot_joint_pos(1) = legs[2].pos[2](1);
	legs[2].foot_joint_pos(2) = legs[2].pos[2](2) - legs[2].leg_len[2] / 2.0 - legs[2].leg_width[2] / 2.0;

	legs[2].foot_pos(0) = legs[2].foot_joint_pos(0);
	legs[2].foot_pos(1) = legs[2].foot_joint_pos(1);
	legs[2].foot_pos(2) = legs[2].foot_joint_pos(2) - legs[2].foot_height / 2.0;
	//pos_rb.push_back(pos_rb2);

	//pos[2] = pos_rb;
	//joint_pos[2] = joint_pos_rb;



	//std::vector<Vector3d> pos_rf, joint_pos_rf;



	legs[3].joint_pos[0](0) = body.pos(0) + body.lx / 2.0;
	legs[3].joint_pos[0](1) = body.pos(1) - body.ly / 2.0;
	legs[3].joint_pos[0](2) = body.pos(2) - body.lz / 2.0 - legs[3].leg_height[0] / 2.0;

	legs[3].joint_pos[0] += legs[3].pos_offset[0];
	//joint_pos_rf.push_back(joint_pos_rf0);


	legs[3].pos[0](0) = legs[3].joint_pos[0](0);
	legs[3].pos[0](1) = legs[3].joint_pos[0](1) - legs[3].leg_len[0] / 2.0;
	legs[3].pos[0](2) = legs[3].joint_pos[0](2);

	//pos_rf.push_back(pos_rf0);


	legs[3].joint_pos[1](0) = legs[3].pos[0](0);
	legs[3].joint_pos[1](1) = legs[3].pos[0](1) - legs[3].leg_len[0] / 2.0;
	legs[3].joint_pos[1](2) = legs[3].pos[0](2);

	legs[3].joint_pos[1] += legs[3].pos_offset[1];
	//joint_pos_rf.push_back(joint_pos_rf1);


	legs[3].pos[1](0) = legs[3].joint_pos[1](0);
	legs[3].pos[1](1) = legs[3].joint_pos[1](1) - legs[3].leg_len[1] / 2.0;
	legs[3].pos[1](2) = legs[3].joint_pos[1](2);

	//pos_rf.push_back(pos_rf1);


	legs[3].joint_pos[2](0) = legs[3].pos[1](0);
	legs[3].joint_pos[2](1) = legs[3].pos[1](1) - legs[3].leg_len[1] / 2.0;
	legs[3].joint_pos[2](2) = legs[3].pos[1](2);

	legs[3].joint_pos[2] += legs[3].pos_offset[2];
	//joint_pos_rf.push_back(joint_pos_rf2);


	legs[3].pos[2](0) = legs[3].joint_pos[2](0);
	legs[3].pos[2](1) = legs[3].joint_pos[2](1);
	legs[3].pos[2](2) = legs[3].joint_pos[2](2) - legs[3].leg_len[2] / 2.0;

	legs[3].foot_joint_pos(0) = legs[3].pos[2](0);
	legs[3].foot_joint_pos(1) = legs[3].pos[2](1);
	legs[3].foot_joint_pos(2) = legs[3].pos[2](2) - legs[3].leg_len[2] / 2.0 - legs[3].leg_width[2] / 2.0;

	legs[3].foot_pos(0) = legs[3].foot_joint_pos(0);
	legs[3].foot_pos(1) = legs[3].foot_joint_pos(1);
	legs[3].foot_pos(2) = legs[3].foot_joint_pos(2) - legs[3].foot_height / 2.0;
}




void Four_legged_Robot::setMotorOffset(double offset0, double offset1, double offset2)
{
	for (int i = 0; i < 4; i++)
	{
		legs[i].setJointOffset(offset0, offset1, offset2);
	}
}

void Four_legged_Robot::setMotorLimit(double upper_limit0, double upper_limit1, double upper_limit2, double lower_limit0, double lower_limit1, double lower_limit2)
{
	for (int i = 0; i < 4; i++)
	{
		legs[i].setUpperLimitJoint(upper_limit0, upper_limit1, upper_limit2);
		legs[i].setLowerLimitJoint(lower_limit0, lower_limit1, lower_limit2);
	}
}

bool Four_legged_Robot::limitOver(std::vector<double> &t0, std::vector<double> &t1, std::vector<double> &t2, std::vector<double> &t3)
{
	bool ret = false;

	t0[0] = t0[0] - M_PI / 2.0;
	t0[1] = t0[1] - M_PI / 2.0;
	t0[2] = t0[2] - M_PI / 2.0;

	t1[0] = t1[0] - M_PI / 2.0;
	t1[1] = t1[1] - M_PI / 2.0;
	t1[2] = t1[2] - M_PI / 2.0;

	t2[0] = t2[0] + M_PI / 2.0;
	t2[1] = t2[1] - M_PI / 2.0;
	t2[2] = t2[2] - M_PI / 2.0;

	t3[0] = t3[0] + M_PI / 2.0;
	t3[1] = t3[1] - M_PI / 2.0;
	t3[2] = t3[2] - M_PI / 2.0;

	if (legs[0].setAngle(t0))
	{
		ret = true;
	}
	if (legs[1].setAngle(t1))
	{
		ret = true;
	}
	if (legs[2].setAngle(t2))
	{
		ret = true;
	}
	if (legs[3].setAngle(t3))
	{
		ret = true;
	}
	return ret;
}