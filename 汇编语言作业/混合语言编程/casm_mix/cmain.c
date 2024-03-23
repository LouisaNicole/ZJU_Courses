#include <stdio.h>
#include <string.h>
extern void show_char(int x, int y, char c, char color);
extern void char2hex(char xx, char s[]);
extern char hello_str[13];
char far *vp = (char far *)0xB8000000;

int cfun(int x, int y)
{
   return (y*80+x) * 2;
}

main()
{
   int i, n;
   char buf[2], c;
   n = strlen(hello_str);
   for(i=0; i<n; i++)
   {
      c = hello_str[i];
      char2hex(c, buf);
      show_char(0, i, c, 0x71);
      show_char(1, i, buf[0], 0x17);
      show_char(2, i, buf[1], 0x17);
   }
}

