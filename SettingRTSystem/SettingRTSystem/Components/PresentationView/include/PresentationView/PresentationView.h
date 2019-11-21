// -*- C++ -*-
/*!
 * @file  PresentationView.h
 * @brief Presentation View Component
 * @date  $Date$
 *
 * $Id$
 */

#ifndef PRESENTATIONVIEW_H
#define PRESENTATIONVIEW_H

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>
#include <coil/UUID.h>
#include <vector>
#include <iterator>

#include "DataBaseStub.h"

#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/CorbaConsumer.h>

#include "SubFunction.h"


// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

class OtherPort;


void portConnect(PortService_ptr p1, PortService_var p2);

void ListRecursive(CosNaming::NamingContext_ptr context,std::vector<OtherPort> &rtclist,std::string &name, TreeObject *to);

int rtc_get_rtclist(RTC::CorbaNaming &naming,std::vector<OtherPort> &rtclist, TreeObject *to, std::string IP_adress);

/*!
 * @class OtherPort
 * @brief データポートオブジェクト、パスを格納するクラス
 *
 */
class OtherPort
{
	public:
		/**
		*@brief コンストラクタ
		* @param p データポートオブジェクト
		* @param s パス
		*/
		OtherPort(RTC::PortService_var p, std::vector<std::string> s)
		{
			
			pb = p;
			buff = s;
		};
		RTC::PortService_var pb; /**<　@brief  */
		std::vector<std::string> buff; /**<　@brief  */
		
};

/*!
 * @class PresentationView
 * @brief Presentation View Component
 *
 */
class PresentationView
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  PresentationView(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~PresentationView();

  /*!
   * @brief m_imageの取得
   * @return CameraImage型のデータ
   */
  CameraImage *getImage();
  bool imageIsNew;	/**<　@brief  */

  /*!
   * @brief スライドを進める
   * @param num 進めるスライド数
   */
  void writeSlideNumberOut(int num);
  /*!
   * @brief スライドを戻る
   * @param num 戻るスライド数
   */
  void writeEffectNumberOut(int num);
  /*!
   * @brief 実行周期取得
   * @return 実行周期
   */
  int getRate();
  /*!
   * @brief 線データ出力
   * @param dt 描画点
   */
  void putPenData(std::vector<int>*dt);
  /*!
   * @brief データベースに登録された動画リストを取得
   * @return 動画リスト
   */
  std::vector<std::vector<std::string>> getList();
  /*!
   * @brief 動画の名前を指定して動画を送信しているRTCと接続
   * @param name 動画の名前
   * @param m_List 動画リスト
   * @return 成功した場合True、失敗した場合False
   */
  bool connectDPort(const char *name, std::vector<std::vector<std::string>> m_List);
  /*!
   * @brief データポートを接続
   * @param m_path RTCのパス
   * @param pname データポート名
   * @return 成功した場合True、失敗した場合False
   */
  bool connectDPorts(std::string m_path, std::string pname, PortService_ptr p1);
  /*!
   * @brief 動画リストから名前で動画の情報を取得
   * @param name 動画の名前
   * @param m_List 動画リスト
   * @return RTCの情報
   */
  std::vector<std::string> getPath(const char *name, std::vector<std::vector<std::string>> m_List);
  /*!
   * @brief パスからデータポートオブジェクトを取得
   * @param name パス
   * @param ops データポートオブジェクトのリスト
   * @param op 取得したデータポートオブジェクト
   * @return 取得に成功した場合True、失敗した場合False
   */
  bool getRTC(std::vector<std::string> name, std::vector<OtherPort> ops, OtherPort &op);

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
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

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
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

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
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

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
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

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
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
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
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

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
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  CameraImage m_image;
  /*!
   */
  InPort<CameraImage> m_imageIn;
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">

  TimedShort m_SlideNumberOut;
  /*!
   */
  OutPort<TimedShort> m_SlideNumberOutOut;

  TimedShort m_EffectNumberOut;
  /*!
   */
  OutPort<TimedShort> m_EffectNumberOutOut;

  TimedShortSeq m_Pen;
  /*!
   */
  OutPort<TimedShortSeq> m_PenOut;
  
  // </rtc-template>

  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  


  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  RTC::CorbaPort m_DataBasePort;
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  /*!
   */
  RTC::CorbaConsumer<DataBase::mDataBase> m_database;

  // </rtc-template>

 private:
	 std::string m_uuidstr;	/**<　@brief  */
	 RTC::Manager* m_manager;	/**<　@brief  */
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


extern "C"
{
  DLL_EXPORT void PresentationViewInit(RTC::Manager* manager);
};

#endif // PRESENTATIONVIEW_H
