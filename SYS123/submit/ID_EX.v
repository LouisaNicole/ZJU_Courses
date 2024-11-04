`timescale 1ns / 1ps

module ID_EX (
    input clk,
    input rst,
    input switch,
    // input [1:0] ID_branch,
    input [63:0] ID_pc,
    input [31:0] ID_ins,
    input [63:0] ID_rs1,
    input [63:0] ID_rs2,
    input [21:0] ID_decode,
    input [63:0] ID_imm,
    input [63:0] ID_pc4,
    input flush,
    input halt,
    input ID_valid,
    // output reg [1:0] EX_branch,
    output reg [63:0] EX_pc,
    output reg [31:0] EX_ins,
    output reg [63:0] EX_rs1,
    output reg [63:0] EX_rs2,
    output reg [21:0] EX_decode,
    output reg [63:0] EX_imm,
    output reg [63:0] EX_pc4,
    output reg EX_valid,

    input id_csr_sel,
    output reg ex_csr_sel,
    input [1:0] ID_priv,
    output reg [1:0] EX_priv,
    input [11:0] ID_csr_addr,
    output reg [11:0] EX_csr_addr,
    input [63:0] ID_csr_val,
    output reg [63:0] EX_csr_val,
    input ID_csr_we,
    output reg EX_csr_we,
    input [1:0] ID_csr_ret,
    output reg [1:0] EX_csr_ret,

    input ID_jump,
    output reg EX_jump
);
    initial begin
        EX_ins = 32'b0;
        EX_pc = 64'b0;
        EX_valid = 0;
        EX_pc4 = 64'b0;
        EX_rs1 = 64'b0;
        EX_rs2 = 64'b0;
        EX_decode = 22'b0;
        EX_imm = 64'b0;   
        EX_csr_addr = 12'b0;
        EX_csr_val = 64'b0; 
        EX_csr_we = 0; 
        EX_csr_ret = 2'b0;
        EX_priv = 2'b0; 
        ex_csr_sel = 0;
        EX_jump = 0;      
    end
    always @(posedge clk or negedge rst) begin
        if(switch) begin
            EX_ins <= 32'b0;
            EX_pc <= 64'b0;
            EX_valid <= 0;
            EX_pc4 <= 64'b0;
            EX_rs1 <= 64'b0;
            EX_rs2 <= 64'b0;
            EX_decode <= 22'b0;
            EX_imm <= 64'b0; 
            EX_csr_val <= 64'b0;
            EX_csr_addr <= 12'b0;
            EX_csr_we <= 0;
            EX_csr_ret <=2'b0;
            EX_priv <= 2'b0;
            // EX_branch <= 2'b0;
            ex_csr_sel <= 0;
            EX_jump <= 0;
        end
        else if(halt) begin
            EX_pc <= EX_pc;
            EX_ins <= EX_ins;
            EX_valid <= EX_valid;
            EX_pc4 <= EX_pc4;
            EX_rs1 <= EX_rs1;
            EX_rs2 <= EX_rs2;
            EX_decode <= EX_decode;   
            EX_imm <= EX_imm;
            EX_csr_val <= EX_csr_val;
            EX_csr_addr <= EX_csr_addr;
            EX_csr_we <= EX_csr_we;
            EX_csr_ret <= EX_csr_ret;
            EX_priv <= EX_priv;
            // // EX_branch <= EX_branch;   
            ex_csr_sel <= ex_csr_sel; 
            EX_jump <= EX_jump;
        end
        else if(flush|!rst) begin
            EX_ins <= 32'b0;
            EX_pc <= 64'b0;
            EX_valid <= 0;
            EX_pc4 <= 64'b0;
            EX_rs1 <= 64'b0;
            EX_rs2 <= 64'b0;
            EX_decode <= 22'b0;
            EX_imm <= 64'b0; 
            EX_csr_val <= 64'b0;
            EX_csr_addr <= 12'b0;
            EX_csr_we <= 0;
            EX_csr_ret <=2'b0;
            EX_priv <= 2'b0;
            // EX_branch <= 2'b0;
            ex_csr_sel <= 0;
            EX_jump <= 0;
        end
        else begin
            EX_ins <= ID_ins;
            EX_pc <= ID_pc;
            EX_pc4 <= ID_pc4;
            EX_valid <= ID_valid;
            EX_rs1 <= ID_rs1;
            EX_rs2 <= ID_rs2;
            EX_decode <= ID_decode;
            EX_imm <= ID_imm; 
            EX_csr_addr <= ID_csr_addr;
            EX_csr_val <= ID_csr_val;
            EX_csr_we <= ID_csr_we;
            EX_csr_ret <= ID_csr_ret;
            EX_priv <= ID_priv;
            ex_csr_sel <= id_csr_sel;
            EX_jump <= ID_jump;
            // EX_branch <= ID_branch; 
        end
    end
    // assign ex_csr_sel = id_csr_sel;
endmodule