// minclient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "IasClient.h"
#include "ChatClient.h"

int _tmain(int argc, _TCHAR* argv[])
{
	ChatClient *chat_client;
	IasClient *ias_client;

	chat_client = new ChatClient();
	chat_client->Connect();

	chat_client->Send("Create client.\n");
	ias_client = new IasClient();

	chat_client->Send("Init.\n");
	ias_client->init();
	chat_client->Send("Begin session.\n");
	ias_client->begin_session();
	chat_client->Send("Record event: StartMinClientDemo\n");
	ias_client->record_event(L"StartMinClientDemo\n");

	chat_client->Send("Record event: EndMinClientDemo\n");
	ias_client->record_event(L"EndMinClientDemo\n");
	chat_client->Send("End session.\n");
	ias_client->end_session();
	chat_client->Send("Deinit.\n");
	ias_client->deinit();

	for (int i = 1; i < 20; i++) {
		chat_client->Send(".\n");
	}

	chat_client->Close();


	delete chat_client;
	//delete ias_client;

	return 0;
}

