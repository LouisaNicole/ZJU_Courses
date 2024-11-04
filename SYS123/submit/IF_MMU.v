module IF_MMU (
    input clk,
    input rst,
    input switch,
    input [63:0] satp,
    input [1:0] priv,
    input [63:0] IF_pc,
    input [31:0] IF_ins_pc,
    input b_stall_mmu,
    output reg b_stall_save,

    output [63:0] page_pc,
    input [63:0] page_addr,
    input rvalid,
    
    output [31:0] IF_ins,
    output if_request,
    output phy_if_stall
);
    wire [63:0] VPN2 = {55'b0, IF_pc[38:30]};
    wire [63:0] VPN1 = {55'b0, IF_pc[29:21]};
    wire [63:0] VPN0 = {55'b0, IF_pc[20:12]};
    wire [63:0] PPN = {20'b0, satp[43:0]};
    wire [63:0] PTE = {20'b0, page_addr[53:10]};
    wire [63:0] offset = {52'b0, IF_pc[11:0]};
    reg [2:0] state;
    reg if_request_reg;
    reg [63:0] pc_reg;
    
    parameter IDLE = 3'b000;
    parameter PAGE2 = 3'b001;
    parameter PAGE1 = 3'b010;
    parameter PAGE0 = 3'b011;
    parameter NOPAGE = 3'b100;

    // always @(posedge clk) begin
    //     if (b_stall_mmu) b_stall_save <= 1'b1;
    //     else b_stall_save <= b_stall_save;
    //     if (state == NOPAGE) b_stall_save <= 1'b0;
    // end
    // reg save;
    // always @(posedge clk) begin
    //     if (b_stall_mmu) begin
    //         b_stall_save <= 1'b1;
    //         save <= 1'b1;
    //     end
    //     else if (save == 1'b1 && state != IDLE) begin
    //         b_stall_save <= b_stall_save;
    //         // save <= 1'b0;
    //     end
    //     else if (save == 1'b1 && state == IDLE) begin
    //         b_stall_save <= 1'b0;
    //         // save <= 1'b0;
    //     end
    //     else if (satp != 64'b0) b_stall_save <= 1'b0;
    //     else b_stall_save <= b_stall_save;
    // end

    always @(posedge clk or negedge rst) begin
        if(rst | switch) begin
            if_request_reg <= 1'b0;
            state <= IDLE;
        end
        else begin
            case (state)
                IDLE: begin
                    if((satp == 64'b0 || IF_pc[63:28] == 36'h000000008) || priv == 2'b11) begin
                        if_request_reg <= 1'b1;
                        pc_reg <= IF_pc;
                        state <= NOPAGE;  // 直接读内存不用访问页表
                    end
                    else begin
                        if_request_reg <= 1'b1;
                        pc_reg <= ((PPN << 12) + (VPN2 << 3));
                        state <= PAGE2;  // 进入一级页表
                    end
                end 
                PAGE2: begin // 访存一级页表
                    if(~rvalid) begin
                        state <= PAGE2;          
                    end
                    else begin
                        if(page_addr[3:1]!=3'b000) begin
                            // pc_reg <= IF_pc;
                            // if_request_reg <= 1'b0;
                            pc_reg <= ((PTE << 12) + {34'b0, IF_pc[29:0]});
                            state <= NOPAGE;
                        end
                        else begin
                            pc_reg <= ((PTE << 12) + (VPN1 << 3));
                            state <= PAGE1;  // 进入二级页表
                        end
                    end
                end
                PAGE1: begin // 访存二级页表
                    if(~rvalid) begin
                        state <= PAGE1;          
                    end
                    else begin
                        pc_reg <= ((PTE << 12) + (VPN0 << 3));
                        state <= PAGE0; // 进入三级页表
                    end
                end
                PAGE0: begin // 访存三级页表
                    if(~rvalid) begin
                        state <= PAGE0;          
                    end
                    else begin
                        pc_reg <= ((PTE << 12) + offset);
                        state <= NOPAGE;
                    end
                end
                NOPAGE: begin // 访存最终物理地址
                    // if_request_reg <= 1'b1;
                    if(~rvalid) begin
                        state <= NOPAGE;          
                    end
                    else begin
                        if_request_reg <= 1'b0;
                        state <= IDLE;
                    end
                end
                default: begin
                    if_request_reg <= 1'b0;
                    state <= IDLE;
                end
            endcase
        end
    end

    assign IF_ins = IF_pc[2]? page_addr[63:32]:page_addr[31:0];
    // assign page_pc = (b_stall_save & satp==64'b0 & !phy_if_stal) ? IF_pc : pc_reg;
    assign page_pc = pc_reg;
    assign if_request = if_request_reg;
    assign phy_if_stall = (state!=NOPAGE || ~rvalid);

endmodule