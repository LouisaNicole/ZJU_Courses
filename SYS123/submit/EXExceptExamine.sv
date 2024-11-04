`include "ExceptStruct.vh"
module EXExceptExamine(
    input clk,
    input rst,
    input stall,
    input flush,

    input [63:0] pc_ex,
    input [1:0] priv,
    input is_ecall_ex,
    input is_ebreak_ex,
    input illegal_ex,
    input [31:0] inst_ex,
    input valid_ex,
    
    input ExceptStruct::ExceptPack except_ex,
    output ExceptStruct::ExceptPack except_mem,
    output except_happen_ex
);
    
    import ExceptStruct::ExceptPack;
    ExceptPack except_new;
    ExceptPack except;

    InstExamine instexmaine_ex(
        .PC_i(pc_ex),
        .priv_i(priv),
        .inst_i(inst_ex),
        .valid_i(valid_ex),
        .except_o(except_new),
        .is_ecall_id_i(is_ecall_ex), ////////////
        .is_ebreak_id_i(is_ebreak_ex), ///////////
        .illegal_id_i(illegal_ex) ///////////////
    );

    assign except=except_ex.except?except_ex:except_new;
    assign except_happen_ex=except_new.except&~except_ex.except;

    ExceptReg exceptreg_ex(
        .clk(clk),
        .rst(rst),
        .stall(stall),
        .flush(flush),
        .except_i(except),
        .except_o(except_mem)
    );

endmodule 
