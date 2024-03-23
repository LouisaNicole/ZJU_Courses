;����Ҫ��:
;���³���Ĺ����ǴӼ�������һ�г��Ȳ�����8���ַ���
;16�����ַ��������浽����s�У��ٰѸ��ַ���ת����
;32λ���������浽����result�С�ע���ַ���sһ����
;00h�ַ�������
;���磺����"8086CaFe"����result��ֵ=8086CAFEh��
;������´��벹��������
;==========������´��뱣�浽src\main.asm==============================
;==========ѡ��main.sh��src�ļ���->�Ҽ�->ѹ����submit.zip�ύ==========
.386
data segment use16
sth db 10h dup(0)
s   db 100h dup('S')
result dd 0
data ends

code segment use16
assume cs:code, ds:data
main:
   mov ax, data
   mov ds, ax
   mov si, offset s
input_next:
   mov ah, 1
   int 21h; AL=getchar()
   cmp al, 0Dh; �ж��Ƿ�Ϊ�س���
   je input_done
   mov [si], al
   add si, 1                     
   jmp input_next
input_done:
   mov byte ptr [si], 0
;����#1_begin��#1_end֮�䲹�����ʵ�����¹���:
;��s�а�����16�����ַ���ת����32λ���������浽
;����result��
;#1_begin-------------------------------------
   mov si,0h
   mov eax,0
   mov ebx,0

lop:
   cmp s[si],00h
   je endcode
   cmp s[si],'9'
   jbe number_flag
   cmp s[si],'F'
   jbe alpha_flag1
   cmp s[si],'f'
   jbe alpha_flag2

alpha_flag1:
   cmp s[si],'A'
   jae alpha1

alpha_flag2:
   cmp s[si],'a'
   jae alpha2

number_flag:
   cmp s[si],'0'
   jae number

number:
   mov al,s[si]
   sub al,'0'
   add ebx,eax
   rol ebx,4
   add si,1
   jmp lop

alpha1:
   mov al,s[si]
   sub al,'A'
   add al, 0Ah
   add ebx,eax
   rol ebx,4
   add si,1
   jmp lop

alpha2:
   mov al,s[si]
   sub al,'a'
   add al, 0Ah
   add ebx,eax
   rol ebx,4
   add si,1
   jmp lop

endcode:
   ror ebx,4
   mov result,ebx
;#1_end========================================
   mov ah, 4Ch
   int 21h
code ends
end main
;==========������ϴ��뱣�浽src\main.asm==============================
