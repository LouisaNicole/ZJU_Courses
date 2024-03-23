        .ORIG x3000
INIT1   LDI  R1,ADDR1       ;Get the str1's address
        AND  R3,R3,#0       ;R3 is the lenth of str1
loopR1  LDR  R2,R1,#0       ;Get the str1's first character(R2)
        ADD  R2,R2,#0
        BRz  INIT2          ;End str1
        ADD  R1,R1,#1
        AND  R5,R5,#0
        ADD  R5,R5,#-16
        ADD  R5,R5,#-16     
        ADD  R5,R5,R2
        BRz  loopR1         ;Skip the space enter  
        ADD  R3,R3,#1    
        BRnzp loopR1   
;
INIT2   LDI  R1,ADDR2       ;Get the str2's address
        AND  R4,R4,#0       ;R4 is the lenth of str2
loopR2  LDR  R2,R1,#0       ;Get the str1's first character
        ADD  R2,R2,#0
        BRz  LENTH          ;End str2
        ADD  R1,R1,#1 
        AND  R5,R5,#0
        ADD  R5,R5,#-16
        ADD  R5,R5,#-16     
        ADD  R5,R5,R2
        BRz  loopR2         ;Skip the space enter  
        ADD  R4,R4,#1   
        BRnzp loopR2
;
LENTH   NOT  R3,R3
        ADD  R3,R3,#1
        ADD  R4,R4,R3
        BRnp OUTNO          ;Length is not equal, failed.
;
        AND  R3,R3,#0
        AND  R1,R1,#0        
        ADD  R1,R1,#13      ;26 lowercase letters.
        ADD  R1,R1,#13
        LEA  R2,COUNT       ;An array to store the numbers of letters.
        
INIT    STR  R3,R2,#0       ;Initialize the counter array to 0.
        ADD  R2,R2,#1
        ADD  R1,R1,#-1
        BRnp INIT
;
        LDI  R1,ADDR1       ;Get the str1's address.
        LEA  R2,COUNT
CNTR1   LDR  R3,R1,#0       ;R3 is the character in str1.
        BRz  END1
        ADD  R1,R1,#1
        ADD  R3,R3,#-16     ;Convert character to number.
        ADD  R3,R3,#-16
        BRz  CNTR1          ;Space
        ADD  R3,R3,#-16
        ADD  R3,R3,#-16
        ADD  R3,R3,#-16
        ADD  R3,R3,#-16
        ADD  R3,R3,#-1
        BRzp SMALL1
        ADD  R3,R3,#15
        ADD  R3,R3,#15
        ADD  R3,R3,#2
;
SMALL1  ADD  R3,R3,R2       ;Calculate the physical address.
        LDR  R4,R3,#0
        ADD  R4,R4,#1
        STR  R4,R3,#0       ;Records the number of characters.
        LDR  R5,R1,#0
        BRnp CNTR1
;
END1    LDI  R1,ADDR2       ;Get the str2's address.
        LEA  R2,COUNT
CNTR2   LDR  R3,R1,#0       ;R3 is the character in str2.
        BRz  END2
        ADD  R1,R1,#1
        ADD  R3,R3,#-16     ;Convert character to number.
        ADD  R3,R3,#-16
        BRz  CNTR2          ;Space
        ADD  R3,R3,#-16
        ADD  R3,R3,#-16
        ADD  R3,R3,#-16
        ADD  R3,R3,#-16
        ADD  R3,R3,#-1
        BRzp SMALL2
        ADD  R3,R3,#15
        ADD  R3,R3,#15
        ADD  R3,R3,#2
;
SMALL2  ADD  R3,R3,R2       ;Calculate the physical address.
        LDR  R4,R3,#0
        ADD  R4,R4,#-1
        STR  R4,R3,#0       ;Records the number of characters.
        LDR  R5,R1,#0
        BRnp CNTR2
;
END2    AND  R1,R1,#0       ;Initializing the i to 0.
        LEA  R2,COUNT
        AND  R5,R5,#0
;
LOOPCNT ADD  R5,R1,#-13
        ADD  R5,R5,#-13     ;Loop 26 times.
        BRz  JUDGE
        ADD  R3,R1,R2
        ADD  R1,R1,#1
        LDR  R4,R3,#0  
        BRz  LOOPCNT        ;R4!=0 means not a match.
;
JUDGE   AND  R5,R5,#0
        ADD  R5,R1,#-13
        ADD  R5,R5,#-13
        BRnp OUTNO
;
OUTYES  LEA  R0,YES
        PUTS
        HALT
;
OUTNO   LEA  R0,NO
        PUTS
        HALT
;
YES     .STRINGZ "YES"
NO      .STRINGZ "NO"
COUNT   .BLKW 26
ADDR1   .FILL x4000
ADDR2   .FILL x4001
        .END
;
;
        .ORIG x4000
        .FILL str1
        .FILL str2 
str1    .STRINGZ " Dormi tory "
str2    .STRINGZ " dirty rOom "
        .END