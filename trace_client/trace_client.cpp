// trace_client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ClientPopen.h"

int _tmain(int argc, _TCHAR* argv[])
{


	ClientPopen *p = new ClientPopen();
	p->Run();

	delete p;



	return 0;
}

