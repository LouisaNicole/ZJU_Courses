;����Ҫ��:
comment %
��������һ�����ʽ, �ñ��ʽ�а������ɸ�ʮ���ƷǷ�����(��4294967295)�����������:
   + * /
����ñ��ʽ��ʮ������ֵ��
���г�������ֻ��Ҫ������(��������),
���ʽ�е����������Ҫ�������ȼ���һ�ɰ�������˳����㡣
�����ʽ�е��κ�һ������������32λ(������0FFFFFFFFh),
��ò���������������32λ(������32λ)��
���磺
���룺
12345+56789*54321/9876
�����
0005CD62
=======================================================================%
;==========������´��뱣�浽src\main.asm==============================
;==========ѡ��main.sh��src�ļ���->�Ҽ�->ѹ����submit.zip�ύ==========
.386
data segment use16
t db "0123456789ABCDEF"
buf  db 81, 0, 81 dup(0)
b    dd 0
c    dd 0
prev_op  dw 1; 1 means '+', 2 means '*', 3 means '/', 0 means '\0'
fun  dw 0000h, fun_add, fun_mul, fun_div
s    db 00h, '+', '*', '/'
data ends

code segment use16
assume cs:code, ds:data
output:
   push eax
   push ebx
   push ecx
   push edx
   mov bx, offset t
   mov ecx, 8
next:
   rol eax, 4
   push eax
   and eax, 0Fh
   xlat
   mov ah, 2
   mov dl, al
   int 21h
   pop eax
   loop next
   mov ah, 2
   mov dl, 0Dh
   int 21h
   mov dl, 0Ah
   int 21h
   pop edx
   pop ecx
   pop ebx
   pop eax
   ret

main:
   cld
   mov ax, data
   mov ds, ax
   mov ah, 0Ah
   mov dx, offset buf
   int 21h
   xor bx, bx
   mov bl, buf[1]    ; BL=�����ַ����ĳ���
   mov buf[bx+2], 00h; ������Ļس����滻��00h
                     ; buf[2]�����ַ���������
   mov ah, 2
   mov dl, 0Dh
   int 21h           ; ����س�
   mov dl, 0Ah
   int 21h           ; �������
   ;
   lea si, buf[2]    ; ds:si->������ַ���
   ;
;����#1_begin��#1_end֮�䲹�����ʵ�����¹���:
;    ����ds:siָ��ı��ʽ,���������浽����[b]��
;ע��: 
;    ���в����������Զ��庯��������������
;    ����#1_begin��#1_end֮��
;#1_begin-------------------------------------
lop:
   mov di, 0
   cmp prev_op, 0
   je do_output
   jmp process

process:
   cmp di, 4
   jae flag
   mov al, [si]
   cmp al, s[di]
   je flag
   add di, 1
   jmp process

flag:
   cmp di, 4
   jb exefun
   jmp execal

exefun:
   cmp prev_op, 1
   je fun_add
   cmp prev_op, 2
   je fun_mul
   cmp prev_op, 3
   je fun_div
      
execal:
   mov ebx, 10
   mov eax, [c]
   mul ebx
   mov [c], eax
   mov eax, 0
   mov al, [si]
   sub al, '0'
   add [c], eax
   add si, 1
   jmp lop

fun_add:
   mov ebx, [c]
   add [b], ebx
   mov [c], 0
   mov cx, di
   mov [prev_op], cx
   add si, 1
   jmp lop

fun_mul:
   mov ebx, [c]
   mov eax, [b]
   mul ebx
   mov [b], eax
   mov [c], 0
   mov cx, di
   mov [prev_op], cx
   add si, 1
   jmp lop

fun_div:
   mov eax, [b]
   mov edx, 0
   mov ebx, [c]
   div ebx
   mov [b], eax
   mov [c], 0
   mov cx, di
   mov [prev_op], cx
   add si, 1
   jmp lop

;#1_end=======================================
do_output:
   mov eax, [b]
   call output; ��16���Ƹ�ʽ�������b��ֵ
exit:
   mov ah, 4Ch
   int 21h
code ends
end main
;==========������ϴ��뱣�浽src\main.asm==============================