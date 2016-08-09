// -*- C++ -*-
/*!
 * @file  Speech.cpp
 * @brief Speech RTC
 * @date $Date$
 *
 * $Id$
 */

#include "Speech.h"

#include <locale.h>
#include <Windows.h>
#include <tchar.h>
#include <sapi.h>

// Module specification
// <rtc-template block="module_spec">
static const char* speech_spec[] =
  {
    "implementation_id", "Speech",
    "type_name",         "Speech",
    "description",       "Speech RTC",
    "version",           "1.0.0",
    "vendor",            "takahashi",
    "category",          "Sound",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
	// Configuration variables
	"conf.default.speak_text", "hello,world",
	// Widget
	"conf.__widget__.speak_text", "text",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
Speech::Speech(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_speakIn("speak", m_speak)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
Speech::~Speech()
{
}



RTC::ReturnCode_t Speech::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("speak", m_speakIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  bindParameter("speak_text", m_speak_text, "hello,world");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Speech::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Speech::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Speech::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t Speech::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Speech::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t Speech::onExecute(RTC::UniqueId ec_id)
{
	if (m_speakIn.isNew())
	{
		if (m_speakIn.read() == true)
		{
			WCHAR	wText[100];
			size_t wLen = 0;

			setlocale(LC_ALL, "japanese");
			mbstowcs_s(&wLen, wText, 20, m_speak_text, _TRUNCATE);

			ISpVoice * pVoice = NULL;

			::CoInitialize(NULL);

			CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
			pVoice->Speak(wText, 0, NULL);
			pVoice->Release();
			pVoice = NULL;

			::CoUninitialize();
		}
	}

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t Speech::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Speech::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Speech::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Speech::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t Speech::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void SpeechInit(RTC::Manager* manager)
  {
    coil::Properties profile(speech_spec);
    manager->registerFactory(profile,
                             RTC::Create<Speech>,
                             RTC::Delete<Speech>);
  }
  
};


