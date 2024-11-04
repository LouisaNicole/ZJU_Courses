`timescale 1ns / 1ps

module MEM_WB (
    input clk,
    input rst,
    input [1:0] MEM_branch,
    input [63:0] MEM_pc,
    input [31:0] MEM_ins,
    input [21:0] MEM_decode,
    input [63:0] MEM_alu,
    input [63:0] MEM_mem,
    input [63:0] MEM_pc4,
    input flush,
    input halt,
    input MEM_valid,
    output reg [1:0] WB_branch,
    output reg [63:0] WB_pc,
    output reg [31:0] WB_ins,
    output reg [63:0] WB_alu,
    output reg [63:0] WB_mem,
    output reg [63:0] WB_pc4,
    output reg [21:0] WB_decode,
    output reg WB_valid,

    input [1:0] MEM_priv,
    output reg [1:0] WB_priv,
    input [11:0] MEM_csr_addr,
    output reg [11:0] WB_csr_addr,
    input [63:0] MEM_csr_val_alu,
    output reg [63:0] WB_csr_val_alu,
    input MEM_csr_we,
    output reg WB_csr_we,
    input [1:0] MEM_csr_ret,
    output reg [1:0] WB_csr_ret
);
    initial begin
        WB_ins = 32'b0;
        WB_pc = 64'b0;
        WB_valid = 0;
        WB_pc4 = 64'b0;
        WB_mem = 64'b0;
        WB_decode = 22'b0;
        WB_alu = 64'b0;
        WB_branch = 2'b0;
        WB_csr_addr = 12'b0;
        WB_csr_val_alu = 64'b0;
        WB_csr_we = 0;
        WB_csr_ret = 2'b0; 
        WB_priv = 2'b0;    
    end
    always @(posedge clk or negedge rst) begin
        if(halt) begin
            WB_pc <= WB_pc;
            WB_ins <= WB_ins;
            WB_valid <= WB_valid;
            WB_pc4 <= WB_pc4;
            WB_mem <= WB_mem;
            WB_decode <= WB_decode;   
            WB_alu <= WB_alu;
            WB_branch <= WB_branch;  
            WB_csr_addr <= WB_csr_addr;
            WB_csr_val_alu <= WB_csr_val_alu;
            WB_csr_we <= WB_csr_we;
            WB_csr_ret <= WB_csr_ret;     
            WB_priv <= WB_priv;
        end
        else if(flush|!rst) begin
            WB_ins <= 32'b0;
            WB_pc <= 64'b0;
            WB_valid <= 0;
            WB_pc4 <= 64'b0;
            WB_mem <= 64'b0;
            WB_decode <= 22'b0;
            WB_alu <= 64'b0; 
            WB_branch <= 2'b0;
            WB_csr_addr <= 12'b0;
            WB_csr_val_alu <= 64'b0;
            WB_csr_we <= 0;
            WB_csr_ret <= 2'b0;
            WB_priv <= 2'b0;
        end
        else begin
            WB_ins <= MEM_ins;
            WB_pc <= MEM_pc;
            WB_pc4 <= MEM_pc4;
            WB_valid <= MEM_valid;
            WB_mem <= MEM_mem;
            WB_decode <= MEM_decode;
            WB_alu <= MEM_alu;
            WB_branch <= MEM_branch;
            WB_csr_addr <= MEM_csr_addr;
            WB_csr_val_alu <= MEM_csr_val_alu;
            WB_csr_we <= MEM_csr_we;
            WB_csr_ret <= MEM_csr_ret;
            WB_priv <= MEM_priv;
        end
    end
endmodule