/*!
* @file  Leg_Object.cpp
* @brief �r����N���X
*
*/


#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "Leg_Object.h"

#define DEFAULT_SAMPLING_TIME 0.1
#define DEFAULT_LIFT_HEIGHT 0.05


/**
*@brief �R���X�g���N�^
*/
Leg_Object::Leg_Object()
{
	state = MOVE_STOP;
	last_state = MOVE_STOP;
	sampling_time = DEFAULT_SAMPLING_TIME;
	//step_time = DEFAULT_STEP_TIME;
	max_count = 10000;
	count = 0;
	offset_count = 0;
	trot_offset = 0;

	x_offset = 0;
	y_offset = 0;

	lift_height = DEFAULT_LIFT_HEIGHT;
	for (int i = 0; i < 3; i++)
	{
		theta[i] = 0;
	}

	foot_mass = 0;
	foot_width = 0;
	foot_len = 0;
	foot_height = 0;
	for (int i = 0; i < 3; i++)
	{
		leg_len[i] = 0;
		leg_width[i] = 0;
		leg_height[i] = 0;
		leg_mass[i] = 0;
		jointOffset[i] = 0;
		UpperLimitJoint[i] = 0;
		LowerLimitJoint[i] = 0;
		
	}
	offset_angle = 0;
	rotate_len = 0;
	rotete_vel = 0;
	step_time = 0;
	start_angle = 0;
	
	reset_offset();
}

/**
*@brief �r���S�Ē�~���Ă��邩�𔻒�
*@param legs �r�̃��X�g
*@param len �r�̃��X�g�̃T�C�Y
*@return ��~���Ă��Ȃ��r�̐��A�S�Ē�~���Ă���ꍇ��0
*/
int Leg_Object::LegsStop(Leg_Object *legs, int len)
{
	int count = 0;
	for (int i = 0; i < len; i++)
	{
		if (legs[i].state == MOVE_STOP)
		{
			count++;
		}
	}
	return count;
}

/**
*@brief �I�t�Z�b�g��0�ɂ���
*/
void Leg_Object::reset_offset()
{
	stability_x_offset = 0;
	stability_y_offset = 0;
	next_stability_x_offset = 0;
	next_stability_y_offset = 0;

	intermittent_x_offset = 0;
	intermittent_y_offset = 0;
	next_intermittent_x_offset = 0;
	next_intermittent_y_offset = 0;
}

/**
*@brief �����ʒu�ݒ�
*@param cs ��ʒu
*/
void Leg_Object::set_center_pos(Vector3d cs)
{
	state = MOVE_STOP;
	center_pos = cs;
	current_pos = cs;
}


/**
*@brief �X�V
*/
void Leg_Object::update()
{
	//std::cout << rotete_vel << std::endl;
	if (state == ON_GROUND_CRAWL || state == ON_GROUND_TROT)
	{
		double diff = (double)(-count + offset_count +trot_offset*max_count) * rotete_vel * sampling_time;
		
		current_pos(0) = rotate_pos(0) + rotate_len*cos(offset_angle + diff);
		current_pos(1) = rotate_pos(1) + rotate_len*sin(offset_angle + diff);
		current_pos(2) = center_pos(2);
		count++;
		//std::cout << max_count << "\t" << count << "\t" << rotate_pos(0) << "\t" << rotate_pos(1) << "\t" << rotate_len << "\t" << offset_angle << std::endl;
		//std::cout << offset_angle + diff << std::endl;
		//std::cout << center_pos(0) << "\t" << center_pos(1) << "\t" << center_pos(2) << std::endl;
		//std::cout << current_pos(0) << "\t" << current_pos(1) << "\t" << current_pos(2) << std::endl;
	}
	else if (state == NOT_ON_GROUND_CRAWL || state == NOT_ON_GROUND_INTERMITTENT_CRAWL || state == NOT_ON_GROUND_TROT)
	{
		//double diff = (double)(count*3 + offset_count) * rotete_vel * sampling_time;
		double h_offset = 0;

		if (count <= max_count / 3)
		{
			h_offset = lift_height*((double)count / ((double)max_count / 3.0));
			
		}
		else if (count >= max_count * 2 / 3)
		{
			h_offset = lift_height*(1 - ((double)count - 2.0 * (double)max_count / 3.0) / ((double)max_count / 3.0));
		}
		else
		{
			h_offset = lift_height;
		}
		//std::cout << max_count << "\t" << count << "\t" << h_offset << std::endl;


		current_pos(0) = start_pos(0) + (target_pos(0) - start_pos(0))*(double)count / (double)max_count;
		current_pos(1) = start_pos(1) + (target_pos(1) - start_pos(1))*(double)count / (double)max_count;
		current_pos(2) = center_pos(2) + h_offset;

		//std::cout << target_pos(0) << "\t" << target_pos(1) << "\t" << target_pos(2) << std::endl;
		//std::cout << current_pos(0) << "\t" << current_pos(1) << "\t" << current_pos(2) << std::endl;
		
		count++;
	}
	else if (state == ON_GROUND_INTERMITTENT_CRAWL)
	{
		/*current_pos(0) = start_pos(0) + (target_pos(0) - start_pos(0))*count / max_count;
		current_pos(1) = start_pos(1) + (target_pos(1) - start_pos(1))*count / max_count;
		current_pos(2) = center_pos(2);
		count++;*/

		double diff = (double)(-count + offset_count) * rotete_vel * sampling_time;

		current_pos(0) = rotate_pos(0) + rotate_len*cos(offset_angle + diff) + x_offset*((double)count / (double)max_count) + intermittent_x_offset;
		current_pos(1) = rotate_pos(1) + rotate_len*sin(offset_angle + diff) + y_offset*((double)count / (double)max_count) + intermittent_y_offset;
		current_pos(2) = center_pos(2);
		//std::cout << current_pos(2) << std::endl;

		count++;

		
	}

	else if (state == ON_GROUND_MOVE_TARGET)
	{
		//std::cout << count << "\t" << start_pos(0) << std::endl;
		current_pos(0) = start_pos(0) + (target_pos(0) - start_pos(0))*(double)count / (double)max_count;
		current_pos(1) = start_pos(1) + (target_pos(1) - start_pos(1))*(double)count / (double)max_count;
		current_pos(2) = center_pos(2);

		count++;
	}



	
	
	if (count > max_count)
	{
		stability_x_offset = next_stability_x_offset;
		stability_y_offset = next_stability_y_offset;

		intermittent_x_offset = next_intermittent_x_offset;
		intermittent_y_offset = next_intermittent_y_offset;
		//next_stability_x_offset = 0;
		//next_stability_y_offset = 0;
		count = 0;
		//std::cout << last_state << std::endl;
		if (state == ON_GROUND_MOVE_TARGET && last_state == MOVE_STOP)set_state(MOVE_STOP);
		else set_state(MOVE_PAUSE);
	}
}

void Leg_Object::set_state(FootState s)
{
	last_state = state;
	state = s;
	if (state == NOT_ON_GROUND_CRAWL || state == NOT_ON_GROUND_INTERMITTENT_CRAWL || state == NOT_ON_GROUND_TROT)
	{
		start_pos = current_pos;
	}
}

void Leg_Object::setTargetPos(Vector3d tp, int mc)
{
	target_pos = tp + center_pos;
	start_pos = current_pos;
	max_count = mc;
}

/**
*@brief ��]���S�ʒu�A��]���x�Ȃǂ̐ݒ�
*@param p ��]���S�ʒu
*@param rv ��]���x
*@param mc �X�e�b�v��
*@param sampling �T���v�����O����
*@param target_position_update true�̏ꍇ�͖ڕW�ʒu���Đݒ肷��
*@param targetpos_rate �Đݒ肷��ڕW�ʒu
*/
void Leg_Object::setRotateStatus(Vector3d p, double rv, int mc, double sampling, bool target_position_update, double targetpos_rate)
{

		rotate_pos = p;
		rotete_vel = rv;
		sampling_time = sampling;
		//step_time = step;
		double dpx = center_pos(0) - p(0);
		double dpy = center_pos(1) - p(1);
		if (state == NOT_ON_GROUND_CRAWL || state == NOT_ON_GROUND_INTERMITTENT_CRAWL || state == NOT_ON_GROUND_TROT)
		{
		}
		else
		{
			dpx += stability_x_offset;
			dpy += stability_y_offset;
		}
		//std::cout << center_pos(1) << "\t" << center_pos(0) << std::endl;
		//std::cout << dpx << "\t" << dpy << std::endl;
		rotate_len = sqrt(dpx*dpx + dpy*dpy);
		offset_angle = atan2(dpy, dpx);



		max_count = mc;

		if (target_position_update)
		{
			if (state == NOT_ON_GROUND_CRAWL)
			{
				//std::cout << targetpos_rate << std::endl;
				double max_diff = (double)(max_count * 3.0 * targetpos_rate + offset_count) * rotete_vel * sampling_time;
				target_pos(0) = rotate_pos(0) + rotate_len*cos(offset_angle + max_diff);
				target_pos(1) = rotate_pos(1) + rotate_len*sin(offset_angle + max_diff);

				next_stability_x_offset = 0;
				next_stability_y_offset = 0;
				next_intermittent_x_offset = 0;
				next_intermittent_y_offset = 0;
			}
			else if (state == NOT_ON_GROUND_INTERMITTENT_CRAWL)
			{

				double max_diff = (double)(max_count * 2.0 + offset_count) * rotete_vel * sampling_time;
				//std::cout << rotete_vel << "\t" << sampling_time << "\t" << max_diff << std::endl;
				target_pos(0) = rotate_pos(0) + rotate_len*cos(offset_angle + max_diff*targetpos_rate);
				target_pos(1) = rotate_pos(1) + rotate_len*sin(offset_angle + max_diff*targetpos_rate);

				next_stability_x_offset = 0;
				next_stability_y_offset = 0;
				next_intermittent_x_offset = 0;
				next_intermittent_y_offset = 0;
				//std::cout << target_pos(0) << "\t" << target_pos(1) << std::endl;
			}
			else if (state == ON_GROUND_INTERMITTENT_CRAWL)
			{
				double max_diff = (double)(-max_count + offset_count) * rotete_vel * sampling_time;

				target_pos(0) = rotate_pos(0) + rotate_len*cos(offset_angle + max_diff) + x_offset + intermittent_x_offset;
				target_pos(1) = rotate_pos(1) + rotate_len*sin(offset_angle + max_diff) + y_offset + intermittent_y_offset;
				
			}
			else if (state == ON_GROUND_CRAWL)
			{
				double max_diff = (double)(-max_count + offset_count) * rotete_vel * sampling_time;

				target_pos(0) = rotate_pos(0) + rotate_len*cos(offset_angle + max_diff);
				target_pos(1) = rotate_pos(1) + rotate_len*sin(offset_angle + max_diff);
				
			}
			else if (state == MOVE_PAUSE || state == MOVE_STOP)
			{
				target_pos = current_pos;
			}
			else if (state == ON_GROUND_TROT)
			{
				double max_diff = (double)(-max_count + offset_count + trot_offset*max_count) * rotete_vel * sampling_time;
				//std::cout << max_count << "\t" << offset_count << std::endl;
				target_pos(0) = rotate_pos(0) + rotate_len*cos(offset_angle + max_diff);
				target_pos(1) = rotate_pos(1) + rotate_len*sin(offset_angle + max_diff);

			}
			else if (state == NOT_ON_GROUND_TROT)
			{
				//std::cout << max_count << "\t" << offset_count << std::endl;
				double max_diff = (double)(max_count * targetpos_rate + offset_count + trot_offset*max_count) * rotete_vel * sampling_time;
				target_pos(0) = rotate_pos(0) + rotate_len*cos(offset_angle + max_diff);
				target_pos(1) = rotate_pos(1) + rotate_len*sin(offset_angle + max_diff);
				//std::cout << target_pos(0) << std::endl;
			}
		}

}

/**
*@brief �ڒn���Ă��邩�̔���
*@return �ڒn���Ă���ꍇ��true
*/
bool Leg_Object::onGround()
{
	if (state == NOT_ON_GROUND_CRAWL || state == NOT_ON_GROUND_INTERMITTENT_CRAWL || state == NOT_ON_GROUND_TROT)
	{
		return false;
	}
	return true;
}

/**
*@brief �t�^���w�ɂ��֐ߊp�x���v�Z
*@param pos �r��ʒu
*@return �֐ߊp�x
*/
std::vector<double> Leg_Object::inverseKinematics(Vector3d pos)
{
	std::vector<double> the;
	for (int i = 0; i < 3; i++)
	{
		the.push_back(0);
	}

	the[0] = atan2(pos(1), pos(0));

	double ld_xy = sqrt(pos(0)*pos(0) + pos(1)*pos(1)) - leg_len[0];
	double ld = sqrt(pos(2)*pos(2) + ld_xy*ld_xy);
	double c3 = (ld*ld - leg_len[1] * leg_len[1] - leg_len[2] * leg_len[2]) / (2 * leg_len[1] * leg_len[2]);
	double s3 = sqrt(1 - c3*c3);

	the[2] = atan2(s3, c3);

	double A = ld_xy;
	double M = leg_len[1] + leg_len[2] * c3;
	double B = pos[2];
	double N = leg_len[2] * s3;
	the[1] = atan2(M*A - N*B, N*A + M*B);

	return the;
}


/**
*@brief ���^���w�ɂ��r��ʒu���v�Z
*@param the �֐ߊp�x
*@return �r��ʒu
*/
Vector3d Leg_Object::calcKinematics(std::vector<double> the)
{
	Vector3d pos;
	if (the.size() < 3)return pos;
	pos(2) = leg_len[1] * cos(the[1]) + leg_len[2] * cos(the[1] + the[2]);
	double ld = leg_len[1] * sin(the[1]) + leg_len[2] * sin(the[1] + the[2]) + leg_len[0];
	pos(0) = ld * cos(the[0]);
	pos(1) = ld * sin(the[0]);
	return pos;
}

/**
*@brief ��]���x�A�X�e�b�v���̍Đݒ�
*@param rv ��]���x
*@param len ��]���S�܂ł̒���
*@param mc �X�e�b�v��
*/
void Leg_Object::update_status(double rv, int mc)
{

	count = count * mc / max_count;
	offset_count = offset_count * mc / max_count;

	rotete_vel = rotete_vel * max_count / mc;
	
	max_count = mc;
	/*
	if (rv*rotete_vel >= 0)rotete_vel = rv;
	else rotete_vel = -rv;
	*/
	
	//rotate_len = len;
	//std::cout << count << "\t" << offset_count << "\t" << max_count << std::endl;
}

/**
*@brief �V�r�����̐ݒ�
*@param lh ����
*/
void Leg_Object::setLiftHeight(double lh)
{
	lift_height = lh;
}


/**
*@brief �W���C���g�̃I�t�Z�b�g�ݒ�
*@param o1 �W���C���g0�̃I�t�Z�b�g
*@param o1 �W���C���g1�̃I�t�Z�b�g
*@param o1 �W���C���g2�̃I�t�Z�b�g
*/
void Leg_Object::setJointOffset(double o0, double o1, double o2)
{
	jointOffset[0] = o0;
	jointOffset[1] = o1;
	jointOffset[2] = o2;
}
/**
*@brief �W���C���g�̉��͈͏���̐ݒ�
*@param o1 �W���C���g0�̉��͈͏���l
*@param o1 �W���C���g1�̉��͈͏���l
*@param o1 �W���C���g2�̉��͈͏���l
*/
void Leg_Object::setUpperLimitJoint(double l0, double l1, double l2)
{
	UpperLimitJoint[0] = l0;
	UpperLimitJoint[1] = l1;
	UpperLimitJoint[2] = l2;
}
/**
*@brief �W���C���g�̉��͈͉����̐ݒ�
*@param o1 �W���C���g0�̉��͈͉����l
*@param o1 �W���C���g1�̉��͈͉����l
*@param o1 �W���C���g2�̉��͈͉����l
*/
void Leg_Object::setLowerLimitJoint(double l0, double l1, double l2)
{
	LowerLimitJoint[0] = l0;
	LowerLimitJoint[1] = l1;
	LowerLimitJoint[2] = l2;
}


/**
*@brief �֐ߊp�x�̐ݒ�
*@param t �֐ߊp�x
*@return true�̏ꍇ�͉��͈͊O
*/
bool Leg_Object::setAngle(std::vector<double> t)
{
	bool  ret = false;
	for (int i = 0; i < 3; i++)
	{
		if (UpperLimitJoint[i] < t[i])
		{
			theta[i] = UpperLimitJoint[i];
			ret = true;
		}
		else if (LowerLimitJoint[i] > t[i])
		{
			theta[i] = UpperLimitJoint[i];
			ret = true;
		}
		else
		{
			theta[i] = t[i];
		}
	}
	return ret;
}