;----------������´��뱣�浽src\main.asm------------------------------
;----------ѡ��main.sh��src�ļ���->�Ҽ�->ѹ����submit.zip�ύ----------
.386
data segment use16
sth db 10 dup(0)
s db 10 dup('S'), 0; ����ʱ����s�ĳ��ȼ����ݺʹ���������һ��,
                   ; ��sһ����һ������C���Ա�׼���ַ���
data ends

code segment use16
assume cs:code, ds:data
main:
   mov ax, data
   mov ds, ax
;��#1_begin��#1_end֮�䲹�����ʵ��puts(s)��Ч��,����������ַ���s����������,����Ҫ�����0Dh��0Ah
;#1_begin--------------------------------------
   mov di, 0
next:   
   cmp s[di], 0
   je ending
   mov ah, 02h
   mov dl, s[di]
   int 21h
   inc di
   jmp next   
ending:
   mov ah, 02h
   mov dl, 0Dh
   int 21h
   mov ah, 02h
   mov dl, 0Ah
   int 21h
;#1_end----------------------------------------
   mov ah, 4Ch
   int 21h
code ends
end main
;----------������ϴ��뱣�浽src\main.asm------------------------------
