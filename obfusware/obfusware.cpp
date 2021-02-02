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
unsigned int checksum = 2795625010;

int is_not_debbugging(){

	//fake return to address 0x0040105D


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

	// IDA / 010 Editor
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

	// OllyDbg
	LPCWSTR wCName5 = L"OllyDbg";
	if (FindWindow(wCName5, NULL)){
		printf("DEBUG 10 detecté\n");
		//return 0;
	}

	// MASM32
	LPCWSTR wCName6 = L"qe4_class";
	if (FindWindow(wCName6, NULL)){
		printf("DEBUG 11 detecté\n");
		//return 0;
	}

	// DebugView
	LPCWSTR wCName7 = L"dbgviewClass";
	if (FindWindow(wCName7, NULL)){
		printf("DEBUG 12 detecté\n");
		//return 0;
	}

	// WinObj
	LPCWSTR wCName8 = L"WinObjWClass";
	if (FindWindow(wCName8, NULL)){
		printf("DEBUG 13 detecté\n");
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

void ccpuid(int CPUInfo[4], int InfoType){
 __asm {
     mov    esi, CPUInfo
     mov    eax, InfoType
     xor    ecx, ecx  
     cpuid  
     mov    dword ptr [esi +  0], eax
     mov    dword ptr [esi +  4], ebx  
     mov    dword ptr [esi +  8], ecx  
     mov    dword ptr [esi + 12], edx  
  }
}

bool isGuestOSVM(){
	unsigned int cpuInfo[4];
    ccpuid((int*)cpuInfo,1);
    return ((cpuInfo[2] >> 31) & 1) == 1;
}
	
static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};

void build_decoding_table() {

    decoding_table = (char *) malloc(256);

    for (int i = 0; i < 64; i++)
        decoding_table[(unsigned char) encoding_table[i]] = i;
}


void base64_cleanup() {
    free(decoding_table);
}

char *base64_encode(const unsigned char *data,
                    int input_length,
                    int *output_length) {

    *output_length = ((input_length - 1) / 3) * 4 + 4; 

    char *encoded_data = (char *) malloc(*output_length);
    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        int octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        int octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        int octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

	encoded_data[*output_length] = '\0';
    return encoded_data;
}


unsigned char *base64_decode(const char *data,
                             int input_length,
                             int *output_length) {

    if (decoding_table == NULL) build_decoding_table();

    if (input_length % 4 != 0) return NULL;

    *output_length = input_length / 4 * 3;
	printf("ol = %d\n", *output_length);
    if (data[input_length - 1] == '=') (*output_length)--;
    if (data[input_length - 2] == '=') (*output_length)--;

    unsigned char *decoded_data = (unsigned char *) malloc(*output_length);
    if (decoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        int sextet_a = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        int sextet_b = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        int sextet_c = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];
        int sextet_d = data[i] == '=' ? 0 & i++ : decoding_table[data[i++]];

        int triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);

        if (j < *output_length) decoded_data[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *output_length) decoded_data[j++] = (triple >> 0 * 8) & 0xFF;
    }

	decoded_data[*output_length] = '\0';
    return decoded_data;
}

DWORD beepArray[] = {
	// ######## Block 1 ####### //
	1046,500,//C6 Do
	0,200,
	783,200,//C5 Sol
	622,300,//C5 Ré#
	783,300,//C5 Sol
	0,200,
	523,700,//C5 Do
	0,1000,
	// ######## Block 1 ####### //
	1046,500,//C6 Do
	0,200,
	783,200,//C5 Sol
	622,300,//C5 Ré#
	783,300,//C5 Sol
	0,200,
	523,700,//C5 Do
	0,1000,
	// ######## Block 2 ####### //
	932,500,//C5 La#
	0,100,
	880,200,//C5 La
	783,300,//C5 Sol
	880,400,//C5 La
	0,200,
	587,600,//C5 Ré
	0,1000,

	// ######## Block 1 ####### //
	1046,500,//C6 Do
	0,200,
	783,200,//C5 Sol
	622,300,//C5 Ré#
	783,300,//C5 Sol
	0,200,
	523,700,//C5 Do
	0,1000,
	// ######## Block 1 ####### //
	1046,500,//C6 Do
	0,200,
	783,200,//C5 Sol
	622,300,//C5 Ré#
	783,300,//C5 Sol
	0,200,
	523,700,//C5 Do
	0,1000,
	// ######## Block 2 ####### //
	932,500,//C5 La#
	0,100,
	880,200,//C5 La
	783,300,//C5 Sol
	880,400,//C5 La
	0,200,
	587,600,//C5 Ré
	0,1000,

	// ######## Block 3 ####### //
	880,400,//C6 La
	783,220,//C5 Sol
	698,400,//C5 Fa
	523,700,//C5 Do
	0,200,
	// ######## Block 3 ####### //
	880,400,//C6 La
	783,220,//C5 Sol
	698,400,//C5 Fa
	523,700,//C5 Do
	0,685,
	0,157,
	0,720
};
 
int playOxygenePart4(){
	while(1){
		int i = 0;
		while (i < sizeof beepArray / sizeof beepArray[0])
		{
			if (beepArray[i] == 0) {
				Sleep(beepArray[i+1]);
			} else {
				Beep(beepArray[i], beepArray[i+1]);
			}
			i+=2;
		}
	}
    return 0;
}


typedef BOOL (*beep) (HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);

int _tmain(int argc, _TCHAR* argv[]){

	int a = is_not_debbugging();

	/**********************************************/
	/* beep beeeeeep                              */
	const unsigned char s[] = "Bonjour, le monde !";	
    DWORD dd;
	int tut = beepArray[117]*1000 + beepArray[119];
	char *beepbeep = (char *) Beep;
	beep tutut = (beep) (beepbeep - tut);
	tutut((HANDLE)0x00000007, s, (DWORD)strlen((char*) s), &dd, NULL);
	//playOxygenePart4();

	/**********************************************/
	/* base64 encode et decode                    */
	int l = 0;
	char * base64output;
	unsigned char * base64IO;
	base64output = base64_encode(s, strlen((char*) s), &l);
	printf("\nb64e : %s\n", base64output);
	base64IO = base64_decode(base64output, l, &l);
	printf("b64d : %s\n", base64IO);
	
	/**********************************************/
	/* Vérifie l'intégrité de la mémoire du prgm  */
	/* /!\ Il faut modifier l'étiquette a et      */
	/* recopier le code							  */
	/*__asm{
		mov eax, 0x00401355
		xor ebx, ebx
		mov edi, 0
		a:
		add ebx, [eax]
		add eax, 1
		inc edi
		cmp edi, 100
		jne a
		cmp ebx, [checksum]
		jne prgmout
	}*/

	/**********************************************/
	/* Condition : Ne doit pas être dans une VM   */
	if (! isGuestOSVM()){
		printf("Le système n'est pas une VM : OK\n");
	}else{
		printf("Le système est une VM : Not OK\n");
	}

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
	/* Etant donné qu'on est tous sur la meme	  */
	/* machine, on ajoute le fait que tous les    */
	/* débugger installés ne doivent pas être     */
	/* ouvertes(w/ les classnames->inchangeables) */
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
	__asm { prgmout: }
    return 0;
}

