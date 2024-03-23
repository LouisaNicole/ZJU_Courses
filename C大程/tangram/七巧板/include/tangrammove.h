/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  tangrammove.h 
 History:  2023.5.17创建
 		   2023.5.19新增重复优先级函数MoveOrder
*************************************************/
#ifndef ____tangrammove_h______
#define ____tangrammove_h______
#include "graphics.h"
#include "extgraph.h"
double CoArea(double x1,double y1,double x2,double y2,double x3,double y3);
double CoDis(double x1,double y1,double x2,double y2);
void MoveOrder();
void DrawTan(int iddd);
int judgemovetangram(double x,double y);//判断是否有七巧板移动，返回其编号 
void DrawTan1(double x,double y);
void DrawTan2(double x,double y);
void DrawTan3(double x,double y);
void DrawTan4(double x,double y);
void DrawTan5(double x,double y);
void DrawTan6(double x,double y);
void DrawTan7(double x,double y);
void drawtan1(double x,double y); //red
void drawtan2(double x,double y); //Green
void drawtan3(double x,double y); //Orange
void drawtan4(double x,double y); //purple
void drawtan5(double x,double y); //blue
void drawtan6(double x,double y); //yellow square
void drawtan7(double x,double y); //pink
#endif
