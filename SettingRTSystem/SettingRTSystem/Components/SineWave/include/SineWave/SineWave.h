// -*- C++ -*-
/*!
 * @file  SineWave.h
 * @brief Sine Wave
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef SINEWAVE_H
#define SINEWAVE_H

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

#include "DyPortBase.h"
#include "RTMath.h"

class SineWaveCompBase;


/*!
 * @class SineWave
 * @brief Sine Wave
 *
 * 正弦波を生成
 *
 */
class SineWave
  : public DynamicComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  SineWave(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~SineWave();
  void configUpdate();
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
   * データ型
   * - Name: dataType dataType
   * - DefaultValue: TimedDouble
   * - Constraint: (TimedDouble,TimedFloat,TimedDoubleSeq,TimedFlo
   *               atSeq)
   */
  std::string m_dataType;
  /*!
   * ステップ幅
   * - Name: samplingTime samplingTime
   * - DefaultValue: 0.01
   */
  std::chrono::nanoseconds m_samplingTime;
  /*!
   * 
   * - Name: realTime realTime
   * - DefaultValue: OFF
   * - Constraint: (ON,OFF)
   */
  std::string m_realTime;
  /*!
   * 振幅
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: amplitude amplitude
   * - DefaultValue: 1
   */
  std::string m_amplitude;
  /*!
   * 正弦波に追加する定数値
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: bias bias
   * - DefaultValue: 0
   */
  std::string m_bias;
  /*!
   * 周波数
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: frequency frequency
   * - DefaultValue: 1
   * - Unit: rad/sec
   */
  std::string m_frequency;
  /*!
   * 位相
   * シーケンス型で入力する場合は”,”で区切ってください。
   * - Name: phase phase
   * - DefaultValue: 0
   * - Unit: rad
   */
  std::string m_phase;
  int m_data_size;
  // </rtc-template>

  // DataInPort declaration
  // <rtc-template block="inport_declare">
  
  // </rtc-template>


  // DataOutPort declaration
  // <rtc-template block="outport_declare">
  
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
	SineWaveCompBase *func;
	std::string last_dataType;
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

};


class SineWaveCompBase : public RTCLogicBase
{
public:
	virtual void setSamplingTime(std::chrono::nanoseconds s)
	{
	
	};
	virtual void setConfig(bool c)
	{

	};
	virtual void setAmplitude(std::string a)
	{

	};
	virtual void setBias(std::string b)
	{

	};
	virtual void setFrequency(std::string f)
	{

	};
	virtual void setPhase(std::string p)
	{

	};
	virtual void setDataSize(int s)
	{

	};
};




template <class T, class T2>
class SineWaveSingle : public SineWaveCompBase
{
public:
	SineWaveSingle(SineWave *rtc)
	{
		m_outport = new DataTypeOutPort<T,T2>("out", rtc);
		
	};
	~SineWaveSingle()
	{
		delete m_outport;
	}
	void setSamplingTime(std::chrono::nanoseconds s)
	{
		func.setSamplingTime(s);
	};
	void setConfig(bool c)
	{
		func.setConfig(c);
	};
	void setAmplitude(std::string a)
	{
		std::vector<T2> tmp_ad;
		if(getValueInString(a,tmp_ad))
		{
			func.setAmplitude(tmp_ad[0]);
		}
	};
	void setBias(std::string b)
	{
		std::vector<T2> tmp_bs;
		if(getValueInString(b,tmp_bs))
		{
			func.setBias(tmp_bs[0]);
		}
	};
	void setFrequency(std::string f)
	{
		std::vector<T2> tmp_fc;
		if(getValueInString(f,tmp_fc))
		{
			func.setFrequency(tmp_fc[0]);
		}
	};
	void setPhase(std::string p)
	{
		std::vector<T2> tmp_ph;
		if(getValueInString(p,tmp_ph))
		{
			func.setPhase(tmp_ph[0]);
		}
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){

		T2 ans = func.calc();

		//std::cout << ans << std::endl;
		m_outport->setData(ans);
			
		
		
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){
		func.reset();
		return RTC::RTC_OK;
	};


	DataTypeOutPort<T,T2>* m_outport;
	RTSineWave<T2> func;
	

};


template <class T, class T2>
class SineWaveSeq : public SineWaveCompBase
{
public:
	SineWaveSeq(SineWave *rtc)
	{
		m_outport = new DataTypeOutPortSeq<T,T2>("out", rtc);
		
	};
	~SineWaveSeq()
	{
		delete m_outport;
	}
	void setSamplingTime(std::chrono::nanoseconds s)
	{
		samplingTime = s;
		for (typename std::vector<RTSineWave<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setSamplingTime(s);
		}
	};
	void setConfig(bool c)
	{
		realTime = c;
		for (typename std::vector<RTSineWave<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).setConfig(c);
		}
	};
	void setAmplitude(std::string a)
	{
		getValueInString(a,amplitude);
		for (typename decltype(func)::size_type i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(amplitude,i,v))return;
			func[i].setAmplitude(v);
		}
	};
	void setBias(std::string b)
	{
		getValueInString(b,bias);
		for (typename decltype(func)::size_type i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(bias,i,v))return;
			func[i].setBias(v);
		}
	};
	void setFrequency(std::string f)
	{
		getValueInString(f,frequency);
		for (typename decltype(func)::size_type i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(frequency,i,v))return;
			func[i].setFrequency(v);
		}
	};
	void setPhase(std::string p)
	{
		getValueInString(p,phase);
		for (typename decltype(func)::size_type i=0;i < func.size();i++)
		{
			T2 v;
			if(!getValueInList<T2>(phase,i,v))return;
			func[i].setPhase(v);
		}
	};
	virtual void setDataSize(int s)
	{
		m_data_size = s;
	};
	RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){


			for(int i=0;i < m_data_size;i++)
			{
				
				if((int)func.size()-1 < i)
				{
					RTSineWave<T2> sw_tmp = RTSineWave<T2>();
					sw_tmp.setSamplingTime(samplingTime);
					sw_tmp.setConfig(realTime);

					T2 v;
					if(!getValueInList(amplitude,i,v))return RTC::RTC_ERROR;
					sw_tmp.setAmplitude(v);
					if(!getValueInList(bias,i,v))return RTC::RTC_ERROR;
					sw_tmp.setBias(v);
					if(!getValueInList(frequency,i,v))return RTC::RTC_ERROR;
					sw_tmp.setFrequency(v);
					if(!getValueInList(phase,i,v))return RTC::RTC_ERROR;
					sw_tmp.setPhase(v);

					func.push_back(sw_tmp);
					
				}
				
			}
			std::vector<T2> ans;
			for (typename std::vector<RTSineWave<T2>>::iterator it = func.begin(); it != func.end(); ++it)
			{

				ans.push_back((*it).calc());
				
			}
			if(ans.size() > 0)
			{
				//for (typename std::vector<T2>::iterator it = ans.begin(); it != ans.end(); ++it)
				//	std::cout << (*it) << std::endl;
				m_outport->setData(ans);
			}
		
		
		return RTC::RTC_OK;
	};
	RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){
		for (typename std::vector<RTSineWave<T2>>::iterator it = func.begin(); it != func.end(); ++it)
		{
			(*it).reset();
		}
		return RTC::RTC_OK;
	};

	DataTypeOutPortSeq<T,T2>* m_outport;
	std::vector<RTSineWave<T2>> func;
	bool realTime;
	std::chrono::nanoseconds samplingTime;
	std::vector<T2> amplitude;
	std::vector<T2> bias;
	std::vector<T2> frequency;
	std::vector<T2> phase;
	int m_data_size;
};


extern "C"
{
  DLL_EXPORT void SineWaveInit(RTC::Manager* manager);
};

#endif // SINEWAVE_H
