// -*- C++ -*-
/*!
 * @file  NineAxisSensor_RT_USB.h
 * @brief RT-USB-9AXIS-00 Component
 * @date  $Date$
 *
 * @author 宮本信彦
 * n-miyamoto@aist.go.jp
 * 産業技術総合研究所　
 * ロボットイノベーション研究センター　
 * ロボットソフトウェアプラットフォーム研究チーム
 *
 * LGPL
 *
 * $Id$
 */

#ifndef NINEAXISSENSOR_RT_USB_H
#define NINEAXISSENSOR_RT_USB_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include "RT_Usb_Nine_Axis_Sensor.h"

/*!
 * @class NineAxisSensor_RT_USB
 * @brief RT-USB-9AXIS-00 Component
 *
 * USB出力9軸IMUセンサモジュール制御RTC
 *
 */
class NineAxisSensor_RT_USB
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  NineAxisSensor_RT_USB(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~NineAxisSensor_RT_USB();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>

  /***
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 姿勢のオフセット
   * - Name: rotOffset rotOffset
   * - DefaultValue: 0
   */
  double m_rotOffset;
  /*!
   * 地磁気データX軸方向のオフセット
   * - Name: magnOffsetX magnOffsetX
   * - DefaultValue: -84
   */
  short int m_magnOffsetX;
  /*!
   * 地磁気データY軸方向のオフセット
   * - Name: magnOffsetY magnOffsetY
   * - DefaultValue: -13
   */
  short int m_magnOffsetY;
  /*!
   * 地磁気データZ軸方向のオフセット
   * - Name: magnOffsetZ magnOffsetZ
   * - DefaultValue: -36
   */
  short int m_magnOffsetZ;
  /*!
   * 9軸センサモジュールに対応するデバイスファイル
   * - Name: serial_port serial_port
   * - DefaultValue: /dev/ttyACM0
   */
  std::string m_serial_port;

  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedAcceleration3D m_acc;
  /*!
   * 加速度センサの計測値
   * - Type: RTC::TimedAcceleration3D
   * - Unit: m/s^2
   */
  OutPort<RTC::TimedAcceleration3D> m_accOut;
  RTC::TimedDoubleSeq m_magn;
  /*!
   * 地磁気センサの計測値
   * - Type: RTC::TimedDoubleSeq
   */
  OutPort<RTC::TimedDoubleSeq> m_magnOut;
  RTC::TimedAngularVelocity3D m_gyro;
  /*!
   * ジャイロセンサーの計測値
   * - Type: RTC::TimedAngularVelocity3D
   * - Unit: rad/s
   */
  OutPort<RTC::TimedAngularVelocity3D> m_gyroOut;
  RTC::TimedDouble m_temp;
  /*!
   * 温度センサの計測値
   * - Type: RTC::TimedDouble
   * - Unit: 度
   */
  OutPort<RTC::TimedDouble> m_tempOut;
  RTC::TimedOrientation3D m_rot;
  /*!
   * センサ情報から計算した姿勢
   * - Type: RTC::TimedOrientation3D
   * - Unit: rad
   */
  OutPort<RTC::TimedOrientation3D> m_rotOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
	RT_Usb_Nine_Axis_Sensor *rt_usb_sensor;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void NineAxisSensor_RT_USBInit(RTC::Manager* manager);
};

#endif // NINEAXISSENSOR_RT_USB_H
