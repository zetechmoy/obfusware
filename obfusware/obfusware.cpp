// obfusware.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#define _CRT_SECURE_NO_WARNINGS 1
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include <Windows.h>
#include <winuser.h>

#ifndef SPI_GETWHEELSCROLLLINES
#define SPI_GETWHEELSCROLLLINES   104
#endif
#include "zmouse.h"

int nb_windows_opened = 0;

int is_not_debbugging(){

	/* dont forget to uncomment return 0*/

	if(IsDebuggerPresent()){
		printf("DEBUG 1 detecté\n");
		//return 0;
	}

	BOOL reponse;
	CheckRemoteDebuggerPresent( GetCurrentProcess(), &reponse);
	if(reponse){
		printf("DEBUG 2 detecté\n");
		//return 0;
	}

	char * peb;
	__asm{
		mov ebx, 0x30
		xor ecx, ecx
		mov eax, fs:[ebx+ecx]
		;mov eax, fs:[0x30]
		mov peb, eax
	};

	if(peb[2]){
		printf("DEBUG 3 detecté\n");
		//return 0;
	}

	if(peb[104] & 0x70){
		printf("DEBUG 4 detecté\n");
		//return 0;
	}

	//works even if is launched in console
	SetLastError(0);
	OutputDebugStringA("Hello, debugger");
	if (GetLastError() != 0){
		printf("DEBUG 5 detecté\n");
		//return 0;
	}

	// IDA
	LPCWSTR wCName1 = L"QWidget";
	if (FindWindow(wCName1, NULL)){
		printf("DEBUG 6 detecté\n");
		//return 0;
	}

	// WinDbg
	LPCWSTR wCName2 = L"WinDbgFrameClass";
	if (FindWindow(wCName2, NULL)){
		printf("DEBUG 7 detecté\n");
		//return 0;
	}

	// Console
	LPCWSTR wCName3 = L"ConsoleWindowClass";
	if (FindWindow(wCName3, NULL)){
		printf("DEBUG 8 detecté\n");
		//return 0;
	}

	// Gestionnaire de fichiers
	LPCWSTR wCName4 = L"CabinetWClass";
	if (FindWindow(wCName4, NULL)){
		printf("DEBUG 9 detecté\n");
		//return 0;
	}

	return 1;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam) {
    char buff[255], buff2[255];;

    if (IsWindowVisible(hWnd)) {
        GetWindowTextA(hWnd, (LPSTR) buff, 254);
		GetClassNameA(hWnd, (LPSTR) buff2, 254);
        //printf("%s %s\n", buff, buff2);
		nb_windows_opened = nb_windows_opened + 1;
    }

    return TRUE;
}

void affiche(char s[]){
    DWORD dwBytesWritten;
	WriteFile((HANDLE)0x00000007, s, (DWORD)strlen(s), &dwBytesWritten, NULL);
}

UINT GetNumScrollLines(void){
   HWND hdlMsWheel;
   UINT ucNumLines=3;  // 3 is the default
   OSVERSIONINFO osversion;
   UINT uiMsh_MsgScrollLines;
   
   memset(&osversion, 0, sizeof(osversion));
   osversion.dwOSVersionInfoSize =sizeof(osversion);
   GetVersionEx(&osversion);

   if ((osversion.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) || ( (osversion.dwPlatformId == VER_PLATFORM_WIN32_NT) && (osversion.dwMajorVersion < 4) )){
        hdlMsWheel = FindWindow(MSH_WHEELMODULE_CLASS, MSH_WHEELMODULE_TITLE);
        if (hdlMsWheel){
           uiMsh_MsgScrollLines = RegisterWindowMessage(MSH_SCROLL_LINES);
           if (uiMsh_MsgScrollLines)
                ucNumLines = (int)SendMessage(hdlMsWheel, uiMsh_MsgScrollLines, 0, 0);
        }
   } else if ( (osversion.dwPlatformId == VER_PLATFORM_WIN32_NT) && (osversion.dwMajorVersion >= 4) ){
      SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &ucNumLines, 0);
   }
   return ucNumLines;
}


int _tmain(int argc, _TCHAR* argv[]){

	/**********************************************/
	/* Condition : La VM doit tourner depuis      */
	/* au moins 1234567890 millis (~343 heures)   */
	DWORD tc = GetTickCount();
	if (tc > 1234567890){
		printf("Le système est allumé depuis suffisamment de temps : OK\n");
	}else{
		printf("Le système n'est pas allumé depuis suffisamment de temps : Not OK\n");
	}

	//printf("\naddr = %p", IsDebuggerPresent);
	//printf("\naddr = %p", WriteFile);

	/**********************************************/
	/* Condition : La souris doit être placée     */
	/* aux coordonnées (65, 65) pour les		  */
	/* coordonnées ('A', 'A')                     */
	POINT p;
	GetCursorPos(&p);
	if (p.x == 65 && p.y == 65){
		printf("La souris est à la bonne place : OK\n");
	}else{
		printf("La souris n'est pas à la bonne place : Not OK\n");
	}


	/**********************************************/
	/* Random fonction qui compile mais qui sert  */
	/* à rien                                     */
	int nb = GetNumScrollLines();
	printf("NumScrollLines : %d\n",nb);

	/**********************************************/
	/* Condition : Plus de 500 fenêtres ouvertes  */
	EnumWindows(EnumWindowsProc, 0);
	if(nb_windows_opened >= 500){
		printf("Enough windows are opened (%d) : OK\n", nb_windows_opened);
	}else{
		printf("Not enough windows are opened (%d) : Not OK\n", nb_windows_opened);
	}

	/**********************************************/
	/* Condition : heure actuelle = 04h01 du matin*/
	char ostime[128], osdate[128];
    _tzset();
	
	_strtime_s( ostime, 128 );
    _strdate_s( osdate, 128 );

	if(strncmp(osdate, "02/01/21", 10) == 0 && strncmp(ostime, "14:46:30", 8) == 0){
		printf("Time Comparison is OK\n");
	}else{
		printf("Time Comparison is Not OK\n");
	}

	/**********************************************/
	/* Condition : n'est pas en train de debugger */
	/* Ainsi que certaines fenêtres ouvertes	  */
	// https://github.com/ThomasThelen/AntiDebugging/


	if(is_not_debbugging()){
		printf("Is Not Debugging : OK\n");
	}else{
		printf("Is Debugging : Not OK\n");
	}

	/**********************************************/

	//attention la condition ne doit pas être codée en dur
	//elle doit être dans le if direct car sinon on
	//peut simplement changer la valeur en mémoire
	int condition = 1; 

	if(condition){
		affiche("Bonjour, le monde !\n");
	}else{
		affiche("Hello, world !\n");
	}

	while(1);
    return 0;
}

