#pragma once

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>

#define PORT 5150
#define DATA_BUFSIZE 8192

class RcvSrv
{
public:
	RcvSrv();
	~RcvSrv();

private:
	typedef struct _SOCKET_INFORMATION {
		CHAR Buffer[DATA_BUFSIZE];
		WSABUF DataBuf;
		SOCKET Socket;
		OVERLAPPED Overlapped;
		DWORD BytesSEND;
		DWORD BytesRECV;
	} SOCKET_INFORMATION, *LPSOCKET_INFORMATION;

	// Global var
	DWORD TotalSockets = 0;
	LPSOCKET_INFORMATION SocketArray[FD_SETSIZE];

public:
	int Recvd();

private:
	BOOL CreateSocketInformation(SOCKET s);
	void FreeSocketInformation(DWORD Index);

};

