        .ORIG x3000
        LEA   R2,STRING
        LEA   R5,MEM
        LD    R4,OFFSET
        ADD   R5,R5,R4
        AND   R6,R6,#0
        ADD   R6,R6,R5     ;Initial the head & tail pointer R5=R6.
        GETC
        OUT                ;The input is displayed.
        LD    R4,ENTER
        ADD   R4,R4,R0
        BRz   END          ;End and output the string.
        LD    R4,LPOP
        ADD   R4,R4,R0
        BRz   FLAG         ;Start whether to pop first
        LD    R4,RPOP
        ADD   R4,R4,R0
        BRz   FLAG         ;Start whether to pop first
        BRnzp JUDGE        ;Begin judge!!!
;
JUDGE0  AND   R4,R4,#0
        ADD   R4,R5,#0
        NOT   R4,R4
        ADD   R4,R4,#1
        ADD   R4,R4,R6     ;R5==R6 means an empty list
        BRz   FLAG
JUDGE   LD    R4,LPOP
        ADD   R4,R4,R0
        BRz   POPL
        LD    R4,RPOP
        ADD   R4,R4,R0
        BRz   POPR
        LD    R4,LPUSH
        ADD   R4,R4,R0
        BRz   PUSHL            
        LD    R4,RPUSH
        ADD   R4,R4,R0
        BRz   PUSHR 
;
POPL    LDR   R0,R5,#0     ;R5 is the address of the head value.
        STR   R0,R2,#0
        ADD   R2,R2,#1
        ADD   R5,R5,#1     
        BRnzp NEXT
;
PUSHL   GETC               ;Input the actual value.
        OUT
        ADD   R5,R5,#-1    ;R5 is the address of the head value.
        STR   R0,R5,#0
        BRnzp NEXT
;   
POPR    ADD   R6,R6,#-1    ;R6 is the address after the tail value.
        LDR   R0,R6,#0
        STR   R0,R2,#0
        ADD   R2,R2,#1
        BRnzp NEXT
;
PUSHR   GETC               ;Input the actual value.
        OUT
        STR   R0,R6,#0     ;R6 is the address after the tail value.
        ADD   R6,R6,#1
        BRnzp NEXT
;
NEXT    GETC               ;Input the next 'opcode'.
        OUT
        LD    R4,ENTER
        ADD   R4,R4,R0
        BRz   END          ;End and output the string.
        LD    R4,LPOP
        ADD   R4,R4,R0
        BRz   JUDGE0
        LD    R4,RPOP
        ADD   R4,R4,R0
        BRz   JUDGE0
        BRnzp JUDGE
;
FLAG    LD    R4,UNDER     ;Record the empty list and store '_'
        STR   R4,R2,#0
        ADD   R2,R2,#1
        BRnzp NEXT       
;
END     ADD   R4,R4,#0
        STR   R4,R2,#0
        LEA   R0,STRING
        PUTS
        HALT
;
OFFSET  .FILL #100
ENTER   .FILL #-10
LPOP    .FILL #-45
LPUSH   .FILL #-43
RPUSH   .FILL #-91
RPOP    .FILL #-93
UNDER   .FILL #95          ;The ascII of "_"
STRING  .BLKW 100
MEM     .BLKW 200
        .END