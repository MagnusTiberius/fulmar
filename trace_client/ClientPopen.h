#pragma once

#include "ChatClient.h"

const size_t sz = 64;

class ClientPopen
{
public:
	ClientPopen();
	~ClientPopen();

	void Run();

private:
	
	char   psBuffer[sz];
	FILE   *chkdsk;

	ChatClient *chat_client;
};

