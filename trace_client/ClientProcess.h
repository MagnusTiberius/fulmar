#pragma once

#include <windows.h> 
#include <tchar.h>
#include <stdio.h> 
#include <strsafe.h>

#define BUFSIZE 4096 

class ClientProcess
{
public:
	ClientProcess();
	~ClientProcess();

private:
	/* child process's STDIN is the user input or data that you enter into the child process - READ */
	HANDLE g_hChildStd_IN_Rd = NULL;
	/* child process's STDIN is the user input or data that you enter into the child process - WRITE */
	HANDLE g_hChildStd_IN_Wr = NULL;
	/* child process's STDOUT is the program output or data that child process returns - READ */
	HANDLE g_hChildStd_OUT_Rd = NULL;
	/* child process's STDOUT is the program output or data that child process returns - WRITE */
	HANDLE g_hChildStd_OUT_Wr = NULL;

	SECURITY_ATTRIBUTES saAttr;

	void ErrorExit(LPTSTR msg);

public:
	void CreateChildProcess();
	void WriteToPipe(CHAR chBuf[]);
	void ReadFromPipe(void);

};

