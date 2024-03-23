/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  Judge.h 
 History:  2023.5.23创建
 		   2023.5.25新增点在线段函数 IsOnLine
*************************************************/
#ifndef ____Judge_h______
#define ____Judge_h______
bool IsIntersect(double x1, double y1, double x2, double y2,\
    double x3, double y3, double x4, double y4);
int IsOnLine(double x1,double y1,double x2,double y2,double x3,double y3);
int PicJudge();
int Judge(double a[][2]);
#endif
