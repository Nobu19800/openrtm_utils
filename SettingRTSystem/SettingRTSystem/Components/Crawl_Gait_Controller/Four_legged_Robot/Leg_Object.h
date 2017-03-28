/*!
* @file  Leg_Object.h
* @brief �r����N���X
*
*/


#ifndef Leg_Object_H
#define Leg_Object_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

using namespace Eigen;



enum FootState
{
	ON_GROUND_CRAWL = 0,
	NOT_ON_GROUND_CRAWL = 1,
	MOVE_STOP = 2,
	MOVE_PAUSE = 3,
	ON_GROUND_INTERMITTENT_CRAWL = 4,
	NOT_ON_GROUND_INTERMITTENT_CRAWL = 5,
	ON_GROUND_MOVE_TARGET = 6,
	ON_GROUND_TROT = 7,
	NOT_ON_GROUND_TROT = 8,
};



/**
* @class Leg_Object
*@brief �r����N���X
*/
class Leg_Object
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	Leg_Object();
	/**
	*@brief �r���S�Ē�~���Ă��邩�𔻒�
	*@param legs �r�̃��X�g
	*@param len �r�̃��X�g�̃T�C�Y
	*@return ��~���Ă��Ȃ��r�̐��A�S�Ē�~���Ă���ꍇ��0
	*/
	static int LegsStop(Leg_Object *legs, int len);

	/**
	*@brief ��]���S�ʒu�A��]���x�Ȃǂ̐ݒ�
	*@param p ��]���S�ʒu
	*@param rv ��]���x
	*@param mc �X�e�b�v��
	*@param sampling �T���v�����O����
	*@param target_position_update true�̏ꍇ�͖ڕW�ʒu���Đݒ肷��
	*@param targetpos_rate �Đݒ肷��ڕW�ʒu
	*/
	void setRotateStatus(Vector3d p, double rv, int mc, double sampling, bool target_position_update = true, double targetpos_rate = 1);
	/**
	*@brief �X�V
	*/
	void update();
	/**
	*@brief �����ʒu�ݒ�
	*@param cs ��ʒu
	*/
	void set_center_pos(Vector3d cs);
	/**
	*@brief ��Ԑݒ�
	*@param s ���
	*/
	void set_state(FootState s);
	/**
	*@brief �ڕW�ʒu�ݒ�
	*@param tp �ڕW�ʒu
	*@param mc �X�e�b�v��
	*/
	void setTargetPos(Vector3d tp, int mc);
	/**
	*@brief �I�t�Z�b�g��0�ɂ���
	*/
	void reset_offset();
	/**
	*@brief ��]���x�A�X�e�b�v���̍Đݒ�
	*@param rv ��]���x
	*@param len ��]���S�܂ł̒���
	*@param mc �X�e�b�v��
	*/
	void update_status(double rv, int mc);
	/**
	*@brief �ڒn���Ă��邩�̔���
	*@return �ڒn���Ă���ꍇ��true
	*/
	bool onGround();
	/**
	*@brief �t�^���w�ɂ��֐ߊp�x���v�Z
	*@param pos �r��ʒu
	*@return �֐ߊp�x
	*/
	std::vector<double> inverseKinematics(Vector3d pos);
	/**
	*@brief ���^���w�ɂ��r��ʒu���v�Z
	*@param the �֐ߊp�x
	*@return �r��ʒu
	*/
	Vector3d calcKinematics(std::vector<double> the);
	/**
	*@brief �V�r�����̐ݒ�
	*@param lh ����
	*/
	void setLiftHeight(double lh);
	/**
	*@brief �W���C���g�̃I�t�Z�b�g�ݒ�
	*@param o1 �W���C���g0�̃I�t�Z�b�g
	*@param o1 �W���C���g1�̃I�t�Z�b�g
	*@param o1 �W���C���g2�̃I�t�Z�b�g
	*/
	void setJointOffset(double o0, double o1, double o2);
	/**
	*@brief �W���C���g�̉��͈͏���̐ݒ�
	*@param o1 �W���C���g0�̉��͈͏���l
	*@param o1 �W���C���g1�̉��͈͏���l
	*@param o1 �W���C���g2�̉��͈͏���l
	*/
	void setUpperLimitJoint(double l0, double l1, double l2);
	/**
	*@brief �W���C���g�̉��͈͉����̐ݒ�
	*@param o1 �W���C���g0�̉��͈͉����l
	*@param o1 �W���C���g1�̉��͈͉����l
	*@param o1 �W���C���g2�̉��͈͉����l
	*/
	void setLowerLimitJoint(double l0, double l1, double l2);
	/**
	*@brief �֐ߊp�x�̐ݒ�
	*@param t �֐ߊp�x
	*@return true�̏ꍇ�͉��͈͊O
	*/
	bool setAngle(std::vector<double> t);

	Vector3d pos[3];
	Vector3d pos_offset[3];
	Vector3d joint_pos[3];
	double foot_mass;
	double foot_width;
	double foot_len;
	double foot_height;
	Vector3d foot_pos;
	Vector3d foot_joint_pos;
	double theta[3];
	double leg_len[3], leg_width[3], leg_height[3];
	double leg_mass[3];
	double jointOffset[3];
	double UpperLimitJoint[3];
	double LowerLimitJoint[3];
	Vector3d center_pos;	
	double offset_angle;
	Vector3d rotate_pos;
	double rotate_len;
	double rotete_vel;
	FootState state;
	FootState last_state;
	double sampling_time;
	double step_time;
	int max_count;
	int count;
	Vector3d current_pos;
	double start_angle;
	int offset_count;
	Vector3d start_pos;
	Vector3d target_pos;
	double x_offset;
	double y_offset;
	//double move_rate;

	double stability_x_offset;
	double stability_y_offset;
	double next_stability_x_offset;
	double next_stability_y_offset;
	//int current_offset_count;

	double intermittent_x_offset;
	double intermittent_y_offset;
	double next_intermittent_x_offset;
	double next_intermittent_y_offset;

	double trot_offset;

	double lift_height;

};




#endif