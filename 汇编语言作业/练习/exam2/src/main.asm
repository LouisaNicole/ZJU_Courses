;==========请把以下代码保存到src\main.asm==============================
;==========选中main.sh及src文件夹->右键->压缩成submit.zip提交==========
.386
data segment use16
sth db 10h dup(0)
n dw 0FFF0h   
s db 10h dup(0)
data ends

code segment use16
assume cs:code, ds:data
;void f(short int n, char s[])
;注意f()的参数通过堆栈传递,其中n就是[bp+4], s就是[bp+6]。
;在函数f()中不可直接引用data段中的变量n及数组s, 否则会产生编译错误。
f proc near
   push bp
   mov bp, sp
;请在#1_begin和#1_end之间补充代码实现以下功能:
;把16位符号数n转化成十进制字符串保存到数组s中,并在字符串后面填充'$'
;例如,当n=0FFF0h时, s的内容为: '-', '1', '6', '$'
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
   inc ax ;n变成正数
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
;==========请把以上代码保存到src\main.asm==============================
