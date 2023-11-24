#####英文单词：
- transistors 晶体管
- microprocessors 微处理机
- deconstruct 解构（抽象的反义）
- central processing unit (CPU)
- interface 接口
- bit vector 位向量
- MOS metal-oxide semiconductor金属氧化物半导体
- asynchronous 异步的
- abbreviation 缩写
- Sequential 顺序式
- Iterative 迭代式
- mnemonic 助记符
- Subroutines 子程序
- Factorial 阶乘


##unit1
###1、Two Recurring Themes（重复出现主题）：
    The two themes are (a) the notion of abstraction and 
    (b) the importance of not separating in your mind the notions of hardware and software.
####(a) abstraction：The power of abstraction allows us to “usually” operate at a level where wedo not have to think about the underlying layers all the time.
1. Productivity enhancer 
2. more efficient
3. deal with a situation at a higher level 
4. not get bogged down in the detail 
5. There is an underlying assumption to this, however: when everything aboutthe detail is just fine.
####(b) hardware and software：mastering both hardware and software


###2、 A Computer System
    ENIAC -->  Burroughs A series --> desktops --> laptops --> smartphones

###3、Two Very Important Ideas
####(a) All computers can do exactly the same things. 
####(b) It is necessary to transform our problem from the language of humans to the voltages that influence the flow of electrons.

###4、Computers as Universal Computational Devices
    Computer scientists believe that anything that can be computed, can be computed by a computer provided it has enough time and enough memory.
Turing proposed in 1937 that all computations could be carried out by a particular kind of machine, which is now called a Turing machine.（did not actually build one）

###5、Levels of transformation
####Problem
    Natural language is filled with ambiguity
####Algorithms
    An algorithm is a step-by-step procedure that is guaranteed to terminate, such that each step is precisely stated and can be carried out by the computer.
- definiteness: describe the notion that each step is ==precisely stated==.
- effective computability: describe the notion that each step can be ==carried out by a computer==.
- finiteness: describe the notion that the procedure ==terminates==.
####Language
    The next step is to transform the algorithm into a computer program in one of the programming languages that are available.
    Programming languages are “mechanical languages.”
    There is generally one such low-level language for each computer which is called the assembly language.
####Machine (ISA) Architecture
    The next step is to translate the program into the instruction set of the particular computer that will be used to carry out the work of the program.
(ISA) is the complete specification(完整规范) of the interface between ==programs== that have been written and the underlying computer ==hardware== that must carry out the work of those programs.
-  the ISA of a computer specifies the interface between the computer program directing the computer hardware and the hardware carrying out those directions.
  1. ==opcode==：what operations the computer can perform and where to get the data needed to perform those operations.
  2. The term operand is used to describe individual data values.
   -  The ISA specifies the acceptable representations for operands. They are called ==data types==.（A data type is a representation of an operand）
   -  The ISA specifies the mechanisms that the computer can use to figure out where the operands are located. These mechanisms are called ==addressing modes==.
   -  The ISA also specifies the number of unique locations that comprise the computer’s memory and the number of individual 0s and 1s that are contained in each
location.
####Microarchitecture
    The next step is the implementation of the ISA, referred to as its microarchitecture.
A microstructure can only implement one ISA. But an ISA can be implemented on a variety of microstructures.
####Circuits
    combine basic operations to realize microarchitecture
####Devices
     each basic logic circuit is implemented in accordance with the requirements of the particular device technology used.
CMOS & PMOS

###6、hw
![Alt text](image.png)

---

##unit2 Bits, Data Types, andOperations
###1、Data types
![Alt text](image-1.png)
###2、Operations
- DeMorgan’s Law. 
  ![Alt text](image-3.png)
###3、floating point data type
The 32-bit floating point data type.
![Alt text](image-4.png)
N = (?1)^S^ × 1. fraction × 2^exponent-127^, 1 ≤ exponent ≤ 254
e.g.1 00111101100000000000000000000000 = +1.0...0 · 2^-4^
e.g.2![Alt text](image-5.png)

- The smallest number that can be represented in ==normalized== form is
  N = 1.00000000000000000000000 × 2^-126^
- The biggest number that can be represented in ==normalized== form is
  N = 1.11111111111111111111111 × 2^127^
- subnormal numbers cannot be represented in normalized form.(指数为00000000 用于表示非常靠近0的数字) 
  N = (-1)^S^ × 0. fraction × 2^-126^
- The largest ==subnormal== number is
N = 0.11111111111111111111111 × 2^-126^
- The smallest ==subnormal== number is
N = 0.00000000000000000000001×2^-126^
- when exponent equals to 1111 1111 and fraction is 000...000 , then it means ==infinity==(无穷大)
- when exponent equals to 1111 1111 and fraction is ==not== 000...000 , then it means ==NaN==
![Alt text](image-16.png)
  
---

##unit3 Digital Logic Structures
###1、The Transistor
-  NMOS
![Alt text](image-6.png)
  the gate of the N-type transistor is supplied with 1.2 volts, the connection from source to drain acts like a piece of wire.(1代表gate连通，0代表断开)
  
- PMOS (0代表gate连通，1代表断开)
![Alt text](image-8.png)

- ==CMOS== circuits contain both PMOS & NMOS
1. The NOT Gate(inverter):
![Alt text](image-9.png)

2. NOR
![Alt text](image-10.png)

3. OR
![Alt text](image-11.png)

**! ! when we connect a P-type transistor to ground or an N-type transistor to 1.2 volts, because of the electrical characteristics of the transistors, we get what is usually referred to as a transmission voltage of approximately 0.5 volts across the transistor.**
![Alt text](image-13.png)

4. NAND & AND
![Alt text](image-14.png)

###2、Combinational Logic Circuits
1. Decoder：decoders have n inputs and 2n outputs. 
exactly one output is 1 for each possible input pattern

![Alt text](image-15.png)

2. Mux: a mux consists of 2n inputs and n select lines
![Alt text](image-17.png)

3. Adder: 
![Alt text](image-18.png)
![Alt text](image-19.png)
**in the rightmost circuit, S0 and C1 depend only
on two inputs, A0 and B0. Since that circuit depends on only two inputs, it has been referred to as a half adder. Since the other circuits depend on all three inputs, they are referred to as full adders.**

'
4. The Programmable Logic Array (PLA)
![Alt text](image-20.png)

5.  Logical Completeness: 
   Any logic function can be implemented, provided that enough AND, OR, and NOT gates are available.
- NAND gate is logically completed:
![Alt text](image-21.png)

###3、Basic Storage Elements
####The R-S Latch（锁存器）
![Alt text](image-22.png)
- as long as the inputs S and R remain 1, the state of the circuit will not change.
  
    |R|S|锁存器|
    |:---:|:---:|:---:|
    1|1|not change
    1|0|set to 1
    0|1|set to 0
    0|0|not allowed

#### The Gated D Latch
![Alt text](image-23.png)
- Thus, the R-S latch is set to 1 or 0 according to whether D is 1 or 0.

![Alt text](image-30.png)

###4、The Concept of Memory
####address space：
We refer to the total number of uniquely identifiable locations as the memory’s
address space.
####addressability：
The number of bits stored in each memory location is the memory’s addressability.
- A 22-by-3-Bit Memory ： the memoryhas an address space of four locations and an addressability of three bits.
![Alt text](image-24.png)
![Alt text](image-26.png)

- With write enable (WE) also asserted, the three bits D[2:0] can be written into the three gated
latches corresponding to that word line.

![Alt text](image-31.png)

###5、Sequential Logic Circuits：
     ·These structures base their decisions not only on the **input values now present**, 
     but also on **what has happened before**. 
     ·They contain storage elements that allow them to keep track of prior history information.
####The Synchronous Finite State Machine
==asynchronous==：there is no fixed amount of time between successive inputs to the finite state machine.(连续输入之间没有固定时间量)
- We say A Very Old Soft Drink Machine ，A Tic-Tac-Toe Machine are asynchronous（异步的） because there is nothing synchronizing when each state transition must occur.
  
we say that computers are synchronous because the state transitions take place, one after the other, at identical fixed units of time.

####The Clock
    A synchronous finite state machine transitions from its current state to its next state after an identical fixed interval of time. 
    Control of that synchronous behavioris in part the responsibility of the clock circuit.

####A Problem with Gated Latches as Storage Elements
That is, we do not want the input to the storage elements to take effect until the end of the current clock cycle.
![Alt text](image-27.png)
![Alt text](image-28.png)

###6、hw
![Alt text](image-29.png)
![Alt text](image-33.png)
![Alt text](image-34.png)
![Alt text](image-35.png)

###7、Pre_LC3
![Alt text](image-32.png)

##unit4 The von Neumann Model
###1、Basic Components
1. A computer program consists of a set of instructions, each specifying a welldefined piece of work for the computer to carry out.
2. The von Neumann model consists of five
parts: ==memory, a processing unit, input, output, and a control unit.==
- memory： 
  place the ==address== of thatlocation in the memory’s address register (MAR) and then interrogate（询问） the computer’s memory. The ==information== stored in the location having that address will be placed in the memory’s data register (MDR).
- processing unit：
  The ALU normally processes data elements of a ==fixed size== referred to as the word length of the computer. The data elements are called ==words==； The most common form of temporary storage is a set of registers.
- Input and Output
- Control Unit: 
the control unit has an instruction register to contain that instruction; control unit has a register that contains the next instruction’s address (pc)

###2、The LC-3: An Example von Neumann Machine
![Alt text](image-36.png)

####Instruction:
- Operate instructions operate on data.(ADD AND NOT)
- Data movement instructions move information from the processing unit to and from memory and to and from input/output devices.(LD ST)
- Control instructions are necessary for altering the sequential processing of instructions.(BR JMP TRAP)

####The Instruction Cycle：
- FETCH： The FETCH phase obtains the next instruction from memory and loads it into the instruction register (IR) of the control unit.
  ![Alt text](image-38.png)
  ![Alt text](image-39.png)
- DECODE： Input is the four-bit opcode IR [15:12]. The output line asserted is the one corresponding to the opcode at the input.
- EVALUATE ADDRESS ：This phase computes the address of the memory location that is needed to process the instruction.（LD和ST相关指令需要）
- FETCH OPERANDS （reading memory source oprands）
- EXECUTE ： This phase carries out the execution of the instruction. In the ADD example, this phase consisted of the step of performing the addition in the ALU. In the JMP example，this executes pc.
- STORE RESULT (store the result in the destination register or memory)
####Control of the Instruction Cycle:
The instruction cycle is controlled by a ==synchronous== finite state machine.
![Alt text](image-40.png)

###3、hw
![Alt text](image-41.png)
==LD==:
![Alt text](image-74.png)
==LDR==：
![Alt text](image-75.png)
##unit5 LC3
- word-addressable: we refer to 16 bits as one word, and the LC-3 is 2^16^ · 16 bits.
- The instruction set is defined by its set of
==opcodes, data types, and addressing modes==. The addressing modes determine where the operands are located. The data type is the representation of the operands in 0s and 1s.
- The LC-3 ISA has 15 instructions, each identified by its unique ==opcode==.
- Every opcode will interpret the bit patterns of its operands according to the ==data type== it is designed to support.(2’s complement integers)
- The LC-3 supports five ==addressing modes==: **immediate** (or literal), **register**, and three memory addressing modes: **PC-relative**, **indirect**, and **Base+offset**.
-  Condition Codes: N Z P
![Alt text](image-42.png)
![Alt text](image-43.png)

###1、Operate Instructions
#### ADD, AND, and NOT
![Alt text](image-44.png)
![Alt text](image-53.png)
#### LEA
    DR = PC? + SEXT(PCoffset9)
![Alt text](image-45.png)
###2、Data Movement Instructions
####① PC-Relative Mode：LD and ST
    DR = mem[PC + SEXT(PCoffset9)] （LD）
![Alt text](image-46.png)
####②  Indirect Mode：LDI and STI
    DR = mem[mem[PC + SEXT(PCoffset9)]];
![Alt text](image-47.png)
####③ Base+offset Mode：LDR and STR
    DR = mem[BaseR + SEXT(offset6)]
![Alt text](image-48.png)
###3、Control Instructions
#### Conditional Branches：BR
     operate instructions (ADD, AND, NOT) 
     and load instructions (LD, LDI, LDR) 
     change the conditional code
     
     During the EXECUTE phase of the BR instruction cycle, 
     the processor examines the condition codes
![Alt text](image-49.png)

    if ((n AND N) OR (z AND Z) OR (p AND P)) 
    PC = PC + SEXT(PCoffset9);
#### JMP and RET
    PC = BaseR
    ·JMP R2 ; PC ← R2
    ·RET ; PC ← R7
#### JSR(R)
![Alt text](image-50.png)

####另外RTI
    RTI is the last instruction in both interrupt and trap service routines and returns control to the program that was running.
####另外TRAP
    If the the program is executing in User mode, the User Stack Pointer must be saved and the System Stack Pointer loaded.
![Alt text](image-51.png)

###4、Basic Components of the Data Path
![Alt text](image-36.png)
#### BUS
    transfer up to 16 bits of information
#### Memory
    MAR  MDR
#### The ALU and the Register File
    The results of an ALU operation are (a) a result that is stored in one of the registers, and (b) the three single-bit condition codes.
#### The PC and the PCMUX
    from pc_incremented or PC+PCoffset (this addition takes place in the special adder and not in the ALU) or bus
####  The MARMUX
    two sources will supply the MAR with the appropriate address during the execution of a load, a store, or a TRAP instruction.

###5、The Instruction Cycle Specific to the LC-3
    e.g. 0110 011 010 000100
          LDR  R3  R2    4
####1. fetch：
第一周期pc加载到MAR中，并且pc自增
第二周期访存，指令加载到MDR中
第三周期MDR的内容被加载到指令寄存器（IR）中
####2. decode：
第四周期IR中的内容被解码产生控制信号
####3. evaluate address：
第五周期R2的内容和IR的符号扩展位[5：0]被添加并通过MARMUX传到总线。（ADDR1MUX选择SR1OUT，ADDR2MUX从正确的源中选择第二个）
####4. operand fetch:
下一个周期中（或在多个周期中），通过总线传来的地址给到MAR，该地址上的值将被加载到MDR中
####5. execuate：
不需要
####6. store result：
在最后一个周期中，MDR的内容被控到总线上，从全局总线中它被加载到R3中，并设置NZP条件代码

###==DataPath== 见ppt

##unit6 Problem Solving
###1、constructure
![Alt text](image-54.png)
###2、LC-3 simulator 
1. Write values into memory locations and into registers.
2. Execute instruction sequences in a program.
3. Stop execution when desired.
4. Examine what is in memory and registers at any point in the program.
-  Set Values
-  Execute Sequences ：run, step, and set breakpoints
-  Display Values ： examine the results

##unit7 Assenmbly language
    In fact, it is usually the case that each ISA has only one assembly language
###1、An Assembly Language Program
Label(symbolic addresses) Opcode Operands ; Comment

    e.g AGAIN ADD R3, R3, R2
              AND R3, R3, #0
              LD  R2, NUMBER
              BRp AGAIN
###2、Pseudo-Ops (Assembler Directives) 伪操作系统（汇编程序指令）
###### .ORIG： place the first LC-3 ISA instruction
###### .FILL： set aside the ==next== location in the program and initialize it with the value of the operand
###### .BLKW： set aside some number of ==sequential== memory locations
###### .STRINGZ： initialize a sequence of n+1 memory locations，the last word is x0000
          .ORIG x3010
    HELLO .STRINGZ "Hello, World!"
###### .END
###3、 Assembly Process
1. **The First Pass: Creating the Symbol Table**
the symbol table is simply a correspondence of symbolic names with their 16-bit memory addresses.
2. **The Second Pass: Generating the Machine Language Program**
go through the assembly language program a second time, line by line.

###4、hw
![Alt text](image-52.png)

##unit8 Data Structures
###Subroutines：
####1、Saving and Restoring Registers
- we use the term caller save if the calling program handles the problem. We use the term callee save if the called program handles the problem.
####2、Library Routines 库
![Alt text](image-55.png)

###Stack：LIFO
    We use R6 to contain the address of the top of the stack
![Alt text](image-56.png)
**Note that those two elements that were popped are still present in memory locations**

    PUSH    ADD R6,R6,#-1
            STR R0,R6,#0

    POP     LDR R0,R6,#0
            ADD R6,R6,#1

```
Underflow：
POP     AND R5,R5,#0
        LD R1,EMPTY
        ADD R2,R6,R1
        BRz Failure
        LDR R0,R6,#0
        ADD R6,R6,#1
        RET
Failure ADD R5,R5,#1
        RET
EMPTY   .FILL xC000 ; EMPTY <-- -x4000
```
```
overflow:
PUSH    AND R5,R5,#0
        LD R1,MAX
        ADD R2,R6,R1
        BRz Failure
        ADD R6,R6,#-1
        STR R0,R6,#0
        RET
Failure ADD R5,R5,#1
        RET
MAX     .FILL xC005 ; MAX <-- -x3FFB
;以上图为上下界
```

###Recursion, a Powerful Technique When Used Appropriately: pdf 292

###Queue： FIFO pdf 299 
    Remove from Front, Insert at Rear
![Alt text](image-57.png)
#####Wrap-Around:
The code for insert is similar. If REAR contains x8005, we need to set R4 to x8000 before we can insert an element at the rear of the queue.
```
        LD      R2, LAST
        ADD     R2,R4,R2
        BRnp    SKIP_1
        LD      R4,FIRST
        BR      SKIP_2
SKIP_1  ADD R4,R4,#1
SKIP_2  STR R0,R4,#0 ; R0 gets the front of the queue
        RET
LAST    .FILL 7FFB ; LAST contains the negative of 8005
FIRST   .FILL x8000
```

#####How Many Elements Can We Store in a Queue?
 allow a queue to store only ==n-1== elements if space for n elements has been allocated.

![Alt text](image-58.png)

#####underflow
```
if FRONT = REAR, the queue is empty. Our code to test for underflow is

            AND     R5,R5,#0 ; Initialize R5 to 0
            NOT     R2,R3
            ADD     R2,R2,#1 
            ADD     R2,R2,R4
            BRz     UNDERFLOW
; code to remove the front of the queue and return success.
UNDERFLOW   ADD R5,R5,#1
            RET
```
#####overflow
```
first increment the REAR pointer. If that causes FRONT = REAR, 
then the queue already contains n-1 elements, which means it is full

            AND     R5,R5,#0 ; Initialize R5 to 0
           *ADD     R4,R4,#1
            NOT     R2,R3
            ADD     R2,R2,#1 
            ADD     R2,R2,R4
            BRz     UNDERFLOW
; code to remove the front of the queue and return success.
UNDERFLOW   ADD R5,R5,#1
            RET
```
###hw
![Alt text](image-59.png)

##unit9 I/O
###1、Privilege, Priority, and the Memory Address Space
#### Privilege：
the right to do something, such as execute a particular instruction or access a particular memory location

        We say a program is executing in Supervisor mode to indicate privileged, or User mode to indicate unprivileged
#### Priority：
the urgency of a program to execute
#### The Processor Status Register (PSR)
PSR[15]=0 means supervisor privilege, and PSR[15]=1 means unprivileged. Bits [10:8] specify the priority level (PL) of the program. The highest priority level is 7 (PL7), the lowest is PL0. The PSR also contains the current values of the condition codes
![Alt text](image-60.png)
####Organization of Memory：
![Alt text](image-61.png)

    When privilege changes, for example, from Supervisor mode to User mode, the SP is stored in Saved SSP, and the SP is loaded from Saved USP
###2、Input and Output
    Even the simplest I/O devices usuallyneed at least two registers: one to hold the data being transferred between the device and the computer, （数据）
    and one to indicate status information about the device. （状态信息）
####Memory-Mapped I/O vs. Special I/O Instructions：
    Some computers use special input and output instructions. 
    Most computers prefer to use the same data movement instructions that are used to move data in and out of memory.
- the I/O device registers are mapped to a set of addresses
that are allocated to I/O device registers rather than to memory locations. Hence the name memory-mapped I/O.其中在LC3中，Addresses xFE00 to xFFFF are reserved for input/output device registers.
####Asynchronous vs. Synchronous:
    Most interaction between a processor and I/O is asynchronous. To control processing in an asynchronous world requires some protocol or handshaking mechanism
####Interrupt-Driven vs. Polling：
    The ASCII code is in the input device register. You need to read it.” This is called interrupt-driven I/O, where the keyboard controls the interaction。
    √ This second type of interaction when the processor is in charge is called polling, since the ready bit is polled by the processor, asking if any key has been struck
- If input/output is controlled by the processor (i.e., via polling), then a program can repeatedly test KBSR[15] until it notes that the bit is set.
- In this way, KBSR[15] provides the mechanism to guarantee that each key typed will be loaded exactly ==once==.
#### Input from the Keyboard ：
    keyboard data register (KBDR) xFE02 ；bits [7:0] are used for the data, and bits [15:8] contain x00
    and the keyboard status register (KBSR). xFE00 ；bit [15] contains the synchronization mechanism, that is, the ready bit.
    
![Alt text](image-64.png)
![Alt text](image-62.png)
####Output to the Monitor：
    DDR is assigned address xFE06. DSR is assigned address xFE04.
![Alt text](image-63.png)

###3、Implementation of Memory-Mapped I/O, Revisited
![Alt text](image-65.png)

###4、Operating System Service Routines (LC-3 Trap Routines)
####The Trap Mechanism：
- A set of service routines
- A table of the starting addresses
- The TRAP instruction：
  1. ==The PSR and PC are both pushed onto the system stack==. Since the PC was incremented, the return ==linkage== is automatically saved in the PC
    （如果处于用户模式，则堆栈指针R6指向用户堆栈。在将PSR和PC推到系统堆栈之前，R6的当前内容必须存储在保存的USP中，保存的SSP的内容必须加载到R6中）
  2. PSR[15]被设置为0，因为服务例程将需要主管特权才能执行。PSR[10：8]保持不变，因为TRAP例程的优先级与请求它的程序的优先级相同
  3. 8位的陷阱向量被零扩展到16位，以形成一个与陷阱向量表中的一个位置相对应的地址。对于陷阱向量x23，该地址是x0023。内存位置x0023包含x04A0，即TRAP x23服务例程的起始地址。PC上加载了x04A0，完成了指令周期。
- A linkage back to the user program.
  
####The RTI Instruction: To Return Control to the Calling Program
    将系统堆栈上的前两个值弹出到PC和PSR中
    一旦PSR从系统堆栈中弹出，就必须检查PSR[15]，以查看在执行TRAP指令时，处理器是在用户模式或监督模式下运行。
#### A Trap Routine for Halting the Computer：
    In the LC-3, the RUN latch is bit [15] of the Master Control Register (MCR), which is memory-mapped to location xFFFE

####recall：
![Alt text](image-66.png)
![Alt text](image-67.png)
###5、Interrupts and Interrupt Driven I/O
    polling requires the processor to waste a lot of time spinning its wheels, re-executing again and again the LDI and BR instructions until the ready bit is set.
    Interrupt-driven I/O allows the processor to spend its time doing what is hopefully useful work, executing some other program perhaps, until it is notified that some I/O device needs attention
#### There are two parts to interrupt-driven I/O:
1. the mechanism that enables an I/O device to interrupt the processor, and
2. the mechanism that handles the interrupt request.
#####Part I: Causing the Interrupt to Occur 
- Several things must be true for an I/O device to actually interrupt the program that is running:
1. The I/O device must want service. (It is the ready bit of the KBSR or the DSR)
2. The device must have the right to request the service. (这是中断启用位，它可以由处理器设置或清除.在大多数I/O设备中该中断启用（IE）位是设备状态寄存器的一部分。在图KBSR和DSR中，IE位是[14]位。If the interrupt enable bit (bit [14]) is clear, it does not matter whether the
ready bit is set)
![Alt text](image-68.png)
3. The device request must be more urgent than what the processor is currently doing.
- The INT Signal:
To stop the processor from continuing execution of its currently running program and service an interrupt request, the INT signal must be asserted.(If the PL of that request is higher than the PL of the currently executing program, the INT signal is asserted.)
中断在完成这条指令后进行：since the state of the computer is the state created by the completion of the current instruction
#####Part II: Handling the Interrupt Request
1. Initiate the interrupt (1: Interrupt signal is detected 1: Program A is put into suspended animation 1: PC is loaded with the starting address of Program B)

        Save the State of the Interrupted Program 所有通用寄存器的内容、PC和PSR
        Load the State of the Interrupt Service Routine 加载中断服务例程的PC和PSR
2. Service the interrupt (2: Program B starts satisying I/O device’s needs 2: Program B continues satisfying I/O device’s needs 2: Program B continues satisfying I/O device’s needs 2: Program B finishes satisfying I/O device’s needs)
3. Return from the interrupt We will discuss each.(3: Program A is brought back to life)
###### 任何具有更高优先级且位于正在运行的程序外部的事件都可能中断计算机。它通过提供INT信号、INTV向量和优先级来实现这一点。
####exception：
the LC-3 ISA specifies three exception conditions: privilege mode violation, illegal opcode, and access control violation (ACV). The privilege mode violation occurs if the processor attempts to execute the RTI instruction while running in User mode. The illegal opcode exception occurs if the processor attempts to execute an instruction having the unused opcode (bits [15:12] = 1101). The ACV exception occurs if the processor attempts to access privileged memory (i.e., a memory location in system space or a device register having an address from xFE00 to xFFFF while running in User mode).
![Alt text](image-71.png)
###6、hw
![Alt text](image-69.png)
![Alt text](image-70.png)

###appendix：
![Alt text](image-76.png)
![Alt text](image-72.png)
![Alt text](image-73.png)

