/*************************************************
 Copyright 羌沈洁、陆依敏、李凯悦. 2023. All rights reserved.
 File name:  absorb.h 
 History:  2023.5.22创建
 		   2023.5.24新增点吸附函数 PointAbsorb
*************************************************/
#ifndef ____absorb_h______
#define ____absorb_h______
#include "genlib.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Judge.h"
int PointAbsorb(double x1,double y1,double x2,double y2,double *dx,double *dy);
void swap(double *x,double *y);
void TanAbsorb();
double PointDistance(double x1, double y1,double x2,double y2);
int IsAbsorb(double x1,double y1,double x2,double y2,double x3,double y3,\ 
    double x4,double y4,double *dx,double *dy);
void Absorb();
void AbsorbOutline(double a[][2]);
#endif
