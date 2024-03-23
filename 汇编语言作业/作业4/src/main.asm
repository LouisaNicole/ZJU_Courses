;本题要求:
;以下程序的功能是从键盘输入一个十六进制数，
;该十六进制数一共2位，其中十位保存到buf[0]
;中，个位保存到buf[1]中，无论十位还是个位
;只要输入的是字母则一定是大写形式。接下去
;按以下步骤从屏幕第0行起输出16行内容，每行
;都输出字符c+i(i为屏幕行号)及其16进制ASCII码:
;(1)把buf[0]及buf[1]中的十六进制字符脱去引号
;(2)计算buf[0]<<4 | buf[1]的值并保存到变量c中
;(3)i=0
;(4)在(0,i)处显示字符c, 颜色为7Ch
;(5)在(1,i)处显示字符c的2位十六进制ASCII码, 颜色为1Ah
;(6)c++
;(7)i++
;(8)if(i<16) goto (4)
;(9)结束程序运行

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
;请在#1_begin和#1_end之间补充代码实现以下功能:
;(1)把buf[0]及buf[1]中的十六进制字符脱去引号
;(2)计算buf[0]<<4 | buf[1]的值并保存到变量c中
;(3)i=0
;(4)在(0,i)处显示字符c, 颜色为7Ch
;(5)在(1,i)处显示字符c的2位十六进制ASCII码, 颜色为1Ah
;(6)c++
;(7)i++
;(8)if(i<16) goto (4)
;(9)结束程序运行
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
