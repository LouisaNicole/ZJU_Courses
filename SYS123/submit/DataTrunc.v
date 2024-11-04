`timescale 1ns / 1ps
module DataTrunc (
    input [63:0] alu,
    input [63:0] rw_rdata,
    input [2:0] memdata_width,
    output [63:0] mem
);
    reg [63:0] mem_reg;
    always @(*) begin
        case (memdata_width)
            3'b000: mem_reg = 64'b0;
            3'b001: mem_reg = rw_rdata; //ld
            3'b010: begin  //lw
                if(alu[2]==1'b1) mem_reg = {{32{rw_rdata[63]}},rw_rdata[63:32]};
                else mem_reg = {{32{rw_rdata[31]}},rw_rdata[31:0]};
            end 
            3'b011: begin  //lh
                case (alu[2:1])
                    2'b00:  mem_reg = {{48{rw_rdata[15]}},rw_rdata[15:0]};
                    2'b01:  mem_reg = {{48{rw_rdata[31]}},rw_rdata[31:16]};
                    2'b10:  mem_reg = {{48{rw_rdata[47]}},rw_rdata[47:32]};
                    2'b11:  mem_reg = {{48{rw_rdata[63]}},rw_rdata[63:48]};
                endcase
            end 
            3'b100: begin  //lb
                case (alu[2:0])
                    3'b000: mem_reg = {{56{rw_rdata[7]}},rw_rdata[7:0]};
                    3'b001: mem_reg = {{56{rw_rdata[15]}},rw_rdata[15:8]}; 
                    3'b010: mem_reg = {{56{rw_rdata[23]}},rw_rdata[23:16]}; 
                    3'b011: mem_reg = {{56{rw_rdata[31]}},rw_rdata[31:24]};
                    3'b100: mem_reg = {{56{rw_rdata[39]}},rw_rdata[39:32]};
                    3'b101: mem_reg = {{56{rw_rdata[47]}},rw_rdata[47:40]};
                    3'b110: mem_reg = {{56{rw_rdata[55]}},rw_rdata[55:48]};
                    3'b111: mem_reg = {{56{rw_rdata[63]}},rw_rdata[63:56]};
                endcase
            end
            3'b101: begin  //lwu
                if(alu[2]==1'b1) mem_reg = {32'b0,rw_rdata[63:32]};
                else mem_reg = {32'b0,rw_rdata[31:0]};
            end 
            3'b110: begin  //lhu
                case (alu[2:1])
                    2'b00:  mem_reg = {48'b0,rw_rdata[15:0]};
                    2'b01:  mem_reg = {48'b0,rw_rdata[31:16]};
                    2'b10:  mem_reg = {48'b0,rw_rdata[47:32]};
                    2'b11:  mem_reg = {48'b0,rw_rdata[63:48]};
                endcase
            end 
            3'b111: begin  //lbu
                case (alu[2:0])
                    3'b000: mem_reg = {56'b0,rw_rdata[7:0]};
                    3'b001: mem_reg = {56'b0,rw_rdata[15:8]}; 
                    3'b010: mem_reg = {56'b0,rw_rdata[23:16]}; 
                    3'b011: mem_reg = {56'b0,rw_rdata[31:24]};
                    3'b100: mem_reg = {56'b0,rw_rdata[39:32]};
                    3'b101: mem_reg = {56'b0,rw_rdata[47:40]};
                    3'b110: mem_reg = {56'b0,rw_rdata[55:48]};
                    3'b111: mem_reg = {56'b0,rw_rdata[63:56]};
                endcase
            end
        endcase
    end
    assign mem = mem_reg;
endmodule