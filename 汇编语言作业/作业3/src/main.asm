;����Ҫ��:
comment %
���³���Ĺ����ǴӼ�������һ���ַ�c�������
n�������������n=c-'0'���ײ�ո���=n-1������
����ո�������1���ײ��ַ���=1�����������ַ���
����2��ÿ��������ַ����̶�Ϊc��
����ַ������int 21h��2�Ź��ܣ�����ͨ��д�Կ�
��ַʵ���ַ���������⣬������һ��ʱҲ��Ҫ��
ĩβ���0Dh��0Ah��
���磺����5����Ӧ�����
    5
   555
  55555
 5555555
555555555
;������´��벹������
%
;==========������´��뱣�浽src\main.asm==============================
;==========ѡ��main.sh��src�ļ���->�Ҽ�->ѹ����submit.zip�ύ==========
data segment
c    db 0
rows dw 0
spaces_on_this_row dw 0
digits_on_this_row dw 0
data ends

stack segment stack
    db 128 dup (?)
stack ends

code segment
assume cs:code, ds:data
main:
   mov ax, data
   mov ds, ax
   mov ah, 1
   int 21h       ; AL=getchar()
   mov [c], al   ; ����������ַ�������c��
   sub al, '0'   ; ������������ַ��ѵ�����
   mov ah, 0     ; AX�ĸ�8λ����
   mov [rows], ax; �ܹ���Ҫ������������浽����rows��
   dec ax        ; ax--
   mov [spaces_on_this_row], ax; ������Ҫ����Ŀո�ĸ���
   mov [digits_on_this_row], 1 ; ������Ҫ��������ֵĸ���
   cmp [rows], 0
   je exit
   mov ah, 2
   mov dl, 0Dh
   int 21h; ����س�
   mov ah, 2
   mov dl, 0Ah
   int 21h; �������
;����#1_begin��#1_end֮�䲹�����ʵ�����¹���:
;���n�������������n=c-'0'���ײ�ո���=n-1������
;����ո�������1���ײ��ַ���=1�����������ַ���
;����2��ÿ��������ַ����̶�Ϊc��
;����ַ������int 21h��2�Ź��ܣ�����ͨ��д�Կ�
;��ַʵ���ַ���������⣬������һ��ʱҲ��Ҫ��
;ĩβ���0Dh��0Ah��
;#1_begin-------------------------------------

lop1:
   cmp [rows], 0
   je exit
   mov cx, [spaces_on_this_row]
blank:
   cmp cx, 0
   je lop2
   mov ah, 2
   mov dl, ' '
   int 21h
   sub cx, 1
   jmp blank

lop2:
   mov cx, [digits_on_this_row]
digit:
   cmp cx, 0
   je end_lop
   mov ah, 2
   mov dl, [c]
   int 21h
   sub cx, 1
   jmp digit

end_lop:
   mov ah, 2
   mov dl, 0Dh
   int 21h; ����س�
   mov ah, 2
   mov dl, 0Ah
   int 21h; �������
   sub [rows], 1
   sub [spaces_on_this_row], 1
   add [digits_on_this_row], 2
   jmp lop1

;#1_end=======================================
exit:
   mov ah, 4Ch
   int 21h
code ends
end main
;==========������ϴ��뱣�浽src\main.asm==============================
