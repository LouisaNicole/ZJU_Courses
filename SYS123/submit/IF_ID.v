`timescale 1ns / 1ps

module IF_ID (
    input clk,
    input rst,
    input switch,
    input [63:0] IF_pc,
    input [31:0] IF_ins,
    input flush,
    input halt,
    input IF_valid,
    input [63:0] IF_pc4,
    output reg [63:0] ID_pc,
    output reg [31:0] ID_ins,
    output reg ID_valid,
    output reg [63:0] ID_pc4,

    input IF_jump,
    output reg ID_jump
);
    initial begin
        ID_ins = 32'b0;
        ID_pc = 64'b0;
        ID_valid = 0;
        ID_pc4 = 64'b0;
        ID_jump = 0;
        // ID_csr_addr = 12'b0;
    end
    always @(posedge clk or negedge rst) begin
        if (switch) begin
            ID_ins <= 32'b0;
            ID_pc <= 64'b0;
            ID_valid <= 0;
            ID_pc4 <= 64'b0;
            ID_jump <= 0;
        end
        else if(halt) begin
            ID_pc <= ID_pc;
            ID_ins <= ID_ins;
            ID_valid <= ID_valid;
            ID_pc4 <= ID_pc4;
            ID_jump <= ID_jump;
            // ID_csr_addr <= ID_csr_addr;
        end
        else if(flush|!rst) begin
            ID_ins <= 32'b0;
            ID_pc <= 64'b0;
            ID_valid <= 0;
            ID_pc4 <= 64'b0;
            ID_jump <= 0;
            // ID_csr_addr = 12'b0;
        end
        else begin
            ID_ins <= IF_ins;
            ID_pc <= IF_pc;
            ID_pc4 <= IF_pc4;
            ID_valid <= IF_valid;
            ID_jump <= IF_jump;
            // ID_csr_addr <= IF_csr_addr;
        end
    end
endmodule