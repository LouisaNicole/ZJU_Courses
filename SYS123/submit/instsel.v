module InstSelect (
    input clk,
    input rst,
    input wait_stall,
    input [31:0] inst,
    output reg [31:0] IF_inst
);  
    initial begin
        IF_inst = 32'b0;
    end
    always @(posedge clk or negedge rst) begin
        if(!rst) IF_inst <= 32'b0;
        else begin
            IF_inst <= wait_stall ? IF_inst : inst;
        end
    end
endmodule