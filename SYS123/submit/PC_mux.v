`timescale 1ns / 1ps

module PC_mux(
    input [63:0] PC_4,
    input [1:0] b_stall,
    input [63:0] PC_4_ex,
    input [63:0] alu,
    input [1:0] br_taken, 
    input npc_sel,
    // input switch_mode,
    // input [63:0] pc_csr,
    // input IF_jump,
    // input [63:0] pc_target_if,
    output [63:0] PCout
);
    initial begin
        PCout_reg = 0; 
    end
    reg [63:0] PCout_reg;
    always@(*) begin
        // if (switch_mode) begin
        //     PCout_reg = pc_csr;
        // end
        if(b_stall==2'b10) begin
            PCout_reg = PC_4_ex;
        end
        else if(b_stall==2'b01) begin
            PCout_reg = alu;
        end
        else if(br_taken == 2'b00) begin
            if(npc_sel) PCout_reg = alu;
            else PCout_reg = PC_4;
        end  //正常的PC增加
        // else if(IF_jump) begin
        //     PCout_reg = pc_target_if;
        // end  
        // else if(br_taken == 2'b01) PCout_reg = alu;
        else PCout_reg = PC_4;
    end
    assign PCout = PCout_reg;
    
endmodule