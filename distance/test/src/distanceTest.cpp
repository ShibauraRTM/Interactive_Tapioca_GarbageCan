// -*- C++ -*-
/*!
 * @file  distanceTest.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "distanceTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* distance_spec[] =
  {
    "implementation_id", "distanceTest",
    "type_name",         "distanceTest",
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
distanceTest::distanceTest(RTC::Manager* manager)
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
distanceTest::~distanceTest()
{
}



RTC::ReturnCode_t distanceTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("0or1", m_0or1In);
  
  // Set OutPort buffer
  addOutPort("distance", m_distanceOut);
  
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
RTC::ReturnCode_t distanceTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distanceTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distanceTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t distanceTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t distanceTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t distanceTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t distanceTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distanceTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distanceTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distanceTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t distanceTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void distanceTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(distance_spec);
    manager->registerFactory(profile,
                             RTC::Create<distanceTest>,
                             RTC::Delete<distanceTest>);
  }
  
};


