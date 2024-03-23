#include <stdio.h>
int main(){
    int R0 = Mem[x3100];
    int R1 = 3;  //To find three consecutive ones.
    int R3 = 1;  //R3 = 0000 0000 0000 0001
    int R4, R2;
    while(R3 != 0){    //If R3 == 0, the program has run the 16th bit of data in memory.
        R4 = R0 & R3;  //Determine whether the digit in the data is 1.
        R1 --;  
        if(R1 == 0) break;   //Three consecutive ones have been found.
        if(R4 == 0) R1 = 3;  //A zero appears, so restart searching.
        R3 = R3 + R3;  //R3 moves one bit to the left to find the next 1.
    }
    if(R3 != 0) R2 = 1;
    else R2 = 0;
}