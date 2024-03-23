/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  Hint.c 
 History:  2023.5.28创建完成 
*************************************************/
#include <math.h>
#include "Hint.h"
#include "tangrammove.h"
#include "graphics.h"
#include "extgraph.h"
#define cita 0.463647609
#define pi 3.1415926
extern double TanCurrentPos[8][6][2];
extern double TanPos[8][2];
extern int angle[8];
//正方形图形提示 
void Hint1(){
	if(fabs(TanCurrentPos[1][3][0]-6)>0.1||fabs(TanCurrentPos[1][3][1]-2.6)>0.1||\
	fabs(TanCurrentPos[1][1][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[1][1][1]-2.6)>0.1){
		angle[1]=0;
		TanPos[1][0]=6;
		TanPos[1][1]=2.6;
	}
	else if(fabs(TanCurrentPos[2][3][0]-6)>0.1||fabs(TanCurrentPos[2][3][1]-2.6-2*sqrt(2))>0.1||\
	fabs(TanCurrentPos[2][1][0]-6)>0.1||fabs(TanCurrentPos[2][1][1]-2.6)>0.1){
		angle[2]=6;
		TanPos[2][0]=6;
		TanPos[2][1]=2.6+2*sqrt(2);
	}
	else if(fabs(TanCurrentPos[3][3][0]-6-sqrt(2))>0.1||fabs(TanCurrentPos[3][3][1]-2.6-2*sqrt(2))>0.1||\
	fabs(TanCurrentPos[3][1][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[3][1][1]-2.6-sqrt(2))>0.1){
		angle[3]=7;
		TanPos[3][0]=6+sqrt(2);
		TanPos[3][1]=2.6+2*sqrt(2);
	}
	else if(fabs(TanCurrentPos[4][3][0]-6-sqrt(2))>0.1||fabs(TanCurrentPos[4][3][1]-2.6-2*sqrt(2))>0.1||\
	fabs(TanCurrentPos[4][1][0]-6)>0.1||fabs(TanCurrentPos[4][1][1]-2.6-2*sqrt(2))>0.1){
		angle[4]=4;
		TanPos[4][0]=6+sqrt(2);
		TanPos[4][1]=2.6+2*sqrt(2);
	}
	else if(fabs(TanCurrentPos[6][4][0]-6-sqrt(2))>0.1||fabs(TanCurrentPos[6][4][1]-2.6-sqrt(2))>0.1||\
	fabs(TanCurrentPos[6][1][0]-6-1.5*sqrt(2))>0.1||fabs(TanCurrentPos[6][1][1]-2.6-1.5*sqrt(2))>0.1){
		angle[6]=1;
		TanPos[6][0]=6+sqrt(2);
		TanPos[6][1]=2.6+sqrt(2);
	}
	else if(fabs(TanCurrentPos[5][3][0]-6-1.5*sqrt(2))>0.1||fabs(TanCurrentPos[5][3][1]-2.6-0.5*sqrt(2))>0.1||\
	fabs(TanCurrentPos[5][1][0]-6-1.5*sqrt(2))>0.1||fabs(TanCurrentPos[5][1][1]-2.6-1.5*sqrt(2))>0.1){
		angle[5]=2;
		TanPos[5][0]=6+1.5*sqrt(2);
		TanPos[5][1]=2.6+0.5*sqrt(2);
	}
	else if(fabs(TanCurrentPos[7][4][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[7][4][1]-2.6)>0.1||\
	fabs(TanCurrentPos[7][1][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[7][1][1]-2.6-sqrt(2))>0.1){
		angle[7]=2;
		TanPos[7][0]=6+2*sqrt(2);
		TanPos[7][1]=2.6;
	}
}
//天鹅图形 
void Hint2(){
	if(fabs(TanCurrentPos[1][3][0]-5-2*sqrt(2))>0.1||fabs(TanCurrentPos[1][3][1]-4)>0.1||\
	fabs(TanCurrentPos[1][1][0]-5>0.1)||fabs(TanCurrentPos[1][1][1]-4)>0.1){
		angle[1]=4;
		TanPos[1][0]=5+2*sqrt(2);
		TanPos[1][1]=4;
	}
	else if(fabs(TanCurrentPos[2][3][0]-5-2*sqrt(2))>0.1||fabs(TanCurrentPos[2][3][1]-4>0.1||\
	fabs(TanCurrentPos[2][1][0]-3-2*sqrt(2))>0.1||fabs(TanCurrentPos[2][1][1]-2)>0.1)){
		angle[2]=5;
		TanPos[2][0]=5+2*sqrt(2);
		TanPos[2][1]=4;
	}
	else if(fabs(TanCurrentPos[3][3][0]-5-2*sqrt(2))>0.1||fabs(TanCurrentPos[3][3][1]-4)>0.1||\
	fabs(TanCurrentPos[3][1][0]-5-2*sqrt(2))>0.1||fabs(TanCurrentPos[3][1][1]-2)>0.1){
		angle[3]=6;
		TanPos[3][0]=5+2*sqrt(2);
		TanPos[3][1]=4;
	}
	else if(fabs(TanCurrentPos[4][3][0]-8-sqrt(2))>0.1||fabs(TanCurrentPos[4][3][1]-4-sqrt(2))>0.1||\
	fabs(TanCurrentPos[4][1][0]-7-sqrt(2))>0.1||fabs(TanCurrentPos[4][1][1]-5-sqrt(2))>0.1){
		angle[4]=3;
		TanPos[4][0]=8+sqrt(2);
		TanPos[4][1]=4+sqrt(2);
	}
	else if(fabs(TanCurrentPos[6][4][0]-6-sqrt(2)>0.1||fabs(TanCurrentPos[6][4][1]-3-sqrt(2))>0.1||\
	fabs(TanCurrentPos[6][1][0]-6-1.5*sqrt(2))>0.1||fabs(TanCurrentPos[6][1][1]-3-0.5*sqrt(2))>0.1)){
		angle[6]=7;
		TanPos[6][0]=6+sqrt(2);
		TanPos[6][1]=3+sqrt(2);
	}
	else if(fabs(TanCurrentPos[5][3][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[5][3][1]-3)>0.1||\
	fabs(TanCurrentPos[5][1][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[5][1][1]-3-sqrt(2))>0.1){
		angle[5]=2;
		TanPos[5][0]=6+2*sqrt(2);
		TanPos[5][1]=3;
	}
	else if(fabs(TanCurrentPos[7][4][0]-6-sqrt(2))>0.1||fabs(TanCurrentPos[7][4][1]-3-sqrt(2))>0.1||\
	fabs(TanCurrentPos[7][1][0]-7-sqrt(2))>0.1||fabs(TanCurrentPos[7][1][1]-4-sqrt(2)>0.1)){
		angle[7]=1;
		TanPos[7][0]=6+sqrt(2);
		TanPos[7][1]=3+sqrt(2);
	}
}
//房子 
void Hint3(){
	if(fabs(TanCurrentPos[1][3][0]-5.5)>0.1||fabs(TanCurrentPos[1][3][1]-2.5-sqrt(2))>0.1||\
	fabs(TanCurrentPos[1][1][0]-5.5-2*sqrt(2))>0.1||fabs(TanCurrentPos[1][1][1]-2.5-sqrt(2))>0.1){
		angle[1]=0;
		TanPos[1][0]=5.5;
		TanPos[1][1]=2.5+sqrt(2);
	}
	else if(fabs(TanCurrentPos[2][3][0]-6)>0.1||fabs(TanCurrentPos[2][3][1]-2.5)>0.1||\
	fabs(TanCurrentPos[2][1][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[2][1][1]-2.5)>0.1){
		angle[2]=0;
		TanPos[2][0]=6;
		TanPos[2][1]=2.5;
	}
	else if(fabs(TanCurrentPos[3][3][0]-6)>0.1||fabs(TanCurrentPos[3][3][1]-2.5)>0.1||\
	fabs(TanCurrentPos[3][1][0]-6-sqrt(2))>0.1||fabs(TanCurrentPos[3][1][1]-2.5-sqrt(2))>0.1){
		angle[3]=1;
		TanPos[3][0]=6;
		TanPos[3][1]=2.5;
	}
	else if(fabs(TanCurrentPos[4][3][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[4][3][1]-2.5-sqrt(2))>0.1||\
	fabs(TanCurrentPos[4][1][0]-6-sqrt(2))>0.1||fabs(TanCurrentPos[4][1][1]-2.5-sqrt(2))>0.1){
		angle[4]=4;
		TanPos[4][0]=6+2*sqrt(2);
		TanPos[4][1]=2.5+sqrt(2);
	}
	else if(fabs(TanCurrentPos[6][4][0]-4.5-2*sqrt(2))>0.1||fabs(TanCurrentPos[6][4][1]-3.5-sqrt(2))>0.1||\
	fabs(TanCurrentPos[6][1][0]-5.5-2*sqrt(2))>0.1||fabs(TanCurrentPos[6][1][1]-3.5-sqrt(2))>0.1){
		angle[6]=0;
		TanPos[6][0]=4.5+2*sqrt(2);
		TanPos[6][1]=3.5+sqrt(2);
	}
	else if(fabs(TanCurrentPos[5][3][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[5][3][1]-2.5)>0.1||\
	fabs(TanCurrentPos[5][1][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[5][1][1]-2.5-sqrt(2))>0.1){
		angle[5]=2;
		TanPos[5][0]=6+2*sqrt(2);
		TanPos[5][1]=2.5;
	}
	else if(fabs(TanCurrentPos[7][4][0]-4.5-2*sqrt(2))>0.1||fabs(TanCurrentPos[7][4][1]-3.5-sqrt(2))>0.1||\
	fabs(TanCurrentPos[7][1][0]-5.5-2*sqrt(2))>0.1||fabs(TanCurrentPos[7][1][1]-3.5-sqrt(2))>0.1){
		angle[7]=7;
		TanPos[7][0]=4.5+2*sqrt(2);
		TanPos[7][1]=3.5+sqrt(2);
	}
}
//宝剑 
void Hint4(){
	if(fabs(TanCurrentPos[1][3][0]-6)>0.1||fabs(TanCurrentPos[1][3][1]-2.5)>0.1||\
	fabs(TanCurrentPos[1][1][0]-6-2*sqrt(2))>0.1||fabs(TanCurrentPos[1][1][1]-2.5)>0.1){
		angle[1]=0;
		TanPos[1][0]=6;
		TanPos[1][1]=2.5;
	}
	else if(fabs(TanCurrentPos[2][3][0]-6-0.5*sqrt(2))>0.1||fabs(TanCurrentPos[2][3][1]-2.5-2.5*sqrt(2))>0.1||\
	fabs(TanCurrentPos[2][1][0]-6-0.5*sqrt(2))>0.1||fabs(TanCurrentPos[2][1][1]-2.5-0.5*sqrt(2))>0.1){
		angle[2]=6;
		TanPos[2][0]=6+0.5*sqrt(2);
		TanPos[2][1]=2.5+2.5*sqrt(2);
	}
	else if(fabs(TanCurrentPos[3][3][0]-7-sqrt(2))>0.1||fabs(TanCurrentPos[3][3][1]-1.5)>0.1||\
	fabs(TanCurrentPos[3][1][0]-5-sqrt(2))>0.1||fabs(TanCurrentPos[3][1][1]-1.5)>0.1){
		angle[3]=4;
		TanPos[3][0]=7+sqrt(2);
		TanPos[3][1]=1.5;
	}
	else if(fabs(TanCurrentPos[4][3][0]-6-1.5*sqrt(2))>0.1||fabs(TanCurrentPos[4][3][1]-2.5-0.5*sqrt(2))>0.1||\
	fabs(TanCurrentPos[4][1][0]-6-1.5*sqrt(2))>0.1||fabs(TanCurrentPos[4][1][1]-2.5-1.5*sqrt(2))>0.1){
		angle[4]=2;
		TanPos[4][0]=6+1.5*sqrt(2);
		TanPos[4][1]=2.5+0.5*sqrt(2);
	}
	else if(fabs(TanCurrentPos[6][4][0]-5.5-sqrt(2))>0.1||fabs(TanCurrentPos[6][4][1]-1.5)>0.1||\
	fabs(TanCurrentPos[6][1][0]-6.5-sqrt(2))>0.1||fabs(TanCurrentPos[6][1][1]-1.5)>0.1){
		angle[6]=0;
		TanPos[6][0]=5.5+sqrt(2);
		TanPos[6][1]=1.5;
	}
	else if(fabs(TanCurrentPos[5][3][0]-6-sqrt(2))>0.1||fabs(TanCurrentPos[5][3][1]-2.5-2*sqrt(2))>0.1||\
	fabs(TanCurrentPos[5][1][0]-6-sqrt(2))>0.1||fabs(TanCurrentPos[5][1][1]-2.5-3*sqrt(2))>0.1){
		angle[5]=2;
		TanPos[5][0]=6+sqrt(2);
		TanPos[5][1]=2.5+2*sqrt(2);
	}
	else if(fabs(TanCurrentPos[7][4][0]-6-sqrt(2))>0.1||fabs(TanCurrentPos[7][4][1]-2.5-3*sqrt(2))>0.1||\
	fabs(TanCurrentPos[7][1][0]-6-sqrt(2))>0.1||fabs(TanCurrentPos[7][1][1]-2.5-2*sqrt(2))>0.1){
		angle[7]=6;
		TanPos[7][0]=6+sqrt(2);
		TanPos[7][1]=2.5+3*sqrt(2);
	}
}
//大树 
void Hint5(){
	if(fabs(TanCurrentPos[1][3][0]-7.5+sqrt(2))>0.1||fabs(TanCurrentPos[1][3][1]-4.5)>0.1||\
	fabs(TanCurrentPos[1][1][0]-7.5-sqrt(2))>0.1||fabs(TanCurrentPos[1][1][1]-4.5)>0.1){
		angle[1]=0;
		TanPos[1][0]=7.5-sqrt(2);
		TanPos[1][1]=4.5;
	}
	else if(fabs(TanCurrentPos[2][3][0]-9.5)>0.1||fabs(TanCurrentPos[2][3][1]-2.5)>0.1||\
	fabs(TanCurrentPos[2][1][0]-7.5)>0.1||fabs(TanCurrentPos[2][1][1]-4.5)>0.1){
		angle[2]=3;
		TanPos[2][0]=9.5;
		TanPos[2][1]=2.5;
	}
	else if(fabs(TanCurrentPos[3][3][0]-5.5)>0.1||fabs(TanCurrentPos[3][3][1]-2.5)>0.1||\
	fabs(TanCurrentPos[3][1][0]-7.5)>0.1||fabs(TanCurrentPos[3][1][1]-2.5)>0.1){
		angle[3]=0;
		TanPos[3][0]=5.5;
		TanPos[3][1]=2.5;
	}
	else if(fabs(TanCurrentPos[4][3][0]-6.5)>0.1||fabs(TanCurrentPos[4][3][1]-4.5)>0.1||\
	fabs(TanCurrentPos[4][1][0]-5.5)>0.1||fabs(TanCurrentPos[4][1][1]-3.5)>0.1){
		angle[4]=5;
		TanPos[4][0]=6.5;
		TanPos[4][1]=4.5;
	}
	else if(fabs(TanCurrentPos[6][4][0]-6.5)>0.1||fabs(TanCurrentPos[6][4][1]-3.5)>0.1||\
	fabs(TanCurrentPos[6][1][0]-7.5)>0.1||fabs(TanCurrentPos[6][1][1]-3.5)>0.1){
		angle[6]=0;
		TanPos[6][0]=6.5;
		TanPos[6][1]=3.5;
	}
	else if(fabs(TanCurrentPos[5][3][0]-6.5)>0.1||fabs(TanCurrentPos[5][3][1]-3.5)>0.1||\
	fabs(TanCurrentPos[5][1][0]-7.5)>0.1||fabs(TanCurrentPos[5][1][1]-2.5)>0.1){
		angle[5]=7;
		TanPos[5][0]=6.5;
		TanPos[5][1]=3.5;
	}
	else if(fabs(TanCurrentPos[7][4][0]-9.5)>0.1||fabs(TanCurrentPos[7][4][1]-3.5)>0.1||\
	fabs(TanCurrentPos[7][1][0]-8.5)>0.1||fabs(TanCurrentPos[7][1][1]-4.5)>0.1){
		angle[7]=3;
		TanPos[7][0]=9.5;
		TanPos[7][1]=3.5;
	}
}
//骆驼 
void Hint6(){
	if(fabs(TanCurrentPos[1][3][0]-5.5)>0.1||fabs(TanCurrentPos[1][3][1]-1.5)>0.1||\
	fabs(TanCurrentPos[1][1][0]-7.5)>0.1||fabs(TanCurrentPos[1][1][1]-3.5)>0.1){
		angle[1]=1;
		TanPos[1][0]=5.5;
		TanPos[1][1]=1.5;
	}
	else if(fabs(TanCurrentPos[2][3][0]-7.5-0.5*sqrt(2))>0.1||fabs(TanCurrentPos[2][3][1]-3.5+1.5*sqrt(2))>0.1||\
	fabs(TanCurrentPos[2][1][0]-7.5-0.5*sqrt(2))>0.1||fabs(TanCurrentPos[2][1][1]-3.5-0.5*sqrt(2))>0.1){
		angle[2]=2;
		TanPos[2][0]=7.5+0.5*sqrt(2);
		TanPos[2][1]=3.5-1.5*sqrt(2);
	}
	else if(fabs(TanCurrentPos[3][3][0]-5.5)>0.1||fabs(TanCurrentPos[3][3][1]-3.5)>0.1||\
	fabs(TanCurrentPos[3][1][0]-7.5)>0.1||fabs(TanCurrentPos[3][1][1]-3.5)>0.1){
		angle[3]=0;
		TanPos[3][0]=5.5;
		TanPos[3][1]=3.5;
	}
	else if(fabs(TanCurrentPos[4][3][0]-7.5-1.5*sqrt(2))>0.1||fabs(TanCurrentPos[4][3][1]-3.5-2*sqrt(2))>0.1||\
	fabs(TanCurrentPos[4][1][0]-7.5-0.5*sqrt(2))>0.1||fabs(TanCurrentPos[4][1][1]-3.5-2*sqrt(2))>0.1){
		angle[4]=4;
		TanPos[4][0]=7.5+1.5*sqrt(2);
		TanPos[4][1]=3.5+2*sqrt(2);
	}
	else if(fabs(TanCurrentPos[6][4][0]-7.5)>0.1||fabs(TanCurrentPos[6][4][1]-3.5)>0.1||\
	fabs(TanCurrentPos[6][1][0]-7.5-0.5*sqrt(2))>0.1||fabs(TanCurrentPos[6][1][1]-3.5-0.5*sqrt(2))>0.1){
		angle[6]=1;
		TanPos[6][0]=7.5;
		TanPos[6][1]=3.5;
	}
	else if(fabs(TanCurrentPos[5][3][0]-7.5-0.5*sqrt(2))>0.1||fabs(TanCurrentPos[5][3][1]-3.5-sqrt(2))>0.1||\
	fabs(TanCurrentPos[5][1][0]-7.5-0.5*sqrt(2))>0.1||fabs(TanCurrentPos[5][1][1]-3.5)>0.1){
		angle[5]=6;
		TanPos[5][0]=7.5+0.5*sqrt(2);
		TanPos[5][1]=3.5+sqrt(2);
	}
	else if(fabs(TanCurrentPos[7][4][0]-7.5-sqrt(2))>0.1||fabs(TanCurrentPos[7][4][1]-3.5-0.5*sqrt(2))>0.1||\
	fabs(TanCurrentPos[7][1][0]-7.5-sqrt(2))>0.1||fabs(TanCurrentPos[7][1][1]-3.5+0.5*sqrt(2))>0.1){
		angle[7]=2;
		TanPos[7][0]=7.5+sqrt(2);
		TanPos[7][1]=3.5+0.5*sqrt(2);
	}
}
//鱼 
void Hint7(){
	if(fabs(TanCurrentPos[1][3][0]-7.5)>0.1||fabs(TanCurrentPos[1][3][1]-6)>0.1||\
	fabs(TanCurrentPos[1][1][0]-5.5)>0.1||fabs(TanCurrentPos[1][1][1]-4)>0.1){
		angle[1]=5;
		TanPos[1][0]=7.5;
		TanPos[1][1]=6;
	}
	else if(fabs(TanCurrentPos[2][3][0]-5.5)>0.1||fabs(TanCurrentPos[2][3][1]-4)>0.1||\
	fabs(TanCurrentPos[2][1][0]-7.5)>0.1||fabs(TanCurrentPos[2][1][1]-2)>0.1){
		angle[2]=7;
		TanPos[2][0]=5.5;
		TanPos[2][1]=4;
	}
	else if(fabs(TanCurrentPos[3][3][0]-7.5)>0.1||fabs(TanCurrentPos[3][3][1]-5.5)>0.1||\
	fabs(TanCurrentPos[3][1][0]-7.5)>0.1||fabs(TanCurrentPos[3][1][1]-3.5)>0.1){
		angle[3]=6;
		TanPos[3][0]=7.5;
		TanPos[3][1]=5.5;
	}
	else if(fabs(TanCurrentPos[4][3][0]-9.5)>0.1||fabs(TanCurrentPos[4][3][1]-5.5)>0.1||\
	fabs(TanCurrentPos[4][1][0]-8.5)>0.1||fabs(TanCurrentPos[4][1][1]-4.5)>0.1){
		angle[4]=5;
		TanPos[4][0]=9.5;
		TanPos[4][1]=5.5;
	}
	else if(fabs(TanCurrentPos[6][4][0]-8.5)>0.1||fabs(TanCurrentPos[6][4][1]-3.5)>0.1||\
	fabs(TanCurrentPos[6][1][0]-9.5)>0.1||fabs(TanCurrentPos[6][1][1]-3.5)>0.1){
		angle[6]=0;
		TanPos[6][0]=8.5;
		TanPos[6][1]=3.5;
	}
	else if(fabs(TanCurrentPos[5][3][0]-8.5)>0.1||fabs(TanCurrentPos[5][3][1]-3.5)>0.1||\
	fabs(TanCurrentPos[5][1][0]-9.5)>0.1||fabs(TanCurrentPos[5][1][1]-2.5)>0.1){
		angle[5]=7;
		TanPos[5][0]=8.5;
		TanPos[5][1]=3.5;
	}
	else if(fabs(TanCurrentPos[7][4][0]-7.5)>0.1||fabs(TanCurrentPos[7][4][1]-2.5)>0.1||\
	fabs(TanCurrentPos[7][1][0]-8.5)>0.1||fabs(TanCurrentPos[7][1][1]-2.5)>0.1){
		angle[7]=1;
		TanPos[7][0]=7.5;
		TanPos[7][1]=2.5;
	}
}
//祈祷者 
void Hint8(){
	if(fabs(TanCurrentPos[1][3][0]-3.5-3*sqrt(2))>0.1||fabs(TanCurrentPos[1][3][1]-3.5)>0.1||\
	fabs(TanCurrentPos[1][1][0]-3.5-3*sqrt(2))>0.1||fabs(TanCurrentPos[1][1][1]-3.5-2*sqrt(2))>0.1){
		angle[1]=2;
		TanPos[1][0]=3.5+3*sqrt(2);
		TanPos[1][1]=3.5;
	}
	else if(fabs(TanCurrentPos[2][3][0]-5.5-2*sqrt(2))>0.1||fabs(TanCurrentPos[2][3][1]-1.5-sqrt(2))>0.1||\
	fabs(TanCurrentPos[2][1][0]-3.5-2*sqrt(2))>0.1||fabs(TanCurrentPos[2][1][1]-3.5-sqrt(2))>0.1){
		angle[2]=3;
		TanPos[2][0]=5.5+2*sqrt(2);
		TanPos[2][1]=1.5+sqrt(2);
	}
	else if(fabs(TanCurrentPos[3][3][0]-5.5-sqrt(2))>0.1||fabs(TanCurrentPos[3][3][1]-1.5-sqrt(2))>0.1||\
	fabs(TanCurrentPos[3][1][0]-5.5-2*sqrt(2))>0.1||fabs(TanCurrentPos[3][1][1]-1.5)>0.1){
		angle[3]=7;
		TanPos[3][0]=5.5+sqrt(2);
		TanPos[3][1]=1.5+sqrt(2);
	}
	else if(fabs(TanCurrentPos[4][3][0]-3.5-3*sqrt(2))>0.1||fabs(TanCurrentPos[4][3][1]-2.5-sqrt(2))>0.1||\
	fabs(TanCurrentPos[4][1][0]-4.5-3*sqrt(2))>0.1||fabs(TanCurrentPos[4][1][1]-3.5-sqrt(2))>0.1){
		angle[4]=1;
		TanPos[4][0]=3.5+3*sqrt(2);
		TanPos[4][1]=2.5+sqrt(2);
	}
	else if(fabs(TanCurrentPos[6][4][0]-3.5-3.5*sqrt(2)>0.1||fabs(TanCurrentPos[6][4][1]-3.5-1.25*sqrt(2))>0.1||\
	fabs(TanCurrentPos[6][1][0]-3.5-4*sqrt(2))>0.1||fabs(TanCurrentPos[6][1][1]-3.5-1.75*sqrt(2))>0.1)){
		angle[6]=1;
		TanPos[6][0]=3.5+3.5*sqrt(2);
		TanPos[6][1]=3.5+1.25*sqrt(2);
	}
	else if(fabs(TanCurrentPos[5][3][0]-5.5-sqrt(2))>0.1||fabs(TanCurrentPos[5][3][1]-1.5)>0.1||\
	fabs(TanCurrentPos[5][1][0]-5.5-2*sqrt(2))>0.1||fabs(TanCurrentPos[5][1][1]-1.5>0.1)){
		angle[5]=0;
		TanPos[5][0]=5.5+sqrt(2);
		TanPos[5][1]=1.5;
	}
	else if(fabs(TanCurrentPos[7][4][0]-5.5)>0.1||fabs(TanCurrentPos[7][4][1]-1.5)>0.1||\
	fabs(TanCurrentPos[7][1][0]-5.5-sqrt(2))>0.1||fabs(TanCurrentPos[7][1][1]-1.5)>0.1){
		angle[7]=0;
		TanPos[7][0]=5.5;
		TanPos[7][1]=1.5;
	}
}
