/*!
* @file  Four_legged_Robot.h
* @brief �l�����s���{�b�g����N���X
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
*@brief �l�����s���{�b�g����N���X
*/
class Four_legged_Robot
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	Four_legged_Robot();
	/**
	*@brief �R�s�[�R���X�g���N�^
	*/
	Four_legged_Robot(Four_legged_Robot &fo);
	/**
	*@brief �f�X�g���N�^
	*/
	~Four_legged_Robot();
	/**
	*@brief �r��ʒu����֐ߊp�x�擾
	*@param the �r��ʒu
	* @return �֐ߊp�x
	*/
	std::vector<double> inverseKinematics(Vector3d pos, int num);
	/**
	*@brief �r��ʒu�擾
	*@param the �֐ߊp�x
	* @return �r��ʒu
	*/
	Vector3d calcKinematics(std::vector<double> the, int num);
	/**
	*@brief �֐ߊp�x�����
	* @param the �֐ߊp�x
	*/
	void setAngle(std::vector<double> the[4]);
	/**
	*@brief �r�摬�x����֐ߊp���x���擾
	* @param v �r�摬�x
	* @return �֐ߊp���x
	*/
	Vector3d calcJointVel(std::vector<double> the[4]);
	/**
	*@brief �֐ߊp���x�̓��͂���֐ߊp�x���X�V
	* @param the �֐ߊp���x
	*/
	void updatePos(std::vector<double> the[4]);
	/**
	*@brief ������
	*/
	void update();
	/**
	*@brief �N���[�����e�̑���ʒu�v�Z
	* @param vx ���x(X������)
	* @param vy ���x(Y������)
	* @param dthe ��]���x
	* @param stride ����
	*/
	void crawl_gait(double vx, double vy, double dthe, double stride);
	/**
	*@brief �ԟ[�N���[�����e�̑���ʒu�v�Z
	* @param vx ���x(X������)
	* @param vy ���x(Y������)
	* @param dthe ��]���x
	* @param stride ����
	*/
	void intermittent_crawl_gait(double vx, double vy, double dthe, double stride);
	/**
	*@brief �g���b�g���e�̑���ʒu�v�Z
	* @param vx ���x(X������)
	* @param vy ���x(Y������)
	* @param dthe ��]���x
	* @param stride ����
	*/
	void trot_gait(double vx, double vy, double dthe, double stride);
	/**
	*@brief ���ݕ��ݒ�
	* @param st �T���v�����O����
	*/
	void setSamplingTime(double st);
	/**
	*@brief �����ʒu�ݒ�
	* @param pos_x �ʒu(X)
	* @param pos_y �ʒu(Y)
	* @param pos_z �ʒu(Z)
	*/
	void setCenterPosition(double pos_x, double pos_y, double pos_z);
	/**
	*@brief �Œ����]�T�ݒ�
	* @param msm ����]�T
	*/
	void setMinMargin(double msm);

	/**
	*@brief �V�r�����ݒ�ݒ�
	* @param h ����
	*/
	void setLiftHeight(double h);
	/**
	*@brief ���{�b�g�̌��݈ʒu�ݒ�
	* @param pos ���݈ʒu
	* @param rot ���݂̎p��
	*/
	void setCurrentPosition(Vector3d pos, Vector3d rot);

	/**
	*@brief ����]�T�擾
	*@return ����]�T
	*/
	double getStabilityMargin();
	/**
	*@brief NE����]�T�擾
	*@return NE����]�T
	*/
	double getNEStabilityMargin();

	/**
	*@brief �{�f�B�̃p�����[�^�ݒ�
	*@param size ���@
	*@param pos ���S�ʒu
	*@param mass �d��
	*/
	void setBodyParam(Vector3d size, Vector3d pos, double mass);
	/**
	*@brief �����N�̃p�����[�^�ݒ�
	*@param size ���@
	*@param offset �I�t�Z�b�g
	*@param mass �d��
	*@param num �ԍ�
	*/
	void setLinkParam(Vector3d size, Vector3d offset, double mass, int num);
	/**
	*@brief �����N0�̃p�����[�^�ݒ�
	*@param size ���@
	*@param offset �I�t�Z�b�g
	*@param mass �d��
	*/
	void setLink0Param(Vector3d size, Vector3d offset, double mass);
	/**
	*@brief �����N1�̃p�����[�^�ݒ�
	*@param size ���@
	*@param offset �I�t�Z�b�g
	*@param mass �d��
	*/
	void setLink1Param(Vector3d size, Vector3d offset, double mass);
	/**
	*@brief �����N2�̃p�����[�^�ݒ�
	*@param size ���@
	*@param offset �I�t�Z�b�g
	*@param mass �d��
	*/
	void setLink2Param(Vector3d size, Vector3d offset, double mass);
	/**
	*@brief �����̃p�����[�^�ݒ�
	*@param size ���@
	*@param offset �I�t�Z�b�g
	*@param mass �d��
	*/
	void setFootParam(Vector3d size, Vector3d offset, double mass);
	/**
	*@brief �ݒ肵�������N�p�����[�^����ʒu�A�p�����Čv�Z
	*/
	void setPose();
	/**
	*@brief �֐߃I�t�Z�b�g�ݒ�
	*@param offset0 �֐�0�̃I�t�Z�b�g
	*@param offset1 �֐�1�̃I�t�Z�b�g
	*@param offset2 �֐�2�̃I�t�Z�b�g
	*/
	void setMotorOffset(double offset0, double offset1, double offset2);
	/**
	*@brief �����̃p�����[�^�ݒ�
	*@param upper_limit0 �֐�0�̏��
	*@param upper_limit1 �֐�1�̏��
	*@param upper_limit2 �֐�2�̏��
	*@param lower_limit0 �֐�0�̉���
	*@param lower_limit1 �֐�1�̉���
	*@param lower_limit2 �֐�2�̉���
	*/
	void setMotorLimit(double upper_limit0, double upper_limit1, double upper_limit2, double lower_limit0, double lower_limit1, double lower_limit2);
	/**
	*@brief �֐ߊp�x�����͈͓����̔���
	*@param t0 �r0�̊֐ߊp�x
	*@param t1 �r1�̊֐ߊp�x
	*@param t2 �r2�̊֐ߊp�x
	*@param t3 �r3�̊֐ߊp�x
	*@return true�̏ꍇ�͉��͈͊O
	*/
	bool limitOver(std::vector<double> &t0, std::vector<double> &t1, std::vector<double> &t2, std::vector<double> &t3);
	Leg_Object legs[4];
	Body_Object body;
	


	CrawlGait *cw_obj;
	IntermittentCrawlGait *icw_obj;
	TrotGait *trot_obj;
};



#endif