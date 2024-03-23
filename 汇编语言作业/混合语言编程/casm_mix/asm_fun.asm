public _char2hex, _show_char, _hello_str; public使它们变成全局, C语言中才可以引用它们
extrn _cfun:near, _vp:dword ; 声明C语言函数_cfun的类型为near ptr, C语言变量
                            ; _vp的类型为dword ptr, 汇编语言中才可以引用它们
.386
_DATA	segment word public 'DATA' use16
t db "0123456789ABCDEF"
_hello_str db "Hello,world!", 0
_DATA ends

_TEXT segment byte public 'CODE' use16
assume  cs:_TEXT, ds:_DATA

comment # =======================================
void show_char(int x, int y, char c, char color)
{
   char far *p = _vp + (y*80+x)*2;
   *p = c;
   *(p+1) = color;
}
================================================= #
_show_char:
  push bp
  mov bp, sp
  push bx
  push es
  les bx, [_vp]    ; ES=0B800h, BX=0000h
                   ; _vp是定义在C语言中的远指针: 
                   ; char far *vp = (char far *)0xB8000000;
;------------------;
; mov ax, [bp+6]   ; AX = y
; mov cx, 80       ; CX = 80
; mul cx           ; AX = y*80
; add ax, [bp+4]   ; AX = y*80 + x
; shl ax, 1        ; AX = (y*80+x) * 2
;------------------;
  push word ptr [bp+6]; y
  push word ptr [bp+4]; x
  call _cfun          ; 调用C语言函数int cfun(int x, int y)
  add sp, 4           ; 清理堆栈中的2个参数
                      ; cfun()返回AX = (y*80+x) * 2
  add bx, ax       ; ES:BX就是远指针p
  mov al, [bp+8]   ; AL = c
  mov es:[bx], al  ; *p = c
  mov al, [bp+10]  ; AL = color
  mov es:[bx+1], al; *(p+1) = color
  pop es
  pop bx
  pop bp
  ret

comment # ======================================================= 
void char2hex(char xx, char s[]) /* 把8位数转化成16进制格式 */
{
   char t[] = "0123456789ABCDEF";
   s[0] = t[(xx >> 4) & 0x0F]; /* 高4位 */
   s[1] = t[xx & 0x0F];        /* 低4位 */
}
================================================================= #
_char2hex:
  push bp
  mov bp, sp
  push bx
  push si
  mov bx, offset t
  mov al, [bp+4]
  shr al, 4
  and al, 0Fh
  xlat; AL=[BX+AL]
  mov si, [bp+6]; si=s
  mov [si], al  ; s[0] = AL
  mov al, [bp+4]
  and al, 0Fh
  xlat
  mov [si+1], al; s[1] = AL
  pop si
  pop bx
  pop bp
  ret
_TEXT ends
end
