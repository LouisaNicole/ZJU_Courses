`timescale 1ns / 1ps

module ALU_MUX(
    input csr_reg,
    input [63:0] reg_alu,
    input [63:0] csr_alu,
    output reg [63:0] alu_out
);
    always@(*) begin
        case (csr_reg)
            1'b0: alu_out = reg_alu;
            1'b1: alu_out = csr_alu;
            default: alu_out = 0;
        endcase
    end
endmodule