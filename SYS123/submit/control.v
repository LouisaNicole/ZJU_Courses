`timescale 1ns / 1ps

module Control(
    input [31:0] inst,
    output [21:0] decode,
    output reg ID_csr_we,
    output reg [1:0] ID_csr_ret,
    output reg [11:0] ID_csr_addr,
    output reg csr_reg
);
    
    reg we_reg, npc_sel, we_mem;
    reg [1:0] alu_asel, alu_bsel, wb_sel;
    reg [2:0] immgen_op, bralu_op, memdata_width;
    reg [3:0] alu_op;

    initial begin
        ID_csr_we = 0; 
        ID_csr_ret = 2'b0;
        ID_csr_addr = 12'b0;
        csr_reg = 0;
    end

    always@(*) begin
        we_reg = 0; npc_sel = 0; we_mem = 0;
        alu_asel = 0; alu_bsel = 0; wb_sel = 0;
        immgen_op = 0; bralu_op = 0; memdata_width = 0;
        alu_op = 0;
        ID_csr_we = 0; ID_csr_addr = 12'b0; csr_reg = 0; ID_csr_ret = 2'b0;

        case (inst[6:0])
        7'b0110011: begin //r
            we_reg = 1; npc_sel = 0; we_mem = 0;
            alu_asel = 1; alu_bsel = 1; wb_sel = 1;
            immgen_op = 0; bralu_op = 0; memdata_width = 0;

            if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b000)begin //add
                alu_op = 4'b0000;
            end 
            else if(inst[31:25] == 7'b0100000 && inst[14:12] == 3'b000)begin //sub
                alu_op = 4'b0001;
            end 
            else if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b001)begin //sll
                alu_op = 4'b0111;
            end 
            else if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b010)begin //slt
                alu_op = 4'b0101;
            end 
            else if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b011)begin //sltu
                alu_op = 4'b0110;
            end 
            else if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b100)begin //xor
                alu_op = 4'b0100;
            end 
            else if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b101)begin //srl
                alu_op = 4'b1000;
            end 
            else if(inst[31:25] == 7'b0100000 && inst[14:12] == 3'b101)begin //sra
                alu_op = 4'b1001;
            end 
            else if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b110)begin //or
                alu_op = 4'b0011;
            end 
            else if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b111)begin //and
                alu_op = 4'b0010;
            end 
            else alu_op = 4'b0000;
        end 

        7'b0010011: begin //i
            we_reg = 1; npc_sel = 0; we_mem = 0;
            alu_asel = 1; alu_bsel = 2'b10; wb_sel = 1;
            immgen_op = 1; bralu_op = 0; memdata_width = 0;
        
            if(inst[14:12] == 3'b000)begin //addi
                alu_op = 4'b0000;
            end 
            else if(inst[14:12] == 3'b010)begin //slti
                alu_op = 4'b0101;
            end 
            else if(inst[14:12] == 3'b011)begin //sltiu
                alu_op = 4'b0110;
            end 
            else if(inst[14:12] == 3'b100)begin //xori
                alu_op = 4'b0100;
            end 
            else if(inst[14:12] == 3'b110)begin //ori
                alu_op = 4'b0011;
            end 
            else if(inst[14:12] == 3'b111)begin //andi
                alu_op = 4'b0010;
            end 
            else if(inst[14:12] == 3'b001)begin //slli
                alu_op = 4'b0111;
            end 
            else if(inst[31:26] == 6'b000000 && inst[14:12] == 3'b101)begin //srli
                alu_op = 4'b1000;
            end 
            else if(inst[31:26] == 6'b010000 && inst[14:12] == 3'b101)begin //srai
                alu_op = 4'b1001;
            end 
            else alu_op = 4'b0000;
        end

        7'b0000011: begin //l
            we_reg = 1; npc_sel = 0; we_mem = 0;
            alu_asel = 1; alu_bsel = 2'b10; wb_sel = 2'b10;
            immgen_op = 3'b001; bralu_op = 0; alu_op = 4'b0000;
        
            if(inst[14:12] == 3'b000)begin //lb
                memdata_width = 3'b100;
            end
            else if(inst[14:12] == 3'b001)begin //lh
                memdata_width = 3'b011;
            end
            else if(inst[14:12] == 3'b010)begin //lw
                memdata_width = 3'b010;
            end
            else if(inst[14:12] == 3'b011)begin //ld
                memdata_width = 3'b001;
            end
            else if(inst[14:12] == 3'b100)begin //lbu
                memdata_width = 3'b111;
            end
            else if(inst[14:12] == 3'b101)begin //lhu
                memdata_width = 3'b110;
            end
            else if(inst[14:12] == 3'b110)begin //lwu
                memdata_width = 3'b101;
            end
            else memdata_width = 3'b000;
        end

        7'b0100011: begin //s
            alu_op = 4'b0000;
            we_reg = 0; npc_sel = 0; we_mem = 1;
            alu_asel = 1; alu_bsel = 2'b10; wb_sel = 0;
            immgen_op = 3'b010; bralu_op = 0;

            if(inst[14:12] == 3'b011)begin //sd
                memdata_width = 3'b001;
            end
            else if(inst[14:12] == 3'b010)begin //sw
                memdata_width = 3'b010;
            end
            else if(inst[14:12] == 3'b001)begin //sh
                memdata_width = 3'b011;
            end
            else if(inst[14:12] == 3'b000)begin //sb
                memdata_width = 3'b100;
            end
            else memdata_width = 3'b000;
        end

        7'b1100011:begin //b
            alu_op = 4'b0000;
            we_reg = 0; npc_sel = 0; we_mem = 0;
            alu_asel = 2'b10; alu_bsel = 2'b10; wb_sel = 0;
            immgen_op = 3'b011; memdata_width = 3'b000;

            if(inst[14:12] == 3'b000)begin //beq
                bralu_op = 3'b001;
            end
            else if(inst[14:12] == 3'b001)begin //bne
                bralu_op = 3'b010;
            end
            else if(inst[14:12] == 3'b100)begin //blt
                bralu_op = 3'b011;
            end
            else if(inst[14:12] == 3'b101)begin //bge
                bralu_op = 3'b100;
            end
            else if(inst[14:12] == 3'b110)begin //bltu
                bralu_op = 3'b101;
            end
            else if(inst[14:12] == 3'b111)begin //bgeu
                bralu_op = 3'b110;
            end
            else bralu_op = 3'b000;
        end

        7'b0110111:begin //lui
            alu_op = 4'b0000;
            we_reg = 1; npc_sel = 0; we_mem = 0;
            alu_asel = 2'b00; alu_bsel = 2'b10; wb_sel = 1;
            immgen_op = 3'b100; bralu_op = 3'b000; memdata_width = 3'b000;
        end
        7'b0010111:begin //auipc
            alu_op = 4'b0000;
            we_reg = 1; npc_sel = 0; we_mem = 0;
            alu_asel = 2'b10; alu_bsel = 2'b10; wb_sel = 1;
            immgen_op = 3'b100; bralu_op = 3'b000; memdata_width = 3'b000;
        end

        7'b1101111:begin //jal
            alu_op = 4'b0000;
            we_reg = 1; npc_sel = 1; we_mem = 0;
            alu_asel = 2'b10; alu_bsel = 2'b10; wb_sel = 2'b11;
            immgen_op = 3'b101; bralu_op = 3'b000; memdata_width = 3'b000;
        end

        7'b1100111:begin //jalr
            alu_op = 4'b0000;
            we_reg = 1; npc_sel = 1; we_mem = 0;
            alu_asel = 2'b01; alu_bsel = 2'b10; wb_sel = 2'b11;
            immgen_op = 3'b001; bralu_op = 3'b000; memdata_width = 3'b000;
        end

        7'b0011011: begin//remian i
            we_reg = 1; npc_sel = 0; we_mem = 0;
            alu_asel = 1; alu_bsel = 2'b10; wb_sel = 1;
            immgen_op = 1; bralu_op = 0; memdata_width = 0;

            if(inst[14:12] == 3'b000)begin //addiw
                alu_op = 4'b1010;
            end 
            else if(inst[14:12] == 3'b001)begin //slliw
                alu_op = 4'b1100;
            end 
            else if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b101)begin //srliw
                alu_op = 4'b1101;
            end 
            else if(inst[31:25] == 7'b0100000 && inst[14:12] == 3'b101)begin //sraiw
                alu_op = 4'b1110;
            end
            else alu_op = 0;
        end

        7'b0111011: begin //remain r
            we_reg = 1; npc_sel = 0; we_mem = 0;
            alu_asel = 1; alu_bsel = 1; wb_sel = 1;
            immgen_op = 0; bralu_op = 0; memdata_width = 0;

            if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b000)begin //addw
                alu_op = 4'b1010;
            end 
            else if(inst[31:25] == 7'b0100000 && inst[14:12] == 3'b000)begin //subw
                alu_op = 4'b1011;
            end 
            else if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b001)begin //sllw
                alu_op = 4'b1100;
            end
            else if(inst[31:25] == 7'b0000000 && inst[14:12] == 3'b101)begin //srlw
                alu_op = 4'b1101;
            end 
            else if(inst[31:25] == 7'b0100000 && inst[14:12] == 3'b101)begin //sraw
                alu_op = 4'b1110;
            end 
            else alu_op = 0;
        end

        7'b1110011: begin
            we_reg = 1;
            ID_csr_we = 1; 
            ID_csr_addr = inst[31:20];
            csr_reg = 1;
            immgen_op = 3'b110;
            wb_sel = 1;
            case (inst[14:12])
                3'b000: begin
                    case (inst[31:20])
                        12'b000000000000: begin // ecall
                            ID_csr_ret = 2'b00;
                        end 
                        12'b000100000010: begin // sret
                            ID_csr_ret = 2'b01;
                        end
                        12'b001100000010: begin // mret
                            ID_csr_ret = 2'b10;
                        end
                        default: ID_csr_ret = 2'b00;
                    endcase
                end
                3'b001: begin // csrrw
                    alu_op = 4'b0001;
                end
                3'b010: begin // csrrs
                    alu_op = 4'b0010;
                end
                3'b011: begin // csrrc
                    alu_op = 4'b0011;
                end
                3'b101: begin // csrrwi
                    alu_op = 4'b0100;
                end
                3'b110: begin // csrrsi
                    alu_op = 4'b0101;
                end
                3'b111: begin // csrrci
                    alu_op = 4'b0110;
                end
                default: alu_op = 4'b0;
            endcase
        end

        default: alu_op = 0;
        endcase
    end

    assign decode = {we_reg,we_mem,npc_sel,immgen_op,alu_op,bralu_op,alu_asel,alu_bsel,wb_sel,memdata_width};
endmodule


    // `define rtype 7'b0110011;
    // `define itype 7'b0010011;
    // `define ltype 7'b0000011;
    // `define stype 7'b0100011;
    // `define btype 7'b1100011;
    // `define luitype 7'b0110111;
    // `define auipctype 7'b0010111;
    // `define jaltype 7'b1101111;
    // `define jalrtype 7'b1100111;
    // `define remainitype 7'b0011011;
    // `define remainrtype 7'b0111011;

    // reg opcode = inst[6:0];

    // wire is_r = opcode == `rtype;
    // wire is_i = opcode == `itype;
    // wire is_l = opcode == `ltype;
    // wire is_s = opcode == `stype;
    // wire is_b = opcode == `btype;
    // wire is_lui = opcode == `luitype;
    // wire is_auipc = opcode == `auipctype;
    // wire is_jal = opcode == `jaltype;
    // wire is_jalr = opcode == `jalrtype;
    // wire is_remaini = opcode == `remainitype;
    // wire is_remainr = opcode == `remainrtype;

    
    // reg we_reg = is_r | is_i | is_l | is_lui | is_remaini |is_remainr;
    // reg npc_sel = is_jal | is_jalr;
    // reg we_mem = is_s;