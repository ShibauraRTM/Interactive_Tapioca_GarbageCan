// -*- C++ -*-
/*!
 * @file  music.cpp
 * @brief make a sound
 * @date $Date$
 *
 * @author Kohei Kubota<tacotanx@gmail.com>
 *
 * ありません。
 *
 * $Id$
 */

#include "music.h"
#include "DxLib.h"
// Module specification
// <rtc-template block="module_spec">
static const char* music_spec[] =
  {
    "implementation_id", "music",
    "type_name",         "music",
    "description",       "make a sound",
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
music::music(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_1or0In("1or0", m_1or0)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
music::~music()
{
}



RTC::ReturnCode_t music::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("1or0", m_1or0In);
  
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
RTC::ReturnCode_t music::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t music::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t music::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * DXライブラリをウィンドウモードにする。
 */

RTC::ReturnCode_t music::onActivated(RTC::UniqueId ec_id)
{
	ChangeWindowMode(TRUE);
	
	if (DxLib_Init() == -1)    // ＤＸライブラリ初期化処理
	{
		return RTC::RTC_ERROR;    // エラーが起きたら直ちに終了
	}

  return RTC::RTC_OK;
}

/*!
 * DXライブラリを終了する。
 */

RTC::ReturnCode_t music::onDeactivated(RTC::UniqueId ec_id)
{
	DxLib_End();

  return RTC::RTC_OK;
}


/*!
 * InPortから入ってくる数字が0から1になったときに水滴が落ちる音を出
 * す。
 */

RTC::ReturnCode_t music::onExecute(RTC::UniqueId ec_id)
{
	if (m_1or0In.isNew())
	{

		m_1or0In.read();
		if (m_1or0.data == 0)
			flag = 1;


		if (m_1or0.data == 1 && flag == 1)
		{
			flag = 0;
	
			PlaySoundFile(_T("water-drop3.mp3"), DX_PLAYTYPE_NORMAL); // water-drop3.mp3(タピオカが落ちる音)の再生


		}
	}
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t music::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t music::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t music::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t music::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t music::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void musicInit(RTC::Manager* manager)
  {
    coil::Properties profile(music_spec);
    manager->registerFactory(profile,
                             RTC::Create<music>,
                             RTC::Delete<music>);
  }
  
};


