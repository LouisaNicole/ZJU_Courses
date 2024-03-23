/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  Judge.c 
 History:  2023.5.23创建
 		   2023.5.25新增点在线段函数 IsOnLine
*************************************************/
#include <stdio.h>
#include <math.h>
extern int picture;
extern double TanCurrentPos[8][6][2];
//八个图形的外框点额坐标保存 
double a1[6][2]={6,2.6,  6,2.6+2*sqrt(2),  6+2*sqrt(2),2.6+2*sqrt(2),  6+2*sqrt(2),2.6,  6,2.6, 0,0};
double a2[15][2]={5,4,  5+2*sqrt(2),4,  6+sqrt(2),3+sqrt(2),  6+sqrt(2),4+sqrt(2),\
       7+sqrt(2),5+sqrt(2),  8+sqrt(2),4+sqrt(2),  7+sqrt(2),4+sqrt(2),\
	   6+1.5*sqrt(2),3+1.5*sqrt(2),  6+2*sqrt(2),3+sqrt(2),   6+2*sqrt(2),3,    5+2*sqrt(2),2,\
	   3+2*sqrt(2),2,   5+sqrt(2),4-sqrt(2),   5,4,0,0};
double a3[13][2]={6,2.5,  6,2.5+sqrt(2),  5.5,2.5+sqrt(2),  5.5+sqrt(2),2.5+2*sqrt(2),\
       4.5+2*sqrt(2),3.5+sqrt(2),  4.5+2*sqrt(2),4.5+sqrt(2),  5.5+2*sqrt(2),4.5+sqrt(2),\
	   5.5+2*sqrt(2),3.5+sqrt(2),  6.5+2*sqrt(2),2.5+sqrt(2),  6+2*sqrt(2),2.5+sqrt(2),\
	   6+2*sqrt(2),2.5,  6,2.5,0,0};
double a4[16][2]={6,2.5,  6+0.5*sqrt(2),2.5+0.5*sqrt(2),  6+0.5*sqrt(2),2.5+2.5*sqrt(2),\
	   6+sqrt(2),2.5+3*sqrt(2),  6+1.5*sqrt(2),2.5+2.5*sqrt(2),  6+1.5*sqrt(2),2.5+0.5*sqrt(2),\
	   6+2*sqrt(2),2.5,  6.5+sqrt(2),2.5,  6.5+sqrt(2),1.5,  7+sqrt(2),1.5,  6+sqrt(2),0.5,\
	   5+sqrt(2),1.5,  5.5+sqrt(2),1.5,  5.5+sqrt(2),2.5,  6,2.5,0,0};
double a5[13][2]={5.5,2.5,  9.5,2.5,  8.5,3.5,  9.5,3.5,  8.5,4.5,  7.5+sqrt(2),4.5,\
       7.5,4.5+sqrt(2),  7.5-sqrt(2),4.5,  6.5,4.5,  5.5,3.5,  6.5,3.5,  5.5,2.5,0,0};
double a6[15][2]={5.5,1.5,  5.5,3.5,  6.5,4.5,  7.5-0.5*sqrt(2),3.5+0.5*sqrt(2),\
       7.5,3.5+sqrt(2),  7.5+0.5*sqrt(2),3.5+0.5*sqrt(2),  7.5+0.5*sqrt(2),3.5+2*sqrt(2),\
	   7.5+1.5*sqrt(2),3.5+2*sqrt(2),  7.5+sqrt(2),3.5+1.5*sqrt(2),  7.5+sqrt(2),3.5+0.5*sqrt(2),\
	   7.5+0.5*sqrt(2),3.5,  7.5+0.5*sqrt(2),3.5-1.5*sqrt(2),  7.5-0.5*sqrt(2),3.5-0.5*sqrt(2),  5.5,1.5,0,0};
double a7[11][2]={5.5,4,  7.5,6,  7.5,5.5,  8.5,4.5,  9.5,5.5,  9.5,2.5,  8.5,3.5,\
       7.5,2.5,  7.5,2,  5.5,4,0,0};
double a8[20][2]={5.5,1.5,  5.5+0.5*sqrt(2),1.5+0.5*sqrt(2),  5.5+1.5*sqrt(2),1.5+0.5*sqrt(2),\
       5.5+sqrt(2),1.5+sqrt(2),  3.5+2*sqrt(2),1.5+sqrt(2),  3.5+2*sqrt(2),3.5+sqrt(2),\
	   3.5+3*sqrt(2),3.5+2*sqrt(2),  3.5+3*sqrt(2),3.5+1.75*sqrt(2),  3.5+3.5*sqrt(2),3.5+2.25*sqrt(2),\
	   3.5+4*sqrt(2),3.5+1.75*sqrt(2),  3.5+3.5*sqrt(2),3.5+1.25*sqrt(2),  3.5+3*sqrt(2),3.5+1.75*sqrt(2),\
	   3.5+3*sqrt(2),3.5+sqrt(2),  4.5+3*sqrt(2),3.5+sqrt(2),  3.5+3*sqrt(2),2.5+sqrt(2),  3.5+3*sqrt(2),3.5,\
	   5.5+2*sqrt(2),1.5+sqrt(2),  5.5+2*sqrt(2),1.5,  5.5,1.5,0,0};
//判断线段相交函数 
int IsIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	double d = (x2-x1)*(y4-y3)-(y2-y1)*(x4-x3);
	if (d != 0)
	{
		double r = ((y1-y3)*(x4-x3)-(x1-x3)*(y4-y3)) / d;
		double s = ((y1-y3)*(x2-x1)-(x1-x3)*(y2-y1)) / d;
		if ((r >= 0) && (r <= 1) && (s >= 0) && (s <= 1))
		{
			return 1;
		}
	}
	return 0;
}
//判断点在线段上函数 
int IsOnLine(double x1, double y1, double x2, double y2, double x3, double y3){
	double d1 = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	double d2 = sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
	double d = sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
	if(d1+d2-d <= 0.005) return 1;
	return 0;
}
//判断游戏成功函数 
int Judge(double a[][2]){
	int i = 0,sum = 0,j,k,m,n;
   	for(j=7;j>=1;j--){
    	k=1;
   		while(TanCurrentPos[j][k][0]){
			i=0;sum=0;
			int f=1;
			while(a[i+1][0]&&f){
				if(IsOnLine(TanCurrentPos[j][k][0],TanCurrentPos[j][k][1],a[i][0],a[i][1],a[i+1][0],a[i+1][1])){
					f=0;
					break;
				}
    			sum += IsIntersect(a[i][0],a[i][1],a[i+1][0],a[i+1][1],\
				TanCurrentPos[j][k][0],TanCurrentPos[j][k][1],9.8,7.4); //任意一条射线 
				i++;
			} 
			if(sum%2==0&&f) return 0; 
			
			// 取出来的点是TanCurrentPos[j][k]; 
			for(m=1;m<=7;m++){  //判断板子之间的重叠 
				int num=3;
				if(m==6||m==7) num=4;
				if(m==j) continue;
				n=1;//另一个板子上的点
				int flag=1;
				while(n<=num&&flag){
					if(IsOnLine(TanCurrentPos[j][k][0],TanCurrentPos[j][k][1],TanCurrentPos[m][n][0],TanCurrentPos[m][n][1],\
					TanCurrentPos[m][n%num+1][0],TanCurrentPos[m][n%num+1][1])) {
						flag=0;
						continue;
					}
					n++;
				}
				if(flag==0) break;//点在边上，满足条件，看下一个点 
				n=1;flag=1;
				int last = 0, now = 0;
				while(n<=num&&flag){
					double x1=TanCurrentPos[m][n%num+1][0]-TanCurrentPos[m][n][0],y1=TanCurrentPos[m][n%num+1][1]-TanCurrentPos[m][n][1];
					double x2=TanCurrentPos[j][k][0]-TanCurrentPos[m][n][0],y2=TanCurrentPos[j][k][1]-TanCurrentPos[m][n][1];
					double ans = x1*y2-x2*y1;
					if(ans>0) now=1;
					else if(ans<0) now=2;
					else now=0;
					last|=now;
					if(last==3) flag=0;	// last=3，点在外部，看下一个板子 
					n++;
				}// 到最后都不等于3，说明在内部，需要返回 
				
				if(last!=3) return 0;
			}
			k++;
		}
	}
	return 1;
}
//选择判断的图形 
int PicJudge(){
	int sum=0;
	switch(picture){
		case 1: sum = Judge(a1); break; 
		case 2: sum = Judge(a2); break;
		case 3: sum = Judge(a3); break;
		case 4: sum = Judge(a4); break;
		case 5: sum = Judge(a5); break;
		case 6: sum = Judge(a6); break;
		case 7: sum = Judge(a7); break;
		case 8: sum = Judge(a8); break;
	}
	return sum;
}
