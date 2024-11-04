module for_rs_csr (
    // input [1:0] temp,
    input [2:0] forward_csr_signal1,
    input [1:0] forward_csr_signal2,
    input [63:0] csr_rs1,
    input [63:0] mem_alu_data,
    input [63:0] wb_alu_data,
    input [63:0] wb_mem_data,
    input [63:0] wb_temp_alu_data,
    input [63:0] wb_temp_mem_data,  
    input [63:0] ex_csr_val,
    input [63:0] mem_csr_val,
    input [63:0] wb_csr_val,
    input [63:0] wb_temp_csr_val,
    output reg [63:0] csr_rs1_data,
    output reg [63:0] csr_val_data
);

    always @(*) begin
        case (forward_csr_signal1)
            3'b01: begin
                csr_rs1_data = mem_alu_data;
            end
            3'b10: begin
                csr_rs1_data = wb_alu_data;
            end
            3'b11: begin
                csr_rs1_data = wb_mem_data;
            end
            3'b100: begin
                csr_rs1_data = wb_temp_mem_data;
            end
            3'b101: begin
                csr_rs1_data = wb_temp_alu_data;
            end
            default: begin
                csr_rs1_data = csr_rs1;
            end
        endcase
        case (forward_csr_signal2)
            2'b01: begin
                csr_val_data = mem_csr_val;
            end 
            2'b10: begin
                csr_val_data = wb_csr_val;
            end 
            2'b11: begin
                csr_val_data = wb_temp_csr_val;
            end 
            default: csr_val_data = ex_csr_val;
        endcase
    end
endmodule