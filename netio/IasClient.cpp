#include "IasClient.h"

//const wchar_t* appid = L"deadbeef";

const wchar_t* appid = L"Z-BenPlayground";
auto tid = L"dd88c56e-0716-4b60-850a-7591987cd447";

auto appv = L"1.2.3.4";
//auto tid = L"deadbeef-dead-beef-dead-beefdeadbeef";


IasClient::IasClient()
{
	begTime = clock();
	sdk_handle = nullptr;

	//chat_client = new ChatClient();
	//chat_client->Connect();

#ifdef _DEBUG
	configuration = L"Debug";
#else
	configuration = L"Release";
#endif

#ifdef _WIN64   
	platform = L"win64";
#else
	platform = L"win32";
#endif


}


IasClient::~IasClient()
{
	//delete chat_client;
}


void IasClient::init()
{
	hres = Initialize(&sdk_handle, appid, L"appversion", tid, nullptr, nullptr);
	//chat_client->Send("=========================>>>>Initialize\n");
}

void IasClient::begin_session()
{
	hres = BeginSession(sdk_handle, &hsess, 0);
}

void IasClient::record_event(wchar_t* msg)
{
	hres = RecordEvent(sdk_handle, hsess, msg, 1, 0);

	//wchar_t *msgout = new wchar_t[512];
	//swprintf_s(msgout, 512, L"=========================>>>>%s%s%s", msg, configuration, platform);

	//std::wstring mout;

	//mout.append(msg);
	//mout.append(configuration);
	//mout.append(platform);

	//const wchar_t* m = mout.c_str();
	//hres = RecordEvent(sdk_handle, hsess, m, 1, 0);

	hres = RecordEvent(sdk_handle, hsess, msg, 1, 0);

	//char* mbstr = new char[512];
	//wcstombs_s(512, mbstr, m, 512);
	//const char* c = mbstr;
	//chat_client->Send("=========================>>>>record event\n");
}

void IasClient::record_event_keyvalue(wchar_t* msg)
{
	//wchar_t* const * keys;
	//const wchar_t* const * values;
	//size_t cnt;
	//for (auto const &it1 : map_fps) {

	//}
	//hres = RecordEventEx(sdk_handle, hsess, msg, 1, 0, keys, values, cnt);
}


void IasClient::record_event_seg(wchar_t* msg, wchar_t* segkeys[], wchar_t* segvals[], size_t cnt)
{
	auto const eos = '\0';
	auto const spc = ' ';
	for (size_t i = 0; i < cnt; i++) {
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
	//wchar_t* msgout = new wchar_t[512];
	//swprintf_s(msgout, 512, L"=========================>>>>%s%s%s", msg, configuration, platform);
	// send event
	//hres = RecordEventEx(sdk_handle, hsess, msgout, cnt, 0, segkeys, segvals, cnt);

	hres = RecordEventEx(sdk_handle, hsess, msg, cnt, 0, segkeys, segvals, cnt);
}

void IasClient::end_session()
{
	hres = EndSession(sdk_handle, hsess);
}

void IasClient::deinit()
{
	hres = Deinitialize(sdk_handle);
	//chat_client->Send("=========================>>>>Deinitialize\n");

}

unsigned long IasClient::elapsed_time()
{
	auto seconds = ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
	return seconds;
}

void IasClient::capture_fps(int t0, float fps)
{
	char* s = new char[512];
	sprintf_s(s, 512, "%s", t0);
	std::string ts = std::string(s);

	map_fps[ts] = fps;
}