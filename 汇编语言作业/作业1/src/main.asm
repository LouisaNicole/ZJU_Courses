;����Ҫ��:
;���³���Ĺ����ǴӼ�������һ���ַ��������浽����s�У�
;�����ȡ������s�е�Ԫ�أ����˵������ַ���Сд��ĸ����
;���ַ�ȫ�����浽����t�С�����s��t�е��ַ�����������00h
;�ַ�(��C�����е�'\0'�ַ�)������
;���磺����"abcXYZ123#$@"��������t��Ӧ�ô��
;"XYZ#$@"��������´��벹��������
;==========������´��뱣�浽src\main.asm==============================
;==========ѡ��main.sh��src�ļ���->�Ҽ�->ѹ����submit.zip�ύ==========
data segment
sth db 10h dup(0)
s db 100h dup('S')
t db 100h dup('T')
data ends
code segment
assume cs:code, ds:data
main:
   mov ax, data
   mov ds, ax
   mov bx, 0
input_next:
   mov ah, 1
   int 21h; AL=getchar()
   cmp al, 0Dh; �ж��Ƿ�Ϊ�س���
   je input_done
   mov s[bx], al
   add bx, 1                     
   jmp input_next
input_done:
   mov s[bx], 0
;����#1_begin��#1_end֮�䲹�����ʵ�����¹���:
;���ȡ������s�е�Ԫ�أ����˵������ַ���Сд��ĸ��
;�����ַ�ȫ�����浽����t�С�ע��t�е��ַ�������
;��00h�ַ�(��C�����е�'\0'�ַ�)������
;#1_begin-------------------------------------
   mov bx, 0
   mov di, 0
   mov si, 0

cmp1:
   cmp s[di], 00h
   je last
   
assign1:
   cmp s[di], 'z'
   ja assign5

assign2:
   cmp s[di], '0'
   jb assign5

assign3:
   cmp s[di], 'a'
   jae assign6
   
assign4:
   cmp s[di], '9'
   ja assign5
   jmp assign6

assign5:
   mov bx, word ptr s[di]
   mov word ptr t[si], bx
   add di,1
   add si,1
   jmp cmp1

assign6:
   add di,1
   jmp cmp1

last:
;#1_end========================================
   mov ah, 4Ch
   int 21h
code ends
end main
;==========������ϴ��뱣�浽src\main.asm==============================
