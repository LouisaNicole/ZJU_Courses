module ADD(
    input [63:0] pc_in,
    output [63:0] pc_out
);
    assign pc_out = pc_in + 64'd4;
//npc 用于pc地址的自增
endmodule