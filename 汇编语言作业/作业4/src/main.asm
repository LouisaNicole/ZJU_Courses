;����Ҫ��:
;���³���Ĺ����ǴӼ�������һ��ʮ����������
;��ʮ��������һ��2λ������ʮλ���浽buf[0]
;�У���λ���浽buf[1]�У�����ʮλ���Ǹ�λ
;ֻҪ���������ĸ��һ���Ǵ�д��ʽ������ȥ
;�����²������Ļ��0�������16�����ݣ�ÿ��
;������ַ�c+i(iΪ��Ļ�к�)����16����ASCII��:
;(1)��buf[0]��buf[1]�е�ʮ�������ַ���ȥ����
;(2)����buf[0]<<4 | buf[1]��ֵ�����浽����c��
;(3)i=0
;(4)��(0,i)����ʾ�ַ�c, ��ɫΪ7Ch
;(5)��(1,i)����ʾ�ַ�c��2λʮ������ASCII��, ��ɫΪ1Ah
;(6)c++
;(7)i++
;(8)if(i<16) goto (4)
;(9)������������

.386
data segment use16
buf db 0, 0
c   db 0
hex db 0, 0
data ends

code segment use16
assume cs:code, ds:data
main:
   mov ax, data
   mov ds, ax
   mov ax, 0B800h
   mov es, ax
   mov di, 0
   ;
   mov ah, 1
   int 21h
   mov buf[0], al
   mov ah, 1
   int 21h
   mov buf[1], al
;����#1_begin��#1_end֮�䲹�����ʵ�����¹���:
;(1)��buf[0]��buf[1]�е�ʮ�������ַ���ȥ����
;(2)����buf[0]<<4 | buf[1]��ֵ�����浽����c��
;(3)i=0
;(4)��(0,i)����ʾ�ַ�c, ��ɫΪ7Ch
;(5)��(1,i)����ʾ�ַ�c��2λʮ������ASCII��, ��ɫΪ1Ah
;(6)c++
;(7)i++
;(8)if(i<16) goto (4)
;(9)������������
;#1_begin-------------------------------------
   mov cx, 0

   mov bx, offset buf[0]
   call remove_quotation_mark
   mov bx, offset buf[1]
   call remove_quotation_mark
   mov bx, offset c 
   call move_shift_or

lop:
   cmp cx, 16
   jb out_put
   jmp last

remove_quotation_mark:
   cmp byte ptr [bx], '9'
   ja alpha1
   digit1:
      sub byte ptr [bx], '0'
      ret
   alpha1:
      sub byte ptr [bx], 'A'
      add byte ptr [bx], 10
      ret

add_quotation_mark:
   cmp byte ptr [bx], 9
   ja alpha2
   digit2:
      add byte ptr [bx], '0'
      ret
   alpha2:
      add byte ptr [bx], 'A'
      sub byte ptr [bx], 10
      ret

move_shift_or:
   shl byte ptr buf[0], 4 
   mov al, byte ptr buf[0]
   or al, byte ptr buf[1]
   mov [c],al
   ret

out_put:
   mov al, [c]
   mov ah, 7Ch
   mov word ptr es:[di], ax

   mov al, [c]
   shr al, 4
   mov hex[0], al
   mov ah, [c]
   and ah, 00001111B
   mov byte ptr hex[1], ah
   mov bx, offset hex[0]
   call add_quotation_mark
   mov bx, offset hex[1]
   call add_quotation_mark

   mov ah, 1Ah
   mov al, hex[0]
   mov word ptr es:[di+2], ax
   mov ah, 1Ah
   mov al, hex[1]
   mov word ptr es:[di+4], ax
   
   add di,160
   add [c], 1
   add cx, 1
   jmp lop

last:
;#1_end=======================================
   mov ah, 4Ch
   int 21h
code ends
end main
