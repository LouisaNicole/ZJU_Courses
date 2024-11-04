module Cache #(
    parameter integer ADDR_WIDTH = 64,
    parameter integer DATA_WIDTH = 64,
    parameter integer BANK_NUM   = 4,
    parameter integer CAPACITY   = 1024
) (
    input                     clk,
    input                     rstn,
    input  [  ADDR_WIDTH-1:0] addr_cpu,
    input  [  DATA_WIDTH-1:0] wdata_cpu,
    input                     wen_cpu,
    input  [DATA_WIDTH/8-1:0] wmask_cpu,
    input                     ren_cpu,
    output [  DATA_WIDTH-1:0] rdata_cpu,
    output                    hit_cpu,

    Mem_ift.Master mem_ift
);

    reg                      ren_mem;
    reg                      wen_mem;
    reg [    ADDR_WIDTH-1:0] raddr_mem;
    reg [    ADDR_WIDTH-1:0] waddr_mem;
    reg [  DATA_WIDTH*2-1:0] wdata_mem;
    reg [DATA_WIDTH*2/8-1:0] wmask_mem;
    reg [  DATA_WIDTH*2-1:0] rdata_mem;
    reg                      wvalid_mem;
    reg                      rvalid_mem;

    assign mem_ift.Mw.waddr = waddr_mem;
    assign mem_ift.Mr.raddr = raddr_mem;
    assign mem_ift.Mw.wen   = wen_mem;
    assign mem_ift.Mr.ren   = ren_mem;
    assign mem_ift.Mw.wdata = wdata_mem;
    assign mem_ift.Mw.wmask = wmask_mem;
    assign rdata_mem        = mem_ift.Sr.rdata;
    assign rvalid_mem       = mem_ift.Sr.rvalid;
    assign wvalid_mem       = mem_ift.Sw.wvalid;

    localparam BYTE_NUM = DATA_WIDTH / 8;
    localparam LINE_NUM = CAPACITY / 2 / (BANK_NUM * BYTE_NUM);
    localparam GRANU_LEN = $clog2(BYTE_NUM);
    localparam GRANU_BEGIN = 0;
    localparam GRANU_END = GRANU_BEGIN + GRANU_LEN - 1;
    localparam OFFSET_LEN = $clog2(BANK_NUM);
    localparam OFFSET_BEGIN = GRANU_END + 1;
    localparam OFFSET_END = OFFSET_BEGIN + OFFSET_LEN - 1;
    localparam INDEX_LEN = $clog2(LINE_NUM);
    localparam INDEX_BEGIN = OFFSET_END + 1;
    localparam INDEX_END = INDEX_BEGIN + INDEX_LEN - 1;
    localparam TAG_BEGIN = INDEX_END + 1;
    localparam TAG_END = ADDR_WIDTH - 1;
    localparam TAG_LEN = ADDR_WIDTH - TAG_BEGIN;
    typedef logic [TAG_LEN-1:0] tag_t;
    typedef logic [INDEX_LEN-1:0] index_t;
    typedef logic [OFFSET_LEN-1:0] offset_t;

    reg [         ADDR_WIDTH-1:0] addr_wb;
    reg [BANK_NUM*DATA_WIDTH-1:0] data_wb;
    reg                           busy_wb;
    reg                           need_wb;

    reg [         ADDR_WIDTH-1:0] addr_cache;
    reg                           miss_cache;
    reg                           set_cache;
    reg                           busy_rd;
    reg [         ADDR_WIDTH-1:0] addr_rd;
    reg [       DATA_WIDTH*2-1:0] data_rd;
    reg                           wen_rd;
    reg                           set_rd;
    reg                           finish_rd;

    CacheBank #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .DATA_WIDTH(DATA_WIDTH),
        .BANK_NUM  (BANK_NUM),
        .CAPACITY  (CAPACITY)
    ) cache_bank (
        .clk      (clk),
        .rstn     (rstn),
        .addr_cpu (addr_cpu),
        .wdata_cpu(wdata_cpu),
        .wen_cpu  (wen_cpu),
        .wmask_cpu(wmask_cpu),
        .ren_cpu  (ren_cpu),
        .rdata_cpu(rdata_cpu),
        .hit_cpu  (hit_cpu),

        .addr_wb(addr_wb),
        .data_wb(data_wb),
        .busy_wb(busy_wb),
        .need_wb(need_wb),

        .addr_cache(addr_cache),
        .miss_cache(miss_cache),
        .set_cache (set_cache),

        .busy_rd  (busy_rd),
        .addr_rd  (addr_rd),
        .data_rd  (data_rd),
        .wen_rd   (wen_rd),
        .set_rd   (set_rd),
        .finish_rd(finish_rd)
    );

    reg [  ADDR_WIDTH-1:0] addr_mem;
    reg [DATA_WIDTH*2-1:0] data_mem;
    reg [  OFFSET_LEN-2:0] bank_index;
    reg                    finish_wb;
    CacheWriteBuffer #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .DATA_WIDTH(DATA_WIDTH),
        .BANK_NUM  (BANK_NUM)
    ) cache_write_buffer (
        .clk       (clk),
        .rstn      (rstn),
        .addr_wb   (addr_wb),
        .data_wb   (data_wb),
        .busy_wb   (busy_wb),
        .need_wb   (need_wb),
        .miss_cache(miss_cache),

        .addr_mem  (addr_mem),
        .data_mem  (data_mem),
        .bank_index(bank_index),
        .finish_wb (finish_wb)
    );


    reg [1:0] cache_state;
    reg count;
    reg [ADDR_WIDTH-1:0] addr_reg;
    reg set_reg;
    initial begin
        busy_rd = 0;
        ren_mem = 0;
        wen_rd = 0;
        finish_rd = 0;
        finish_wb = 0;
        addr_reg = 0;
        set_reg = 0;
    end
    parameter IDLE = 2'b00;
    parameter READ = 2'b01;
    parameter WRITE = 2'b10;

    assign wdata_mem = data_mem;
    // assign data_rd = rdata_mem;
    assign wmask_mem = 16'hffff;
    always @(posedge clk) begin
        if (!rstn) begin
            count <= 1'b0;
            busy_rd <= 0;
            ren_mem <= 0;
            wen_rd <= 0;
            finish_rd <= 0;
            finish_wb <= 0;
            addr_reg <= 64'b0;
            set_reg <= 1'b0;
            cache_state <= IDLE;
        end

        case (cache_state)
            IDLE: begin
                busy_rd <= 1'b0;
                wen_rd <= 1'b0;
                finish_rd <= 1'b0;
                finish_wb <= 1'b0;
                if (!miss_cache) begin  // cacheback检查未失配，保持IDLE状态
                    cache_state <= IDLE;
                end
                else begin  // cacheback检查失配，进入READ状态
                    busy_rd <= 1;
                    addr_reg <= addr_cache;
                    set_reg <= set_cache;
                    cache_state <= READ;
                end
            end

            READ: begin
                ren_mem <= 1'b1;
                if (count == 1'b0) begin 
                    cache_state <= READ;
                    raddr_mem <= addr_reg;
                    if (!rvalid_mem) begin
                        // ren_mem <= 1'b1;
                        wen_rd <= 1'b0;
                        finish_rd <= 1'b0;
                    end
                    else begin
                        // ren_mem <= 1'b1;
                        count <= 1'b1;
                        wen_rd <= 1'b1;
                        addr_rd <= addr_reg;
                        set_rd <= set_reg;
                        data_rd <= rdata_mem;
                        raddr_mem <= addr_reg + 'd16;
                    end
                end
                else begin
                    raddr_mem <= addr_reg + 'd16;
                    if (!rvalid_mem) begin
                        // ren_mem <= 1'b1;
                        finish_rd <= 0;
                        cache_state <= READ;
                    end
                    else begin
                        // ren_mem <= 1'b1;
                        count <= 1'b0;
                        finish_rd <= 1'b1;
                        wen_rd <= 1'b1;
                        ren_mem <= 1'b0;
                        addr_rd <= addr_reg + 'd16;
                        set_rd <= set_reg;
                        data_rd <= rdata_mem;
                        if (busy_wb) begin  // write back buffer busy，进入WRITE状态
                            // count <= 1'b1;
                            bank_index <= 1'b0;
                            cache_state <= WRITE;
                            // busy_rd <= 0;
                            // ren_mem <= 0;  // 关闭读内存
                        end
                        else begin  // 否则继续保持IDLE状态
                            // count <= 1'b0;
                            // ren_mem <= 0; // 关闭读内存
                            // busy_rd <= 0;
                            cache_state <= IDLE;
                        end
                    end
                end
            end
            
            WRITE: begin
                // busy_rd <= 0;
                wen_rd <= 1'b0;
                // finish_rd <= 1'b0;
                finish_wb <= 1'b0;
                if(count == 1'b0)begin
                    waddr_mem <= addr_mem;
                    // wdata_mem <= data_mem;
                    bank_index <= 1'b0;
                    wen_mem <= 1'b1;
                    // wmask_mem <= 16'hffff;
                    if(!wvalid_mem) begin 
                        cache_state <= WRITE; 
                    end
                    else begin
                        count <= 1'b1;
                        bank_index <= 1'b1;
                        waddr_mem <= addr_mem + 'd16;
                        // wdata_mem <= data_mem;
                        // wen_mem <= 1'b0;
                        cache_state <= WRITE;
                    end
                end 
                else begin
                    waddr_mem <= addr_mem + 'd16;
                    // wdata_mem <= data_mem;
                    // bank_index <= 1'b1;
                    wen_mem <= 1'b1;
                    // wmask_mem <= 16'hffff;
                    if(!wvalid_mem) begin 
                        cache_state <= WRITE; 
                    end
                    else begin
                        count <= 1'b0;
                        finish_wb <= 1'b1;
                        wen_mem <= 1'b0;
                        cache_state <= IDLE;
                    end
                end
            end
            default: cache_state <= IDLE;
        endcase
    end


endmodule
