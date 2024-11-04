`timescale 1ns / 1ps
module Wb_mux (
    input [1:0] wb_sel,
    input [63:0] pc4,
    input [63:0] alu,
    input [63:0] mem,
    output [63:0] dataw
);
    reg [63:0] dataw_reg;
    always @(*) begin
        case (wb_sel)
            2'b00: dataw_reg = 0;
            2'b01: dataw_reg = alu;
            2'b10: dataw_reg = mem;
            2'b11: dataw_reg = pc4;  
        endcase
    end
    assign dataw = dataw_reg; 

endmodule