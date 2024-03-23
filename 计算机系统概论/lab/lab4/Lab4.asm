;System booting code
            .ORIG x0200
            LD   R1, READY
            STI  R1, KBSR1
            LD   R1, INTVSERVICE
            STI  R1, INTVADDR
            LD   R6, OS_SP
            LD   R0, USER_PSR
            ADD  R6, R6, #-1
            STR  R0, R6, #0
            LD   R0, USER_PC
            ADD  R6, R6, #-1
            STR  R0, R6, #0
            RTI
OS_SP       .FILL x3000
USER_PSR    .FILL x8002
USER_PC     .FILL x3000
KBSR1       .FILL xFE00
READY       .FILL x4000
INTVADDR    .FILL x0180
INTVSERVICE .FILL x0800
            .END
; 
;Service Routine for Keyboard Input
            .ORIG x0800
            ST   R1, SAVER
;START       LDI  R1, KBSR2
 ;           BRZP START
            LDI  R7, KBDR
            LD   R1, SAVER
            RTI
SAVER       .FILL x0000
KBSR2       .FILL xFE00
KBDR        .FILL xFE02
            .END
;
;User program
            .ORIG x3000
            LD   R5, INITIAL
            LD   R6, INITIAL
            LD   R7, INITIAL
            AND  R1, R1, #0
            AND  R2, R2, #0       ;Initial r1=0,r2=17
            ADD  R2, R2, #15
            ADD  R2, R2, #2
            BRNZP LOOP20
;
JUDGE       ADD  R7, R7, #0
            BRZ  YES              ;have no interrupt
            BRNZP NO             
;
YES         ADD  R1, R1, #0       
            BRZ  LOOP20
            ADD  R1, R1, #-1      ;down one dot
            ADD  R2, R2, #1
            BRNZP LOOP20
;
NO          AND  R5, R5, #0
            ADD  R5, R7, #0       ;r5=r7, the new alpha/digit
            LD   R3, INITIAL
            NOT  R4, R5
            ADD  R4, R4, #1
            ADD  R4, R4, R3
            BRNZ ALPHA            ;interrupt the alpha
            BRNZP DIGIT           ;interrupt the digit
;
ALPHA       AND  R6, R6, #0
            ADD  R6, R5, #0       ;r6=r7, the new alpha
            BRNZP YES
;
DIGIT       LD   R4, DIGIT0
            ADD  R4, R4, R5
            NOT  R4, R4
            ADD  R4, R4, #1
            ADD  R4, R4, R2
            BRN  NOCHANGE         ;Initial r1=17,r2=0
            LD   R4, DIGIT0
            ADD  R4, R4, R5
            ADD  R1, R1, R4       ;r1=r1+r7
            NOT  R4, R4
            ADD  R4, R4, #1
            ADD  R2, R4, R2       ;r2=r2-r7
            BRNZP LOOP20
;
NOCHANGE    AND  R2, R2, #0
            AND  R1, R1, #0
            ADD  R1, R1, #15
            ADD  R1, R1, #2
            BRNZP LOOP20            
;
LOOP20      LD   R4, DOT         ;PRINT
            AND  R0, R0, #0
            ADD  R0, R0, R4
            AND  R3, R3, #0
            ADD  R3, R3, R1
            BRZ  NEXTM
    LOOPL   OUT
            ADD  R3, R3, #-1
            BRNP LOOPL
    NEXTM   AND  R0, R0, #0
            ADD  R0, R0, R6
            AND  R3, R3, #0
            ADD  R3, R3, #3
    LOOPM   OUT
            ADD  R3, R3, #-1
            BRNP LOOPM
    NEXTR   LD   R4, DOT
            AND  R0, R0, #0
            ADD  R0, R0, R4
            AND  R3, R3, #0
            ADD  R3, R3, R2
            BRZ  NEXT
    LOOPR   OUT
            ADD  R3, R3, #-1
            BRNP LOOPR
    NEXT    AND  R7, R7, #0
            AND  R0, R0, #0    ;\n
            ADD  R0, R0, #10                
;
    DELAY   ST   R1, SAVER1
            LD   R1, COUNT
    LOOP    ADD  R1, R1, #-1
            BRnp LOOP
            LD   R1, SAVER1
;
            OUT
            BRNZP JUDGE
;            
COUNT       .FILL #12560
SAVER1      .BLKW #1
DIGIT0      .FILL #-48
DOT         .FILL #46
INITIAL     .FILL #97
;
            .END