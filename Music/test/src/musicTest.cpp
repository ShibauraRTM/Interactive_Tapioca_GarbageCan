// -*- C++ -*-
/*!
 * @file  musicTest.cpp
 * @brief make a sound
 * @date $Date$
 *
 * @author Kohei Kubota<tacotanx@gmail.com>
 *
 * ありません。
 *
 * $Id$
 */

#include "musicTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* music_spec[] =
  {
    "implementation_id", "musicTest",
    "type_name",         "musicTest",
    "description",       "make a sound",
    "version",           "1.0.0",
    "vendor",            "Kohei Kubota",
    "category",          "Category",
    "activity_type",     "SPORADIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
musicTest::musicTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_1or0In("1or0", m_1or0)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
musicTest::~musicTest()
{
}



RTC::ReturnCode_t musicTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("1or0", m_1or0Out);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t musicTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t musicTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t musicTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * DXライブラリをウィンドウモードにする。
 */

RTC::ReturnCode_t musicTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*!
 * DXライブラリを終了する。
 */

RTC::ReturnCode_t musicTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*!
 * InPortから入ってくる数字が0から1になったときに水滴が落ちる音を出
 * す。
 */

RTC::ReturnCode_t musicTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t musicTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t musicTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t musicTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t musicTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t musicTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void musicTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(music_spec);
    manager->registerFactory(profile,
                             RTC::Create<musicTest>,
                             RTC::Delete<musicTest>);
  }
  
};


