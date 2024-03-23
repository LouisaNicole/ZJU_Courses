/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  variable.h 
 History:  2023.5.15创建
 		   2023.5.28新增枚举help界面、lastpage界面 
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
}Point;  //坐标

typedef struct{
	Page currentPage;
	Page lastPage;
	double winwidth;
	double winheight;
	Point g_mousepoint;
}WINDOW; 

#endif
