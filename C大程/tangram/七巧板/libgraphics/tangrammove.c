/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  tangrammove.c 
 History:  2023.5.17创建
 		   2023.5.19新增重复优先级函数MoveOrder
*************************************************/
#include "tangrammove.h"
#include "graphics.h"
#include "extgraph.h"
#include <math.h>
#include "variable.h"

#define edge 1/sqrt(2)
#define pi 3.1415926
#define cita 0.463647609

extern int id,rolid,picture; 
extern int angle[9];
extern double TanPos[8][2];
extern int ordertan[10];
extern double TanCurrentPos[8][6][2];

double ang;
double DisPos[8];
double TanDisMin[8]={0,1.0,1.0,0.7,0.5,0.5,0.5,0.6};

double CoArea(double x1,double y1,double x2,double y2,double x3,double y3){
	return abs(x1*y2-x1*y3+x2*y3-x2*y1+x3*y1-x2*y2);
}
double CoDis(double x1,double y1,double x2,double y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
//板子的移动顺序，重叠优先级判断 
void MoveOrder(){
	int i,flag=0;
	for(i=1;i<=7;i++){
		if(ordertan[i]==rolid) flag=1;
		if(flag) ordertan[i]=ordertan[i+1];
	}
	ordertan[7]=rolid;
}
//绘制七个板子 
void DrawTan(int iddd){
	switch(iddd){
		case 1: DrawTan1(TanPos[1][0],TanPos[1][1]);break;
		case 2: DrawTan2(TanPos[2][0],TanPos[2][1]);break;
		case 3: DrawTan3(TanPos[3][0],TanPos[3][1]);break;
		case 4: DrawTan4(TanPos[4][0],TanPos[4][1]);break;
		case 5: DrawTan5(TanPos[5][0],TanPos[5][1]);break;
		case 6: DrawTan6(TanPos[6][0],TanPos[6][1]);break;
		case 7: DrawTan7(TanPos[7][0],TanPos[7][1]);break;
	}
}
//七巧板的移动 
int judgemovetangram(double x,double y){
    int i;
    for(i=7;i>=1;i--){
     	int iddd = ordertan[i];
    	int j=3; if(iddd==6||iddd==7) j=4; int num=j;
        int last=0,now=0;
        for(j=1;j<=num;j++){
            double re = (TanCurrentPos[iddd][j%num+1][0]-TanCurrentPos[iddd][j][0])*(y-TanCurrentPos[iddd][j][1])\
            -(x-TanCurrentPos[iddd][j][0])*(TanCurrentPos[iddd][j%num+1][1]-TanCurrentPos[iddd][j][1]);
            if(re>0) now=1;
            else if(re<0) now=2;
            else re=0;
            last|=now;
            if(last==3) break;
        }
        if(last!=3) return iddd;
    } 
    return 0;
} 
//判断是否有七巧板移动，返回其编号 

void DrawTan1(double x,double y){
	StartFilledRegion(1);
	SetPenColor("Red");
	drawtan1(x,y);
	EndFilledRegion();
	if(rolid==1){
		SetPenColor("Black");
		drawtan1(x,y);
	}
}
void DrawTan2(double x,double y){
	StartFilledRegion(1);
	SetPenColor("Gre");
	drawtan2(x,y);
	EndFilledRegion();
	if(rolid==2){
		SetPenColor("Black");
		drawtan2(x,y);
	}
}
void DrawTan3(double x,double y){
	StartFilledRegion(1);
	SetPenColor("Ora");
	drawtan3(x,y);
	EndFilledRegion();
	if(rolid==3){
		SetPenColor("Black");
		drawtan3(x,y);
	}
}
void DrawTan4(double x,double y){
	StartFilledRegion(1);
	SetPenColor("Pur");
	drawtan4(x,y);
	EndFilledRegion();
	if(rolid==4){
		SetPenColor("Black");
		drawtan4(x,y);
	}
}
void DrawTan5(double x,double y){
	StartFilledRegion(1);
	SetPenColor("Blu");
	drawtan5(x,y);
	EndFilledRegion();
	if(rolid==5){
		SetPenColor("Black");
		drawtan5(x,y);
	}
}
void DrawTan6(double x,double y){
	StartFilledRegion(1);
	SetPenColor("Yel");
	drawtan6(x,y);
	EndFilledRegion();
	if(rolid==6){
		SetPenColor("Black");
		drawtan6(x,y);
	}
}
void DrawTan7(double x,double y){
	StartFilledRegion(1);
	SetPenColor("Pin");
	drawtan7(x,y);
	EndFilledRegion();
	if(rolid==7){
		SetPenColor("Black");
		drawtan7(x,y);
	}
}

void drawtan1(double x,double y){
	MovePen(x,y);
	ang=45.0/180*pi*angle[1];
	DrawLine(4*edge*cos(ang),4*edge*sin(ang));
	TanCurrentPos[1][1][0]=GetCurrentX();TanCurrentPos[1][1][1]=GetCurrentY();
	ang+=135.0/180*pi;
	DrawLine(2*cos(ang),2*sin(ang));
	TanCurrentPos[1][2][0]=GetCurrentX();TanCurrentPos[1][2][1]=GetCurrentY();
	ang+=90.0/180*pi;
	DrawLine(2*cos(ang),2*sin(ang));
	TanCurrentPos[1][3][0]=GetCurrentX();TanCurrentPos[1][3][1]=GetCurrentY();
}
void drawtan2(double x,double y){
	MovePen(x,y);
	ang=45.0/180*pi*angle[2];
	DrawLine(4*edge*cos(ang),4*edge*sin(ang));
	TanCurrentPos[2][1][0]=GetCurrentX();TanCurrentPos[2][1][1]=GetCurrentY();
	ang+=135.0/180*pi;
	DrawLine(2*cos(ang),2*sin(ang));
	TanCurrentPos[2][2][0]=GetCurrentX();TanCurrentPos[2][2][1]=GetCurrentY();
	ang+=90.0/180*pi;
	DrawLine(2*cos(ang),2*sin(ang));
	TanCurrentPos[2][3][0]=GetCurrentX();TanCurrentPos[2][3][1]=GetCurrentY();
}
void drawtan3(double x,double y){
	MovePen(x,y);
	ang=45.0/180*pi*angle[3];
	DrawLine(2*cos(ang),2*sin(ang));
	TanCurrentPos[3][1][0]=GetCurrentX();TanCurrentPos[3][1][1]=GetCurrentY();
	ang+=135.0/180*pi;
	DrawLine(2*edge*cos(ang),2*edge*sin(ang));
	TanCurrentPos[3][2][0]=GetCurrentX();TanCurrentPos[3][2][1]=GetCurrentY();
	ang+=90.0/180*pi;
	DrawLine(2*edge*cos(ang),2*edge*sin(ang));
	TanCurrentPos[3][3][0]=GetCurrentX();TanCurrentPos[3][3][1]=GetCurrentY();
} 
void drawtan4(double x,double y){
	MovePen(x,y);
	ang=45.0/180*pi*angle[4];
	DrawLine(2*edge*cos(ang),2*edge*sin(ang));
	TanCurrentPos[4][1][0]=GetCurrentX();TanCurrentPos[4][1][1]=GetCurrentY();
	ang+=135.0/180*pi;
	DrawLine(cos(ang),sin(ang));
	TanCurrentPos[4][2][0]=GetCurrentX();TanCurrentPos[4][2][1]=GetCurrentY();
	ang+=90.0/180*pi;
	DrawLine(cos(ang),sin(ang));
	TanCurrentPos[4][3][0]=GetCurrentX();TanCurrentPos[4][3][1]=GetCurrentY();
} 
void drawtan5(double x,double y){
	MovePen(x,y);
	ang=45.0/180*pi*angle[5];
	DrawLine(2*edge*cos(ang),2*edge*sin(ang));
	TanCurrentPos[5][1][0]=GetCurrentX();TanCurrentPos[5][1][1]=GetCurrentY();
	ang+=135.0/180*pi;
	DrawLine(cos(ang),sin(ang));
	TanCurrentPos[5][2][0]=GetCurrentX();TanCurrentPos[5][2][1]=GetCurrentY();
	ang+=90.0/180*pi;
	DrawLine(cos(ang),sin(ang));
	TanCurrentPos[5][3][0]=GetCurrentX();TanCurrentPos[5][3][1]=GetCurrentY();
} 
void drawtan6(double x,double y){
	MovePen(x,y);
	ang=45.0/180*pi*angle[6];
	DrawLine(cos(ang),sin(ang));
	TanCurrentPos[6][1][0]=GetCurrentX();TanCurrentPos[6][1][1]=GetCurrentY();
	ang+=90.0/180*pi;
	DrawLine(cos(ang),sin(ang));
	TanCurrentPos[6][2][0]=GetCurrentX();TanCurrentPos[6][2][1]=GetCurrentY();
	ang+=90.0/180*pi;
	DrawLine(cos(ang),sin(ang));
	TanCurrentPos[6][3][0]=GetCurrentX();TanCurrentPos[6][3][1]=GetCurrentY();
	ang+=90.0/180*pi;
	DrawLine(cos(ang),sin(ang));
	TanCurrentPos[6][4][0]=GetCurrentX();TanCurrentPos[6][4][1]=GetCurrentY();
}//正方形 
void drawtan7(double x,double y){
	MovePen(x,y);
	ang=45.0/180*pi*angle[7];
	DrawLine(2*edge*cos(ang),2*edge*sin(ang));
	TanCurrentPos[7][1][0]=GetCurrentX();TanCurrentPos[7][1][1]=GetCurrentY();
	ang+=45.0/180*pi;
	DrawLine(cos(ang),sin(ang));
	TanCurrentPos[7][2][0]=GetCurrentX();TanCurrentPos[7][2][1]=GetCurrentY();
	ang+=135.0/180*pi;
	DrawLine(2*edge*cos(ang),2*edge*sin(ang));
	TanCurrentPos[7][3][0]=GetCurrentX();TanCurrentPos[7][3][1]=GetCurrentY();
	ang+=45.0/180*pi;
	DrawLine(cos(ang),sin(ang));
	TanCurrentPos[7][4][0]=GetCurrentX();TanCurrentPos[7][4][1]=GetCurrentY();
}


