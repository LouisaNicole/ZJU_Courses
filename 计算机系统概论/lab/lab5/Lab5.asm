            .ORIG x3000
            LD   R6, N
            ADD  R6, R6, #-1    ;Stack_base x3FFF
            LDI  R2, M
            LDI  R4, N
            AND  R5, R5, #0
MULTIPLY    ADD  R2, R2, #0
            BRZ  CALCULATE
            ADD  R5, R5, R4
            ADD  R2, R2, #-1
            BRNZP MULTIPLY
CALCULATE   ST   R5, LOOPMN     ;calculate n*m
            ST   R5, COUNT      ;calculate n*m to record the count
;
START       LD   R0, NUMBER     ;get the initial ADDRESS
            LD   R3, NUMBER     ;get the initial ADDRESS
            LDI  R1, NUMBER     ;get the initial DATA
            JSR  FIND_NEXT      ;first recursive function
            ADD  R2, R3, #0
            ADD  R2, R2, #1
            ST   R2, NUMBER
            LD   R2, COUNT      ;if count==0, end the program
            BRZ  DISPLAY
            BRNZP START           
;
FIND_NEXT   ADD  R6, R6, #-1
            STR  R1, R6, #0     ;store the data
            ADD  R6, R6, #-1
            STR  R3, R6, #0     ;store the address
            ADD  R6, R6, #-1
            STR  R7, R6, #0     ;store the return pc
            ADD  R3, R0, #0     ;record the address and not change the old address
;
CHECK_U     LD   R2, FLAG
            NOT  R2, R2
            ADD  R2, R2, #1
            ADD  R4, R3, R2
            LDI  R2, M
            NOT  R2, R2
            ADD  R2, R2, #1
            ADD  R4, R4, R2
            BRN  CHECK_R        ;the first line has no up number
            ADD  R5, R3, R2     ;up_address
            LDR  R5, R5, #0     ;R5=up_data
            LDR  R4, R3, #0     ;R4=current_data
            NOT  R4, R4
            ADD  R4, R4, #1
            ADD  R5, R5, R4
            BRZP CHECK_R        ;NOT BIGGER
            ADD  R0, R3, R2
            LD   R2, LENTH
            ADD  R2, R2, #1
            ST   R2, LENTH      ;next jump->lenth++
            JSR  FIND_NEXT
            LD   R2, LENTH      ;return->lenth--
            ADD  R2, R2, #-1
            ST   R2, LENTH
;
CHECK_R     LD   R2, FLAG
            NOT  R2, R2
            ADD  R2, R2, #1
            ADD  R4, R3, R2
            ADD  R4, R4, #1
            LDI  R2, M
            NOT  R2, R2
            ADD  R2, R2, #1
LOOP_R      ADD  R4, R4, R2
            BRZ  CHECK_D        ;this line has no right number
            ADD  R4, R4, #0
            BRP  LOOP_R       
            ADD  R5, R3, #1     ;right_address
            LDR  R5, R5, #0     ;R5=right_data
            LDR  R4, R3, #0     ;R4=current_data
            NOT  R4, R4
            ADD  R4, R4, #1
            ADD  R5, R5, R4
            BRZP CHECK_D        ;NOT BIGGER
            ADD  R0, R3, #1  
            LD   R2, LENTH
            ADD  R2, R2, #1
            ST   R2, LENTH 
            JSR  FIND_NEXT
            LD   R2, LENTH
            ADD  R2, R2, #-1
            ST   R2, LENTH
;
CHECK_D     LD   R2, FLAG
            NOT  R2, R2
            ADD  R2, R2, #1
            ADD  R4, R3, R2
            LD   R2, LOOPMN
            NOT  R2, R2
            ADD  R2, R2, #1
            ADD  R4, R4, R2
            LDI  R2, M
            ADD  R4, R4, R2
            BRZP CHECK_L        ;this line has no down number
            ADD  R5, R3, R2     ;down_address
            LDR  R5, R5, #0     ;R5=down_data
            LDR  R4, R3, #0     ;R4=current_data
            NOT  R4, R4
            ADD  R4, R4, #1
            ADD  R5, R5, R4
            BRZP CHECK_L        ;NOT BIGGER
            ADD  R0, R3, R2
            LD   R2, LENTH
            ADD  R2, R2, #1
            ST   R2, LENTH   
            JSR  FIND_NEXT 
            LD   R2, LENTH
            ADD  R2, R2, #-1
            ST   R2, LENTH          
;
CHECK_L     LD   R2, FLAG
            NOT  R2, R2
            ADD  R2, R2, #1
            ADD  R4, R3, R2
            BRZ  JUDGE          ;this line has no left number
            LDI  R2, M
            NOT  R2, R2
            ADD  R2, R2, #1
LOOP_L      ADD  R4, R4, R2
            BRZ  JUDGE          ;this line has no left number
            ADD  R4, R4, #0
            BRP  LOOP_L       
            ADD  R5, R3, #-1    ;left_address
            LDR  R5, R5, #0     ;R5=left_data
            LDR  R4, R3, #0     ;R4=current_data
            NOT  R4, R4
            ADD  R4, R4, #1
            ADD  R5, R5, R4
            BRZP JUDGE 
            ADD  R0, R3, #-1  
            LD   R2, LENTH
            ADD  R2, R2, #1
            ST   R2, LENTH 
            JSR  FIND_NEXT
            LD   R2, LENTH
            ADD  R2, R2, #-1
            ST   R2, LENTH
;
JUDGE       LD   R2, NUMBER
            ADD  R4, R3, #0
            NOT  R4, R4
            ADD  R4, R4, #1
            ADD  R2, R2, R4     ;if R3==initial address
            BRNP NEXT           ;return again to find the initial R3
            LD   R2, COUNT      ;COUNT--(be used to judge the next point) 
            ADD  R2, R2, #-1
            ST   R2, COUNT
    NEXT    LD   R2, LENTH      ;whether the lenth is bigger than max 
            LD   R4, MAX
            NOT  R2, R2
            ADD  R2, R2, #1
            ADD  R4, R4, R2
            BRP  RESTORE        ;return and pop
            LD   R2, LENTH
            ST   R2, MAX
;
RESTORE     ADD  R0, R3, #0
            LDR  R7, R6, #0 
            ADD  R6, R6, #1
            LDR  R3, R6, #0 
            ADD  R6, R6, #1
            LDR  R1, R6, #0
            ADD  R6, R6, #1
            RET
;
DISPLAY     LD   R2, MAX
            HALT
;
N           .FILL x4000
M           .FILL x4001
NUMBER      .FILL x4002
FLAG        .FILL x4002
LENTH       .FILL x0001
MAX         .FILL x0000
LOOPMN      .FILL x0000
COUNT       .FILL x0000
            .END
;
            .ORIG x4000
            .FILL #2 ; N
            .FILL #3 ; M
            .FILL #89 ; the map
            .FILL #89
            .FILL #89
            .FILL #89
            .FILL #89
            .FILL #89
            
            .END