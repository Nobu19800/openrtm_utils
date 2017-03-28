/*!
* @file  Body_Object.h
* @brief �d�S����N���X
*
*/


#ifndef Body_Object_H
#define Body_Object_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

#include "Leg_Object.h"

using namespace Eigen;




/**
* @class Body_Object
*@brief ���̐���N���X
*/
class Body_Object
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	Body_Object();


	/**
	*@brief ��]���S�ʒu�A��]���x�Ȃǂ̐ݒ�
	*@param p ��]���S�ʒu
	*@param rv ��]���x
	*@param mc �X�e�b�v��
	*@param sampling �T���v�����O����
	*@param target_position_update true�̏ꍇ�͖ڕW�ʒu���Đݒ肷��
	*/
	void setRotateStatus(Vector3d p, double rv, int mc, double sampling, bool target_position_update = true);
	/**
	*@brief �X�V
	*/
	void update();

	/**
	*@brief ��Ԑݒ�
	*@param s ���
	*/
	void set_state(FootState s);


	/**
	*@brief ��]���x�A�X�e�b�v���̍Đݒ�
	*@param rv ��]���x
	*@param mc �X�e�b�v��
	*/
	void update_status(double rv, int mc);

	/**
	*@brief �����ʒu�ݒ�
	*@param p �ʒu
	*/
	void set_position(Vector3d p);

	/**
	*@brief �����p���ݒ�
	*@param r �p��
	*/
	void set_orientation(Vector3d r);

	double sampling_time;
	int count;
	int max_count;
	int offset_count;
	double rotete_vel;
	Vector3d pos;
	Vector3d rot;
	double lx, ly, lz;
	double mass;
	FootState state;
	FootState last_state;

	Vector3d start_pos;
	Vector3d current_pos;
	Vector3d current_rot;
	Vector3d target_pos;

	Vector3d rotate_pos;
	double rotate_len;
	double offset_angle;

	double intermittent_x_offset;
	double intermittent_y_offset;



};




#endif