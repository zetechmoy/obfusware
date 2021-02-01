// obfusware.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <windows.h>


int _tmain(int argc, _TCHAR* argv[])
{
    char s[] = "Hello world";
    DWORD dwBytesWritten;
	WriteFile((HANDLE)0x00000007, s, (DWORD)strlen(s), &dwBytesWritten, NULL);    //prints always to console
	while(1);



	//AllocConsole();
    //HANDLE hStdout;
    //HANDLE hStdout2 = (HANDLE)0x00000007;
    //HANDLE hScreenBuffer = CreateFileA("CONOUT$", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

    //hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    //WriteFile(hStdout2, s, (DWORD)strlen(s), &dwBytesWritten, NULL);	//prints always to console

    //WriteFile(hStdout, s, (DWORD)strlen(s), &dwBytesWritten, NULL);     //can be redirected; example TestCON.exe > test.txt
    //WriteFile(hScreenBuffer, s, (DWORD)strlen(s), &dwBytesWritten, NULL);//prints always to console
    //FreeConsole();
	//WriteFile((HANDLE)0x00000007, s, (DWORD)strlen(s), &dwBytesWritten, NULL);
	
	return 0;
}

