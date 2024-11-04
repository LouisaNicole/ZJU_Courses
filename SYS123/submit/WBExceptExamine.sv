`include "ExceptStruct.vh"
module WBExceptExamine(
    input clk,
    input rst,
    input stall,
    input flush,

    input [63:0] pc_wb,
    input [1:0] priv,
    input is_ecall_wb,
    input is_ebreak_wb,
    input illegal_wb,
    input [31:0] inst_wb,
    input valid_wb,
    
    input ExceptStruct::ExceptPack except_wb,
    output ExceptStruct::ExceptPack except_last,
    output except_happen_wb
);
    
    import ExceptStruct::ExceptPack;
    ExceptPack except_new;
    ExceptPack except;

    InstExamine instexmaine_wb(
        .PC_i(pc_wb),
        .priv_i(priv),
        .inst_i(inst_wb),
        .valid_i(valid_wb),
        .except_o(except_new),
        .is_ecall_id_i(is_ecall_wb), ////////////
        .is_ebreak_id_i(is_ebreak_wb), ///////////
        .illegal_id_i(illegal_wb) ///////////////
    );

    assign except=except_wb.except?except_wb:except_new;
    assign except_happen_wb=except_new.except&~except_wb.except;

    ExceptReg exceptreg_wb(
        .clk(clk),
        .rst(rst),
        .stall(stall),
        .flush(flush),
        .except_i(except),
        .except_o(except_last)
    );

endmodule 
