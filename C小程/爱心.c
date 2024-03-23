#include<stdio.h>
#include<process.h> 
int main(){
	system("pause"); 
	double x,y,a;
	
    for(y = 1.5; y > -1.5; y -= 0.1)
	{ 
	    for(x = -2.8; x < 1.5; x += 0.05) 
		{
			a = x * x + y * y - 1;
			putchar(a * a * a - x * x * y * y * y <= 0.0f? '+' : ' ');
		}
		
		putchar('\n');
	}
    getchar(); 
	return 0; 
}

