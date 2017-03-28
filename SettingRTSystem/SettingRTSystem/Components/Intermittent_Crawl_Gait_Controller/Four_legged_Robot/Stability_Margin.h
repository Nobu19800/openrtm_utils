/*!
* @file  Stability_Margin.h
* @brief ����]�T�v�Z�N���X
*
*/


#ifndef Stability_Margin_H
#define Stability_Margin_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Core>
#include <Eigen/LU>
#include <vector>

#include "Leg_Object.h"

using namespace Eigen;



enum Stability_Direction
{
	STB_X_PLUS = 0,
	STB_X_MINUS = 1,
	STB_Y_PLUS = 2,
	STB_Y_MINUS = 3,
};






/**
* @class Stability_Margin
*@brief ����]�T�v�Z�N���X
*/
class Stability_Margin
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	Stability_Margin();
	/**
	*@brief �S�r�������]�T�v�Z
	*@param legs �r�̃��X�g
	*@param ne true�̏ꍇ��NE����]�T���v�Z
	*@param tf true�̏ꍇ�͖ڕW�ʒu�ł̈���]�T���v�Z
	*/
	static Stability_Margin calc_stability_margin(Leg_Object *legs,bool ne = false, bool tf = true);
	/**
	*@brief �d�S�ʒu�Ǝx���r�����̋������v�Z
	*@param pos0 �r0�̈ʒu
	*@param pos1 �r1�̈ʒu
	*@param dir ����ɂȂ�d�S�ʒu�̕���
	*@param ne true�̏ꍇ��NE����]�T���v�Z
	*/
	static Stability_Margin calc_distance(Vector3d pos0, Vector3d pos1, Stability_Direction dir, bool ne = false);
	/**
	*@brief ����]�T���擾
	*@param ne true�̏ꍇ��NE����]�T���擾
	*@return ����]�T
	*/
	double getDistance(bool ne);
	double distance;
	double slope;
	double ne_distance;
	Stability_Direction stb_dir;
};





#endif