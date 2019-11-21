// -*- C++ -*-
/*!
 * @file  DyPortBase.h
 * @brief 
 * @date  $Date$
 *
 * LGPL
 *
 * $Id$
 */

#ifndef DYPORTBASE_H
#define DYPORTBASE_H

#include <rtm/DataFlowComponentBase.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>


class DynamicComponentBase
  : public RTC::DataFlowComponentBase
{
 public:
	DynamicComponentBase(RTC::Manager* manager) : RTC::DataFlowComponentBase(manager)
	{
		
	};
	virtual void configUpdate(){};
};


class RTCLogicBase
{
public:
	virtual ~RTCLogicBase()
	{
	}
	virtual RTC::ReturnCode_t onInitialize(){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onFinalize(){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	
};


class DynamicDataPortBase
{
public:
	virtual ~DynamicDataPortBase()
	{
	}
	virtual bool isNew()
	{
		return true;
	};
};



template <class T, class T2>
class DataTypeInPort : public DynamicDataPortBase
{
public:
	DataTypeInPort(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		In = new T();
		inIn = new RTC::InPort<T>(name.c_str(),*In);
		m_rtc = rtc;
		m_rtc->addInPort(name.c_str(), *inIn);
	};
	~DataTypeInPort()
	{
		m_rtc->removePort(*inIn);
	};
	bool isNew()
	{
		return inIn->isNew();
	};
	T2 getData()
	{
		inIn->read();
		return In->data;
	};
	T *In;
	RTC::InPort<T> *inIn;
	RTC::DataFlowComponentBase *m_rtc;
};

template <class T, class T2>
class DataTypeOutPort : public DynamicDataPortBase
{
public:
	DataTypeOutPort(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		Out = new T();
		outOut = new RTC::OutPort<T>(name.c_str(),*Out);
		m_rtc = rtc;
		m_rtc->addOutPort(name.c_str(), *outOut);
	};
	~DataTypeOutPort()
	{
		m_rtc->removePort(*outOut);
	};
	
	void setData(T2 v)
	{
		Out->data = v;
		outOut->write();
	};
	T *Out;
	RTC::OutPort<T> *outOut;
	RTC::DataFlowComponentBase *m_rtc;
};



template <class T, class T2>
class DataTypeInPortSeq : public DynamicDataPortBase
{
public:
	DataTypeInPortSeq(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		In = new T();
		inIn = new RTC::InPort<T>(name.c_str(),*In);
		m_rtc = rtc;
		m_rtc->addInPort(name.c_str(), *inIn);
	};
	~DataTypeInPortSeq()
	{
		m_rtc->removePort(*inIn);
	};
	bool isNew()
	{
		return inIn->isNew();
	};
	std::vector<T2> getData()
	{
		inIn->read();
		std::vector<T2> ans;
		for(int i=0;i < In->data.length();i++)
		{
			ans.push_back(In->data[i]);
		}
		return ans;
	};
	T *In;
	RTC::InPort<T> *inIn;
	RTC::DataFlowComponentBase *m_rtc;
};

template <class T, class T2>
class DataTypeOutPortSeq : public DynamicDataPortBase
{
public:
	DataTypeOutPortSeq(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		Out = new T();
		outOut = new RTC::OutPort<T>(name.c_str(),*Out);
		m_rtc = rtc;
		m_rtc->addOutPort(name.c_str(), *outOut);
	};
	~DataTypeOutPortSeq()
	{
		m_rtc->removePort(*outOut);
	};
	
	void setData(std::vector<T2> v)
	{
		//Out->data = v;
		Out->data.length(v.size());
		for(int i=0;i < v.size();i++)
		{
			Out->data[i] = v[i];
		}
		outOut->write();
	};
	T *Out;
	RTC::OutPort<T> *outOut;
	RTC::DataFlowComponentBase *m_rtc;
};

class DynamicPortConfigUpdateParam
    : public RTC::ConfigurationSetListener
{
public:
	/**
	*@brief コンストラクタ
	* @param e_rtc ExcelRTC
	*/
    DynamicPortConfigUpdateParam(DynamicComponentBase *rtc)
    {
		m_rtc = rtc;
    }
	/**
	*@brief 
	* @param config_set 
	*/
    void operator()(const coil::Properties& config_set)
	{
		
		m_rtc->configUpdate();
		
    }
	DynamicComponentBase *m_rtc; /**<　@brief  */

};

template <class T>
void updatePortList(std::vector<T*> &v, int num, std::string id, RTC::DataFlowComponentBase* rtc)
{
	
	if(num > v.size())
	{
		for(int i=v.size();i < num;i++)
		{
			std::string name = id + coil::otos<int>(i);

			T* iep = new T(name, rtc);

			v.push_back(iep);

		}
		
	}
	else if(num < v.size())
	{
		for (std::vector<T*>::iterator it = v.begin()+num; it != v.end();)
		{
			delete *it;
			it = v.erase( it );
		}
	}
};



#endif 
