module My_FSM (
    input clk,
    input stall,
    input csr_stall,
    input wire if_stall,
    input wire is_ex_jump,
    input wire predict_ex_jump,
    output reg flag,  // 跳转错误的转台保存，用于后续的flush
    output reg [1:0] b_stall
);
    initial begin
        flag = 0;
    end
    always @(posedge clk) begin
        if(is_ex_jump==1'b1 && predict_ex_jump==1'b0 && if_stall && ~stall && ~csr_stall) begin
            flag <= 1;
        end
        else if(is_ex_jump==1'b0 && predict_ex_jump==1'b1 && if_stall && ~stall && ~csr_stall) begin
            flag <= 1;
        end
        else if(!if_stall) begin
            flag <= 0;
        end
        else begin
            flag <= flag;
        end
    end

    always @(*) begin
        if(is_ex_jump==1'b1 && predict_ex_jump==1'b0) begin //预计不跳，实际跳
            b_stall = 2'b01;
        end
        else if(is_ex_jump==1'b0 && predict_ex_jump==1'b1) begin //预计跳，实际不跳
            b_stall = 2'b10;
        end
        else begin
            b_stall = 0; 
        end
    end
endmodule
//这里模仿之前lab6的fsm在非idle状态且跳转的时候将bstall置为1