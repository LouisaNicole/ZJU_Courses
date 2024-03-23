#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include "imgui.h"
#include "DisplayPage.h" 
#include "variable.h"
#include "tangrammove.h"

#define edge 1/sqrt(2) 

int time; 

WINDOW win; 
double TanPos[8][2] = {0.0,0.0,0.1,5.4,0.1,3.8, 0.5,2.7, 0.3,1.7, 1.8,1.7, 0.5,0.4, 1.7,0.5}; //���ɰ���ʼ��λ�� 
int angle[8]; //���ɰ���б�Ƕ� 
int id; //׼���ƶ������ɰ����� 
int rolid; //ѡ�е����ɰ���� 
int picture; //ѡ�е�ͼ�α�� 
double TanCurrentPos[8][6][2]; // �����ɰ�ÿ�����ʵʱλ�� 
int ordertan[10]={0,1,2,3,4,5,6,7};//�����ӵ�˳��
// �����İ���Ҫ��󻭣����Էŵ���� 


//void KeyboardEventProcess(int key,int event);/*������Ϣ�ص�����*/
//void CharEventProcess(char c);/*�ַ���Ϣ�ص�����*/
void MouseEventProcess(int x, int y, int button, int event);/*�����Ϣ�ص�����*/
void TimerEventProcess(int timerID);/*��ʱ����Ϣ�ص�����*/

void Initial();

void Main(){
	SetWindowTitle("���ɰ�");
	SetWindowSize(10, 8); // ��λ - Ӣ��
    InitGraphics();
    Initial();
    
	//registerCharEvent(CharEventProcess);        // �ַ�
	//registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerTimerEvent(TimerEventProcess);      // ��ʱ��    
}

void Initial(){
	SetColors();
	SetFont("Arial");  
	DisplayInitialPage(&win);
	win.currentPage=InitialPage;
    win.winwidth = GetWindowWidth();
    win.winheight = GetWindowHeight();	
    picture = 0; 
}

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event);
	static bool ismovetangram = FALSE;
	static bool iselse = FALSE;
	static double omx = 0.0, omy = 0.0;
	double mx,my;
    win.g_mousepoint.x = mx = ScaleXInches(x);
	win.g_mousepoint.y = my = ScaleYInches(y);
	switch(event){
		case BUTTON_DOWN:
			id = judgemovetangram(mx,my);
			if(button==LEFT_BUTTON&&id&&win.currentPage!=InitialPage&&win.currentPage!=SelectPage){
				rolid = id;
				MoveOrder();
				ismovetangram = 1;
				omx = mx;
				omy = my;
			}
			break;
		case BUTTON_UP:
			if(button==LEFT_BUTTON){
				ismovetangram = 0;
				iselse = 0;
				id = 0;
			}
			if(win.currentPage!=InitialPage&&win.currentPage!=SelectPage&&win.currentPage!=HelpPage) Absorb();
			Display(&win);
			break;	
		case MOUSEMOVE:
			if(ismovetangram){
				TanPos[id][0]+=mx-omx;
				TanPos[id][1]+=my-omy;
				omx = mx;
				omy = my;
			}
			break;

	}
	Display(&win);
}

void TimerEventProcess(int timerID)
{
	switch(timerID){
		case 1:
			time++;
			SetPenColor("Nav");
			drawRectangle(8,7,1,1,1);
			string s = IntegerToString(time);
			MovePen(8,7);
			SetPenColor("Black");
			DrawTextString(s);
			if(time==100){
				cancelTimer(1);
				SetPenColor("Nav");
		        drawRectangle(0,0,10,8,1);
            	SetPenColor("Black");
               	SetPointSize(70);
				drawLabel(2.5, 5, "Game Over!");
				SetPointSize(26);
				if(button(GenUIID(0),2.5,2.5,1.5,0.6,"Reselect")){
					win.currentPage=SelectPage;
					Display(&win);
				}
				if(button(GenUIID(0),6,2.5,1.2,0.6,"Retry")){
					TanClear();
					time = 0;
					startTimer(1,1000);
					Display(&win);
				}
			}
			
			break;
	}
}
	


