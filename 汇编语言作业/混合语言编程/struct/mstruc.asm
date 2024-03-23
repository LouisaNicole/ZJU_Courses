comment #=================================
±‡“Î°¢µ˜ ‘≤Ω÷Ë:
masm /Ml mstruc;
copy mstruc.obj \tc
tcc -v cstruc.c mstruc.obj
td cstruc.exe
==========================================#

public _f

student struc
sname db 10 dup(0)
score dw 0
student ends

extrn _a:byte

_DATA segment word public 'DATA'
_DATA ends

_TEXT segment byte public 'CODE'
assume cs:_TEXT, ds:_DATA
_f:
   push bp
   mov bp, sp
   push bx
   mov bx, [bp+4]
   mov ax, _a.score
   xchg ax, [bx].score
   mov _a.score, ax
   pop bx
   pop bp
   ret
_TEXT ends
end

