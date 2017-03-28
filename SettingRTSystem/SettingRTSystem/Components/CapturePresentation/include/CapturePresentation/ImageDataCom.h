// -*- C++ -*-
/*!
 * @file  ImageDataCom.h
 * @brief �摜�f�[�^����M�̊֐�
 * @date  $Date$
 *
 * $Id$
 */

#ifndef IMAGEDATACOM_H
#define IMAGEDATACOM_H

#include <string>
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include "InterfaceDataTypesStub.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/imgproc.hpp>


/**
*@brief CameraImage�^����IplImage�̉摜�f�[�^���擾
* @param ci CameraImage�^�̉摜�f�[�^
* @return IplImage�̉摜�f�[�^
*/
IplImage* GetCameraImage(RTC::CameraImage *ci);

/**
*@brief IplImage�̉摜�f�[�^��CameraImage�^�̃f�[�^�ɐݒ�
* @param ci CameraImage�^�̃f�[�^
* @param im IplImage�̉摜�f�[�^
* @param string_encode ���k�̌`��(off�͈��k�Ȃ��Apng�Ajpeg��I���\)
* @param int_encode_quality ���k��(png��0�`10�Ajpeg��0�`100)
*/
void SetCameraImage(RTC::CameraImage *ci, IplImage* im, std::string string_encode = "off", int int_encode_quality = 75);


#endif