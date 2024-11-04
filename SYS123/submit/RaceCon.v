`timescale 1ns / 1ps

module RaceController(
    input wire stall,
    input wire csr_stall,
    input wire switch,
    // output wire temp_stall,
    // input wire id_except,
    // input wire B_flag,
    // input [1:0] ID_branch,
    // input switch_flush,
    // input valid_mem_mmio,
    // input ren_cpu_fsm,
    // input wait_stall,
    // input fsm_stall,
    input flag,
    input b_stall,
    input if_stall, mem_stall,
    input [21:0] EX_decode,
    input [1:0] EX_branch,
    output wire stall_PC,
    output wire stall_IFID,
    output wire stall_IDEXE,
    output wire stall_EXEMEM,
    output wire stall_MEMWB,
    output wire flush_IFID,
    output wire flush_IDEXE,
    output wire flush_EXEMEM,
    output wire flush_MEMWB
);  

    // assign flush_IFID = switch | EX_branch == 2'b01 | EX_decode[19] | if_stall;
    // assign flush_IDEXE = switch | EX_branch == 2'b01 | EX_decode[19];
    // assign flush_EXEMEM = switch | csr_stall | stall | b_stall;
    // assign flush_MEMWB = switch | mem_stall | b_stall;
    // assign stall_PC = csr_stall | stall | if_stall | mem_stall;
    // assign stall_IFID = csr_stall | stall | mem_stall | b_stall;
    // assign stall_IDEXE = csr_stall | stall | mem_stall | b_stall;
    // assign stall_EXEMEM = mem_stall;
    // assign stall_MEMWB = 0;

    assign flush_IFID = switch | b_stall | if_stall | flag;
    assign flush_IDEXE = switch | b_stall | flag;
    assign flush_EXEMEM = switch | csr_stall | stall;
    assign flush_MEMWB = switch | mem_stall;
    assign stall_PC = csr_stall | stall | if_stall | mem_stall | flag;
    assign stall_IFID = csr_stall | stall | mem_stall;
    assign stall_IDEXE = csr_stall | stall | mem_stall;
    assign stall_EXEMEM = mem_stall;
    assign stall_MEMWB = 0;
    // assign temp_stall = stall | mem_stall;

endmodule
