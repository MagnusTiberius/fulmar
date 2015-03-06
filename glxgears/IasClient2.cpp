#include "IasClient2.h"

auto appid = L"Z-BenPlayground";
auto appv = L"1.2.3.4";
auto tid = L"dd88c56e-0716-4b60-850a-7591987cd447";


IasClient2::IasClient2()
{
	begTime = clock();
}


IasClient2::~IasClient2()
{
}


void IasClient2::init()
{
	hres = Initialize(appid, L"appversion", tid, nullptr, nullptr);
}

void IasClient2::begin_session()
{
	hres = BeginSession(&hsess, 0);
}

void IasClient2::record_event(wchar_t* msg)
{
	hres = RecordEvent(hsess, msg, 1, 0);  
}

void IasClient2::record_event_keyvalue(wchar_t* msg)
{
	wchar_t* const * keys;
	const wchar_t* const * values;
	size_t cnt;
	for (auto const &it1 : map_fps) {

	}
	hres = RecordEventEx(hsess, msg, 1, 0, keys, values, cnt);
}


void IasClient2::record_event_seg(wchar_t* msg, wchar_t* segkeys[], wchar_t* segvals[], size_t cnt)
{
	auto const eos = '\0';
	auto const spc = ' ';
	for (int i = 0; i < cnt; i++) {
		wchar_t* p = segvals[i];
		int skip = 0;
		for (int j = 0; p[j] != eos; j++) {
			if (p[j] == spc) {
				skip++;
			}
			else {
				break;
			}
		}
		int k = 0;
		for (int j = skip; p[j] != eos; j++) {
			auto c = p[j];
			p[k] = c;
			k++;
		}
		p[k] = eos;
	}
	// send event
	hres = RecordEventEx(hsess, msg, cnt, 0, segkeys, segvals, cnt);
}

void IasClient2::end_session()
{
	hres = EndSession(hsess);
}

void IasClient2::deinit()
{
	hres = Deinitialize(); 
}

unsigned long IasClient2::elapsed_time()
{
	auto seconds = ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
	return seconds;
}

void IasClient2::capture_fps(int t0, float fps)
{
	char* s;
	sprintf(s, "%s", t0);

	std::string ts = std::string(s);

	map_fps[ts] = fps;
}