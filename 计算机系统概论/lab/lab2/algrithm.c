#include<stdio.h>
#include<string.h>
int main(){
    char str1,str2;      //save strings
    char *p=str1; 
    int count[26]={0};   //counter
    int i,flag;
    if(strlen(str1)!=strlen(str2)) flag=0;  //strlen is same
    while(*p!=0){
        count[*p-'a']++; //Records the number of characters present in string 1
        p++;
    }
    p=str2;
    while(*p!=0){
        count[*p-'a']--; //Records the number of characters present in string 2
        p++;
    }
    for(i=0;i<26;i++){
        if(count[i]!=0) flag=0; //Failure if non-zero occurs.
    }
    if(i==26) flag=1;
    return 0;
}