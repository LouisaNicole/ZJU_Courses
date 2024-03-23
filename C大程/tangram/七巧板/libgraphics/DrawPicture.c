/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  DrawPicture.c 
 History:  2023.5.13创建完成
*************************************************/
#include "graphics.h"
#include "extgraph.h"
#include "DrawPicture.h" 
//都以小三角形边长为基准 
//天鹅,(x,y)为最左边点
void DrawSwan(double x,double y,double len,int fillflag)
{
	double a=sqrt(2)*len;
	MovePen(x, y);
	if( fillflag ) StartFilledRegion(1); 
	{
		DrawLine(2*a,0);
		DrawLine(len-a,a-len);
		DrawLine(0,len);
		DrawLine(len,len);
		DrawLine(len,-len);
		DrawLine(-len,0);
		DrawLine(a/2.0-len,a/2.0-len);
		DrawLine(a/2.0,-a/2.0);
		DrawLine(0,-a);
		DrawLine(-len,-len);
		DrawLine(-2*len,0);
		DrawLine(2*len-a,2*len-a);
		DrawLine(-a,a);
	}
	if( fillflag ) EndFilledRegion();
}
//房子,(x,y)为左下角点
void DrawHouse(double x,double y,double len,int fillflag) 
{
	double a=sqrt(2)*len;
	MovePen(x, y);
	if( fillflag ) StartFilledRegion(1); 
	{
		DrawLine(0,a);
		DrawLine(-len/2.0,0);
		DrawLine(a,a);
		DrawLine(a-len,len-a);
		DrawLine(0,len);
		DrawLine(len,0);
		DrawLine(0,-len);
		DrawLine(len,-len);
		DrawLine(-len/2.0,0);
		DrawLine(0,-a);
		DrawLine(-2*a,0);
	}
	if( fillflag ) EndFilledRegion();
}
//宝剑,(x,y)为最左边点
void DrawSword(double x,double y,double len,int fillflag) 
{
	double a=sqrt(2)*len;
	MovePen(x, y);
	if( fillflag ) StartFilledRegion(1); 
	{	
		DrawLine(a/2.0,a/2.0);
		DrawLine(0,2*a);
		DrawLine(a/2.0,a/2.0);
		DrawLine(a/2.0,-a/2.0);
		DrawLine(0,-2*a);
		DrawLine(a/2.0,-a/2.0);
		DrawLine(len/2.0-a,0);
		DrawLine(0,-len);
		DrawLine(len/2.0,0);
		DrawLine(-len,-len);
		DrawLine(-len,len);
		DrawLine(len/2.0,0);
		DrawLine(0,len);
		DrawLine(len/2.0-a,0);
	}
	if( fillflag ) EndFilledRegion();
}
//小树，(x,y)为左下角点 
void DrawTree(double x,double y,double len,int fillflag)
{
	double a=sqrt(2)*len;
	MovePen(x, y);
	if( fillflag ) StartFilledRegion(1); 
	{	
		DrawLine(4*len,0);
		DrawLine(-len,len);
		DrawLine(len,0);
		DrawLine(-len,len);
		DrawLine(a-len,0);
		DrawLine(-a,a);
		DrawLine(-a,-a);
		DrawLine(a-len,0);
		DrawLine(-len,-len);
		DrawLine(len,0);
		DrawLine(-len,-len);
	}
	if( fillflag ) EndFilledRegion();
}
//骆驼，(x,y)为左下角点
void DrawCamel(double x,double y,double len,int fillflag)
{
	double a=sqrt(2)*len;
	MovePen(x, y);
	if( fillflag ) StartFilledRegion(1); 
	{	
		DrawLine(0,2*len);
		DrawLine(len,len);
		DrawLine(len-a/2.0,a/2.0-len);
		DrawLine(a/2.0,a/2.0);
		DrawLine(a/2.0,-a/2.0);
		DrawLine(0,3.0*a/2.0);
		DrawLine(a,0);
		DrawLine(-a/2.0,-a/2.0);
		DrawLine(0,-a);
		DrawLine(-a/2.0,-a/2.0);
		DrawLine(0,-3.0*a/2.0);
		DrawLine(-a,a);
		DrawLine(a/2.0-2*len,a/2.0-2*len);
	}
	if( fillflag ) EndFilledRegion();
} 
//鱼，(x,y)为最左边点
void DrawFish(double x,double y,double len,int fillflag)
{
	double a=sqrt(2)*len;
	MovePen(x, y);
	if( fillflag ) StartFilledRegion(1); 
	{	
		DrawLine(2*len,2*len);
		DrawLine(0,-len/2.0);
		DrawLine(len,-len);
		DrawLine(len,len);
		DrawLine(0,-3*len);
		DrawLine(-len,len);
		DrawLine(-len,-len);
		DrawLine(0,-len/2.0);
		DrawLine(-2*len,2*len);
	}
	if( fillflag ) EndFilledRegion();
 } 
 //祈祷的人，(x,y)为左下角点
 void DrawPray(double x,double y,double len,int fillflag)
 {
 	double a=sqrt(2)*len;
	MovePen(x, y);
	if( fillflag ) StartFilledRegion(1); 
	{	
		DrawLine(a/2.0,a/2.0);
		DrawLine(a,0);
		DrawLine(-a/2.0,a/2.0);
		DrawLine(a-2*len,0);
		DrawLine(0,2*len);
		DrawLine(a,a);
		DrawLine(0,-a/4.0);
		DrawLine(a/2.0,a/2.0);
		DrawLine(a/2.0,-a/2.0);
		DrawLine(-a/2.0,-a/2.0);
		DrawLine(-a/2.0,a/2.0);
		DrawLine(0,-3.0*a/4.0);
		DrawLine(len,0);
		DrawLine(-len,-len);
		DrawLine(0,len-a);
		DrawLine(2*len-a,a-2*len);
		DrawLine(0,-a);
		DrawLine(-2*a,0);
	}
	if( fillflag ) EndFilledRegion();
  } 
  

void DrawShape_1(double x,double y,double len)//正方形 
{
	double a=2*sqrt(2*len*len);
	SetPenColor("Lem");
	drawRectangle(x,y,a,a,1);
	SetPenColor("Black");
	drawRectangle(x,y,a,a,0);	
}
void DrawShape_2(double x,double y,double len)//天鹅
{
	SetPenColor("Lem");
    DrawSwan(x,y,len,1);
    SetPenColor("Black");
    DrawSwan(x,y,len,0);
}
void DrawShape_3(double x,double y,double len)//房子
{
	SetPenColor("Lem");
    DrawHouse(x,y,len,1);
    SetPenColor("Black");
    DrawHouse(x,y,len,0);
 } 
 void DrawShape_4(double x,double y,double len)//宝剑 
 {
 	SetPenColor("Lem");
    DrawSword(x,y,len,1);
    SetPenColor("Black");
    DrawSword(x,y,len,0);
 }
 void DrawShape_5(double x,double y,double len)//小树 
 {
 	SetPenColor("Lem");
    DrawTree(x,y,len,1);
    SetPenColor("Black");
    DrawTree(x,y,len,0);
 }
 void DrawShape_6(double x,double y,double len)//骆驼
{
 	SetPenColor("Lem");
    DrawCamel(x,y,len,1);
    SetPenColor("Black");
    DrawCamel(x,y,len,0);
} 
void DrawShape_7(double x,double y,double len)//鱼
{
	SetPenColor("Lem");
    DrawFish(x,y,len,1);
    SetPenColor("Black");
    DrawFish(x,y,len,0);
 } 
 void DrawShape_8(double x,double y,double len)//祈祷的人
 {
 	SetPenColor("Lem");
    DrawPray(x,y,len,1);
    SetPenColor("Black");
    DrawPray(x,y,len,0);
 }   
