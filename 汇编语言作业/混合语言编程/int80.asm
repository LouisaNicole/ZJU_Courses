
code segment
assume cs:code, ds:code
old_80h dw 0, 0
main:
   xor ax, ax
   mov es, ax
   mov bx, 80h*4; mov bx, 200h
   mov ax, es:[bx]
   mov old_80h[0], ax
   mov ax, es:[bx+2]
   mov old_80h[2], ax
   ;
   mov word ptr es:[bx], offset int_80h
   mov es:[bx+2], cs
   ;
   mov ah, 1
   int 80h; AL=键盘输入的ASCII码
next:
   mov ah, 2
   mov dl, al
   int 80h
   ;
   mov ax, old_80h[0]
   mov es:[bx], ax
   mov ax, old_80h[2]
   mov es:[bx+2], ax
   ;
   mov ah, 4Ch
   int 21h
int_80h: ; ISR(Interrupt Service Routine)
         ; 中断服务函数
         ; 中断函数里面不能破坏任意寄存器的值
   cmp ah, 1
   je is_1
is_2:
   push es
   push bx
   mov bx, 0B800h
   mov es, bx
   mov byte ptr es:[160], dl
   mov byte ptr es:[161], 17h
   pop bx
   pop es
   jmp done
is_1:
   int 21h
done:
   iret
code ends
end main


