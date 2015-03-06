#pragma once

#include "ias2.h"
#include <time.h>
#include <map>
//#include "ChatClient.h"
#include <string>

class IasClient
{
public:
	IasClient();
	~IasClient();

public:
	void init();
	void begin_session();
	void record_event(wchar_t* msg);
	void record_event_keyvalue(wchar_t* msg);
	void record_event_seg(wchar_t* msg, wchar_t* segkeys[], wchar_t* segvals[], size_t cnt);
	void end_session();
	void deinit();
	unsigned long elapsed_time();
	void capture_fps(int t0, float fps);

private:
	ias_error_t hres;
	ias_session_t hsess;
	ias_handle_t sdk_handle;

	wchar_t *configuration;
	wchar_t *platform;

	unsigned long begTime;
	std::map <std::string, float> map_fps;

	//ChatClient *chat_client;
};

