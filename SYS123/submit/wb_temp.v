`timescale 1ns / 1ps
module wb_temp (
    input clk,rst,
    input temp,
    input temp_wb,
    input temp_wb_csr,
    input [31:0] WB_ins,
    input [21:0] WB_decode,
    input [63:0] WB_alu,
    input [63:0] WB_mem,
    output reg [31:0] WB_temp_ins,
    output reg [21:0] WB_temp_decode,
    output reg [63:0] WB_temp_alu,
    output reg [63:0] WB_temp_mem,
    input mem_stall,

    input [63:0] WB_csr_alu,
    output reg [63:0] WB_temp_csr_alu,
    input [11:0] WB_csr_addr,
    output reg [11:0] WB_temp_csr_addr,
    input WB_csr_we,
    output reg WB_temp_csr_we
);
    initial begin
        WB_temp_ins = 32'b0;
        WB_temp_decode = 22'b0;
        WB_temp_alu = 64'b0;
        WB_temp_mem = 64'b0;   
        WB_temp_csr_alu = 64'b0;    
        WB_temp_csr_we = 0; 
        WB_temp_csr_addr = 12'b0;
    end
    always @(posedge clk or negedge rst) begin
        if(!rst) begin
            WB_temp_ins <= 32'b0;
            WB_temp_decode <= 22'b0;
            WB_temp_alu <= 64'b0;
            WB_temp_mem <= 64'b0;
            WB_temp_csr_alu <= 64'b0;     
            WB_temp_csr_we <= 0; 
            WB_temp_csr_addr <= 12'b0;      
        end
        else if(temp_wb || temp_wb_csr) begin
            WB_temp_ins <= WB_temp_ins;
            WB_temp_decode <= WB_temp_decode;
            WB_temp_alu <= WB_temp_alu;
            WB_temp_mem <= WB_temp_mem;
            WB_temp_csr_alu <= WB_temp_csr_alu;
            WB_temp_csr_we <= WB_temp_csr_we;
            WB_temp_csr_addr <= WB_temp_csr_addr;
        end
        else if(temp || mem_stall) begin
            WB_temp_ins <= WB_ins;
            WB_temp_decode <= WB_decode;
            WB_temp_alu <= WB_alu;
            WB_temp_mem <= WB_mem;
            WB_temp_csr_alu <= WB_csr_alu;
            WB_temp_csr_we <= WB_csr_we;
            WB_temp_csr_addr <= WB_csr_addr;
        end
        else begin
            WB_temp_ins <= 32'b0;
            WB_temp_decode <= 22'b0;
            WB_temp_alu <= 64'b0;
            WB_temp_mem <= 64'b0;
            WB_temp_csr_alu <= 64'b0;
            WB_temp_csr_we <= 0;
            WB_temp_csr_addr <= 12'b0;
        end
    end
endmodule