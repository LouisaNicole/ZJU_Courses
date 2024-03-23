;----------请把以下代码保存到src\main.asm------------------------------
;----------选中main.sh及src文件夹->右键->压缩成submit.zip提交----------
.386
data segment use16
sth db 10 dup(0)
s db 10 dup('S'), 0; 测评时数组s的长度及内容和此样本不会一样,
                   ; 但s一定是一个符合C语言标准的字符串
data ends

code segment use16
assume cs:code, ds:data
main:
   mov ax, data
   mov ds, ax
;在#1_begin和#1_end之间补充代码实现puts(s)的效果,即除了输出字符串s本身内容外,还需要再输出0Dh及0Ah
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
;----------请把以上代码保存到src\main.asm------------------------------
