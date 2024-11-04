`timescale 1ns / 1ps
module Branch (
    input [2:0] bralu_op,
    input signed [63:0] data_r1,
    input signed [63:0] data_r2,
    output reg [1:0] br_taken
);
    // reg [1:0] br_taken;
    
    always @(*) begin
        case (bralu_op)
            3'b000: br_taken = 0;
            3'b001:	begin
                if(data_r1 == data_r2) br_taken = 2'b01;
                else br_taken = 2'b10;
            end
            3'b010: begin
                if(data_r1 != data_r2) br_taken = 2'b01;
                else br_taken = 2'b10;
            end
            3'b011: begin
                if(data_r1 < data_r2) br_taken = 2'b01;
                else br_taken = 2'b10;
            end
            3'b100: begin
                if(data_r1 >= data_r2) br_taken = 2'b01;
                else br_taken = 2'b10;
            end
            3'b101: begin
                if({1'b0,data_r1} < {1'b0,data_r2}) br_taken = 2'b01;
                else br_taken = 2'b10;
            end
            3'b110: begin
                if({1'b0,data_r1} >= {1'b0,data_r2}) br_taken = 2'b01;
                else br_taken = 2'b10;
            end 
            default: br_taken = 0;
        endcase
    end
    // assign br_taken = br_taken;
endmodule