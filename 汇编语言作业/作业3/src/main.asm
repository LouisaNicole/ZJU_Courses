;本题要求:
comment %
以下程序的功能是从键盘输入一个字符c，再输出
n层金字塔，其中n=c-'0'，首层空格数=n-1，后续
各层空格数逐层减1，首层字符数=1，后续各层字符数
逐层加2，每层输出的字符均固定为c。
输出字符请调用int 21h的2号功能，不能通过写显卡
地址实现字符输出。另外，输出最后一层时也需要在
末尾输出0Dh及0Ah。
例如：输入5，则应该输出
    5
   555
  55555
 5555555
555555555
;请把以下代码补充完整
%
;==========请把以下代码保存到src\main.asm==============================
;==========选中main.sh及src文件夹->右键->压缩成submit.zip提交==========
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
   mov [c], al   ; 保存输入的字符到变量c中
   sub al, '0'   ; 把输入的数字字符脱掉引号
   mov ah, 0     ; AX的高8位清零
   mov [rows], ax; 总共需要输出的行数保存到变量rows中
   dec ax        ; ax--
   mov [spaces_on_this_row], ax; 首行需要输出的空格的个数
   mov [digits_on_this_row], 1 ; 首行需要输出的数字的个数
   cmp [rows], 0
   je exit
   mov ah, 2
   mov dl, 0Dh
   int 21h; 输出回车
   mov ah, 2
   mov dl, 0Ah
   int 21h; 输出换行
;请在#1_begin和#1_end之间补充代码实现以下功能:
;输出n层金字塔，其中n=c-'0'，首层空格数=n-1，后续
;各层空格数逐层减1，首层字符数=1，后续各层字符数
;逐层加2，每层输出的字符均固定为c。
;输出字符请调用int 21h的2号功能，不能通过写显卡
;地址实现字符输出。另外，输出最后一层时也需要在
;末尾输出0Dh及0Ah。
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
   int 21h; 输出回车
   mov ah, 2
   mov dl, 0Ah
   int 21h; 输出换行
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
;==========请把以上代码保存到src\main.asm==============================
