`timescale 1ns / 1ps
module Imm_gen(
    input [2:0] immgen_op,
    input [24:0] ins,
    output [63:0] imm
);  
    reg [63:0] imm_reg;    
    always @(*) begin
        case (immgen_op)
            3'b000: imm_reg = 0;
            3'b001: imm_reg = {{52{ins[24]}},ins[24:13]};//i
            3'b010: imm_reg = {{52{ins[24]}},ins[24:18],ins[4:0]};//s
            3'b011: imm_reg = {{52{ins[24]}},ins[0],ins[23:18],ins[4:1],1'b0};//b
            3'b100: imm_reg = {{32{ins[24]}},ins[24:5],12'b0};//u
            3'b101: imm_reg = {{44{ins[24]}},ins[12:5],ins[13],ins[23:14],1'b0};//j
            3'b110: imm_reg = {{59'b0},ins[12:8]};//csr
            default: imm_reg = 0;
        endcase 
    end
    assign imm = imm_reg;

endmodule