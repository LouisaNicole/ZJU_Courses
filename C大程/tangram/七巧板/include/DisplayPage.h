/*************************************************
 Copyright Ǽ��ࡢ½���������. 2023. All rights reserved.
 File name:  DisplayPage.h 
 History:  2023.5.11����
 		   2023.5.20������Ϸ�жϺ�������
 		   2023.5.27����ʵ���ļ���ȡ����ʱ��������
 		   2023.5.28����ʵ����Ϸ��������Ϸ��ʾ�Ľ��湦�� 
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
void DisplayInitialPage(WINDOW *win);//��ȡ��ҳ�� 
void DisplaySelectPage(WINDOW *win);//��ȡѡ��ҳ��
void DisplaySquarePage(WINDOW *win);//���������ɰ�
void DisplaySwanPage(WINDOW *win);//��������ɰ�
void DisplayHousePage(WINDOW *win);//���������ɰ� 
void DisplaySwordPage(WINDOW *win);//���������ɰ�
void DisplayTreePage(WINDOW *win);//С�������ɰ�
void DisplayCamelPage(WINDOW *win);//���������ɰ�
void DisplayFishPage(WINDOW *win);//�������ɰ�
void DisplayPrayPage(WINDOW *win);//���������ɰ�
void DisplayHelpPage(WINDOW *win);//��Ϸ˵�� 
void DisplayCreatPage(WINDOW *win);
void check(WINDOW *win);
void DrawOthers(WINDOW *win);
void TanClear();
void Hint();
void Time(WINDOW *win);
void Save();
 
#endif
