`timescale 1ns / 1ps

module ALU_mux_b(
    input [1:0] bsel,
    input [63:0] rs2,
    input [63:0] imm,
    output [63:0] b_out
);
    reg [63:0] b_out_reg;
    always@(*) begin
        case (bsel)
            2'b00: b_out_reg = 0;
            2'b01: b_out_reg = rs2;
            2'b10: b_out_reg = imm;
            default: b_out_reg = 0;
        endcase
    end
    assign b_out = b_out_reg;
endmodule