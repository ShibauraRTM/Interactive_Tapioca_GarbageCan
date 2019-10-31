// -*- C++ -*-
/*!
 * @file  CreateTapioca.cpp
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

#include "CreateTapioca.h"

// Module specification
// <rtc-template block="module_spec">
static const char* createtapioca_spec[] =
  {
    "implementation_id", "CreateTapioca",
    "type_name",         "CreateTapioca",
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
CreateTapioca::CreateTapioca(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_addTapiIn("addTapi", m_addTapi)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CreateTapioca::~CreateTapioca()
{
}



RTC::ReturnCode_t CreateTapioca::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("addTapi", m_addTapiIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CreateTapioca::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapioca::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapioca::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * BulletWorldの生成。
 */

RTC::ReturnCode_t CreateTapioca::onActivated(RTC::UniqueId ec_id)
{
	tapiocaNum = 0;

	//make window
	app = new SimpleOpenGL3App("CreateTapioca", 1260, 1120, true);
	//app = new SimpleOpenGL3App("Bullet Physics", 1024, 768, true);

	//using mouse

	//GUI
	gui = new OpenGLGuiHelper(app, false);        //OpenGLを引数にGUIのインスタンスを作る
	CommonExampleOptions options(gui);          //GUIのインスタンスを引数にoptionsを生成
	example = MultiBodySoftContactCreateFunc(options);  //CreateFuncが必ず必要

	example->initPhysics();
	example->resetCamera();

	clock.reset();


  return RTC::RTC_OK;
}

/*!
 * BulletWorldの初期化と破棄。
 */

RTC::ReturnCode_t CreateTapioca::onDeactivated(RTC::UniqueId ec_id)
{
	example->exitPhysics();
	if (example != NULL) {
		delete example;
		example = NULL;
	}
	if (app != NULL) {
		delete app;
		app = NULL;
	}
	return RTC::RTC_OK;
  return RTC::RTC_OK;
}

/*!
 * 受け取る数字が0から1になったとき、タピオカを表示する。
 * 40個タピオカがたまると一括ですべてを消す。
 * ウィンドウが閉じられたときにDeactivateする。
 */

RTC::ReturnCode_t CreateTapioca::onExecute(RTC::UniqueId ec_id)
{
	if (m_addTapiIn.isNew()) {
		m_addTapiIn.read();
		if (m_addTapi.data == 0)
			flag = 1;

	}

	if (flag == 1 && m_addTapi.data == 1)
	{
		flag = 0;

		example->keyboardCallback('a', true);
		printf("TapiocaNum=%d\n", tapiocaNum);
		if (tapiocaNum >= 40) {
			example->keyboardCallback('r', true);
			tapiocaNum = 0;
		}
		else {
			tapiocaNum++;
		}
	}
	app->m_instancingRenderer->init();
	app->m_instancingRenderer->updateCamera(app->getUpAxis());

	btScalar dtSec = btScalar(clock.getTimeInSeconds());
	if (dtSec < 0.1) {
		dtSec = 0.1;
	}
	example->stepSimulation(dtSec);
	clock.reset();

	example->renderScene();

	app->swapBuffer();

	if (app->m_window->requestedExit()) {
		RTC::ExecutionContext_var ec = get_context(ec_id);
		if (!CORBA::is_nil(ec)) {
			ec->deactivate_component(::RTC::RTObject::_duplicate(getObjRef()));
		}
	}

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CreateTapioca::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapioca::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapioca::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapioca::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CreateTapioca::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CreateTapiocaInit(RTC::Manager* manager)
  {
    coil::Properties profile(createtapioca_spec);
    manager->registerFactory(profile,
                             RTC::Create<CreateTapioca>,
                             RTC::Delete<CreateTapioca>);
  }
  
};


