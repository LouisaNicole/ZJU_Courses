module CSRALU(
    input [3:0] alu_op,
    input [63:0] EX_csr_val,
    input [63:0] EX_rs1,
    input [63:0] EX_csr_imm,
    output reg [63:0] EX_csr_val_alu
);
    always@(*) begin
        case (alu_op)
            4'b0001:  begin
                EX_csr_val_alu = EX_rs1;
            end  //csrrw
            4'b0010:  begin
                EX_csr_val_alu = EX_csr_val | EX_rs1;
            end  //csrrs
            4'b0011:  begin
                EX_csr_val_alu = EX_csr_val & (~EX_rs1);
            end  //csrrc
            4'b0100:  begin
                EX_csr_val_alu = EX_csr_imm;
            end  //csrrwi
            4'b0101:  begin
                EX_csr_val_alu = EX_csr_val | EX_csr_imm;
            end  //csrrsi
            4'b0110:  begin
                EX_csr_val_alu = EX_csr_val & (~EX_csr_imm);
            end  //csrrci
            default:  EX_csr_val_alu = 0;
        endcase
    end
    
endmodule