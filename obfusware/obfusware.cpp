// obfusware.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
    char s[] = "Hello world";
    DWORD dwBytesWritten;
	WriteFile((HANDLE)0x00000007, s, (DWORD)strlen(s), &dwBytesWritten, NULL);    //prints always to console
	printf("\naddr IsDebuggerPresent = %p", IsDebuggerPresent);
	printf("\naddr WriteFile = %p", WriteFile);
	int delta = 7C82F6EF - 7C8112FF;
	
	while(1);	
	return 0;
}

