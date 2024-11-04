`timescale 1ns / 1ps
module Datasel (
    input [63:0] alu,
    input [63:0] rw_wdata,
    input [2:0] memdata_width,
    output [63:0] datasel
);
    reg [63:0] datasel_reg;
    always @(*) begin
        case (memdata_width)
            3'b000: datasel_reg = 64'b0;
            3'b001: datasel_reg = rw_wdata; //ld
            3'b010: begin  //lw
                if(alu[2]==1'b1) datasel_reg = {rw_wdata[31:0],32'b0};
                else datasel_reg = {{32{rw_wdata[31]}},rw_wdata[31:0]};
            end 
            3'b011: begin  //lh
                case (alu[2:1])
                    2'b00:  datasel_reg = {{48{rw_wdata[15]}},rw_wdata[15:0]};
                    2'b01:  datasel_reg = {{32{rw_wdata[15]}},rw_wdata[15:0],16'b0};
                    2'b10:  datasel_reg = {{16{rw_wdata[15]}},rw_wdata[15:0],32'b0};
                    2'b11:  datasel_reg = {rw_wdata[15:0],48'b0};
                endcase
            end 
            3'b100: begin  //lb
                case (alu[2:0])
                    3'b000: datasel_reg = {{56{rw_wdata[7]}},rw_wdata[7:0]};
                    3'b001: datasel_reg = {{48{rw_wdata[7]}},rw_wdata[7:0],8'b0}; 
                    3'b010: datasel_reg = {{40{rw_wdata[7]}},rw_wdata[7:0],16'b0}; 
                    3'b011: datasel_reg = {{32{rw_wdata[7]}},rw_wdata[7:0],24'b0};
                    3'b100: datasel_reg = {{24{rw_wdata[7]}},rw_wdata[7:0],32'b0};
                    3'b101: datasel_reg = {{16{rw_wdata[7]}},rw_wdata[7:0],40'b0};
                    3'b110: datasel_reg = {{8{rw_wdata[7]}},rw_wdata[7:0],48'b0};
                    3'b111: datasel_reg = {rw_wdata[7:0],56'b0};
                    // datasel_reg = {rw_wdata[7:0],rw_wdata[7:0],rw_wdata[7:0],rw_wdata[7:0],rw_wdata[7:0],rw_wdata[7:0],rw_wdata[7:0],rw_wdata[7:0]};
                endcase
            end
            3'b101: begin  //lwu
                if(alu[2]==1'b1) datasel_reg = {rw_wdata[31:0],32'b0};
                else datasel_reg = {{32{rw_wdata[31]}},rw_wdata[31:0]};
            end 
            3'b110: begin  //lhu
                case (alu[2:1])
                    2'b00:  datasel_reg = {{48{rw_wdata[15]}},rw_wdata[15:0]};
                    2'b01:  datasel_reg = {{32{rw_wdata[15]}},rw_wdata[15:0],16'b0};
                    2'b10:  datasel_reg = {{16{rw_wdata[15]}},rw_wdata[15:0],32'b0};
                    2'b11:  datasel_reg = {rw_wdata[15:0],48'b0};
                endcase
            end 
            3'b111: begin  //lbu
                case (alu[2:0])
                    3'b000: datasel_reg = {{56{rw_wdata[7]}},rw_wdata[7:0]};
                    3'b001: datasel_reg = {{48{rw_wdata[7]}},rw_wdata[7:0],8'b0}; 
                    3'b010: datasel_reg = {{40{rw_wdata[7]}},rw_wdata[7:0],16'b0}; 
                    3'b011: datasel_reg = {{32{rw_wdata[7]}},rw_wdata[7:0],24'b0};
                    3'b100: datasel_reg = {{24{rw_wdata[7]}},rw_wdata[7:0],32'b0};
                    3'b101: datasel_reg = {{16{rw_wdata[7]}},rw_wdata[7:0],40'b0};
                    3'b110: datasel_reg = {{8{rw_wdata[7]}},rw_wdata[7:0],48'b0};
                    3'b111: datasel_reg = {rw_wdata[7:0],56'b0};
                endcase
            end
        endcase
    end
    assign datasel = datasel_reg;
endmodule