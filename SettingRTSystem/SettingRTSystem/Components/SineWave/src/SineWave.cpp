// -*- C++ -*-
/*!
 * @file  SineWave.cpp
 * @brief Sine Wave
 * @date $Date$
 *
 * LGPL
 *
 * $Id$
 */

#include "SineWave.h"

// Module specification
// <rtc-template block="module_spec">
static const char* sinewave_spec[] =
  {
    "implementation_id", "SineWave",
    "type_name",         "SineWave",
    "description",       "Sine Wave",
    "version",           "1.0.0",
    "vendor",            "Miyamoto Nobuhiko",
    "category",          "Math",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.dataType", "TimedDouble",
    "conf.default.samplingTime", "0.01",
    "conf.default.realTime", "OFF",
    "conf.default.amplitude", "1",
    "conf.default.bias", "0",
    "conf.default.frequency", "1",
    "conf.default.phase", "0",
    "conf.default.data_size", "1",
    // Widget
    "conf.__widget__.dataType", "radio",
    "conf.__widget__.samplingTime", "text",
    "conf.__widget__.realTime", "radio",
    "conf.__widget__.amplitude", "text",
    "conf.__widget__.bias", "text",
    "conf.__widget__.frequency", "text",
    "conf.__widget__.phase", "text",
    "conf.__widget__.data_size", "spin",
    // Constraints
    "conf.__constraints__.dataType", "(TimedDouble,TimedFloat,TimedDoubleSeq,TimedFloatSeq)",
    "conf.__constraints__.realTime", "(ON,OFF)",
    "conf.__constraints__.data_size", "1<=x<=1000",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SineWave::SineWave(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : DynamicComponentBase(manager)

    // </rtc-template>
{
	func = NULL;
}

/*!
 * @brief destructor
 */
SineWave::~SineWave()
{
}


void SineWave::configUpdate()
{
	this->m_configsets.update("default");
	m_dataType = coil::eraseBlank(std::move(m_dataType));
	m_realTime = coil::eraseBlank(std::move(m_realTime));

	if(last_dataType != m_dataType)
	{
		last_dataType = m_dataType;
		if(func)
		{
			delete func;
		}

		if(m_dataType == "TimedDouble")
		{
			func = new SineWaveSingle<TimedDouble, double>(this);
		}
		
		else if(m_dataType == "TimedFloat")
		{
			func = new SineWaveSingle<TimedFloat, float>(this);
		}
		


		else if(m_dataType == "TimedDoubleSeq")
		{
			func = new SineWaveSeq<TimedDoubleSeq, double>(this);
		}
		
		else if(m_dataType == "TimedFloatSeq")
		{
			func = new SineWaveSeq<TimedFloatSeq, float>(this);
		}
		
		
	}

	if(func)
	{
		func->setSamplingTime(m_samplingTime);
		if(m_realTime == "ON")
		{
			func->setConfig(true);
		}
		else
		{
			func->setConfig(false);
		}
		func->setAmplitude(m_amplitude);
		func->setBias(m_bias);
		func->setFrequency(m_frequency);
		func->setPhase(m_phase);
		func->setDataSize(m_data_size);
	}
		
}


RTC::ReturnCode_t SineWave::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("dataType", m_dataType, "TimedDouble");
  bindParameter("samplingTime", m_samplingTime, "0.01");
  bindParameter("realTime", m_realTime, "OFF");
  bindParameter("amplitude", m_amplitude, "1");
  bindParameter("bias", m_bias, "0");
  bindParameter("frequency", m_frequency, "1");
  bindParameter("phase", m_phase, "0");
  bindParameter("data_size", m_data_size, "1");
  // </rtc-template>
  configUpdate();
  this->addConfigurationSetListener(ConfigurationSetListenerType::ON_SET_CONFIG_SET,
                                    new DynamicPortConfigUpdateParam(this));
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onActivated(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onActivated(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onExecute(RTC::UniqueId ec_id)
{
	if(func)
	{
		return func->onExecute(ec_id);
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SineWave::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}



extern "C"
{
 
  void SineWaveInit(RTC::Manager* manager)
  {
    coil::Properties profile(sinewave_spec);
    manager->registerFactory(profile,
                             RTC::Create<SineWave>,
                             RTC::Delete<SineWave>);
  }
  
};


