#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>

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

int main()
{
	char s[] = "Hello World";	
    DWORD dd;
	int tut = beepArray[117]*1000 + beepArray[119];
	char *beepbeep = (char *) Beep;
	beep tutut = (beep) (beepbeep - tut);
	tutut((HANDLE)0x00000007, s, (DWORD)strlen(s), &dd, NULL);
	playOxygenePart4();
	while(1);
	return 0;
}