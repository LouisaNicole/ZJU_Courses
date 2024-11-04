`timescale 1ns / 1ps

module ALU_mux_a(
    input [1:0] asel,
    input [63:0] rs1,
    input [63:0] pc,
    output [63:0] a_out
);
    reg [63:0] a_out_reg;
    always@(*) begin
        case (asel)
            2'b00: a_out_reg = 0;
            2'b01: a_out_reg = rs1;
            2'b10: a_out_reg = pc;
            default: a_out_reg = 0;
        endcase
    end
    assign a_out = a_out_reg;
endmodule