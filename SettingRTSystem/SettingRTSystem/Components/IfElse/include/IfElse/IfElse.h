// -*- C++ -*-
/*!
 * @file  IfElse.h
 * @brief If Else
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef IFELSE_H
#define IFELSE_H

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
#include <coil/stringutil.h>

#include "DyPortBase.h"
#include "CalcFunc.h"


class IfElseCompBase;




/*!
 * @class IfElse
 * @brief If Else
 *
 * このRTCは3個のTimedBoolean型のDataOutPortを備えています。
 * コンフィギュレーションパラメータでIf条件、elseIf条件を設定すると
 * 、条件を満たしたときに対応するデータポートからの出力がTrueになり
 * ます。
 *
 */
class IfElse
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  IfElse(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~IfElse();
  void configUpdate();
  void writeData(bool if_ans, bool ifelse_ans, bool else_ans);

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
   * ifの条件式
   * - Name: if_condition if_condition
   * - DefaultValue: None
   */
  std::string m_if_condition;
  /*!
   * ifelseの条件式
   * - Name: ifelse_condition ifelse_condition
   * - DefaultValue: None
   */
  
  std::string m_ifelse_condition;
  std::string m_dataType;
  int m_imputNum;

  std::string last_dataType;


  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  RTC::TimedBoolean m_IfOut;
  /*!
   * Ifの条件を満たしたときにTrue、満たさないときはFalseを出力しま
   * す。
   * - Type: RTC::TimedBoolean
   */
  OutPort<RTC::TimedBoolean> m_IfOutOut;
  RTC::TimedBoolean m_IfElseOut;
  /*!
   * IfElseの条件を満たしたときにTrue、満たさないときはFalseを出力
   * します。
   * - Type: RTC::TimedBoolean
   */
  OutPort<RTC::TimedBoolean> m_IfElseOutOut;
  RTC::TimedBoolean m_ElseOut;
  /*!
   * いずれの条件も満たさなかった時にTrue、それ以外はFalseを出力し
   * ます。
   * - Type: RTC::TimedBoolean
   */
  OutPort<RTC::TimedBoolean> m_ElseOutOut;
  
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
	IfElseCompBase *func;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};





class IfElseCompBase : public RTCLogicBase
{
public:
	virtual void setCondition(std::string ifcondition, std::string ifelsecondition)
	{
		m_ifcondition = ifcondition;
		m_ifelsecondition = ifelsecondition;
	};
	virtual void changeNum(int num){};
	std::string m_ifcondition;
	std::string m_ifelsecondition;
};

template <class T, class T2>
class IfElseComp : public IfElseCompBase
{
public:
	IfElseComp(IfElse *rtc, int num)
	{
		m_rtc = rtc;
		/*for(int i=0;i < num;i++)
		{
			std::string name = "u" + coil::otos<int>(i);
			DataTypeInPort<T,T2>* iep = new DataTypeInPort<T,T2>(name, m_rtc);
			portList.push_back(iep);
		}*/
		updatePortList<DataTypeInPort<T,T2>>(portList,num,"u",m_rtc);
	};
	~IfElseComp()
	{
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = portList.begin(); it != portList.end(); ++it)
		{
			delete *it;
		}
	};
	void changeNum(int num){
		/*if(num > portList.size())
		{
			for(int i=portList.size();i < num;i++)
			{
				std::string name = "u" + coil::otos<int>(i);
				DataTypeInPort<T,T2>* iep = new DataTypeInPort<T,T2>(name, m_rtc);
				portList.push_back(iep);
			}
		}
		else if(num < portList.size())
		{
			//std::cout << portList.size() << std::endl;
			for (std::vector<DataTypeInPort<T,T2>*>::iterator it = portList.begin()+num; it != portList.end();)
			{
				//DataTypeInPort<T,T2>*tmp = *it;
				delete *it;
				it = portList.erase( it );
				// ++it;
			}
			//std::cout << portList.size() << std::endl;
		}*/
		updatePortList<DataTypeInPort<T,T2>>(portList,num,"u",m_rtc);
	};
	
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){
		
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = portList.begin(); it != portList.end(); ++it)
		{
			if(!(*it)->isNew())
			{
				return RTC::RTC_OK;
			};
		}
		if(m_ifcondition == "None")
		{
			std::cout << "条件式が入力されていません" << std::endl;
			return RTC::RTC_ERROR;
		}
		std::vector<T2> dataList;
		for (typename std::vector<DataTypeInPort<T,T2>*>::iterator it = portList.begin(); it != portList.end(); ++it)
		{
			dataList.push_back((*it)->getData());
		}
		bool if_ans = false;
		bool ifelse_ans = false;
		bool else_ans = false;
		
		std::string text = getTextReplaceVal<T2>(dataList,m_ifcondition);
		bool result;
		bool success = judgeFunc(text,result);
		//std::cout << text << std::endl;
		if(success)
		{
			if_ans = result;
		}
		else
		{
			std::cout << "構文解析に失敗しました" << std::endl;
			return RTC::RTC_ERROR;
		}
		if(m_ifelsecondition != "None")
		{
			text = getTextReplaceVal<T2>(dataList,m_ifelsecondition);
			success = judgeFunc(text,result);
			if(success)
			{
				ifelse_ans = result;
			}
			else
			{
				std::cout << "構文解析に失敗しました" << std::endl;
				return RTC::RTC_ERROR;
			}
		}
		if(!if_ans && !ifelse_ans)
		{
			else_ans = true;
		}
		m_rtc->writeData(if_ans,ifelse_ans,else_ans);
		return RTC::RTC_OK;
	};
	bool judgeFunc(std::string func, bool &result)
	{
		bool_grammar<std::string::const_iterator, T2> grammar;
		std::string::const_iterator iter = func.begin(), end = func.end();
		return boost::spirit::qi::phrase_parse(iter, end, grammar, boost::spirit::ascii::space, result);
	}
	IfElse *m_rtc;
	std::vector<DataTypeInPort<T,T2>*> portList;
	
};




extern "C"
{
  DLL_EXPORT void IfElseInit(RTC::Manager* manager);
};

#endif // IFELSE_H
