#include "ClientPopen.h"


ClientPopen::ClientPopen()
{
}


ClientPopen::~ClientPopen()
{
}


void ClientPopen::Run()
{
	chat_client = new ChatClient();
	chat_client->Connect();

	/* Run DIR so that it writes its output to a pipe. Open this
	* pipe with read text attribute so that we can read it
	* like a text file.
	*/
	if ((chkdsk = _popen("trace.exe  ", "rt")) == NULL)
		exit(1);

	/* Read pipe until end of file. End of file indicates that
	* CHKDSK closed its standard out (probably meaning it
	* terminated).
	*/
	while (!feof(chkdsk))
	{
		//char c = fgetc(chkdsk);
		//if (c != EOF) {
		//	chat_client->Send(&c);
		//	puts(&c);
		//}
		if (fgets(psBuffer, sz, chkdsk) != NULL)
		{
			printf(psBuffer);
		}

		chat_client->Send(psBuffer);
	}

	/* Close pipe and print return value of CHKDSK. */
	printf("\nProcess returned %d\n", _pclose(chkdsk));

	delete chat_client;
}