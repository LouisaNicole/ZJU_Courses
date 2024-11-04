module for_rs (
    // input [1:0] temp,
    input [2:0] forward_signal1,
    input [2:0] forward_signal2,
    input [63:0] data_a,
    input [63:0] data_b,
    input [63:0] mem_alu_data,
    input [63:0] wb_alu_data,
    input [63:0] wb_mem_data,
    input [63:0] wb_temp_alu_data,
    input [63:0] wb_temp_mem_data,    
    output reg [63:0] data_rs1,
    output reg [63:0] data_rs2 
);

    always @(*) begin
        case (forward_signal1)
            3'b01: begin
                data_rs1 = mem_alu_data;
            end
            3'b10: begin
                data_rs1 = wb_alu_data;
            end
            3'b11: begin
                data_rs1 = wb_mem_data;
            end
            3'b100: begin
                data_rs1 = wb_temp_mem_data;
            end
            3'b101: begin
                data_rs1 = wb_temp_alu_data;
            end
            default: begin
                data_rs1 = data_a;
            end
        endcase
        case (forward_signal2)
            3'b01: begin
                data_rs2 = mem_alu_data;
            end
            3'b10: begin
                data_rs2 = wb_alu_data;
            end
            3'b11: begin
                data_rs2 = wb_mem_data;
            end
            3'b100: begin
                data_rs2 = wb_temp_mem_data;
            end
            3'b101: begin
                data_rs2 = wb_temp_alu_data;
            end
            default: begin
                data_rs2 = data_b;
            end
        endcase
    end
endmodule