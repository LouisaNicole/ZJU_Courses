;==========������´��뱣�浽src\main.asm==============================
;==========ѡ��main.sh��src�ļ���->�Ҽ�->ѹ����submit.zip�ύ==========
.386
data segment use16
sth db 10h dup(0)
n dw 0FFF0h   
s db 10h dup(0)
data ends

code segment use16
assume cs:code, ds:data
;void f(short int n, char s[])
;ע��f()�Ĳ���ͨ����ջ����,����n����[bp+4], s����[bp+6]��
;�ں���f()�в���ֱ������data���еı���n������s, ���������������
f proc near
   push bp
   mov bp, sp
;����#1_begin��#1_end֮�䲹�����ʵ�����¹���:
;��16λ������nת����ʮ�����ַ������浽����s��,�����ַ����������'$'
;����,��n=0FFF0hʱ, s������Ϊ: '-', '1', '6', '$'
;#1_begin-----------=========------------------
   mov ax, [bp+4] ;n
   mov bx, [bp+6] ;s[]
   mov si, 1
   mov dx, ax
   and dx, 8000h
   cmp dx, 0
   je pro1
   mov dl, '-'
   mov byte ptr[bx], dl
   inc bx
   not ax
   inc ax ;n�������
pro1:
   push ax
   mov cx, 10
num:
   xor dx, dx
   div cx
   cmp ax, 0
   je pro2
   inc si
   jmp num
pro2:
   mov ah, '$'
   mov byte ptr[bx+si], ah
   pop ax
digit:
   xor dx, dx
   div cx
   add dx, '0'
   mov byte ptr[bx+si-1], dl
   dec si
   cmp si, 0
   jne digit
   mov sp, bp
;#1_end-------------=========------------------
   pop bp
   ret
f endp

main:
   mov ax, data
   mov ds, ax
   mov ax, offset s
   push ax
   push [n]
   call f
   add sp, 4
   mov ah, 9
   mov dx, offset s
   int 21h
   mov ah, 4Ch
   int 21h
code ends
end main
;==========������ϴ��뱣�浽src\main.asm==============================
