
void StringCount( char s[] ){
    int letter=0,blank=0,digit=0,other=0;
    int i,n=strlen(s);/*strlen计算字符的长度 即碰到'/0'空字符就结束*/ 
    for(i=0;i<n;i++){
        scanf("%c",&s[i]);
        if(s[i]>='a'&&s[i]<='z'||s[i]>='A'&&s[i]<='Z'){
            letter++;
        }
        else if(s[i]>='0'&&s[i]<='9'){
            digit++;
        }
        else if(s[i]==' '||s[i]=='\n'){
            blank++;
        }
        else {other++;}
    }
    printf("letter = %d, blank = %d, digit = %d, other = %d",letter,blank,digit,other);
}

