/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  DisplayPage.h 
 History:  2023.5.11创建
 		   2023.5.20新增游戏判断函数功能
 		   2023.5.27新增实现文件读取、计时器的需求
 		   2023.5.28新增实现游戏帮助和游戏提示的界面功能 
*************************************************/
#include "imgui.h"
#include "extgraph.h"
#include "graphics.h"
#include <stdlib.h>
#include <math.h>
#include "DrawPicture.h"
#include "ColorChoose.h"
#include "variable.h"
#include "DisplayPage.h"
#include "Hint.h"

#define cita 0.463647609
#define pi 3.1415926

extern int id,rolid,picture;
extern int angle[8];
extern int ordertan[10];
extern double TanPos[8][2];
extern double TanCurrentPos[8][6][2];
extern int time;
extern int picture;

//判断游戏是否成功 
void check(WINDOW *win){
	int result_judge=PicJudge();
	if(result_judge==1){
		cancelTimer(1);
		SetPenColor("Nav");
		drawRectangle(0,0,win->winwidth,win->winheight,1);
    	SetPenColor("Black");
    	SetPointSize(70);
    	drawLabel(3.5,5,"Success!");
    	SetPointSize(26);
		if (button(GenUIID(0),2,2,2.5,0.6, "Replay the game")){
			TanClear(); 
			startTimer(1,1000);
			Display(&win);
			result_judge = 2;
		}
		if (button(GenUIID(0),6,2,2.5,0.6, "Reselect the game")){
			Save();
			win->currentPage=SelectPage;
			Display(&win);
			result_judge = 2;
		}
	}
}

void DrawOthers(WINDOW *win){
	int i;	
	for(i=1;i<=7;i++) DrawTan(ordertan[i]);
	if(win->currentPage==CreatPage){
		if(button(GenUIID(0),6.1,7,1.3,0.6,"ReCreat")){
		TanClear();
	    }
	    return;
	}
	
	if(button(GenUIID(0),6.1,7,0.8,0.6,"Retry")){
		TanClear();
	}
	if(button(GenUIID(0),6.9,7,0.8,0.6,"Hint")){
		Hint();
	}
	Time(win);
}
//七巧板复位 
void TanClear(){
	TanPos[1][0]=0.1; TanPos[1][1]=5.4;
	TanPos[2][0]=0.1; TanPos[2][1]=3.8;
	TanPos[3][0]=0.5; TanPos[3][1]=2.7;
	TanPos[4][0]=0.3; TanPos[4][1]=1.7;
	TanPos[5][0]=1.8; TanPos[5][1]=1.7;
	TanPos[6][0]=0.5; TanPos[6][1]=0.4;
	TanPos[7][0]=1.7; TanPos[7][1]=0.5;	
	int i=0;
	for(i=1;i<=7;i++) angle[i]=0;
	for(i=1;i<=7;i++) ordertan[i]=i;
	if(picture!=9){
		time=0;
	} 
	//time = 0;
	rolid = 0;
}
//提示函数 
void Hint(){
	switch(picture){
		case 1: Hint1(); break; 
		case 2: Hint2(); break;
		case 3: Hint3(); break;
		case 4: Hint4(); break;
		case 5: Hint5(); break;
		case 6: Hint6(); break;
		case 7: Hint7(); break;
		case 8: Hint8(); break;
	}
}
//计数器函数 
void Time(WINDOW *win){
	SetPenColor("Nav");
	drawRectangle(8,7,1,1,1);
	string s = IntegerToString(time);
	MovePen(8,7);
	SetPenColor("Black");
	DrawTextString(s);
	if(time==100){
		cancelTimer(1);
		SetPenColor("Nav");
		drawRectangle(0,0,win->winwidth,win->winheight,1);
    	SetPenColor("Black");
    	SetPointSize(70);
    	drawLabel(2.5,5,"Game Over!");
    	SetPointSize(26);
		if(button(GenUIID(0),2.5,2.5,1.5,0.6,"Reselect")){
			win->currentPage=SelectPage;
			Display(&win);
		}
		if(button(GenUIID(0),6,2.5,1.2,0.6,"Retry")){
			TanClear();
			time = 0;
			startTimer(1,1000);
			Display(&win);
		}
	}
}
void DrawButton(WINDOW* win){
	setButtonColors("Bur", "Bro","White", "Bro", 1);
	if (button(GenUIID(0),0,7.7,1.2,0.3, "Reselect"))
	{
		Save();
		win->currentPage = SelectPage;
		cancelTimer(1);
	}
	if (button(GenUIID(0), 1.2,7.7,1.2,0.3, "Exit"))
	{
		Save();
		exit(-1);
	}	
	if (button(GenUIID(0),2.4,7.7,1.2,0.3, "Help")){
    	win->lastPage = win->currentPage;
    	win->currentPage = HelpPage;
	}
	setButtonColors("Bro", "White","White", "Peru", 1);
	if (button(GenUIID(0),4.5,7,0.8,0.6, "Left"))
	{
		double ang;
		double aaa[8]={0,sqrt(10),sqrt(10),sqrt(5),sqrt(10)/2,sqrt(10)/2,sqrt(2),sqrt(5)};
		switch(rolid){
			case 1:
			case 2: 
			case 3: 
			case 4: 
			case 5: ang=pi/4*angle[rolid]+cita-3.0/8*pi; break;
			case 6: ang=pi/4*angle[6]-pi/8; break;
			case 7: ang=pi/4*angle[7]-cita-pi/8; break;
		}
		angle[rolid]=(angle[rolid]+1)%8; 
		TanPos[rolid][0]+=aaa[rolid]*sin(pi/8)*cos(ang);
		TanPos[rolid][1]+=aaa[rolid]*sin(pi/8)*sin(ang);
	}
	if (button(GenUIID(0),5.3,7,0.8,0.6, "Right"))
	{
		double ang;
		double aaa[8]={0,sqrt(10),sqrt(10),sqrt(5),sqrt(10)/2,sqrt(10)/2,sqrt(2),sqrt(5)};
		switch(rolid){
			case 1:
			case 2: 
			case 3:
			case 4: 
			case 5: ang=pi/4*angle[rolid]+cita+3.0/8*pi; break;
			case 6: ang=pi/4*angle[6]+5.0/8*pi; break;
			case 7: ang=pi/4*angle[7]-cita+5.0/8*pi; break;
		}
		angle[rolid]=(angle[rolid]-1)%8;
		TanPos[rolid][0]+=aaa[rolid]*sin(pi/8)*cos(ang);
		TanPos[rolid][1]+=aaa[rolid]*sin(pi/8)*sin(ang);
	}
}
void DrawBackground(WINDOW* win){
	SetPenColor("Nav");
	SetPointSize(25);
	drawRectangle(0,0,win->winwidth,win->winheight,1);
	DrawButton(win);
}
//初始化界面 
void DisplayInitialPage(WINDOW *win){
	SetPenColor("Nav");
    drawRectangle(0,0,10,8,1);
    SetPenColor("Peru");
    SetPenSize(80);
    SetPointSize(80);
    drawBox(2,4.8,6,1.2,1,"Tangrams",'c',"White");
    SetPenColor("Bro");
	SetPointSize(100); 
	drawLabel(7.5,4.5,"☆");
	SetPenColor("Bro");
	SetPointSize(65); 
	drawLabel(7,4.5,"☆");
	SetPenColor("Bro");
	SetPointSize(40); 
	drawLabel(6.6,4.5,"☆");
    SetPenSize(1);
    SetPointSize(20);
    setButtonColors("Bur", "Bro","White", "Peru", 1);
	if (button(GenUIID(0), 4,2.8,2,0.4, "START"))
	{
		win->currentPage = SelectPage;
	}
	if (button(GenUIID(0), 4,2,2,0.4, "EXIT"))
	{
		exit(-1);
	}
	if (button(GenUIID(0), 4,1.2,2,0.4, "HELP")) {
		win->lastPage = win->currentPage;
		win->currentPage = HelpPage;
	}
} 
//选择界面 
void DisplaySelectPage(WINDOW *win){
	
	TanClear();
	
	SetPenColor("Nav");
	drawRectangle(0,0,win->winwidth,win->winheight,1);
	SetPenColor("Bro");
	SetPointSize(35);
    drawLabel(1.3, win->winheight-1.1, "Choose the shape you want to challenge!");
    setButtonColors("Bur", "Bro","White", "Peru", 1);
    SetPointSize(25);
    if (button(GenUIID(0), 0,7.7,1.2,0.3, "Return"))
	{
		win->currentPage = InitialPage;
		cancelTimer(1);
	}
	if (button(GenUIID(0), 1.2,7.7,1.2,0.3, "Exit"))
	{
		exit(-1);
	}	
	if (button(GenUIID(0), 2.4,7.7,1.2,0.3, "Help"))
	{
		win->lastPage = SelectPage;
		win->currentPage = HelpPage;
	}
	setButtonColors("Bur", "Bro","White", "Peru", 1);
    SetPointSize(15);
    DrawShape_1(0.8,4.9,0.35);
    if (button(GenUIID(0),0.8,4.1,1,0.3, "Square"))
	{	
		FILE *fp;
		if((fp=fopen("picture1.txt","rb"))==NULL){
			exit(0);
		}
		fread(TanPos,8,16,fp);
		fread(angle,8,8,fp);
		fscanf(fp,"%d",&time);
		if(fclose(fp)){
			exit(0);
		}
		startTimer(1,1000);
		win->currentPage = SquarePage;
		picture=1;
	}
	DrawShape_2(2.7,5.4,0.35);
	if (button(GenUIID(0),3,4.1,1,0.3, "Swan"))
	{	
		FILE *fp;
		if((fp=fopen("picture2.txt","rb"))==NULL){
			exit(0);
		}
		fread(TanPos,8,16,fp);
		fread(angle,8,8,fp);
		fscanf(fp,"%d",&time);
		if(fclose(fp)){
			exit(0);
		}
		startTimer(1,1000);
		win->currentPage = SwanPage;
		picture=2;
	}
	DrawShape_3(5.3,4.9,0.35);
	if (button(GenUIID(0),5.3,4.1,1,0.3, "House"))
	{	
		FILE *fp;
		if((fp=fopen("picture3.txt","rb"))==NULL){
			exit(0);
		}
		fread(TanPos,8,16,fp);
		fread(angle,8,8,fp);
		fscanf(fp,"%d",&time);
		if(fclose(fp)){
			exit(0);
		}
		startTimer(1,1000);
		win->currentPage = HousePage;
		picture=3;
	}
	DrawShape_4(7.5,5.2,0.35);
	if (button(GenUIID(0),7.5,4.1,1,0.3, "Sword"))
	{	
		FILE *fp;
		if((fp=fopen("picture4.txt","rb"))==NULL){
			exit(0);
		}
		fread(TanPos,8,16,fp);
		fread(angle,8,8,fp);
		fscanf(fp,"%d",&time);
		if(fclose(fp)){
			exit(0);
		}
		startTimer(1,1000);
		win->currentPage = SwordPage;
		picture=4;
	}
	DrawShape_5(0.6,2.2,0.35);
	if (button(GenUIID(0),0.8,1.5,1,0.3, "Tree"))
	{	
		FILE *fp;
		if((fp=fopen("picture5.txt","rb"))==NULL){
			exit(0);
		}
		fread(TanPos,8,16,fp);
		fread(angle,8,8,fp);
		fscanf(fp,"%d",&time);
		if(fclose(fp)){
			exit(0);
		}
		startTimer(1,1000);
		win->currentPage = TreePage;
		picture=5;
	}
	DrawShape_6(3,2.1,0.35);
	if (button(GenUIID(0),3,1.5,1,0.3, "Camel"))
	{	
		FILE *fp;
		if((fp=fopen("picture6.txt","rb"))==NULL){
			exit(0);
		}
		fread(TanPos,8,16,fp);
		fread(angle,8,8,fp);
		fscanf(fp,"%d",&time);
		if(fclose(fp)){
			exit(0);
		}
		startTimer(1,1000);
		win->currentPage = CamelPage;
		picture=6;
	}
	DrawShape_7(5.1,2.8,0.35);
	if (button(GenUIID(0),5.3,1.5,1,0.3, "Fish"))
	{	
		FILE *fp;
		if((fp=fopen("picture7.txt","rb"))==NULL){
			exit(0);
		}
		fread(TanPos,8,16,fp);
		fread(angle,8,8,fp);
		fscanf(fp,"%d",&time);
		if(fclose(fp)){
			exit(0);
		}
		startTimer(1,1000);
		win->currentPage = FishPage;
		picture=7;
	}
	DrawShape_8(7.5,2,0.35);
	if (button(GenUIID(0),7.5,1.5,1,0.3, "Pray"))
	{	
		FILE *fp;
		if((fp=fopen("picture8.txt","rb"))==NULL){
			exit(0);
		}
		fread(TanPos,8,16,fp);
		fread(angle,8,8,fp);
		fscanf(fp,"%d",&time);
		if(fclose(fp)){
			exit(0);
		}
		startTimer(1,1000);
		win->currentPage = PrayPage;
		picture=8;
	}
	
	if (button(GenUIID(0),1.3,0.5,7,0.4, "Creat Your Own Puzzle"))
	{
    	FILE *fp;
		if((fp=fopen("creat.txt","rb"))==NULL){
			exit(0);
		}
		fread(TanPos,8,16,fp);
		fread(angle,8,8,fp);
		if(fclose(fp)){
			exit(0);
		}
		win->currentPage = CreatPage;
		picture=9;	
	}
} 
//接下来八个函数描述不同的挑战界面 
void DisplaySquarePage(WINDOW *win)
{
	DrawBackground(win);
	DrawShape_1(6,2.6,1);
	DrawOthers(win);
	check(win);
}
void DisplaySwanPage(WINDOW *win)
{
	DrawBackground(win);
	DrawShape_2(5,4,1);	
	DrawOthers(win);
	check(win);
}
void DisplayHousePage(WINDOW *win)
{
    DrawBackground(win);
	DrawShape_3(6,2.5,1);
	DrawOthers(win);
	check(win);
}
void DisplaySwordPage(WINDOW *win)
{
    DrawBackground(win);
	DrawShape_4(6,2.5,1);
	DrawOthers(win);
	check(win);
}
void DisplayTreePage(WINDOW *win)
{
    DrawBackground(win);
	DrawShape_5(5.5,2.5,1);	
	DrawOthers(win);
	check(win);
}
void DisplayCamelPage(WINDOW *win)
{
    DrawBackground(win);
	DrawShape_6(5.5,1.5,1);	
	DrawOthers(win);
	check(win);
}
void DisplayFishPage(WINDOW *win)
{
    DrawBackground(win);
	DrawShape_7(5.5,4,1);
	DrawOthers(win);
	check(win);
}
void DisplayPrayPage(WINDOW *win)
{
    DrawBackground(win);
	DrawShape_8(5.5,1.5,1);	
	DrawOthers(win);
	check(win);
}
void DisplayHelpPage(WINDOW *win)
{
	SetPenColor("Nav");
	drawRectangle(0,0,10,8,1);
	SetPenColor("Bro");
	SetPointSize(32);
    drawLabel(1.7, 6.0, "本游戏有八种七巧板关卡供玩家选择，玩家有");
    drawLabel(1.2, 5.4, "100秒的时间可以拖动和旋转七块板子拼接成固定");
	drawLabel(1.2, 4.8, "图案，拼接过程中将自动判断游戏是否成功，超");
    drawLabel(1.2, 4.2, "时则判断游戏失败，玩家可选择重新挑战或者重");
    drawLabel(1.2, 3.6, "新选择关卡。");
    drawLabel(1.7, 3.0, "游戏过程中玩家可以选择保存游戏状态并退出，");
    drawLabel(1.2, 2.4, "重新打开游戏后可以选择重新开始或继续游戏。玩");
    drawLabel(1.2, 1.8, "家也可以自由绘制图案进行保存并闯关。");
	SetPointSize(25);
    setButtonColors("Bur", "Bro","White", "Bro", 1);
    if (button(GenUIID(0), 0,7.7,1,0.3, "Return"))
	{
		win->currentPage = win->lastPage;
	}
	if(win->lastPage != InitialPage){
		string s = IntegerToString(time);
		MovePen(8,7);
		SetPenColor("Black");
		DrawTextString(s);
	}
	
}
void DisplayCreatPage(WINDOW *win)
{
	DrawBackground(win);
	DrawOthers(win);
 } 
 
void Display(WINDOW *win){ 
	DisplayClear();
	switch(win->currentPage){
		case InitialPage:
			DisplayInitialPage(win);
			break;
		case SelectPage:
			DisplaySelectPage(win);
			break;
		case SquarePage:
			DisplaySquarePage(win);
			break;
		case SwanPage:
			DisplaySwanPage(win);
			break;
		case HousePage:
			DisplayHousePage(win);
			break;
		case SwordPage:
			DisplaySwordPage(win);
			break;
		case TreePage:
			DisplayTreePage(win);
			break;
		case CamelPage:
			DisplayCamelPage(win);
			break;
		case FishPage:
			DisplayFishPage(win);
			break;
		case PrayPage:
			DisplayPrayPage(win);
			break;
		case HelpPage:
			DisplayHelpPage(win);
			break;
		case CreatPage: 
		    DisplayCreatPage(win);
		    break;
		default:
			break;
	    }	
}
//文件保存便于游戏读取 
void Save(){
	FILE *fp;
	switch(picture){
		case 1: fp=fopen("picture1.txt","wb"); break;
		case 2: fp=fopen("picture2.txt","wb"); break;
		case 3: fp=fopen("picture3.txt","wb"); break;
		case 4: fp=fopen("picture4.txt","wb"); break;
		case 5: fp=fopen("picture5.txt","wb"); break;
		case 6: fp=fopen("picture6.txt","wb"); break;
		case 7: fp=fopen("picture7.txt","wb"); break;
		case 8: fp=fopen("picture8.txt","wb"); break;
		case 9: fp=fopen("creat.txt","wb"); break;
	}
	rolid = 0;
	fwrite(TanPos,8,16,fp);
	fwrite(angle,8,8,fp);
	if(picture!=9){
    	fprintf(fp,"%d",time);		
	}
	fclose(fp);
}
