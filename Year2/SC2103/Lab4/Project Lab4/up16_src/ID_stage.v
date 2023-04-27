`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 			NTU
// Engineer: 			Doug
// 
// Create Date:    	Nov 2013 
// Design Name: 
// Module Name:    	IF_stage 
// Project Name: 		uP16_5Stage
// Target Devices: 	Spartan 6
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////

//`include "uP16_define.v"

module ID_stage #(parameter ISIZE=18, DSIZE=16) (
    input Clk, Rst,
	 input RF_writeEnab,
	 input [ISIZE-1:0] inst, 
	 input [DSIZE-1:0] PCplus1, writeData, 
	 input [2:0] WB_RFdest_rd,
	 output [DSIZE-1:0] alt_PC_o,
	 //output reg	[`DSIZE-1:0] EX_PCplus1,
	 output [DSIZE-1:0] readData1, readData2, signE_8immed,			
	 output [2:0] WB_dest_rd,
	 output [3:0] ALUop,
 	 output sel_PC, 
	 output memWriteEnab, memEnab, sel_mem2RF,
    output sel_ALUsrc1, 
    //output sel_ALUsrc2, 
	 output RFwriteEnab
    );

	
	wire [2:0] RR1_rd, RR2_rs;
	
	// module instantiations
	// Reg File
	Reg_File EX_1 (
		.Clk(Clk), .Rst(Rst),
		.Write_Enab(RF_writeEnab),
		.ReadReg1_In(RR1_rd),
		.ReadReg2_In(RR2_rs),
		.WriteReg_In(WB_RFdest_rd),
		.ReadData1_Out(readData1),
		.ReadData2_Out(readData2),
		.WriteData_In(writeData)
		);
		
		
	// Control	
	Control EX_3 (
	.inst(inst),
	.readData1(readData1),
	.readData2(readData2),
	.sel_ALUsrc1(sel_ALUsrc1),
	//.sel_ALUsrc2(sel_ALUsrc2),
	.PC_select(sel_PC),
	.memWriteEnab(memWriteEnab), 
	.memEnab(memEnab), 
	.mem2Reg(sel_mem2RF), 
	.RFwriteEnab(RFwriteEnab),
	.ALUop(ALUop)
	);


	// Split up Instruction into required wires (note OPCode and Funct are in Control module
	assign signE_8immed = {{8{inst[7]}}, inst[7:0]};		// 16 bit sign extended 8 bit immediate value
	// the register signals
	assign RR1_rd = inst[13:11];		// 3 bit Reg file source_1 (address1)
	assign RR2_rs = inst[10:8];		// 3 bit Reg file source_2 (address2)
	assign WB_dest_rd = inst[13:11];	// 3 bit Reg file destination (forward to WB stage)
	// Mux to select PC for Branch 
	assign alt_PC_o = PCplus1 + signE_8immed;		// Next PC for branches

endmodule			// End of ID_stage module 



// The 8 entry Register File. Note R0 is always 0.
//reg file is continious read and clocked write.
module Reg_File #(parameter ISIZE=18, DSIZE=16) (
	input Clk, Rst,
	input Write_Enab,
	input [2:0] ReadReg1_In, ReadReg2_In, WriteReg_In, 
	input [DSIZE-1:0] WriteData_In,
	output [DSIZE-1:0] ReadData1_Out, ReadData2_Out
	);

	// register array definition (Only 8 registers)
	reg [DSIZE-1:0] RegFile[0:7];
	
	always @ (posedge Clk)  // Only a write is Clocked
		if(Rst)
			begin
				RegFile[0] <= 0;
				RegFile[1] <= 0;
				RegFile[2] <= 0;
				RegFile[3] <= 0;
				RegFile[4] <= 0;
				RegFile[5] <= 0;
				RegFile[6] <= 0;
				RegFile[7] <= 0;
				end
			else 
				RegFile[WriteReg_In] <= ((Write_Enab == 1) && (WriteReg_In != 0)) ? WriteData_In : RegFile[WriteReg_In];
				
	assign ReadData1_Out = RegFile[ReadReg1_In];	
	assign ReadData2_Out = RegFile[ReadReg2_In];

endmodule // End of RegFile module




module Control #(parameter ISIZE=18, DSIZE=16) (
	input [ISIZE-1:0] inst,
	input [DSIZE-1:0] readData1, readData2,
	output reg sel_ALUsrc1,   
	//output reg sel_ALUsrc2,   
	//output reg Sel_PC_Br_Jmp, Sel_PC_BJ_RF, Sel_RF_dest, Sel_ALU_PC1,
	output reg PC_select,  
	output reg memWriteEnab, memEnab, mem2Reg,
	output reg RFwriteEnab,
	output reg [3:0] ALUop
	);
	
	// define op codes
	parameter OP0=0, LW=1, SW=2, LLI=3, LUI=4, ADDI=5, BEQ=8, BNE=9, BLT=10, BGT=11;
	
	always @ *
		begin
			ALUop = 4'b0000;			// initialise default values //(NOP)
			PC_select = 1'b0;			// S1: def = 0	// def is PC=PC+1
			sel_ALUsrc1 = 1'b0;		// S2: def = 0	// (RF_Data 1)	
			//sel_ALUsrc2 = 1'b0;		// S3: def = 0	// (RF_Data 2)
			mem2Reg = 1'b0;			// S4: def = 0	// default is ALU result writeback
			RFwriteEnab = 1'b1;		// def = 1 		// default is RF write
			memWriteEnab = 1'b0;		// def = 0		// default is No memory write
			memEnab = 1'b0;			// def = 0		// default is memory disabled
			
			case(inst[17:14])		// The OPCode
				OP0	:	begin 
									ALUop = inst[3:0];	// ALUOp is bottom 4 bits of Function field
									end
				LW		:	begin	
									ALUop = 4'b0001;			// ALU does an ADD (Rs+immed)
									sel_ALUsrc1 = 1'b1;		// S2: Immed on data1
									mem2Reg = 1'b1;			// S4:
									memEnab = 1'b1;
									end
				SW		:	begin	
									ALUop = 4'b0001;			// ALU does an ADD (Rs+immed)
									sel_ALUsrc1 = 1'b1;		// S2: Immed on data1
									memWriteEnab = 1'b1;
									memEnab = 1'b1;
									RFwriteEnab = 1'b0;		// no Rf writeback		
									end
				LLI	:	begin	
									ALUop = 4'b1011;			// ALU does flow through on Rd (similar to mov (0x0A))
									sel_ALUsrc1 = 1'b1;		// S2:									
									//ALUop = 4'b1010;			// ALU does flow through on Rs (same as mov (0x0A))
									//sel_ALUsrc2 = 1'b1;		// S3:									
									end
				LUI	:	begin	
									ALUop = 4'b1100;			// ALU does something strange. Look at ALU code)
									sel_ALUsrc1 = 1'b1;		// S3:									
									//ALUop = 4'b1011;			// ALU does something strange. Look at ALU code)
									//sel_ALUsrc2 = 1'b1;		// S3:									
									end
				ADDI		:	begin	
									ALUop = 4'b0001;			// ALU does an ADD (Rd <- Rs+immed) 			// check this????
									sel_ALUsrc1 = 1'b1;		// S2: Immed on data1									
									end
				BEQ		:	begin	
									PC_select = (readData1 == readData2) ? 1'b1 : 1'b0;	// S1: 
									RFwriteEnab = 1'b0;		// Branch does not write back
									end
				BNE		:	begin	
									PC_select = (readData1 != readData2) ? 1'b1 : 1'b0;	// S1: 
									RFwriteEnab = 1'b0;	// Branch does not write back	
									end
				BLT		:	begin	
									PC_select = (readData1 < readData2) ? 1'b1 : 1'b0; // S1: 
									RFwriteEnab = 1'b0;	// Branch does not write back
									end
				BGT		:	begin	
									PC_select = (readData1 > readData2) ? 1'b1 : 1'b0;	// S1: 
									RFwriteEnab = 1'b0;	// Branch does not write back
									end
				default	:	begin 
									ALUop = 4'b0000;			// Not needed, Covered above
									RFwriteEnab = 1'b0;		// All Reserved must not write back
									end
			endcase
		end
	

endmodule		// End of Control module
