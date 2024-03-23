/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  DisplayPage.h 
 History:  2023.5.11创建
 		   2023.5.20新增游戏判断函数功能
 		   2023.5.27新增实现文件读取、计时器的需求
 		   2023.5.28新增实现游戏帮助和游戏提示的界面功能 
*************************************************/
#ifndef ____DisplayPage_h______
#define ____DisplayPage_h______
#include "imgui.h"
#include "extgraph.h"
#include "graphics.h"
#include <stdlib.h>
#include "DrawPicture.h"
#include "ColorChoose.h"
#include "variable.h"
void DrawButton(WINDOW* win); 
void DrawBackground(WINDOW* win);
void Display(WINDOW *win);
void DisplayInitialPage(WINDOW *win);//调取主页面 
void DisplaySelectPage(WINDOW *win);//调取选择页面
void DisplaySquarePage(WINDOW *win);//正方形七巧板
void DisplaySwanPage(WINDOW *win);//天鹅形七巧板
void DisplayHousePage(WINDOW *win);//房子形七巧板 
void DisplaySwordPage(WINDOW *win);//宝剑形七巧板
void DisplayTreePage(WINDOW *win);//小树形七巧板
void DisplayCamelPage(WINDOW *win);//骆驼形七巧板
void DisplayFishPage(WINDOW *win);//鱼形七巧板
void DisplayPrayPage(WINDOW *win);//祈祷的人七巧板
void DisplayHelpPage(WINDOW *win);//游戏说明 
void DisplayCreatPage(WINDOW *win);
void check(WINDOW *win);
void DrawOthers(WINDOW *win);
void TanClear();
void Hint();
void Time(WINDOW *win);
void Save();
 
#endif
