;����Ҫ��:
;���3��������,���ú���f()��1+2+3+...+n֮�Ͳ����浽����sum��,
;ע��sum���ᳬ��0FFFFh,���ڼ�������в���Ҫ���Ǽӷ����
;==========����������պ�ѱ��ļ����浽src\main.asm==================
;==========ѡ��main.sh��src�ļ���->�Ҽ�->ѹ����submit.zip�ύ==========
.386
data segment use16
sth db 10h dup(0)
n dw 3
sum dw 0
data ends

code segment use16
assume cs:code, ds:data
;����f()ԭ��:
;   short int f(short int n, short int *psum);
;����f()����:
;   ����1+2+3+...n�ĺ�, ���Ѻͱ��浽*psum�С����統n=3ʱ, *psum=6��
;��ʾ:
;   f()�Ĳ���ͨ����ջ����, ����n����[bp+4], psum����[bp+6]��
;ע��:
;   �ں���f()�в���ֱ������data���еı���n��sum, ��������ʧ��
f proc near
   push bp
   mov bp, sp
   mov bx, 0
   mov cx, 0
;#1_begin--------
   mov cx, [bp+4]
;#1_end----------
   mov bx, [bp+6]
   xor ax, ax
next:
   add ax, cx
   loop next
;#2_begin------
   mov [bx], ax
;#2_end--------
   pop bp
   ret
f endp

main:
   mov ax, data
   mov ds, ax
   mov ax, offset sum; ax = sum��ƫ�Ƶ�ַ
;#3_begin------------
   push ax
;#3_end--------------
   push [n]     ; ����n��ֵ������f()
   call f
   add sp, 4    ; �����ջ�ϵ�2������
   mov ax, [sum]; ����ʱ���鵱n=3ʱ,axӦ�õ���6
   mov ah, 4Ch
   int 21h
code ends
end main
;==========���������պ�ѱ��ļ����浽src\main.asm================
