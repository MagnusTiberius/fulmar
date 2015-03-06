#pragma once

#include "ias2.h"
#include <time.h>
#include <map>


class IasClient2
{
public:
	IasClient2();
	~IasClient2();

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
	HANDLE hsess;

	unsigned long begTime;
	std::map <std::string, float> map_fps;
};

