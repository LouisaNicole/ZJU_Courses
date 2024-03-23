// asmtest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//declaration specification
__declspec(naked) int f(int a, int b)
{  
   __asm
   { 
      int 3  // Èí¼þ¶Ïµã,»úÆ÷Âë=0CCh
      push ebp
      mov ebp, esp
      mov eax, [ebp+8]
      add eax, [ebp+0Ch]
      // mov esp, ebp
      pop ebp
      ret
   }
}

int main()
{  
   int a=10, b=20, c;
   c = f(10, 20);
   printf("c=%d\n", c);
	return 0;
}
