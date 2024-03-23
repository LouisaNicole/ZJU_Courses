/*************************************************
 Copyright Ǽ��ࡢ½���������. 2023. All rights reserved.
 File name:  variable.h 
 History:  2023.5.15����
 		   2023.5.28����ö��help���桢lastpage���� 
*************************************************/
#ifndef _variable_h
#define _variable_h
#include "strlib.h"

typedef enum{
    InitialPage, 
    SelectPage,
    SquarePage,
    SwanPage,
    HousePage,
    SwordPage,
    TreePage,
    CamelPage,
    FishPage,
    PrayPage,
    CreatPage,
	HelpPage 
    //Exit,
}Page;

typedef struct
{
    double x;
    double y;
}Point;  //����

typedef struct{
	Page currentPage;
	Page lastPage;
	double winwidth;
	double winheight;
	Point g_mousepoint;
}WINDOW; 

#endif
