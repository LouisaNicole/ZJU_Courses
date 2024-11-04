module forward (
    // input [63:0] ID_ins
    // input [1:0] temp,
    input [31:0] EX_ins,
    input [21:0] EX_decode,
    // input [1:0] EX_Branch,
    input [31:0] MEM_ins,
    input [21:0] MEM_decode,
    input [31:0] WB_ins,
    input [21:0] WB_decode,
    input [31:0] WB_temp_ins,
    input [21:0] WB_temp_decode,
    output reg [2:0] forward_signal1,
    output reg [2:0] forward_signal2,
    output reg temp_wb,
    output reg stall
);

    always @(*) begin
        stall = 0;
        temp_wb = 0;
        if(MEM_ins[11:7]==EX_ins[19:15] & MEM_decode[21] & MEM_ins[11:7]!=0 & MEM_ins[6:0]!=7'b0000011)begin
            forward_signal1 = 3'b01;    //mem.rd==exe.rs1 & not_load
        end
        else if(MEM_ins[11:7]==EX_ins[19:15] & MEM_decode[21] & MEM_ins[11:7]!=0 & MEM_ins[6:0]==7'b0000011)begin
            stall = 1;                  //mem.rd==exe.rs1 & load
            forward_signal1 = 3'b0;
        end
        else if(WB_ins[11:7]==EX_ins[19:15] & WB_decode[21] & WB_ins[11:7]!=0 & WB_ins[6:0]!=7'b0000011)begin
            forward_signal1 = 3'b10;    //wb.rd==exe.rs1 & not_load
        end
        else if(WB_ins[11:7]==EX_ins[19:15] & WB_decode[21] & WB_ins[11:7]!=0 & WB_ins[6:0]==7'b0000011)begin
            forward_signal1 = 3'b11;    //wb.rd==exe.rs1 & load
        end
        else if(WB_temp_ins[11:7]==EX_ins[19:15] & WB_temp_decode[21] & WB_temp_ins[11:7]!=0 & WB_temp_ins[6:0]==7'b0000011)begin
            forward_signal1 = 3'b100;   //wb_temp.rd==exe.rs1 & load
            temp_wb = 1;
        end
        else if(WB_temp_ins[11:7]==EX_ins[19:15] & WB_temp_decode[21] & WB_temp_ins[11:7]!=0 & WB_temp_ins[6:0]!=7'b0000011)begin
            forward_signal1 = 3'b101;   //wb_temp.rd==exe.rs1 & not_load
            temp_wb = 1;
        end
        else begin
            forward_signal1 = 3'b0;
        end



        if(MEM_ins[11:7]==EX_ins[24:20] & MEM_decode[21] & MEM_ins[11:7]!=0 & MEM_ins[6:0]!=7'b0000011)begin
            forward_signal2 = 3'b01;    //mem.rd==exe.rs2 & not_load
        end
        else if(MEM_ins[11:7]==EX_ins[24:20] & MEM_decode[21] & MEM_ins[11:7]!=0 & MEM_ins[6:0]==7'b0000011)begin
            stall = 1;                  //mem.rd==exe.rs2 & load
            forward_signal2 = 3'b0;
        end
        else if(WB_ins[11:7]==EX_ins[24:20] & WB_decode[21] & WB_ins[11:7]!=0 & WB_ins[6:0]!=7'b0000011)begin
            forward_signal2 = 3'b10;    //wb.rd==exe.rs2 & not_load
        end
        else if(WB_ins[11:7]==EX_ins[24:20] & WB_decode[21] & WB_ins[11:7]!=0 & WB_ins[6:0]==7'b0000011)begin
            forward_signal2 = 3'b11;    //wb.rd==exe.rs2 & load
        end
        else if(WB_temp_ins[11:7]==EX_ins[24:20] & WB_temp_decode[21] & WB_temp_ins[11:7]!=0 & WB_temp_ins[6:0]==7'b0000011)begin
            forward_signal2 = 3'b100;   //wb_temp.rd==exe.rs2 & load
            temp_wb = 1;
        end
        else if(WB_temp_ins[11:7]==EX_ins[24:20] & WB_temp_decode[21] & WB_temp_ins[11:7]!=0 & WB_temp_ins[6:0]!=7'b0000011)begin
            forward_signal2 = 3'b101;   //wb_temp.rd==exe.rs2 & not_load
            temp_wb = 1;
        end
        else begin
            forward_signal2 = 3'b0;
        end

    end
endmodule