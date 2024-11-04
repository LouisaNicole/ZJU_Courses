module BranchPrediction #(
    parameter DEPTH      = 32,  // BTB 和 BHT 表项的个数
    parameter ADDR_WIDTH = 64,  // 地址宽度
    parameter STATE_NUM  = 2    // BHT 的分支预测器的位数
) (
    input                   clk,
    input                   rst,
    // IF 阶段进行预测的部分
    input  [ADDR_WIDTH-1:0] pc_if,          // 当前的 PC，用于索引对应的表项
    output                  jump_if,        // BHT 判断是否要跳转
    output [ADDR_WIDTH-1:0] pc_target_if,   // BTB 给出跳转的目标地址
    // EXE 阶段进行跳转的确认和修正，BHT、BTB 的更新
    input [ADDR_WIDTH-1:0] pc_exe,          // 跳转指令的地址，用于索引 BTB 和 BHT
    input [ADDR_WIDTH-1:0] pc_target_exe,   // 跳转的目标，更新 BTB
    input                  jump_exe,        // 是否发生跳转，跳转与否更新 BHT
    input                  is_jump_exe      // 是否是跳转指令，是跳转指令 BTB、BHT 才做对应处理
);

    localparam INDEX_BEGIN = 2;
    localparam INDEX_LEN = $clog2(DEPTH);
    localparam INDEX_END = INDEX_BEGIN + INDEX_LEN - 1;
    localparam TAG_BEGIN = INDEX_END + 1;
    localparam TAG_END = ADDR_WIDTH - 1;
    localparam TAG_LEN = TAG_END - TAG_BEGIN + 1;

    typedef logic [TAG_LEN-1:0] tag_t;
    typedef logic [INDEX_LEN-1:0] index_t;
    typedef logic [STATE_NUM-1:0] state_t;
    typedef logic [ADDR_WIDTH-1:0] addr_t;

    typedef struct {
        tag_t   tag;
        addr_t  target; // BTB 部分（跳转目标地址）
        state_t state;  // BHT 部分（预测状态比特）
        logic   valid;
    } BTBLine;          // BTB、BHT 表项

    BTBLine btb       [DEPTH-1:0];  // 完整的 BTB、BHT 

    tag_t   tag_exe;
    index_t index_exe;
    BTBLine btb_exe;
    assign tag_exe   = pc_exe[TAG_END:TAG_BEGIN];
    assign index_exe = pc_exe[INDEX_END:INDEX_BEGIN];
    assign btb_exe   = btb[index_exe];  // EXE 阶段的索引和对应表项的结果

    tag_t   tag_if;
    index_t index_if;
    BTBLine btb_if;
    assign tag_if   = pc_if[TAG_END:TAG_BEGIN];
    assign index_if = pc_if[INDEX_END:INDEX_BEGIN];
    assign btb_if   = btb[index_if];    // IF 阶段的索引和对应表项的结果

    assign jump_if = (btb[index_if].tag==tag_if) && btb_if.state[1];
    assign pc_target_if = btb_if.target;

    always @(posedge clk or posedge rst) begin
        if(rst) begin
            // 初始化 BTB 和 BHT 表项
            for(integer i = 0; i < DEPTH; i = i + 1) begin
                btb[i].tag <= 57'b0;
                btb[i].target <= 64'b0;
                btb[i].state <= 2'b0;
                btb[i].valid <= 1'b0;
            end
        end
        else begin
            if(is_jump_exe) begin //是跳转指令
                if(btb[index_exe].valid == 0) begin
                    btb[index_exe].valid <= 1;
                    btb[index_exe].tag <= tag_exe;
                    btb[index_exe].target <= pc_target_exe;
                    btb[index_exe].state <= 2'b00;
                end
                else if(btb[index_exe].tag != tag_exe)begin
                    btb[index_exe].tag <= tag_exe;
                    btb[index_exe].target <= pc_target_exe;
                    // btb[index_exe].state <= 2'b00;
                    if(jump_exe) // 跳转
                        btb[index_exe].state <= 2'b01;
                    else
                        btb[index_exe].state <= 2'b00;
                end
                
                else if(jump_exe) begin // 跳转
                    // btb[index_exe].target <= pc_target_exe;
                    if(btb[index_exe].state == 2'b00) begin
                        btb[index_exe].state <= 2'b01;
                    end
                    else begin
                        btb[index_exe].state <= 2'b11;
                        // btb[index_exe].target <= pc_target_exe;
                    end
                end 
                else begin
                    if(btb[index_exe].state == 2'b11) begin
                        btb[index_exe].state <= 2'b10;
                    end
                    else begin
                        btb[index_exe].state <= 2'b00;
                    end
                end
                
            end
            // btb[index_exe] <= btb_exe;  // 更新 BTB 表项
        end
    end


endmodule