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

int _tmain(int argc, _TCHAR* argv[])
{
	/**********************************************/
	//obtenir l'heure et la date
	char tmpbuf[128], timebuf[26], ampm[] = "AM";
    time_t ltime;
    struct _timeb tstruct;
    struct tm today, gmt, xmas = { 0, 0, 12, 25, 11, 93 };
    errno_t err;

    // Set time zone from TZ environment variable. If TZ is not set,
    // the operating system is queried to obtain the default value
    // for the variable.
    //
    _tzset();

    // Display operating system-style date and time.
    _strtime_s( tmpbuf, 128 );
    printf( "OS time:\t\t\t\t%s\n", tmpbuf );
    _strdate_s( tmpbuf, 128 );
    printf( "OS date:\t\t\t\t%s\n", tmpbuf );
	/**********************************************/

	//attention la condition ne doit pas être codée en dur
	//elle doit être dans le if direct car sinon on
	//peut simplement changer la valeur en mémoire
	int condition = 0; 

	if(condition){
		printf("Bonjour, le monde !\n");
	}else{
		printf("Hello, world !\n");
	}

	while(1);
    return 0;
}

