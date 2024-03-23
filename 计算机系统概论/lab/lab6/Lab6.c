#include<stdio.h>
#include<string.h>
#include<math.h>
#define max 65535
short int pc = 0;
short int R[8]={0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777,0x7777};
short int cc[3]={0,0,0};
//
void judge(short int a, int *b, int *p, int *p_start);
void fand(int *ins);
void fadd(int *ins);
void fnot(int *ins);
void fld(short int a, int *ins, int *p, int *p_start);
void fldr(short int a, int *ins, int *p, int *p_start);
void fldi(short int a, int *ins, int *p, int *p_start);
void flea(int *ins);
void fst(short int a, int *ins, int *p, int *p_start);
void fstr(short int a, int *ins, int *p, int *p_start);
void fsti(short int a, int *ins, int *p, int *p_start);
void fbr(int *ins, int *p, int *p_start);
void fjsr(int *ins);
void fjmp(int *ins);
//
int main(){
    int inst[max][16]={0};
    int temp[16];
    unsigned int *p;
    unsigned int *p_start;
    char ch;
    // p = p_start = &inst[0][0];
    // p_start+=16;
    short int i = 0, count = 0, k;
    for(i=0;i<16;i++){
        scanf("%1d",&temp[i]);
    }
    pc=32768*(temp[0])+16384*(temp[1])+8192*(temp[2])+4096*(temp[3])\
        +2048*(temp[4])+1024*(temp[5])+512*(temp[6])+256*(temp[7])\
        +128*(temp[8])+64*(temp[9])+32*(temp[10])+16*(temp[11])\
        +8*(temp[12])+4*(temp[13])+2*(temp[14])+(temp[15]);
    p = p_start = &inst[pc][0];
    count = pc;
    ch=getchar();    
    do{
        for(i=0;i<16;i++){
            scanf("%1d",&inst[count][i]);
        }
        count++;
    }while((ch=getchar()) != EOF);
    i = pc;  //i is the start address
    while(pc<=count){
        if(inst[pc][0]==1 && inst[pc][1]==1 && inst[pc][2]==1 && inst[pc][3]==1) break;
        else judge(i, inst[pc], p, p_start);
    }
    for(k=0;k<8;k++){
        printf("R%d = x%04hX\n",k,(short)R[k]);
    }
    return 0;
}
//
void judge(short int a, int *b, int *p, int *p_start){
    pc++;p+=16;
    if(*b==0 && *(b+1)==0 && *(b+2)==0 && *(b+3)==1) fadd(b);
    else if(*b==0 && *(b+1)==1 && *(b+2)==0 && *(b+3)==1) fand(b);
    else if(*b==1 && *(b+1)==0 && *(b+2)==0 && *(b+3)==1) fnot(b);
    else if(*b==0 && *(b+1)==0 && *(b+2)==1 && *(b+3)==0) fld(a,b,p,p_start);
    else if(*b==1 && *(b+1)==0 && *(b+2)==1 && *(b+3)==0) fldi(a,b,p,p_start);
    else if(*b==0 && *(b+1)==1 && *(b+2)==1 && *(b+3)==0) fldr(a,b,p,p_start);
    else if(*b==1 && *(b+1)==1 && *(b+2)==1 && *(b+3)==0) flea(b);
    else if(*b==0 && *(b+1)==0 && *(b+2)==1 && *(b+3)==1) fst(a,b,p,p_start);
    else if(*b==1 && *(b+1)==0 && *(b+2)==1 && *(b+3)==1) fsti(a,b,p,p_start);
    else if(*b==0 && *(b+1)==1 && *(b+2)==1 && *(b+3)==1) fstr(a,b,p,p_start);
    else if(*b==0 && *(b+1)==0 && *(b+2)==0 && *(b+3)==0) fbr(b,p,p_start);
    else if(*b==1 && *(b+1)==1 && *(b+2)==0 && *(b+3)==0) fjmp(b);
    else if(*b==0 && *(b+1)==1 && *(b+2)==0 && *(b+3)==0) fjsr(b);

}
void fadd(int *ins){
    unsigned short int sr1,sr2,dr;
    if(*(ins+10)==0){//sr2
        sr1=4*(*(ins+7))+2*(*(ins+8))+*(ins+9);
        sr2=4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
        dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
        R[dr]=R[sr1]+R[sr2];
    }
    else{//imm5
        sr1=4*(*(ins+7))+2*(*(ins+8))+*(ins+9);
        sr2=-16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
        dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
        R[dr]=R[sr1]+sr2;
    }
    if(R[dr]>0) {cc[2]=1;cc[1]=0;cc[0]=0;}
    else if(R[dr]==0) {cc[2]=0;cc[1]=1;cc[0]=0;}
    else {cc[2]=0;cc[1]=0;cc[0]=1;}
}
//
void fand(int *ins){
    short int sr1,sr2,dr;
    if(*(ins+10)==0){//sr2
        sr1=4*(*(ins+7))+2*(*(ins+8))+*(ins+9);
        sr2=4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
        dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
        R[dr]=R[sr1] & R[sr2];  //bit and
    }
    else{//imm5
        sr1=4*(*(ins+7))+2*(*(ins+8))+*(ins+9);
        sr2=-16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
        dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
        R[dr]=R[sr1] & sr2;
    }   
    if(R[dr]>0) {cc[2]=1;cc[1]=0;cc[0]=0;}
    else if(R[dr]==0) {cc[2]=0;cc[1]=1;cc[0]=0;}
    else {cc[2]=0;cc[1]=0;cc[0]=1;}
}
//
void fnot(int *ins){
    short int sr,dr;
    sr=4*(*(ins+7))+2*(*(ins+8))+*(ins+9);
    dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
    R[dr]=~R[sr];
    if(R[dr]>0) {cc[2]=1;cc[1]=0;cc[0]=0;}
    else if(R[dr]==0) {cc[2]=0;cc[1]=1;cc[0]=0;}
    else {cc[2]=0;cc[1]=0;cc[0]=1;}
}
void fld(short int a, int *ins, int *p, int *p_start){
    short int dr,offset,m;
    int *q=p_start;
    dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
    offset=-256*(*(ins+7))+128*(*(ins+8))+64*(*(ins+9))+32*(*(ins+10))\
            +16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
    q+=((unsigned)pc+offset-a)*16;
    R[dr]=-1*pow(2,15)*(*q);
    for(m=1;m<16;m++){
        R[dr]+=pow(2,15-m)*(*(q+m));
    }
    if(R[dr]>0) {cc[2]=1;cc[1]=0;cc[0]=0;}
    else if(R[dr]==0) {cc[2]=0;cc[1]=1;cc[0]=0;}
    else {cc[2]=0;cc[1]=0;cc[0]=1;}
}
//
void fldr(short int a, int *ins, int *p, int *p_start){
    short int dr,offset,base_plus,base;
    int *q=p_start;
    int m;
    dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
    base=4*(*(ins+7))+2*(*(ins+8))+*(ins+9);
    offset=-32*(*(ins+10))+16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
    base_plus=(unsigned)R[base]+offset;
    q+=16*(base_plus-a);
    R[dr]=-1*pow(2,15)*(*q);
    for(m=1;m<16;m++){
        R[dr]+=pow(2,15-m)*(*(q+m));
    }
    if(R[dr]>0) {cc[2]=1;cc[1]=0;cc[0]=0;}
    else if(R[dr]==0) {cc[2]=0;cc[1]=1;cc[0]=0;}
    else {cc[2]=0;cc[1]=0;cc[0]=1;}
}
//
void fldi(short int a, int *ins, int *p, int *p_start){
    short int m,dr,offset,pc_plus,offset_plus;
    int *q=p_start;
    dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
    offset=-256*(*(ins+7))+128*(*(ins+8))+64*(*(ins+9))+32*(*(ins+10))\
            +16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
    pc_plus=(unsigned)pc+offset;
    q+=16*(pc_plus-a);
    offset_plus=0;
    for(m=0;m<16;m++){
        offset_plus+=pow(2,15-m)*(*(q+m));
    }
    //
    q=p_start+16*(offset_plus-a);
    R[dr]=-1*pow(2,15)*((*q));
    for(m=1;m<16;m++){
        R[dr]+=pow(2,15-m)*(*(q+m));
    }
    if(R[dr]>0) {cc[2]=1;cc[1]=0;cc[0]=0;}
    else if(R[dr]==0) {cc[2]=0;cc[1]=1;cc[0]=0;}
    else {cc[2]=0;cc[1]=0;cc[0]=1;}
}
//
void flea(int *ins){
    short int dr,offset;
    dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
    offset=-256*(*(ins+7))+128*(*(ins+8))+64*(*(ins+9))+32*(*(ins+10))\
            +16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
    R[dr]=(unsigned)pc+offset;
}
//
void fst(short int a, int *ins, int *p, int *p_start){
    short int m,dr,offset,pc_plus,reg;
    int *q=p_start;
    dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
    offset=-256*(*(ins+7))+128*(*(ins+8))+64*(*(ins+9))+32*(*(ins+10))\
            +16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
    q+=((unsigned)pc+offset-a)*16;
    reg=(unsigned)R[dr];
    for(m=15;m>=0;m--){
        *(q+m)=(reg & 0x0001);
        reg=reg>>1;
    }
}
//
void fstr(short int a, int *ins, int *p, int *p_start){
    short int m,dr,offset,base_plus,base,reg;
    int *q=p_start;
    dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
    base=4*(*(ins+7))+2*(*(ins+8))+*(ins+9);
    offset=-32*(*(ins+10))+16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
    base_plus=(unsigned)R[base]+offset;
    reg=(unsigned)R[dr];
    q+=16*(base_plus-a);
    for(m=15;m>=0;m--){
        *(q+m)=(reg & 1);
        reg=reg>>1;
    }
}
//
void fsti(short int a, int *ins, int *p, int *p_start){
    short int m,dr,offset,pc_plus,offset_plus,reg;
    int *q=p;
    dr=4*(*(ins+4))+2*(*(ins+5))+*(ins+6);
    offset=-256*(*(ins+7))+128*(*(ins+8))+64*(*(ins+9))+32*(*(ins+10))\
            +16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
    reg=(unsigned)R[dr];
    pc_plus=(unsigned)pc+offset;
    q=p_start+16*(pc_plus-a);
    offset_plus=0;
    for(m=0;m<16;m++){
        offset_plus+=pow(2,15-m)*(*(q+m));
    }
    //
    q=p_start+16*(offset_plus-a);
    for(m=15;m>=0;m--){
        *(q+m)=(reg & 0x0001);
        reg=reg>>1;
    }
}
//
void fbr(int *ins, int *p, int *p_start){
    short int offsetbr,ncc,zcc,pcc;
    offsetbr=-256*(*(ins+7))+128*(*(ins+8))+64*(*(ins+9))+32*(*(ins+10))\
            +16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
    ncc=*(ins+4);
    zcc=*(ins+5);
    pcc=*(ins+6);
    if((ncc&cc[0])|(zcc&cc[1])|(pcc&cc[2])){
        pc+=offsetbr;
    }
}
//
void fjsr(int *ins){
    short int offset,base;
    offset=-1024*(*(ins+5))+512*(*(ins+6))+256*(*(ins+7))+128*(*(ins+8))+64*(*(ins+9))+\
            32*(*(ins+10))+16*(*(ins+11))+8*(*(ins+12))+4*(*(ins+13))+2*(*(ins+14))+*(ins+15);
    base=4*(*(ins+7))+2*(*(ins+8))+*(ins+9);
    R[7]=pc;
    if(*(ins+4)==0) pc=(unsigned)R[base];
    else pc=pc+offset;
}
//
void fjmp(int *ins){
    short int base;
    base=4*(*(ins+7))+2*(*(ins+8))+*(ins+9);
    pc=(unsigned)R[base];
}

    