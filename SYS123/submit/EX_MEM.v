`timescale 1ns / 1ps

module EX_MEM (
    input clk,
    input rst,
    input switch,
    input [1:0] EX_branch,
    input [63:0] EX_pc,
    input [31:0] EX_ins,
    input [21:0] EX_decode,
    input [63:0] EX_alu,
    input [63:0] EX_rs2,
    input [63:0] EX_pc4,
    input flush,
    input halt,
    input EX_valid,
    input [7:0] EX_mask,
    output reg [1:0] MEM_branch,
    output reg [63:0] MEM_pc,
    output reg [31:0] MEM_ins,
    output reg [21:0] MEM_decode,
    output reg [63:0] MEM_alu,
    output reg [63:0] MEM_rs2,
    output reg [63:0] MEM_pc4,
    output reg MEM_valid,
    output reg [7:0] MEM_mask,

    input [1:0] EX_priv,
    output reg [1:0] MEM_priv,
    input [11:0] EX_csr_addr,
    output reg [11:0] MEM_csr_addr,
    input [63:0] EX_csr_val_alu,
    output reg [63:0] MEM_csr_val_alu,
    input EX_csr_we,
    output reg MEM_csr_we,
    input [1:0] EX_csr_ret,
    output reg [1:0] MEM_csr_ret
);
    initial begin
        MEM_ins = 32'b0;
        MEM_pc = 64'b0;
        MEM_valid = 0;
        MEM_pc4 = 64'b0;
        MEM_rs2 = 64'b0;
        MEM_decode = 22'b0;
        MEM_alu = 64'b0; 
        MEM_branch = 2'b0;
        MEM_mask = 8'b0;
        MEM_csr_addr = 12'b0;
        MEM_csr_val_alu = 64'b0;
        MEM_csr_we = 0;
        MEM_csr_ret = 2'b0;
        MEM_priv = 2'b0;
    end
    always @(posedge clk or negedge rst) begin
        if(switch) begin
            MEM_ins <= 32'b0;
            MEM_pc <= 64'b0;
            MEM_valid <= 0;
            MEM_pc4 <= 64'b0;
            MEM_rs2 <= 64'b0;
            MEM_decode <= 22'b0;
            MEM_alu <= 64'b0; 
            MEM_branch <= 2'b0;
            MEM_mask <= 8'b0;
            MEM_csr_addr <= 12'b0;
            MEM_csr_val_alu <= 64'b0;
            MEM_csr_we <= 0;
            MEM_csr_ret <= 2'b0;
            MEM_priv <= 2'b0;
        end
        else if(halt) begin
            MEM_pc <= MEM_pc;
            MEM_ins <= MEM_ins;
            MEM_valid <= MEM_valid;
            MEM_pc4 <= MEM_pc4;
            MEM_rs2 <= MEM_rs2;
            MEM_decode <= MEM_decode;   
            MEM_alu <= MEM_alu;  
            MEM_branch <= MEM_branch;   
            MEM_mask <= MEM_mask;
            MEM_csr_addr <= MEM_csr_addr;
            MEM_csr_val_alu <= MEM_csr_val_alu;
            MEM_csr_we <= MEM_csr_we;
            MEM_csr_ret <= MEM_csr_ret;
            MEM_priv <= MEM_priv;
        end
        else if(flush|!rst) begin
            MEM_ins <= 32'b0;
            MEM_pc <= 64'b0;
            MEM_valid <= 0;
            MEM_pc4 <= 64'b0;
            MEM_rs2 <= 64'b0;
            MEM_decode <= 22'b0;
            MEM_alu <= 64'b0; 
            MEM_branch <= 2'b0;
            MEM_mask <= 8'b0;
            MEM_csr_addr <= 12'b0;
            MEM_csr_val_alu <= 64'b0;
            MEM_csr_we <= 0;
            MEM_csr_ret <= 2'b0;
            MEM_priv <= 2'b0;
        end
        else begin
            MEM_ins <= EX_ins;
            MEM_pc <= EX_pc;
            MEM_pc4 <= EX_pc4;
            MEM_valid <= EX_valid;
            MEM_rs2 <= EX_rs2;
            MEM_decode <= EX_decode;
            MEM_alu <= EX_alu; 
            MEM_branch <= EX_branch;
            MEM_mask <= EX_mask;
            MEM_csr_addr <= EX_csr_addr;
            MEM_csr_val_alu <= EX_csr_val_alu;
            MEM_csr_we <= EX_csr_we;
            MEM_csr_ret <= EX_csr_ret;
            MEM_priv <= EX_priv;
        end
    end
endmodule