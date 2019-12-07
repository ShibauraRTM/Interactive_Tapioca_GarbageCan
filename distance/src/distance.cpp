// -*- C++ -*-
/*!
 * @file  distance.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "distance.h"

// Module specification
// <rtc-template block="module_spec">
static const char* distance_spec[] =
  {
    "implementation_id", "distance",
    "type_name",         "distance",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "TCNSK",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.kyori", "5",

    // Widget
    "conf.__widget__.kyori", "text",
    // Constraints

    "conf.__type__.kyori", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
distance::distance(RTC::Manager* manager)
// <rtc-template block="initializer">
	: RTC::DataFlowComponentBase(manager),
	m_distanceIn("distance", m_distance),
	m_0or1Out("0or1", m_0or1)


    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
distance::~distance()
{
}



RTC::ReturnCode_t distance::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("distance", m_distanceIn);
  
  // Set OutPort buffer
  addOutPort("0or1", m_0or1Out);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("kyori", m_kyori, "5");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t distance::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distance::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distance::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t distance::onActivated(RTC::UniqueId ec_id)
{
	
	initial = -1.0;
	waitOutputCount = 0;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t distance::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t distance::onExecute(RTC::UniqueId ec_id)
{
	if (waitOutputCount > 0) {
		waitOutputCount--;//毎回値を減らす
		
		return RTC::RTC_OK;
	}

	if(m_distanceIn.isNew()){
		m_distanceIn.read();
		if ( initial < 0 ) //初めて距離を読み取るとき
		{
			initial = m_distance.data;
		}else
			if (fabs(m_distance.data - initial) >= m_kyori) //初期値と現在の値の差の絶対値が基準値より大きいとき
			{   /*通った*/
				m_0or1.data = 1;
				m_0or1Out.write(); 
				waitOutputCount = 1500; //約1.5秒待つ
			}
			else 
			{ /*通ってない*/
				m_0or1.data = 0;
				m_0or1Out.write();
			}
	
	}
	


  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t distance::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distance::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distance::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distance::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distance::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void distanceInit(RTC::Manager* manager)
  {
    coil::Properties profile(distance_spec);
    manager->registerFactory(profile,
                             RTC::Create<distance>,
                             RTC::Delete<distance>);
  }
  
};


