/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  absorb.c 
 History:  2023.5.22创建
 		   2023.5.24新增点吸附函数 PointAbsorb
*************************************************/
#include "absorb.h"
#include "genlib.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Judge.h"

#define DIS 0.1

extern int time;
extern double TanCurrentPos[8][6][2];
extern int picture;
extern int rolid;
extern double TanPos[8][2];
extern double a1[6][2],a2[15][2],a3[13][2],a4[16][2],a5[13][2],a6[15][2],a7[11][2],a8[20][2];

int numm[8]={0,3,3,3,3,3,4,4};
//点吸附 
int PointAbsorb(double x1,double y1,double x2,double y2,double *dx,double *dy){
	if(PointDistance(x1,y1,x2,y2)<DIS){
		*dx = x1-x2;
		*dy = y1-y2;
		return 1;
	}
	return 0;
}
//点的距离计算函数 
double PointDistance(double x1, double y1,double x2,double y2){
	double result;
	result = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	return result;
}
//交换 
void swap(double *x,double *y){
	double temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
//判断是否吸附函数 
int IsAbsorb(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4,double *dx,double *dy)//前两个点为目标位置，后面两个点在移动 
{
	if(fabs(x1-x2) <= 0.001) {
		if(fabs(x3-x4) <= 0.001){
			if(fabs(x1-x3) > DIS) return 0;
			if(y1 > y2) swap(&y1,&y2);
			if(y3 > y4) swap(&y3,&y4);
			if(y3 >= y2 || y4 <= y1) return 0;
			*dx = x1-x3;
			*dy = 0;
			return 1;
		}
		return 0;
	}
	if(fabs(y1-y2) <= 0.001) {
		if(fabs(y3-y4) <= 0.001){
			if(fabs(y1-y3) > DIS) return 0;
			if(x1 > x2) swap(&x1,&x2);
			if(x3 > x4) swap(&x3,&x4);
			if(x3 >= x2 || x4 <= x1) return 0;
			*dx = 0;
			*dy = y1-y3;
			return 1; 
		}
		return 0;
	}
	if((x1 < x2 && y1 < y2) || (x1 > x2 && y1 > y2)){
		if((x3 < x4 && y3 < y4) || (x3 > x4 && y3 > y4)){
			double dis = (y1-x1)-(y3-x3);
			if(fabs(dis)/sqrt(2) > DIS) return 0;
			if(x1 > x2) swap(&x1,&x2),swap(&y1,&y2);
			if(x3 > x4) swap(&x3,&x4),swap(&y3,&y4);
			if((y3/2-x3/2+x3/sqrt(2) >= y2/2-x2/2+x2/sqrt(2)) || (y4/2-x4/2+x4/sqrt(2)<=y1/2-x1/2+x1/sqrt(2))) return 0;
			*dx = -dis/2;
			*dy = dis/2;
			return 1;
		}
		return 0;
	}
	if((x1 < x2 && y1 > y2) || (x1 > x2 && y1 < y2)){
		if((x3 < x4 && y3 > y4) || (x3 > x4 && y3 < y4)){
			double dis = (y1+x1)-(y3+x3);
			if(fabs(dis)/sqrt(2) > DIS) return 0;
			if(x1 > x2) swap(&x1,&x2),swap(&y1,&y2);
			if(x3 > x4) swap(&x3,&x4),swap(&y3,&y4);
			if((x3+dis/2 >= x2) || (x4+dis/2 <= x1)) return 0;
			*dx = dis/2;
			*dy = dis/2;
			return 1;
		}
		return 0;
	}
	return 0;
}
//执行吸附功能函数 
void Absorb(){
	switch(picture){
		case 1: AbsorbOutline(a1); break; 
		case 2: AbsorbOutline(a2); break;
		case 3: AbsorbOutline(a3); break;
		case 4: AbsorbOutline(a4); break;
		case 5: AbsorbOutline(a5); break;
		case 6: AbsorbOutline(a6); break;
		case 7: AbsorbOutline(a7); break;
		case 8: AbsorbOutline(a8); break;
	}
}
//板子与边吸附 
void AbsorbOutline(double a[][2]){
	int i,j;
	double dx,dy;
	for(i=0;a[i+1][0]!=0;i++){
		j=1;
		int num=numm[rolid];
		while(j<=num){
			if(PointAbsorb(a[i][0],a[i][1],TanCurrentPos[rolid][j][0],TanCurrentPos[rolid][j][1],&dx,&dy)){
				TanPos[rolid][0] += dx;
				TanPos[rolid][1] += dy;
				return;
			}
			j++;
		}
	}
	for(i=0;a[i+1][0]!=0;i++){
		j=1;
		int num=numm[rolid];
		while(j<=num){
			if(IsAbsorb(a[i][0],a[i][1],a[i+1][0],a[i+1][1],TanCurrentPos[rolid][j][0],\
			TanCurrentPos[rolid][j][1],TanCurrentPos[rolid][j%num+1][0],TanCurrentPos[rolid][j%num+1][1],&dx,&dy)){
				TanPos[rolid][0] += dx;
				TanPos[rolid][1] += dy;
				return ;
			}
			j++;
		}
	}
	TanAbsorb();
}
//板子之间的吸附 
void TanAbsorb(){
	int i,j,m;
	double dx,dy;
	for(i=1;i<=7;i++){
		if(i==rolid) continue;
		int num1=numm[i],num2=numm[rolid];
		for(j=1;j<=num1;j++){
			for(m=1;m<=num2;m++){
				if(PointAbsorb(TanCurrentPos[i][j][0],TanCurrentPos[i][j][1],TanCurrentPos[rolid][m][0],TanCurrentPos[rolid][m][1],&dx,&dy)){
					TanPos[rolid][0] += dx;
					TanPos[rolid][1] += dy;
					return ;
				}
			}
		}
	}
	for(i=1;i<=7;i++){
		if(i==rolid) continue;
		int num1=numm[i],num2=numm[rolid];
		for(j=1;j<=num1;j++){
			for(m=1;m<=num2;m++){
				if(IsAbsorb(TanCurrentPos[i][j][0],TanCurrentPos[i][j][1],TanCurrentPos[i][j%num1+1][0],TanCurrentPos[i][j%num1+1][1],\
				TanCurrentPos[rolid][m][0],TanCurrentPos[rolid][m][1],TanCurrentPos[rolid][m%num2+1][0],TanCurrentPos[rolid][m%num2+1][1],&dx,&dy)){
					TanPos[rolid][0] += dx;
					TanPos[rolid][1] += dy;
					return ;
				}
			}
		}
	}
}

