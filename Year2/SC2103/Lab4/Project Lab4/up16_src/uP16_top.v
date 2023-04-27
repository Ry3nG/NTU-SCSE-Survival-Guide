`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 			NTU
// Engineer: 			Doug maskell
// 
// Create Date:    	14/01/2014 
// Design Name: 
// Module Name:    	uP16_top 
// Project Name: 
// Target Devices: 
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


module uP16_top #(parameter ISIZE=18, DSIZE=16) (
    input Clk, Rst,
	 output [3:0] EX_ALUstatus_d,
	 output [ISIZE-1:0] IF_inst_d, 
	 output [DSIZE-1:0] IF_currPC 
	 );


	// Top intermodule connection wires (PR outputs have "_d" identifier) (grouped by signal source)
	// IF and IF/ID PR
	wire [DSIZE-1:0] IF_PCplus1, IF_PCplus1_d; 
	wire [ISIZE-1:0] IF_inst; 		//no IF_inst_d as defined above
	// ID and ID/EX PR
	wire [DSIZE-1:0] ID_altPC;
	wire [DSIZE-1:0] ID_readData1, ID_readData2, ID_signE_8immed; 
	wire [DSIZE-1:0] ID_readData1_d, ID_readData2_d, ID_signE_8immed_d;
	wire [2:0] ID_RFdest_rd, ID_RFdest_rd_d; 
	wire [3:0] ID_ALUop, ID_ALUop_d;
	// EX and EX/Mem PR
	wire [DSIZE-1:0] EX_ALUresult, EX_ALUresult_d;
	wire [2:0] EX_RFdest_rd_d;
	wire [3:0] EX_ALUstatus;
	// Mem (and Mem/WB RF)
	wire [DSIZE-1:0] M_writeData;


// Module instantiations
IF_stage T1 (
	// Inputs
	.Clk(Clk), .Rst(Rst),
	.sel_PC(ID_sel_PC),
	.alt_PC(ID_altPC),					// input [DSIZE-1:0] ID_Alt_PC_in
	// Outputs
	.inst(IF_inst),						// output [ISIZE-1:0] IF_Inst_out,
	.currPC(IF_currPC),					// output reg [DSIZE-1:0] IF_currPC,
	.PCplus1(IF_PCplus1)					// output [DSIZE-1:0] IF_PCplus1
   );


IF_ID_PR T2 (
	// Inputs
	.Clk(Clk), .Rst(Rst),
	.PCplus1(IF_PCplus1),				// input [DSIZE-1:0] IF_PCplus1
	.inst(IF_inst),						// input [ISIZE-1:0] instruction
	// Outputs
	.PCplus1_o(IF_PCplus1_d),			// output reg [DSIZE-1:0] IF_PCplus1
	.inst_o(IF_inst_d)					// output reg [ISIZE-1:0] IF_Inst_out,
   );


ID_stage T3 (
	// Inputs
	.Clk(Clk), .Rst(Rst),
	.RF_writeEnab(EX_RFwriteEnab_d),
	.inst(IF_inst_d), 					// input [ISIZE-1:0] Inst_in
	.PCplus1(IF_PCplus1_d),				// input [DSIZE-1:0] PCplus1
	.writeData(M_writeData),			// input [DSIZE-1:0] WriteData_In,
	.WB_RFdest_rd(EX_RFdest_rd_d),	// input [2:0] WB_RDest_rd,
	// Outputs
	.alt_PC_o(ID_altPC),					// output [DSIZE-1:0] Alt_PC_out
	.readData1(ID_readData1),			// output [DSIZE-1:0] ReadData1,
	.readData2(ID_readData2),			// output [DSIZE-1:0] ReadData2,
	.signE_8immed(ID_signE_8immed),	// output [DSIZE-1:0] SignE_8immed,
	.WB_dest_rd(ID_RFdest_rd),			// output [2:0] WB_RDest_rd
	.ALUop(ID_ALUop),						//	output [3:0] ALUOp,
	.sel_PC(ID_sel_PC),
	.memWriteEnab(ID_memWriteEnab), 	 
	.memEnab(ID_memEnab), 
	.sel_mem2RF(ID_sel_mem2RF), 
	.sel_ALUsrc1(ID_sel_ALUsrc1),
   //.sel_ALUsrc2(ID_sel_ALUsrc2),
	.RFwriteEnab(ID_RFwriteEnab)
	);


ID_EX_PR T4 (
	// Inputs
	.Clk(Clk), .Rst(Rst),
	.readData1(ID_readData1),			// input [DSIZE-1:0] ReadData1,
	.readData2(ID_readData2),			// input [DSIZE-1:0] ReadData2,
	.signE_8immed(ID_signE_8immed),	// input [DSIZE-1:0] SignE_8immed,
	.WB_dest_rd(ID_RFdest_rd),			// input [2:0] WB_RFdest_rd,
	.ALUop(ID_ALUop),						// input [3:0] ALU operation
	.memWriteEnab(ID_memWriteEnab), 	 
	.memEnab(ID_memEnab), 
	.sel_mem2RF(ID_sel_mem2RF), 
	.sel_ALUsrc1(ID_sel_ALUsrc1),
   //.sel_ALUsrc2(ID_sel_ALUsrc2),
	.RFwriteEnab(ID_RFwriteEnab),
	// Outputs
	.readData1_o(ID_readData1_d),			// output [DSIZE-1:0] ReadData1,
	.readData2_o(ID_readData2_d),			// output [DSIZE-1:0] ReadData2,
	.signE_8immed_o(ID_signE_8immed_d),	// output [DSIZE-1:0] SignE_8immed,
	.WB_dest_rd_o(ID_RFdest_rd_d),		// output [2:0] WB_RFdest_rd,
	.ALUop_o(ID_ALUop_d),					// output [3:0] ALU operation
	.memWriteEnab_o(ID_memWriteEnab_d), 	 
	.memEnab_o(ID_memEnab_d), 
	.sel_mem2RF_o(ID_sel_mem2RF_d), 
	.sel_ALUsrc1_o(ID_sel_ALUsrc1_d),
   //.sel_ALUsrc2_o(ID_sel_ALUsrc2_d),
	.RFwriteEnab_o(ID_RFwriteEnab_d)
	);


EX_stage T5 (
	// Inputs
	.Clk(Clk), .Rst(Rst),
	.readData1(ID_readData1_d),			// input [DSIZE-1:0] ReadData1
	.readData2(ID_readData2_d),			// input [DSIZE-1:0] ReadData
	.signE_8immed(ID_signE_8immed_d),	// input [DSIZE-1:0] SignE_8immed
	.ALUop(ID_ALUop_d),						//	input [3:0] EX_ALUOp
	.sel_ALUsrc1(ID_sel_ALUsrc1_d),
   //.sel_ALUsrc2(ID_sel_ALUsrc2_d),
	// Outputs
	.ALUresult(EX_ALUresult),			 	// output [DSIZE-1:0] ALU Result
	.ALUstatus(EX_ALUstatus)				// output [3:0] ALU_Status,
	);


EX_Mem_PR T6 (
	// Inputs
	.Clk(Clk), .Rst(Rst),
	.sel_mem2Reg(ID_sel_mem2RF_d),
	.RFwriteEnab(ID_RFwriteEnab_d),
	.ALUresult(EX_ALUresult),				// input [DSIZE-1:0] ALU Result
	.RFdest_rd(ID_RFdest_rd_d),			// input [2:0] RDest_rd,
	.ALUstatus(EX_ALUstatus),				//	input [3:0] ALU_Status,
	// Outputs
	.sel_mem2Reg_o(EX_sel_mem2Reg_d),
	.RFwriteEnab_o(EX_RFwriteEnab_d),
	.ALUresult_o(EX_ALUresult_d),			// output [DSIZE-1:0] ALU Result // only for data forwarding
	.RFdest_rd_o(EX_RFdest_rd_d),			// output [2:0] RDest_rd // only for data forwarding
	.ALUstatus_o(EX_ALUstatus_d)			//	output [3:0] ALU_Status
	);


Mem_stage T7 (
	// Inputs
	.Clk(Clk), .Rst(Rst),
	.ALUResult(EX_ALUresult_d),			// input [DSIZE-1:0] ALUResult
	.ALUResult_mem(EX_ALUresult),			// input [DSIZE-1:0] unregistered ALUResult from EX stage
	.readData1(ID_readData1_d),			// input [DSIZE-1:0] unregistered readData1 from ID/EX PR
	.memWriteEnab(ID_memWriteEnab_d),	// input unregistered memWriteEnab from ID/EX PR
	.memEnab(ID_memEnab_d),					// input unregistered memEnab from ID/EX PR
	.sel_mem2reg(EX_sel_mem2Reg_d),		// input select for S4 mux from EX/Mem PR
	// Outputs
	.WB_writeData(M_writeData)			// output [DSIZE-1:0] writeBackData2RF
	);


endmodule
