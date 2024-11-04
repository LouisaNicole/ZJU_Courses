module id_temp (
    input [31:0] ID_ins,
    input [31:0] EX_ins,
    input [31:0] WB_ins,
    input stall,
    input csr_stall,
    output temp
);
    
    assign temp = (WB_ins[11:7]==ID_ins[24:20] && WB_ins[31:0]!=32'b0) 
                    || (WB_ins[11:7]==ID_ins[19:15] && WB_ins[31:0]!=32'b0) 
                    || stall
                    || csr_stall;  //id.rs2==wb.rd
        
endmodule