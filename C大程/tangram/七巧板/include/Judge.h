/*************************************************
 Copyright Ǽ��ࡢ½���������. 2023. All rights reserved.
 File name:  Judge.h 
 History:  2023.5.23����
 		   2023.5.25���������߶κ��� IsOnLine
*************************************************/
#ifndef ____Judge_h______
#define ____Judge_h______
bool IsIntersect(double x1, double y1, double x2, double y2,\
    double x3, double y3, double x4, double y4);
int IsOnLine(double x1,double y1,double x2,double y2,double x3,double y3);
int PicJudge();
int Judge(double a[][2]);
#endif
