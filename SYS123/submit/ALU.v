`timescale 1ns / 1ps
module ALU (
    input  [3:0]  alu_op,
    input  signed[63:0] a,
    input  signed[63:0] b,
    output reg [63:0] res
);
    reg [31:0] res_lin;

    always@(*) begin
        res_lin = 32'b0;
        res = 64'b0;
        case (alu_op)
            4'b0000:  res = a + b;  //add
            4'b0001:  res = a - b;  //sub
            4'b0010:  res = a & b;  //and
            4'b0011:  res = a | b;  //or
            4'b0100:  res = a ^ b;  //xor
            4'b0101:  res = {63'b0, (a < b)};  //slt
            4'b0110:  res = {63'b0, ({1'b0,a} < {1'b0,b})};  //sltu
            4'b0111:  res = a << {58'b0,b[5:0]}; //sll
            4'b1000:  res = a >> {58'b0,b[5:0]}; //srl
            4'b1001:  res = a >>> {58'b0,b[5:0]};//sra
            4'b1010:  begin //addw
                res_lin = $signed(a[31:0]) + $signed(b[31:0]); 
                res = {{32{res_lin[31]}},res_lin[31:0]};
            end
            4'b1011:  begin //subw
                res_lin = $signed(a[31:0]) - $signed(b[31:0]); 
                res = {{32{res_lin[31]}},res_lin[31:0]};
            end
            4'b1100:  begin //sllw
                res_lin = a[31:0] << b[4:0]; 
                res = {{32{res_lin[31]}},res_lin[31:0]};
            end
            4'b1101:  begin //srlw
                res_lin = a[31:0] >> b[4:0]; 
                res = {{32{res_lin[31]}},res_lin[31:0]};
            end
            4'b1110:  begin //sraw
                res_lin = $signed(a[31:0]) >>> b[4:0]; 
                res = {{32{res_lin[31]}},res_lin[31:0]};
                end
            default:  res = 64'b0;
        endcase
    end
    
endmodule
