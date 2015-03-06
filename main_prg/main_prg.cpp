// main_prg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ChatClient.h"

int _tmain(int argc, _TCHAR* argv[])
{
	const size_t sz = 256;
	char   psBuffer[sz];
	FILE   *chkdsk;

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
		if (fgets(psBuffer, sz, chkdsk) != NULL)
			printf(psBuffer);
	}

	/* Close pipe and print return value of CHKDSK. */
	printf("\nProcess returned %d\n", _pclose(chkdsk));

	return 0;
}

