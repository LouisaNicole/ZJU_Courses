`include "ExceptStruct.vh"
`include "CSRStruct.vh"
`include "RegStruct.vh"
`include "TimerStruct.vh"
module Core (
    input wire clk,                       /* 鏃堕挓 */ 
    input wire rstn,                       /* 閲嶇疆淇″彿 */ 

    output wire [63:0] pc,                /* current pc */
    input wire [63:0] inst_double,        /* read inst from ram */

    output wire [63:0] address,           /* memory address */
    output wire we_mem,                   /* write enable */
    output wire [63:0] wdata_mem,         /* write data to memory */
    output wire [7:0] wmask_mem,          /* write enable for each byte */ 
    output wire re_mem,                   /* read enable */
    input wire [63:0] rdata_mem,          /* read data from memory */

    input wire if_stall,
    input wire mem_stall,
    output wire if_request,

    // input b_stall,

    // output [1:0] branch,
    // output j,
    // input wait_stall,
    // input fsm_stall,
    // input valid_mem_mmio,
    // input ren_cpu_fsm,
    // input switch_flush,
    
    output wire switch_mode,
    // input wire time_int,
    input TimerStruct::TimerPack time_out,

    output cosim_valid,
    output [63:0] cosim_pc,          /* current pc */
    output [31:0] cosim_inst,        /* current instruction */
    output [ 7:0] cosim_rs1_id,      /* rs1 id */
    output [63:0] cosim_rs1_data,    /* rs1 data */
    output [ 7:0] cosim_rs2_id,      /* rs2 id */
    output [63:0] cosim_rs2_data,    /* rs2 data */
    output [63:0] cosim_alu,         /* alu out */
    output [63:0] cosim_mem_addr,    /* memory address */
    output [ 3:0] cosim_mem_we,      /* memory write enable */
    output [63:0] cosim_mem_wdata,   /* memory write data */
    output [63:0] cosim_mem_rdata,   /* memory read data */
    output [ 3:0] cosim_rd_we,       /* rd write enable */
    output [ 7:0] cosim_rd_id,       /* rd id */
    output [63:0] cosim_rd_data,     /* rd data */
    output [ 3:0] cosim_br_taken,    /* branch taken? */
    output [63:0] cosim_npc,         /* next pc */
    output CSRStruct::CSRPack cosim_csr_info,
    output RegStruct::RegPack cosim_regs,

    output cosim_interrupt,
    output [63:0] cosim_cause
);
    import ExceptStruct::*;
    wire rst=~rstn;

    wire ID_CSR_we,EX_CSR_we,MEM_CSR_we,WB_CSR_we;
    wire [1:0] ID_CSR_ret,EX_CSR_ret,MEM_CSR_ret,WB_CSR_ret;
    wire [1:0] ID_priv,EX_priv,MEM_priv,WB_priv;
    wire [63:0] pc_csr;
    ExceptPack ID_exc,EX_exc,MEM_exc,WB_exc,WB_except_commit;
    initial begin
        ID_exc.except = 0;
        ID_exc.epc = 64'b0;
        ID_exc.ecause = 64'b0;
        ID_exc.etval = 64'b0;
    end
    wire [63:0] satp; 
    CSRModule csrmodule(
        .clk(clk),
        .rst(rst),
        .csr_we_wb(WB_CSR_we),
        .csr_addr_wb(WB_CSR_addr), 
        .csr_val_wb(WB_CSR_val_alu),  
        .csr_addr_id(ID_CSR_addr),
        .csr_val_id(ID_CSR_val),

        .pc_wb(WB_PC),
        .valid_wb(WB_valid_reg),
        .time_out(time_out),
        .csr_ret_wb(WB_CSR_ret),  
        .except_wb(WB_exc),

        .priv(ID_priv), // 3->M 2->H 1->S 0->U
        .switch_mode(switch_mode),
        .inst_wb(WB_INS),
        .csr_we_wb_temp(WB_temp_CSR_we), /////////////////////// 
        .pc_csr(pc_csr), 

        .cosim_interrupt(cosim_interrupt),
        .cosim_cause(cosim_cause),
        .satp(satp),
        .cosim_csr_info(cosim_csr_info)

    );

    wire ID_except_happen,EX_except_happen,MEM_except_happen,WB_except_happen;
    IDExceptExamine id_except(
        .clk(clk),
        .rst(rst),
        .stall(stall_IFID),
        .flush(flush_IFID),
        .pc_id(ID_PC),
        .priv(ID_priv),
        .inst_id(ID_INS),
        .valid_id(ID_valid_reg),
        .except_id(ID_exc),
        .except_exe(EX_exc),
        .except_happen_id(ID_except_happen),
        .is_ecall_id(ID_INS==32'b00000000000000000000000001110011),///////////
        .is_ebreak_id(ID_INS==32'b00000000000100000000000001110011),/////////////
        .illegal_id(1'b0)////////////
    );

    EXExceptExamine ex_except(
        .clk(clk),
        .rst(rst),
        .stall(stall_IDEXE),
        .flush(flush_IDEXE),
        .pc_ex(EX_PC),
        .priv(EX_priv),
        .inst_ex(EX_INS),
        .valid_ex(EX_valid_reg),
        .except_ex(EX_exc),
        .except_mem(MEM_exc),
        .except_happen_ex(EX_except_happen),
        .is_ecall_ex(EX_INS==32'b00000000000000000000000001110011),///////////
        .is_ebreak_ex(EX_INS==32'b00000000000100000000000001110011),/////////////
        .illegal_ex(1'b0)////////////
    );

    MEMExceptExamine mem_except(
        .clk(clk),
        .rst(rst),
        .stall(stall_EXEMEM),
        .flush(flush_EXEMEM),
        .pc_mem(MEM_PC),
        .priv(MEM_priv),
        .inst_mem(MEM_INS),
        .valid_mem(MEM_valid_reg),
        .except_mem(MEM_exc),
        .except_wb(WB_exc),
        .except_happen_mem(MEM_except_happen),
        .is_ecall_mem(MEM_INS==32'b00000000000000000000000001110011),///////////
        .is_ebreak_mem(MEM_INS==32'b00000000000100000000000001110011),/////////////
        .illegal_mem(1'b0)////////////        
    );

    WBExceptExamine wb_except(
        .clk(clk),
        .rst(rst),
        .stall(stall_MEMWB),
        .flush(flush_MEMWB),
        .pc_wb(WB_PC),
        .priv(WB_priv),
        .inst_wb(WB_INS),
        .valid_wb(WB_valid_reg),
        .except_wb(WB_exc),
        .except_last(WB_except_commit),
        .except_happen_wb(WB_except_happen),
        .is_ecall_wb(WB_INS==32'b00000000000000000000000001110011),///////////
        .is_ebreak_wb(WB_INS==32'b00000000000100000000000001110011),/////////////
        .illegal_wb(1'b0)////////////        
    );
    
    // assign pc = !rstn? 0:IF_PC;
    // assign address = !rstn? 0:MEM_alu;              //计算出来的写内存的地址
    // assign we_mem = MEM_signal[20];                 //内存写使能
    // assign re_mem = MEM_INS[6:0]==7'b0000011;       //load指令读使能
    // assign re_mem = rstn;
    // assign wdata_mem = MEM_wdata;
    // assign wmask_mem = MEM_mask;

    // assign IF_INS = inst;
    // assign memory = rdata_mem;
    // assign if_request = ~(EX_branch == 2'b01 | EX_signal[19]);
    // assign if_request = 1'b1;
    

    wire [63:0] data_a,data_b;
    wire [63:0] instruct;
    wire [63:0] memory;
    wire stall_PC,stall_IFID,stall_IDEXE,stall_EXEMEM,stall_MEMWB;
    wire flush_IFID,flush_IDEXE,flush_EXEMEM,flush_MEMWB;

    wire IF_valid_reg,ID_valid_reg,EX_valid_reg,MEM_valid_reg,WB_valid_reg;
    assign IF_valid_reg = ~(b_stall==2'b01 || b_stall==2'b10);

    wire [31:0] IF_INS;
    wire [63:0] IF_PC,IF_PC4,IF_NPC;
    // wire [11:0] IF_CSR_addr;

    // wire [1:0] ID_branch;
    wire [21:0] ID_signal;
    wire [31:0] ID_INS;
    wire [63:0] ID_PC,ID_rd_data,ID_rs1_data,ID_rs2_data,ID_imm,ID_PC4,ID_CSR_val;
    wire [11:0] ID_CSR_addr;

    wire [1:0] EX_branch;
    wire [21:0] EX_signal;
    wire [31:0] EX_INS;
    wire [63:0] EX_PC,EX_rd_data,EX_rs1_data,EX_rs2_data,EX_alu,EX_imm,EX_PC4,EX_wdata,EX_CSR_val,EX_CSR_val_alu;
    wire [7:0] EX_mask;
    wire [11:0] EX_CSR_addr;

    wire [1:0] MEM_branch;
    wire [21:0] MEM_signal;
    wire [31:0] MEM_INS;
    wire [63:0] MEM_PC,MEM_alu,MEM_mem,MEM_wdata,MEM_PC4,MEM_CSR_val_alu;
    wire [11:0] MEM_CSR_addr;
    wire [7:0] MEM_mask;

    wire [1:0] WB_branch;
    wire [21:0] WB_signal;
    wire [31:0] WB_INS;
    wire [63:0] WB_alu,WB_mem,WB_PC4,WB_PC,WB_rd_data,WB_CSR_val_alu;
    wire [11:0] WB_CSR_addr;

    wire flag;
    My_FSM myfsm(
        .clk(clk),
        .if_stall(if_stall),
        .stall(stall_ornot),  // 刚好 ld 完了 b 判断导致ifstall开着出现问题
        .csr_stall(csr_stall_ornot),
        .is_ex_jump(EX_branch == 2'b01 | EX_signal[19]),
        .predict_ex_jump(EX_jump_btb),
        .flag(flag),
        .b_stall(b_stall)
    );

    wire IF_jump_btb;
    wire [63:0] IF_pc_target;
    BranchPrediction branch_prediction(
        .clk(clk),
        .rst(rst),
        .pc_if(IF_PC),
        .jump_if(IF_jump_btb),
        .pc_target_if(IF_pc_target),
        .pc_exe(EX_PC),
        .pc_target_exe(EX_alu),
        .jump_exe(EX_branch == 2'b01), // b跳
        .is_jump_exe(EX_branch == 2'b01 | EX_branch == 2'b10) // b/j指令
    );

    wire [31:0] phy_inst;
    wire if_stall_final;
    wire [63:0] pc_temp;
    IF_MMU mmu_if(
        .clk(clk),
        .rst(rst),
        .switch(switch_mode),
        .satp(satp),
        .priv(ID_priv),
        .IF_pc(IF_PC),
        .IF_ins_pc(IF_INS),
        .b_stall_mmu(b_stall==2'b01 || b_stall==2'b10),
        .b_stall_save(b_stall_save),

        .page_pc(pc_temp),
        .page_addr(inst_double),
        .rvalid(~if_stall),
    
        .IF_ins(IF_INS),
        .if_request(if_request),
        .phy_if_stall(if_stall_final)
    );
    
    reg b_stall_save;
    always @(posedge clk) begin
        if (b_stall==2'b01 || b_stall==2'b10) b_stall_save <= 1'b1;
        else if (satp != 64'b0) b_stall_save <= 1'b0;
        else b_stall_save <= b_stall_save;
    end
    assign pc = ID_priv == 2'b11 ? IF_PC : (b_stall_save ? IF_PC : pc_temp);

    wire stall_ornot,csr_stall_ornot;
    wire [1:0] b_stall;

    RaceController race(
        .switch(switch_mode),
        .stall(stall_ornot),
        .csr_stall(csr_stall_ornot),
        // .temp_stall(temp_stall),
        // .id_except(WB_except_happen),
        // .B_flag(B_flag),
        // .ID_branch(ID_branch),
        // .switch_flush(switch_flush),
        // .valid_mem_mmio(valid_mem_mmio),
        // .ren_cpu_fsm(ren_cpu_fsm),
        // .fsm_stall(fsm_stall),
        // .wait_stall(wait_stall),
        .flag(flag),
        .b_stall(b_stall==2'b01 || b_stall==2'b10),
        .if_stall(if_stall_final),
        .mem_stall(mem_stall_final),
        .EX_decode(EX_signal),
        .EX_branch(EX_branch),
        .stall_PC(stall_PC),          
        .stall_IFID(stall_IFID),
        .stall_IDEXE(stall_IDEXE),
        .stall_EXEMEM(stall_EXEMEM),
        .stall_MEMWB(stall_MEMWB),
        .flush_IFID(flush_IFID),
        .flush_IDEXE(flush_IDEXE),
        .flush_EXEMEM(flush_EXEMEM),
        .flush_MEMWB(flush_MEMWB)
    );

    wire [2:0] FORWARD1,FORWARD2,csr_FORWARD1;
    wire [1:0] csr_FORWARD2;
    // wire [1:0] B_flag;
    wire temp, temp_wb, temp_wb_csr;

    id_temp temp_id(
        .ID_ins(ID_INS),
        .EX_ins(EX_INS),
        .WB_ins(WB_INS),
        .stall(stall_ornot),
        .csr_stall(csr_stall_ornot),
        .temp(temp)
    );

    forward forwarding(
        // .ID_ins(ID_INS),
        .EX_ins(EX_INS),
        .EX_decode(EX_signal),
        // .EX_branch(EX_branch),
        .MEM_ins(MEM_INS),
        .MEM_decode(MEM_signal),
        .WB_ins(WB_INS),
        .WB_decode(WB_signal),
        .WB_temp_ins(WB_temp_INS),
        .WB_temp_decode(WB_temp_signal),
        .forward_signal1(FORWARD1),
        .forward_signal2(FORWARD2),
        .temp_wb(temp_wb),
        .stall(stall_ornot)
        // .B_flag(B_flag)
    );

    forward_csr forwarding_csr(
        // .ID_ins(ID_INS),
        .EX_ins(EX_INS),
        .EX_decode(EX_signal),
        // .EX_branch(EX_branch),
        .MEM_ins(MEM_INS),
        .MEM_decode(MEM_signal),
        .WB_ins(WB_INS),
        .WB_decode(WB_signal),
        .WB_temp_ins(WB_temp_INS),
        .WB_temp_decode(WB_temp_signal),
        .EX_csr_addr(EX_CSR_addr),
        .MEM_csr_addr(MEM_CSR_addr),
        .WB_csr_addr(WB_CSR_addr),
        .WB_temp_csr_addr(WB_temp_CSR_addr),
        .MEM_csr_we(MEM_CSR_we),
        .WB_csr_we(WB_CSR_we),
        .WB_temp_csr_we(WB_temp_CSR_we),
        .forward_csr_signal1(csr_FORWARD1),
        .forward_csr_signal2(csr_FORWARD2),
        .temp_wb_csr(temp_wb_csr),
        .csr_stall(csr_stall_ornot)
        // .B_flag(B_flag)
        // .temp(temp)
    );

    //IF
    
    PC PCC(
        .clk(clk),
        .rst(rstn),
        .switch_mode(switch_mode),
        .pc_csr(pc_csr),
        .stall_pc(stall_PC),
        .stall_ornot(stall_ornot),
        .csr_stall_ornot(csr_stall_ornot),
        .b_stall(b_stall==2'b01 || b_stall==2'b10),
        .PCin(IF_NPC),
        .IF_jump(IF_jump_btb),
        .pc_target_if(IF_pc_target),
        .PCout(IF_PC)
    );

    ADD add(
        .pc_in(IF_PC),
        .pc_out(IF_PC4)
    );
    
    PC_mux pcmux(
        // .switch_mode(switch_mode),
        // .pc_csr(pc_csr),
        .PC_4(IF_PC4),
        .b_stall(b_stall),
        .PC_4_ex(EX_PC4),
        .alu(EX_alu),
        .br_taken(EX_branch),
        .npc_sel(EX_signal[19]),
        // .IF_jump(IF_jump_btb),
        // .pc_target_if(IF_pc_target),
        .PCout(IF_NPC)
    );

    // InstSelect instsel(
    //     .clk(clk),
    //     .rst(rstn),
    //     .wait_stall(if_stall),
    //     .inst(inst),
    //     .IF_inst(IF_INS)
    // );

    wire ID_jump_btb;
    IF_ID if_id(
        .clk(clk),
        .rst(rstn),
        .switch(switch_mode),
        .IF_pc(IF_PC),
        .IF_ins(IF_INS),
        .flush(flush_IFID),
        .halt(stall_IFID),               
        .IF_valid(IF_valid_reg),
        .IF_pc4(IF_PC4),
        .ID_ins(ID_INS),
        .ID_pc(ID_PC),
        .ID_valid(ID_valid_reg),
        .ID_pc4(ID_PC4),

        .IF_jump(IF_jump_btb),
        .ID_jump(ID_jump_btb)

        // .switch_mode(switch_mode),
        // .pc_csr(pc_csr)
    );
    
    //ID

    wire csr_reg_signal;
    Control ctrl(
        .inst(ID_INS),  
        .decode(ID_signal),
        .ID_csr_we(ID_CSR_we),
        .ID_csr_ret(ID_CSR_ret),
        .ID_csr_addr(ID_CSR_addr),
        .csr_reg(csr_reg_signal)
    );
         
    Regs regs(
        .clk(clk),
        .rst(~rstn),
        .read_addr_1(ID_INS[19:15]),
        .read_addr_2(ID_INS[24:20]),
        .we((WB_signal[21] | WB_CSR_we)&~switch_mode),
        .write_addr(WB_INS[11:7]),
        .write_data(WB_rd_data),   
        .read_data_1(ID_rs1_data),
        .read_data_2(ID_rs2_data),
        .cosim_regs(cosim_regs)
    );
    
    Imm_gen img(
        .immgen_op(ID_signal[18:16]),
        .ins(ID_INS[31:7]),
        .imm(ID_imm)
    );
    
    Branch bra(
        .bralu_op(EX_signal[11:9]),
        .data_r1(data_RS1),
        .data_r2(data_RS2),
        .br_taken(EX_branch)
    );

    wire csr_reg_signal_ex, EX_jump_btb;
    ID_EX id_ex(
        .clk(clk),
        .rst(rstn),
        .switch(switch_mode),
        // .ID_branch(ID_branch),
        .ID_pc(ID_PC),
        .ID_ins(ID_INS),
        .ID_rs1(ID_rs1_data),
        .ID_rs2(ID_rs2_data),
        .ID_decode(ID_signal),
        .ID_imm(ID_imm),
        .ID_pc4(ID_PC4),
        .flush(flush_IDEXE),
        .halt(stall_IDEXE),            
        .ID_valid(ID_valid_reg),
        // .EX_branch(EX_branch),
        .EX_ins(EX_INS),
        .EX_pc(EX_PC),
        .EX_rs1(EX_rs1_data),
        .EX_rs2(EX_rs2_data),
        .EX_decode(EX_signal),
        .EX_imm(EX_imm),
        .EX_pc4(EX_PC4),
        .EX_valid(EX_valid_reg),

        .id_csr_sel(csr_reg_signal),
        .ex_csr_sel(csr_reg_signal_ex),
        .ID_priv(ID_priv),
        .EX_priv(EX_priv),
        .ID_csr_addr(ID_CSR_addr),
        .EX_csr_addr(EX_CSR_addr),
        .ID_csr_val(ID_CSR_val),
        .EX_csr_val(EX_CSR_val),
        .ID_csr_we(ID_CSR_we),
        .EX_csr_we(EX_CSR_we),
        .ID_csr_ret(ID_CSR_ret),
        .EX_csr_ret(EX_CSR_ret),

        .ID_jump(ID_jump_btb),
        .EX_jump(EX_jump_btb)
    );

    //EX
    
    ALU_mux_a mux_a(
        .asel(EX_signal[8:7]),
        .rs1(data_RS1),
        .pc(EX_PC),
        .a_out(data_a)
    );

    ALU_mux_b mux_b(
        .bsel(EX_signal[6:5]),
        .rs2(data_RS2),
        .imm(EX_imm),
        .b_out(data_b)
    );

    wire [63:0] EX_alu_temp;
    ALU aluu(
        .alu_op(EX_signal[15:12]),
        .a(data_a),
        .b(data_b),
        .res(EX_alu_temp)
    );

    CSRALU csr_alu(
        .alu_op(EX_signal[15:12]),
        .EX_csr_val(CSR_val_data),
        .EX_rs1(CSR_rs1_data),
        .EX_csr_imm(EX_imm),
        .EX_csr_val_alu(EX_CSR_val_alu)
    );

    ALU_MUX alu_mux(
        .csr_reg(csr_reg_signal_ex),
        .reg_alu(EX_alu_temp),
        .csr_alu(EX_CSR_val),
        .alu_out(EX_alu)
    );

    wire [63:0] data_RS1, data_RS2, CSR_rs1_data, CSR_val_data;

    for_rs for_rs_data(
        // .temp(temp),
        .forward_signal1(FORWARD1),
        .forward_signal2(FORWARD2),
        .data_a(EX_rs1_data),
        .data_b(EX_rs2_data),
        .mem_alu_data(MEM_alu),
        .wb_alu_data(WB_alu),
        .wb_mem_data(WB_mem),
        .wb_temp_alu_data(WB_temp_alu),
        .wb_temp_mem_data(WB_temp_mem),
        .data_rs1(data_RS1),
        .data_rs2(data_RS2)
    );

    for_rs_csr for_rs_csr_data(
        // .temp(temp),
        .forward_csr_signal1(csr_FORWARD1),
        .forward_csr_signal2(csr_FORWARD2),
        .csr_rs1(EX_rs1_data),
        .mem_alu_data(MEM_alu),
        .wb_alu_data(WB_alu),
        .wb_mem_data(WB_mem),
        .wb_temp_alu_data(WB_temp_alu),
        .wb_temp_mem_data(WB_temp_mem),
        .ex_csr_val(EX_CSR_val),
        .mem_csr_val(MEM_CSR_val_alu),
        .wb_csr_val(WB_CSR_val_alu),
        .wb_temp_csr_val(WB_temp_CSR_alu),
        .csr_rs1_data(CSR_rs1_data),
        .csr_val_data(CSR_val_data)
    );

    MaskGen genmask(
        .alu(EX_alu),
        .memdata_width(EX_signal[2:0]),
        .wmask(EX_mask)
    );

    Datasel data(
        .alu(EX_alu),
        .rw_wdata(data_RS2),
        .memdata_width(EX_signal[2:0]),
        .datasel(EX_wdata)
    );

    wire mem_stall_final;
    MEM_MMU mmu_mem(
        .clk(clk),
        .rst(rst),
        .switch(switch_mode),
        .satp(satp),
        .priv(ID_priv),

        .wdata_cpu(MEM_wdata),
        .address_cpu(rst? 0:MEM_alu),
        .mask_cpu(MEM_mask),
        .we_cpu(MEM_signal[20]),
        .re_cpu(MEM_INS[6:0]==7'b0000011),

        .address(address),
        .we_mem(we_mem),
        .re_mem(re_mem),
        .wdata_mem(wdata_mem),
        .wmask_mem(wmask_mem),

        .rdata_mem(rdata_mem),
        .mem_rvalid(~mem_stall),
        .phy_mem(memory),

        .phy_mem_stall(mem_stall_final)
    );
    
    EX_MEM ex_mem(
        .clk(clk),
        .rst(rstn),
        .switch(switch_mode),
        .EX_branch(EX_branch),
        .EX_pc(EX_PC),
        .EX_ins(EX_INS),
        .EX_decode(EX_signal),
        .EX_alu(EX_alu),
        .EX_rs2(EX_wdata),
        .EX_pc4(EX_PC4),
        .flush(flush_EXEMEM),
        .halt(stall_EXEMEM),
        .EX_valid(EX_valid_reg),
        .EX_mask(EX_mask),
        .MEM_branch(MEM_branch),
        .MEM_pc(MEM_PC),
        .MEM_ins(MEM_INS),
        .MEM_decode(MEM_signal),
        .MEM_alu(MEM_alu),
        .MEM_rs2(MEM_wdata),
        .MEM_pc4(MEM_PC4),
        .MEM_valid(MEM_valid_reg),
        .MEM_mask(MEM_mask),

        .EX_priv(EX_priv),
        .MEM_priv(MEM_priv),
        .EX_csr_addr(EX_CSR_addr),
        .MEM_csr_addr(MEM_CSR_addr),
        .EX_csr_val_alu(EX_CSR_val_alu),
        .MEM_csr_val_alu(MEM_CSR_val_alu),
        .EX_csr_we(EX_CSR_we),
        .MEM_csr_we(MEM_CSR_we),
        .EX_csr_ret(EX_CSR_ret),
        .MEM_csr_ret(MEM_CSR_ret)
    );

    //MEM


    // RAM datamem(
    //     .clk(clk),
    //     .rstn(rstn),
    //     .rw_wmode(EX_signal[20]),
    //     .rw_addr(EX_alu[11:3]),
    //     .rw_wdata(EX_wdata),
    //     .rw_wmask(EX_mask),  
    //     .rw_rdata(MEM_mem),     
    //     .ro_addr(stall_PC?IF_PC[11:3]:(!rstn? 0:IF_NPC[11:3])),    
    //     .ro_rdata(instruct)
    // );

    //WB

    DataTrunc dt(
        .alu(MEM_alu),
        .rw_rdata(memory),
        .memdata_width(MEM_signal[2:0]),
        .mem(MEM_mem)
    );

    Wb_mux wb(
        .wb_sel(WB_signal[4:3]),
        .pc4(WB_PC4),
        .alu(WB_alu),
        .mem(WB_mem),
        .dataw(WB_rd_data)  //Rd
    );
    

    MEM_WB mem_wb(
        .clk(clk),
        .rst(rstn),
        .MEM_branch(MEM_branch),
        .MEM_pc(MEM_PC),
        .MEM_ins(MEM_INS),
        .MEM_decode(MEM_signal),
        .MEM_alu(MEM_alu),
        .MEM_mem(MEM_mem),
        .MEM_pc4(MEM_PC4),
        .flush(flush_MEMWB),
        .halt(stall_MEMWB),
        .MEM_valid(MEM_valid_reg),
        .WB_branch(WB_branch),
        .WB_pc(WB_PC),
        .WB_ins(WB_INS),
        .WB_alu(WB_alu),
        .WB_mem(WB_mem),
        .WB_pc4(WB_PC4),
        .WB_decode(WB_signal),
        .WB_valid(WB_valid_reg),

        .MEM_priv(MEM_priv),
        .WB_priv(WB_priv),
        .MEM_csr_addr(MEM_CSR_addr),
        .WB_csr_addr(WB_CSR_addr),
        .MEM_csr_val_alu(MEM_CSR_val_alu),
        .WB_csr_val_alu(WB_CSR_val_alu),
        .MEM_csr_we(MEM_CSR_we),
        .WB_csr_we(WB_CSR_we),
        .MEM_csr_ret(MEM_CSR_ret),
        .WB_csr_ret(WB_CSR_ret)
    );

    wire [63:0] WB_temp_alu, WB_temp_mem,WB_temp_CSR_alu;
    wire [11:0] WB_temp_CSR_addr;
    wire [21:0] WB_temp_signal;
    wire [31:0] WB_temp_INS;
    wire WB_temp_CSR_we;
    wb_temp wb_tmp(
        .clk(clk),
        .rst(rstn),
        .temp(temp),
        .temp_wb(temp_wb),
        .temp_wb_csr(temp_wb_csr),
        .WB_ins(WB_INS),
        .WB_decode(WB_signal),
        .WB_alu(WB_alu),
        .WB_mem(WB_mem),
        .WB_temp_ins(WB_temp_INS),
        .WB_temp_decode(WB_temp_signal),
        .WB_temp_alu(WB_temp_alu),
        .WB_temp_mem(WB_temp_mem),
        .mem_stall(mem_stall),

        .WB_csr_alu(WB_CSR_val_alu),
        .WB_temp_csr_alu(WB_temp_CSR_alu),
        .WB_csr_addr(WB_CSR_addr),
        .WB_temp_csr_addr(WB_temp_CSR_addr),
        .WB_csr_we(WB_CSR_we),
        .WB_temp_csr_we(WB_temp_CSR_we)
    );


    assign cosim_valid=WB_valid_reg&~cosim_interrupt;
    assign cosim_pc=WB_PC;      
    assign cosim_inst=WB_INS;
    assign cosim_rd_we={3'b0,WB_signal[21]};
    assign cosim_rd_id={3'b0,WB_INS[11:7]}; 
    assign cosim_rd_data=WB_rd_data;  

    assign cosim_rs1_id={3'b0,WB_INS[19:15]};
    assign cosim_rs1_data=data_a;
    assign cosim_rs2_id={3'b0,WB_INS[24:20]};
    assign cosim_rs2_data=data_b;
    assign cosim_alu=EX_alu;

    assign cosim_mem_addr=address;
    assign cosim_mem_we={3'b0,EX_signal[20]};
    assign cosim_mem_wdata=EX_wdata;
    assign cosim_mem_rdata=rdata_mem;

    assign cosim_br_taken={2'b0,WB_branch};
    assign cosim_npc=IF_NPC;

endmodule
