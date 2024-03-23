;本题要求:
;以下程序的功能是从键盘输入一行字符串并保存到数组s中，
;再逐个取出数组s中的元素，过滤掉数字字符及小写字母，其
;余字符全部保存到数组t中。其中s及t中的字符串均必须用00h
;字符(即C语言中的'\0'字符)结束。
;例如：输入"abcXYZ123#$@"，则数组t中应该存放
;"XYZ#$@"。请把以下代码补充完整。
;==========请把以下代码保存到src\main.asm==============================
;==========选中main.sh及src文件夹->右键->压缩成submit.zip提交==========
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
   cmp al, 0Dh; 判断是否为回车键
   je input_done
   mov s[bx], al
   add bx, 1                     
   jmp input_next
input_done:
   mov s[bx], 0
;请在#1_begin和#1_end之间补充代码实现以下功能:
;逐个取出数组s中的元素，过滤掉数字字符及小写字母，
;其余字符全部保存到数组t中。注意t中的字符串必须
;用00h字符(即C语言中的'\0'字符)结束。
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
;==========请把以上代码保存到src\main.asm==============================
