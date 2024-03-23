/***************************************
±‡“Î°¢µ˜ ‘≤Ω÷Ë:
masm /Ml mstruc;
copy mstruc.obj \tc
tcc -v cstruc.c mstruc.obj
td cstruc.exe
****************************************/

#include <stdio.h>
struct student
{
   char sname[10];
   short int score;
};
extern void f(struct student *p);

struct student a = {"Tom", 90};

main()
{
   struct student b = {"Jerry", 80};
   f(&b);
   printf("%d, %d\n", a.score, b.score);
}
