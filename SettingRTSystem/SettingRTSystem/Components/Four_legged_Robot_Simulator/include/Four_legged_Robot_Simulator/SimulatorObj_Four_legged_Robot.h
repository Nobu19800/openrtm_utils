/*!
* @file  SimulatorObj.h
* @brief �V�~�����[�V�����֘A�̃N���X
*
*/

#ifndef SIMULATOROBJ_Four_legged_Robot_H
#define SIMULATOROBJ_Four_legged_Robot_H

#define dDOUBLE

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
*@brief �{�f�B�I�u�W�F�N�g
*�ڑ�����W���C���g���܂�
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
*@brief �V�~�����[�V�����̑�������邽�߂̃N���X
*/
class SimulatorObj_Four_legged_Robot
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	SimulatorObj_Four_legged_Robot();
	/**
	*@brief �f�X�g���N�^
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
	*@brief �e�p�����[�^�̏��������s��
	*/
	void makeParam();
	/**
	*@brief �����̍쐬
	* @param body �{�f�B�I�u�W�F�N�g
	*/
	void setBox(MyLink *body);
	/**
	*@brief �~���쐬
	* @param body �{�f�B�I�u�W�F�N�g
	*/
	void setCylinder(MyLink *body);
	/**
	*@brief �q���W�W���C���g�쐬
	* @param body1 �{�f�B1
	* @param body2 �{�f�B2
	*/
	void setHinge(MyLink *body1, MyLink *body2);
	/**
	*@brief �X���C�_�[�W���C���g�쐬
	* @param body1 �{�f�B1
	* @param body2 �{�f�B2
	*/
	void setSlider(MyLink *body1, MyLink *body2);
	/**
	*@brief �Œ�W���C���g�쐬
	* @param body1 �{�f�B1
	* @param body2 �{�f�B2
	*/
	void setFixed(MyLink *body1, MyLink *body2);
	/**
	*@brief �S�{�f�B�A�ڑ�����S�W���C���g����
	*/
	void makeRobot();
	/**
	*@brief �q���W�W���C���g����
	* @param body �{�f�B�I�u�W�F�N�g
	* @param theta �q���W�W���C���g�̈ʒu
	*/
	void controlHinge(MyLink *body, dReal theta);
	/**
	*@brief �X���C�_�[�W���C���g����
	* @param body �{�f�B�I�u�W�F�N�g
	* @param length �X���C�_�[�W���C���g�̈ʒu
	*/
	void controlSlider(MyLink *body, dReal length);
	/**
	*@brief �S�W���C���g����
	*/
	void control();
	/**
	*@brief �X�V
	*/
	void update();
	/**
	*@brief �S�{�f�B�A�ڑ�����S�W���C���g����
	*/
	void destroyRobot();

	/**
	*@brief �ڐG�R�[���o�b�N
	* @param o1 �W�I���g��1
	* @param o2 �W�I���g��2
	*/
	void m_nearCallback(dGeomID o1, dGeomID o2);
	/**
	*@brief ���ݕ��ݒ�
	* @param s �T���v�����O����
	*/
	void setSamplingTime(double s);
	/**
	*@brief �������쐬���邩��ݒ�
	*@param fe true�ő����쐬
	*/
	void setFoot(bool fe);



};



#endif