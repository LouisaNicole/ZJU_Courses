`timescale 1ns / 1ps
module PC(    
    input clk,
    input rst,   
    input stall_pc,
    input stall_ornot,
    input csr_stall_ornot,
    input b_stall,
    input switch_mode,
    input [63:0] pc_csr,
    input [63:0] PCin, 
    input IF_jump,
    input [63:0] pc_target_if,
    output [63:0] PCout    
);    
    reg [63:0] PCout_reg;
    initial begin
        PCout_reg = 64'b0;
    end
    always@(posedge clk or negedge rst) begin      
        if(!rst) begin    
            PCout_reg <= 64'b0;    
        end   
        else if (switch_mode) begin
            PCout_reg <= pc_csr;
        end
        else if (stall_ornot) begin
            PCout_reg <= PCout_reg;
        end
        else if (csr_stall_ornot) begin
            PCout_reg <= PCout_reg;
        end
        else if (stall_pc) begin
            if (b_stall) begin
                PCout_reg <= PCin;    
            end
            else begin
                PCout_reg <= PCout_reg;
            end
        end 
        else if (IF_jump) begin
            PCout_reg <= pc_target_if;
        end   
        else begin    
            PCout_reg <= PCin;    
        end    
    end 
    assign PCout = PCout_reg; 
        
endmodule