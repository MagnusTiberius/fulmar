// runschedtask.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h> 

#include <initguid.h>
#include <ole2.h>
#include <mstask.h>
#include <msterr.h>
#include <wchar.h>

using namespace std;


string get_full_path() {
	ifstream myfile;
	string file1 = "..\\..\\..\\xml\\run_lrio.xml";
	myfile.open(file1);
	if (myfile.is_open()) {
		myfile.close();
		char* abspath = new char[250];
		const char *relpath = file1.c_str();
		char* fullpath = _fullpath(abspath, relpath, 250);
		return abspath;
	}
	file1 = "..\\..\\xml\\run_lrio.xml";
	myfile.open(file1);
	if (myfile.is_open()) {
		myfile.close();
		char* abspath = new char[250];
		const char *relpath = file1.c_str();
		char* fullpath = _fullpath(abspath, relpath, 250);
		return abspath;
	}
	file1 = "..\\xml\\run_lrio.xml";
	myfile.open(file1);
	if (myfile.is_open()) {
		myfile.close();
		char* abspath = new char[250];
		const char *relpath = file1.c_str();
		char* fullpath = _fullpath(abspath, relpath, 250);
		return abspath;
	}
	return "";
}

string get_relative_path() {
	ifstream myfile;
	string file1 = "..\\..\\..\\xml\\run_lrio.xml";
	myfile.open(file1);
	if (myfile.is_open()) {
		myfile.close();
		return file1;
	}
	file1 = "..\\..\\xml\\run_lrio.xml";
	myfile.open(file1);
	if (myfile.is_open()) {
		myfile.close();
		return file1;
	}
	file1 = "..\\xml\\run_lrio.xml";
	myfile.open(file1);
	if (myfile.is_open()) {
		myfile.close();
		return file1;
	}
	return "";
}

/*
int run_it(char* strFunct, char* strstrParams) {
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION ProcessInfo;
	char Args[4096];
	wchar_t Argsw[4096];
	char *pEnvCMD = NULL;
	char *pDefaultCMD = "CMD.EXE";
	ULONG rc;

	memset(&StartupInfo, 0, sizeof(StartupInfo));
	StartupInfo.cb = sizeof(STARTUPINFO);
	StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
	StartupInfo.wShowWindow = SW_HIDE;

	Args[0] = 0;

	//pEnvCMD = getenv("COMSPEC");

	//if (pEnvCMD){

	//	strcpy(Args, pEnvCMD);
	//}
	//else{
		strcpy_s(Args, pDefaultCMD);
	//}

	// "/c" option - Do the command then terminate the command window
	strcat_s(Args, " /c ");
	//the application you would like to run from the command window
	strcat_s(Args, strFunct);
	strcat_s(Args, " ");
	//the parameters passed to the application being run from the command window.
	strcat_s(Args, strstrParams);

	size_t return_value;
	size_t sz = 100;
	size_t count = strlen(Args) + 1;

	//mbstowcs_s(return_value, Argsw, sz, Args, count);

	auto cr = !CreateProcess(NULL, L"schtasks /c /XML lrio.xml", NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&StartupInfo,
		&ProcessInfo);

	if (cr)
	{
		return GetLastError();
	}

	WaitForSingleObject(ProcessInfo.hProcess, INFINITE);
	if (!GetExitCodeProcess(ProcessInfo.hProcess, &rc))
		rc = 0;

	CloseHandle(ProcessInfo.hThread);
	CloseHandle(ProcessInfo.hProcess);

	return rc;

}
*/

HRESULT removetask() {
	HRESULT hr = S_OK;
	ITaskScheduler *pITS;

	ULONG TASKS_TO_RETRIEVE = 20;

	hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_CTaskScheduler,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_ITaskScheduler,
			(void **)&pITS);
		if (FAILED(hr))
		{
			CoUninitialize();
			return hr;
		}
	}
	else
	{
		return hr;
	}

	IEnumWorkItems *pIEnum;
	hr = pITS->Enum(&pIEnum);
	pITS->Release();
	if (FAILED(hr))
	{
		CoUninitialize();
		return hr;
	}

	LPWSTR *lpwszNames;
	DWORD dwFetchedTasks = 0;
	while (SUCCEEDED(pIEnum->Next(TASKS_TO_RETRIEVE,
		&lpwszNames,
		&dwFetchedTasks))
		&& (dwFetchedTasks != 0))
	{
		///////////////////////////////////////////////////////////////
		// Process each task. Note that this example prints the 
		// name of each task to the screen.
		//////////////////////////////////////////////////////////////
		while (dwFetchedTasks)
		{
			wprintf(L"%s\n", lpwszNames[--dwFetchedTasks]);
			CoTaskMemFree(lpwszNames[dwFetchedTasks]);
		}
		CoTaskMemFree(lpwszNames);
	}

	pIEnum->Release();
	CoUninitialize();
	return S_OK;

}

void str_replace(string &s, const string &search, const string &replace)
{
	printf("s=%s\n", s.c_str());
	printf("search=%s\n", search.c_str());
	int pos = s.find(search);
	printf("pos=%5.2d\n", pos);
	if (pos > 0) {
		string s1 = s.substr(0, pos-1);
		cout << "\nfound=============================\n" << s1 << std::endl;
	}

}

std::string get_file_content(const std::string& path)
{
	string str, strTotal;
	ifstream in;
	in.open(path);
	getline(in, str);
	while (in) {
		 strTotal += str;
		 getline(in, str);
	}
	return strTotal;
}

void patch_xml() {
	FILE ** fp = nullptr;
	char * line = NULL;
	size_t len = 0;
	size_t read;

	string file1 = get_relative_path();
	const char *f1 = file1.c_str();
	 fopen_s(fp, f1, "r");
	if (fp == NULL) return;

	char* buf = new char[1024];

	char* b = fgets(buf, 1024, *fp);
	fclose(*fp);

}



int _tmain(int argc, _TCHAR* argv[])
{

	//patch_xml();

	string line;
	ifstream myfile;
	ofstream outfile;

	cout << "run =============================\n" << endl;

	string file1 = get_relative_path();
	myfile.open(file1);
	outfile.open("run_lrio.xml");
	//myfile << "Writing this to a file.\n";
	if (myfile.is_open()) { 
		/* ok, proceed with output */ 
		while (getline(myfile, line)) {
			string fpath = get_full_path();
			//str_replace(line, "{{lrio}}", fpath);
			std::cout << line << std::endl;
			outfile << line << std::endl;
		}
	}

	outfile.close();
	myfile.close();

	std::string infile = get_file_content(file1);
	str_replace(infile, "{{ lrio }}", get_full_path());
	outfile.open("run_lrio.xml");
	outfile << infile << std::endl;
	outfile.close();

	//int res = run_it("schtasks", "/XML lrio.xml");
	char *taskit = new char[250]; 
	
	int res; 

	if (false) {
		sprintf_s(taskit, 250, "schtasks /create /XML %s /tn run_lrio", file1.c_str());
		res = system(taskit);
		std::cout << "result:" << res << std::endl;
		sprintf_s(taskit, 250, "schtasks /run /tn run_lrio");
		res = system(taskit);
		std::cout << "result:" << res << std::endl;
		sprintf_s(taskit, 250, "schtasks /delete /f /tn run_lrio");
		auto resdel = system(taskit);
		std::cout << "result:" << resdel << std::endl;
	}

	if (true) {
		HWND hwnd = 0;
		ShellExecute(hwnd, L"open", L"cmd.exe", L"/c trace.exe", 0, SW_NORMAL);
		system("cmd.exe /c dir c:\\");
		res = system("lrio.exe");
		std::cout << "result:" << res << std::endl;
	}

	//removetask();

	return res;
}

