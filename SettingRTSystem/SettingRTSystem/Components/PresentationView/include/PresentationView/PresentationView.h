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
 * @brief �f�[�^�|�[�g�I�u�W�F�N�g�A�p�X���i�[����N���X
 *
 */
class OtherPort
{
	public:
		/**
		*@brief �R���X�g���N�^
		* @param p �f�[�^�|�[�g�I�u�W�F�N�g
		* @param s �p�X
		*/
		OtherPort(RTC::PortService_var p, std::vector<std::string> s)
		{
			
			pb = p;
			buff = s;
		};
		RTC::PortService_var pb; /**<�@@brief  */
		std::vector<std::string> buff; /**<�@@brief  */
		
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
   * @brief m_image�̎擾
   * @return CameraImage�^�̃f�[�^
   */
  CameraImage *getImage();
  bool imageIsNew;	/**<�@@brief  */

  /*!
   * @brief �X���C�h��i�߂�
   * @param num �i�߂�X���C�h��
   */
  void writeSlideNumberOut(int num);
  /*!
   * @brief �X���C�h��߂�
   * @param num �߂�X���C�h��
   */
  void writeEffectNumberOut(int num);
  /*!
   * @brief ���s�����擾
   * @return ���s����
   */
  int getRate();
  /*!
   * @brief ���f�[�^�o��
   * @param dt �`��_
   */
  void putPenData(std::vector<int>*dt);
  /*!
   * @brief �f�[�^�x�[�X�ɓo�^���ꂽ���惊�X�g���擾
   * @return ���惊�X�g
   */
  std::vector<std::vector<std::string>> getList();
  /*!
   * @brief ����̖��O���w�肵�ē���𑗐M���Ă���RTC�Ɛڑ�
   * @param name ����̖��O
   * @param m_List ���惊�X�g
   * @return ���������ꍇTrue�A���s�����ꍇFalse
   */
  bool connectDPort(const char *name, std::vector<std::vector<std::string>> m_List);
  /*!
   * @brief �f�[�^�|�[�g��ڑ�
   * @param m_path RTC�̃p�X
   * @param pname �f�[�^�|�[�g��
   * @return ���������ꍇTrue�A���s�����ꍇFalse
   */
  bool connectDPorts(std::string m_path, std::string pname, PortService_ptr p1);
  /*!
   * @brief ���惊�X�g���疼�O�œ���̏����擾
   * @param name ����̖��O
   * @param m_List ���惊�X�g
   * @return RTC�̏��
   */
  std::vector<std::string> getPath(const char *name, std::vector<std::vector<std::string>> m_List);
  /*!
   * @brief �p�X����f�[�^�|�[�g�I�u�W�F�N�g���擾
   * @param name �p�X
   * @param ops �f�[�^�|�[�g�I�u�W�F�N�g�̃��X�g
   * @param op �擾�����f�[�^�|�[�g�I�u�W�F�N�g
   * @return �擾�ɐ��������ꍇTrue�A���s�����ꍇFalse
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
	 std::string m_uuidstr;	/**<�@@brief  */
	 RTC::Manager* m_manager;	/**<�@@brief  */
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
