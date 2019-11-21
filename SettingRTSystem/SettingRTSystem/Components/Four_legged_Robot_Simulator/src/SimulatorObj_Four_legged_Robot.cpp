/*!
* @file  SimulatorObj_Four_legged_Robot.cpp
* @brief シミュレーション関連のクラス
*
*/

#include "SimulatorObj_Four_legged_Robot.h"

SimulatorObj_Four_legged_Robot *obj_fourleggedrobot = NULL;





/**
*@brief シミュレーションの操作をするためのクラスのコンストラクタ
*/
SimulatorObj_Four_legged_Robot::SimulatorObj_Four_legged_Robot()
{
	st = 0.01;
	gravity = 9.8;
	pause = false;
	foot_exist = false;

	rb = new Four_legged_Robot();
	

	dInitODE();
	world        = dWorldCreate();
	space        = dHashSpaceCreate(0);
	contactgroup = dJointGroupCreate(0);
	ground       = dCreatePlane(space,0,0,1,0);

	dWorldSetGravity(world, 0, 0, -gravity);
	//dWorldSetGravity(world, 0, 0, 0.0);
	dWorldSetCFM(world, 1e-6);
	dWorldSetERP(world, 1.0);

	makeParam();
	makeRobot();

	obj_fourleggedrobot = this;
}

/**
*@brief シミュレーションの操作をするためのクラスのデストラクタ
*/
SimulatorObj_Four_legged_Robot::~SimulatorObj_Four_legged_Robot()
{
	dSpaceDestroy(space);
	dWorldDestroy(world);
	dCloseODE();
}

/**
*@brief 各パラメータの初期化を行う
*/
void SimulatorObj_Four_legged_Robot::makeParam()
{
	legs.clear();

	for(int i=0;i < 4;i++)
	{
		std::vector<MyLink> links;
		for(int j=0;j < 3;j++)
		{
			MyLink l;
			l.the = 0;
			l.m = rb->legs[i].leg_mass[j];
			if(j != 2)
			{
				l.lx = rb->legs[i].leg_width[j];
				l.ly = rb->legs[i].leg_len[j];
				l.lz = rb->legs[i].leg_height[j];
			}
			else
			{
				l.lx = rb->legs[i].leg_width[j];
				l.ly = rb->legs[i].leg_height[j];
				l.lz = rb->legs[i].leg_len[j];
			}
			l.x = rb->legs[i].pos[j](0);
			l.y = rb->legs[i].pos[j](1);
			l.z = rb->legs[i].pos[j](2);
			l.jx = rb->legs[i].joint_pos[j](0);
			l.jy = rb->legs[i].joint_pos[j](1);
			l.jz = rb->legs[i].joint_pos[j](2);

			if(j == 0)
			{
				l.axisx = 0;
				l.axisy = 0;
				l.axisz = -1;
			}
			else
			{
				if(i == 2 || i == 3)l.axisx = -1;
				else l.axisx = 1;
				l.axisy = 0;
				l.axisz = 0;
			}
			l.red = 1.;
			l.green = 1.;
			/*if (i == 0)
				l.blue = 1.;
			else*/
				l.blue = 0.;
			links.push_back(l);
		}

		if (foot_exist)
		{
			MyLink l;
			l.the = 0;
			l.m = rb->legs[i].foot_mass;


			l.lx = rb->legs[i].foot_width;
			l.ly = rb->legs[i].foot_len;
			l.lz = rb->legs[i].foot_height;

			l.x = rb->legs[i].foot_pos(0);
			l.y = rb->legs[i].foot_pos(1);
			l.z = rb->legs[i].foot_pos(2);
			l.jx = rb->legs[i].foot_joint_pos(0);
			l.jy = rb->legs[i].foot_joint_pos(1);
			l.jz = rb->legs[i].foot_joint_pos(2);

			if (i == 2 || i == 3)l.axisx = -1;
			else l.axisx = 1;
			l.axisy = 0;
			l.axisz = 0;

			l.red = 1.;
			l.green = 1.;
			l.blue = 0.;
			links.push_back(l);
		}
		legs.push_back(links);
	}

	body.m = rb->body.mass;
	body.lx = rb->body.lx;
	body.ly = rb->body.ly;
	body.lz = rb->body.lz;
	body.x = rb->body.pos(0);
	body.y = rb->body.pos(1);
	body.z = rb->body.pos(2);
	body.jx = rb->body.pos(0);
	body.jy = rb->body.pos(1);
	body.jz = rb->body.pos(2);
	body.axisx = 0;
	body.axisy = 0;
	body.axisz = 1;
	body.red = 1.;
	body.green = 1.;
	body.blue = 0.;




}

/**
*@brief 直方体作成
* @param body ボディオブジェクト
*/
void SimulatorObj_Four_legged_Robot::setBox(MyLink *body)
{
	dMass mass;
	body->body  = dBodyCreate(world);
	dMassSetZero(&mass);
	dMassSetBoxTotal(&mass,body->m , body->lx, body->ly, body->lz);
	dBodySetMass(body->body,&mass);
	body->geom = dCreateBox(space,body->lx, body->ly, body->lz);
	dGeomSetBody(body->geom, body->body);
	dBodySetPosition(body->body, body->x, body->y, body->z);
}

/**
*@brief 円柱作成
* @param body ボディオブジェクト
*/
void SimulatorObj_Four_legged_Robot::setCylinder(MyLink *body)
{
	dMass mass;
	body->body  = dBodyCreate(world);
	dMassSetZero(&mass);
	dMassSetCylinderTotal(&mass,body->m , 2, body->lx,  body->lz);
	dBodySetMass(body->body,&mass);
	body->geom = dCreateCylinder(space,body->lx, body->lz);
	dGeomSetBody(body->geom, body->body);
	dBodySetPosition(body->body, body->x, body->y, body->z);
}

/**
*@brief ヒンジジョイント作成
* @param body1 ボディ1
* @param body2 ボディ2
*/
void SimulatorObj_Four_legged_Robot::setHinge(MyLink *body1, MyLink *body2)
{
	body1->joint = dJointCreateHinge(world, 0);
	dJointAttach(body1->joint, body2->body, body1->body);
	dJointSetHingeAnchor(body1->joint, body1->jx, body1->jy, body1->jz);
	dJointSetHingeAxis(body1->joint, body1->axisx, body1->axisy,body1->axisz);
}

/**
*@brief スライダージョイント作成
* @param body1 ボディ1
* @param body2 ボディ2
*/
void SimulatorObj_Four_legged_Robot::setSlider(MyLink *body1, MyLink *body2)
{
	body1->joint = dJointCreateSlider(world, 0);
	dJointAttach(body1->joint, body2->body, body1->body);
	
	dJointSetSliderAxis(body1->joint, body1->axisx, body1->axisy,body1->axisz);
}

/**
*@brief 固定ジョイント作成
* @param body1 ボディ1
* @param body2 ボディ2
*/
void SimulatorObj_Four_legged_Robot::setFixed(MyLink *body1, MyLink *body2)
{
	body1->joint = dJointCreateFixed(world, 0);
	dJointAttach(body1->joint, body2->body, body1->body);
	dJointSetFixed(body1->joint);
}

/**
*@brief 全ボディ、接続する全ジョイント生成
*/
void SimulatorObj_Four_legged_Robot::makeRobot()
{
	mu.lock();

	for (int i = 0; i < legs.size(); i++)
	{
		for (int j = 0; j < legs[i].size(); j++)
		{
			setBox(&legs[i][j]);
		}
	}
	setBox(&body);


	for (int i = 0; i < 4; i++)
	{

		setHinge(&legs[i][0], &body);
		for (int j = 1; j < legs[i].size(); j++)
		{
			setHinge(&legs[i][j], &legs[i][j - 1]);
		}


	}

	pause = true;
	mu.unlock();


}

/**
*@brief 接触コールバック
* @param o1 ジオメトリ1
* @param o2 ジオメトリ2
*/
void SimulatorObj_Four_legged_Robot::m_nearCallback(dGeomID o1, dGeomID o2)
{
	//return;
	
  dBodyID b1 = dGeomGetBody(o1), b2 = dGeomGetBody(o2);
  if (b1 && b2 && dAreConnectedExcluding(b1,b2,dJointTypeContact)) return;
  if (b1 && b2 && dAreConnected(b1,b2)) return;
  if ((o1 != ground) && (o2 != ground)) return;
 
   static const int N = 20;
	dContact contact[N];
	int n = dCollide(o1,o2,N,&contact[0].geom,sizeof(dContact));

	

	if (n > 0) {
		for (int i=0; i<n; i++) {
			contact[i].surface.mode = dContactApprox1|dContactSoftERP|dContactSoftCFM|dContactSlip1|dContactSlip2;



			contact[i].surface.mu   = 0.5;
			contact[i].surface.slip1 = 0.001;
			contact[i].surface.slip2 = 0.001;
			contact[i].surface.soft_erp = 0.3;
			contact[i].surface.soft_cfm = 1e-4;
			dJointID c = dJointCreateContact(world,contactgroup,&contact[i]);
			dJointAttach(c,b1,b2);
		}
	}
}

/**
*@brief 接触コールバック
* @param data データ
* @param o1 ジオメトリ1
* @param o2 ジオメトリ2
*/
static void nearCallback(void *data, dGeomID o1, dGeomID o2) {
	
	if(obj_fourleggedrobot)
	{
		obj_fourleggedrobot->m_nearCallback(o1, o2);
	}
  
		
}

/**
*@brief ヒンジジョイント制御
* @param body ボディオブジェクト
* @param theta ヒンジジョイントの位置
*/
void SimulatorObj_Four_legged_Robot::controlHinge(MyLink *body, dReal theta)
{
	dReal kp = 100;
	dReal tmp = dJointGetHingeAngle(body->joint);
	dReal diff = theta - tmp;
	dReal u = kp * diff;

	dJointSetHingeParam(body->joint,dParamVel, u);
	dJointSetHingeParam(body->joint,dParamFMax,20.);
}

/**
*@brief スライダージョイント制御
* @param body ボディオブジェクト
* @param length スライダージョイントの位置
*/
void SimulatorObj_Four_legged_Robot::controlSlider(MyLink *body, dReal length)
{
	dReal kp = 10;
	dReal tmp = dJointGetSliderPosition(body->joint);
	dReal diff = length - tmp;
	dReal u = kp * diff;

	dJointSetSliderParam (body->joint,dParamVel, u);
	dJointSetSliderParam (body->joint,dParamFMax,20.);
}

/**
*@brief 全ジョイント制御
*/
void SimulatorObj_Four_legged_Robot::control()
{
	rb->setSamplingTime(st);
	/*rb->update(st);

	dReal r2 = dJointGetHingeAngle (link2.joint);
	dReal r3 = dJointGetHingeAngle (link3.joint);

	controlHinge(&link1, -rb->theta[0]+rb->offset[0]);//
	controlHinge(&link2, -rb->theta[1]+rb->offset[1]);//
	controlHinge(&link3, -rb->theta[2]+rb->offset[2]);//
	controlHinge(&linkhs, -r2-r3);//
	controlHinge(&linkh, -rb->theta[3]);//
	controlSlider(&linkf[0], rb->gripperPos/2);//
	controlSlider(&linkf[1], -rb->gripperPos/2);//
	*/
	/*static int count = 0;
	count += 1;

	//if (count < 1000000)rb->crawl_walk(-0.05, 0.0, -0.001);
	//else rb->crawl_walk(0.05, 0.0, -0.03);
	//rb->crawl_walk(0.0, -0.0, -0.3);
	rb->crawl_gait(-0.05, 0.0, -0.0001, 0.08);
	//rb->intermittent_crawl_walk(0,0,0);
	std::cout << count << std::endl;
	for (int i = 0; i < 4; i++)
	{
		Vector3d pos;
		pos = Vector3d(-0.0, rb->legs[i].leg_len[0] + rb->legs[i].leg_len[1], -rb->legs[i].leg_len[2] - rb->body_lz / 2.0 - rb->legs[i].leg_height[0] / 2.0);
			

		if (i == 0)
		{
			pos(0) = pos(0) + rb->body_lx/2.0;
			pos(1) = pos(1) + rb->body_ly / 2.0;
			
		}
		else if (i == 1)
		{
			pos(0) = pos(0) - rb->body_lx / 2.0;
			pos(1) = pos(1) + rb->body_ly / 2.0;
		}
		else if (i == 2)
		{
			pos(1) = -pos(1);
			pos(0) = pos(0) - rb->body_lx / 2.0;
			pos(1) = pos(1) - rb->body_ly / 2.0;
		}
		else if (i == 3)
		{
			pos(1) = -pos(1);
			pos(0) = pos(0) + rb->body_lx / 2.0;
			pos(1) = pos(1) - rb->body_ly / 2.0;
			//std::cout << "pos\t" << pos(0) << "\t" << pos(1) << std::endl;
		}
		
		if (i == 0)std::cout << rb->cw_obj->state << "\t" << rb->legs[i].current_pos[0] - rb->legs[i].center_pos[0] << "\t" << rb->legs[i].current_pos[1] - rb->legs[i].center_pos[1] << std::endl;
		//std::cout << i << "\t" << rb->legs[i].center_pos[0] << "\t" << rb->legs[i].center_pos[1] << std::endl;
		//std::vector<double> ans = rb->inverseKinematics(pos, i);
		std::vector<double> ans = rb->inverseKinematics(rb->legs[i].current_pos, i);
		ans[1] = ans[1] - M_PI / 2.0;
		ans[2] = ans[2] - M_PI / 2.0;
		if (i == 0 || i == 1)ans[0] = ans[0] - M_PI / 2.0;
		else ans[0] = ans[0] + M_PI / 2.0;



		for (int j = 0; j < 3; j++)
		{

			//std::cout << i << "\t" << j << "\t" << ans[j] << std::endl;
			controlHinge(&legs[i][j], ans[j]);
			
		}
		//const dReal *p = dBodyGetPosition(leg[i][2].body);
		//std::cout << i << "\t" << p[0] << "\t" << p[1] << std::endl;
	}*/
	//const dReal *p = dBodyGetPosition(body.body);
	//std::cout << p[0] << std::endl;
	if (foot_exist)
	{
		for (int i = 0; i < legs.size(); i++)
		{
			legs[i][3].the = -legs[i][1].the - legs[i][2].the;
		}
	}
	for (int i = 0; i < legs.size(); i++)
	{
		for (int j = 0; j < legs[i].size(); j++)
		{
			controlHinge(&legs[i][j], legs[i][j].the);
		}
	}
}

/**
*@brief 更新
*/
void SimulatorObj_Four_legged_Robot::update()
{
	if(pause)
	{
		mu.lock();
		control(); 
		dSpaceCollide(space,0,&nearCallback);
		dWorldStep(world, st);
		dJointGroupEmpty(contactgroup);
		mu.unlock();

	}
}

/**
*@brief 全ボディ、接続する全ジョイント消去
*/
void SimulatorObj_Four_legged_Robot::destroyRobot()
{
	mu.lock();
	pause = false;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			dJointDestroy(legs[i][j].joint);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			dBodyDestroy(legs[i][j].body);
			dGeomDestroy(legs[i][j].geom);
		}
	}
	dBodyDestroy(body.body);
	dGeomDestroy(body.geom);
	mu.unlock();
}

/**
*@brief 刻み幅設定
* @param s サンプリング時間
*/
void SimulatorObj_Four_legged_Robot::setSamplingTime(double s)
{
	st = s;
	rb->setSamplingTime(s);
}

/**
*@brief 足裏を作成するかを設定
*@param fe trueで足裏作成
*/
void SimulatorObj_Four_legged_Robot::setFoot(bool fe)
{
	foot_exist = fe;
}
