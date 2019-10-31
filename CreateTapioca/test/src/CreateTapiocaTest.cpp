// -*- C++ -*-
/*!
 * @file  CreateTapiocaTest.cpp
 * @brief CreateTapioca
 * @date $Date$
 *
 * @author Kohei Kubota<tacotanx@gmail.com>
 *
 * zlibライセンス
 *
 * Copyright (c) 2019 Kohei Kubota
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *  claim that you wrote the original software. If you use this software
 *  in a product, an acknowledgment in the product documentation would be
 *  appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *  misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * $Id$
 */

#include "CreateTapiocaTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* createtapioca_spec[] =
  {
    "implementation_id", "CreateTapiocaTest",
    "type_name",         "CreateTapiocaTest",
    "description",       "CreateTapioca",
    "version",           "1.0.0",
    "vendor",            "Kohei Kubota",
    "category",          "Category",
    "activity_type",     "PERIODIC",
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
CreateTapiocaTest::CreateTapiocaTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_addTapiIn("addTapi", m_addTapi)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CreateTapiocaTest::~CreateTapiocaTest()
{
}



RTC::ReturnCode_t CreateTapiocaTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("addTapi", m_addTapiOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CreateTapiocaTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapiocaTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapiocaTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * BulletWorldの生成。
 */

RTC::ReturnCode_t CreateTapiocaTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*!
 * BulletWorldの初期化と破棄。
 */

RTC::ReturnCode_t CreateTapiocaTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*!
 * 受け取る数字が0から1になったとき、タピオカを表示する。
 * 40個タピオカがたまると一括ですべてを消す。
 * ウィンドウが閉じられたときにDeactivateする。
 */

RTC::ReturnCode_t CreateTapiocaTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CreateTapiocaTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapiocaTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapiocaTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapiocaTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapiocaTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CreateTapiocaTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(createtapioca_spec);
    manager->registerFactory(profile,
                             RTC::Create<CreateTapiocaTest>,
                             RTC::Delete<CreateTapiocaTest>);
  }
  
};


