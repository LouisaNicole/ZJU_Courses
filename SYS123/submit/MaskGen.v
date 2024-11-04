`timescale 1ns / 1ps
module MaskGen (
    input [63:0] alu,
    input [2:0] memdata_width,
    output [7:0] wmask
);
    reg [7:0] wmask_reg;
    always @(*) begin
        case (memdata_width)
            3'b001: wmask_reg = 8'b11111111;
            3'b010: begin
                if(alu[2]==1'b1) wmask_reg = 8'b11110000;
                else wmask_reg = 8'b00001111;
            end
            3'b011: begin
                case (alu[2:1])
                    2'b00:  wmask_reg = 8'b00000011;
                    2'b01:  wmask_reg = 8'b00001100;
                    2'b10:  wmask_reg = 8'b00110000;
                    2'b11:  wmask_reg = 8'b11000000;
                endcase
            end
            3'b100: begin
                case (alu[2:0])
                    3'b000: wmask_reg = 8'b00000001;
                    3'b001: wmask_reg = 8'b00000010; 
                    3'b010: wmask_reg = 8'b00000100;
                    3'b011: wmask_reg = 8'b00001000;
                    3'b100: wmask_reg = 8'b00010000;
                    3'b101: wmask_reg = 8'b00100000;
                    3'b110: wmask_reg = 8'b01000000;
                    3'b111: wmask_reg = 8'b10000000;
                endcase
            end 
            3'b101: begin
                if(alu[2]==1'b1) wmask_reg = 8'b11110000;
                else wmask_reg = 8'b00001111;
            end
            3'b110: begin
                case (alu[2:1])
                    2'b00:  wmask_reg = 8'b00000011;
                    2'b01:  wmask_reg = 8'b00001100;
                    2'b10:  wmask_reg = 8'b00110000;
                    2'b11:  wmask_reg = 8'b11000000;
                endcase
            end
            3'b111: begin
                case (alu[2:0])
                    3'b000: wmask_reg = 8'b00000001;
                    3'b001: wmask_reg = 8'b00000010; 
                    3'b010: wmask_reg = 8'b00000100;
                    3'b011: wmask_reg = 8'b00001000;
                    3'b100: wmask_reg = 8'b00010000;
                    3'b101: wmask_reg = 8'b00100000;
                    3'b110: wmask_reg = 8'b01000000;
                    3'b111: wmask_reg = 8'b10000000;
                endcase
            end 
            default: wmask_reg = 8'b00000000;
        endcase
    end
    assign wmask = wmask_reg;
endmodule