module MEM_MMU (
    input clk,
    input rst,
    input switch,
    input [63:0] satp,
    input [1:0] priv,

    input [63:0] wdata_cpu,
    input [63:0] address_cpu,
    input [7:0] mask_cpu,
    input we_cpu,
    input re_cpu,

    output [63:0] address,
    output we_mem,
    output re_mem,
    output [63:0] wdata_mem,
    output [7:0] wmask_mem,

    input [63:0] rdata_mem,
    input mem_rvalid,
    output [63:0]phy_mem,

    output phy_mem_stall
);
    wire [63:0] VPN2 = {55'b0, address_cpu[38:30]};
    wire [63:0] VPN1 = {55'b0, address_cpu[29:21]};
    wire [63:0] VPN0 = {55'b0, address_cpu[20:12]};
    wire [63:0] PPN = {20'b0, satp[43:0]};
    wire [63:0] PTE = {20'b0, rdata_mem[53:10]};
    wire [63:0] offset = {52'b0, address_cpu[11:0]};
    reg [2:0] state;
    reg re_reg, we_reg;
    reg [63:0] address_reg;
    reg [7:0] mask_reg;

    parameter IDLE = 3'b000;
    parameter PAGE2 = 3'b001;
    parameter PAGE1 = 3'b010;
    parameter PAGE0 = 3'b011;
    parameter NOPAGE = 3'b100;

    always @(posedge clk) begin
        if(rst | switch) begin
            re_reg <= 1'b0;
            we_reg <= 1'b0;
            state <= IDLE;
        end
        else if(re_cpu | we_cpu) begin
            case (state)
                IDLE: begin
                    if(satp == 64'b0 || priv == 2'b11) begin
                        re_reg <= re_cpu;
                        we_reg <= we_cpu;
                        address_reg <= address_cpu;
                        mask_reg <= mask_cpu;
                        state <= NOPAGE;  // 直接读内存不用访问页表
                    end
                    else begin
                        re_reg <= 1'b1;
                        we_reg <= 1'b0;
                        mask_reg <= 8'b11111111;
                        address_reg <= ((PPN << 12) + (VPN2 << 3));
                        state <= PAGE2;  // 进入一级页表
                    end
                end 
                PAGE2: begin // 访存一级页表
                    if(~mem_rvalid) begin
                        state <= PAGE2;          
                    end
                    else begin
                        if(rdata_mem[3:1] != IDLE) begin
                            address_reg <= ((PTE << 12) + {34'b0, address_cpu[29:0]});
                            re_reg <= re_cpu;
                            we_reg <= we_cpu;
                            mask_reg <= mask_cpu;
                            state <= NOPAGE;
                        end
                        else begin
                            address_reg <= ((PTE << 12) + (VPN1 << 3));
                            state <= PAGE1;  // 进入二级页表
                        end
                    end
                end
                PAGE1: begin // 访存二级页表
                    if(~mem_rvalid) begin
                        state <= PAGE1;          
                    end
                    else begin
                        address_reg <= ((PTE << 12) + (VPN0 << 3));
                        state <= PAGE0; // 进入三级页表
                    end
                end
                PAGE0: begin // 访存三级页表
                    if(~mem_rvalid) begin
                        state <= PAGE0;          
                    end
                    else begin
                        address_reg <= ((PTE << 12) + offset);
                        re_reg <= re_cpu;
                        we_reg <= we_cpu;
                        mask_reg <= mask_cpu;
                        state <= NOPAGE;
                    end
                end
                NOPAGE: begin // 访存最终物理地址
                    if(~mem_rvalid) begin
                        state <= NOPAGE;          
                    end
                    else begin
                        re_reg <= 1'b0;
                        we_reg <= 1'b0;
                        state <= IDLE;
                    end
                end
                default: begin
                    re_reg <= 1'b0;
                    we_reg <= 1'b0;
                    state <= IDLE;
                end
            endcase
        end
        else begin
            re_reg <= 1'b0;
            we_reg <= 1'b0;
            state <= IDLE;
        end
    end

    assign re_mem = re_reg;
    assign we_mem = we_reg;
    assign wmask_mem = mask_reg;
    assign wdata_mem = wdata_cpu;
    assign phy_mem = rdata_mem;
    assign address = address_reg;
    // 不读不写或者读写完成时取消mem_stall
    assign phy_mem_stall = !((state==IDLE & ~re_cpu & ~we_cpu) | (state==NOPAGE & mem_rvalid));

endmodule