/*!
* @file  DrawThread.h
* @brief �V�~�����[�V�����`��֘A�̃N���X
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
*@brief �V�~�����[�V�����̕`�������X���b�h
*/
class DrawThread_Four_legged_Robot : public virtual coil::Task
{
public:
		/**
		*@brief �R���X�g���N�^
		*/
	DrawThread_Four_legged_Robot(SimulatorObj_Four_legged_Robot *so);
		
		/**
		*@brief �X���b�h���s�֐�
		* @return 
		*/
		virtual int svc();
		/**
		*@brief DrawStuff������
		*/
		void setDrawStuff();
		/**
		*@brief �����̕`��
		* @param body �{�f�B�I�u�W�F�N�g
		*/
		void drawBox(MyLink *body);
		/**
		*@brief �~���`��
		* @param body �{�f�B�I�u�W�F�N�g
		*/
		void drawCylinder(MyLink *body);
		/**
		*@brief �S�{�f�B�`��
		*/
		void drawRobot();

		double fps;
		

		int m_pause;


private:
	SimulatorObj_Four_legged_Robot *m_so;
	dsFunctions   fn;
	

};

#endif