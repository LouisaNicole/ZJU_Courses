;本题要求:
;完成3项程序填空,调用函数f()求1+2+3+...+n之和并保存到变量sum中,
;注意sum不会超过0FFFFh,故在计算过程中不需要考虑加法溢出
;==========请把在完成填空后把本文件保存到src\main.asm==================
;==========选中main.sh及src文件夹->右键->压缩成submit.zip提交==========
.386
data segment use16
sth db 10h dup(0)
n dw 3
sum dw 0
data ends

code segment use16
assume cs:code, ds:data
;函数f()原型:
;   short int f(short int n, short int *psum);
;函数f()功能:
;   计算1+2+3+...n的和, 并把和保存到*psum中。例如当n=3时, *psum=6。
;提示:
;   f()的参数通过堆栈传递, 其中n就是[bp+4], psum就是[bp+6]。
;注意:
;   在函数f()中不可直接引用data段中的变量n及sum, 否则会编译失败
f proc near
   push bp
   mov bp, sp
   mov bx, 0
   mov cx, 0
;#1_begin--------
   mov cx, [bp+4]
;#1_end----------
   mov bx, [bp+6]
   xor ax, ax
next:
   add ax, cx
   loop next
;#2_begin------
   mov [bx], ax
;#2_end--------
   pop bp
   ret
f endp

main:
   mov ax, data
   mov ds, ax
   mov ax, offset sum; ax = sum的偏移地址
;#3_begin------------
   push ax
;#3_end--------------
   push [n]     ; 传递n的值给函数f()
   call f
   add sp, 4    ; 清除堆栈上的2个参数
   mov ax, [sum]; 跟踪时请检查当n=3时,ax应该等于6
   mov ah, 4Ch
   int 21h
code ends
end main
;==========请在完成填空后把本文件保存到src\main.asm================
