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


module ID_EX_PR #(parameter ISIZE=18, DSIZE=16) (
   input Clk, Rst, 
	input [DSIZE-1:0] readData1, readData2, signE_8immed,
	input [2:0] WB_dest_rd,
	input [3:0] ALUop,
	input [1:0] Data1_muxCont, Data2_muxCont,
	input memWriteEnab, memEnab, sel_mem2RF,
	input sel_ALUsrc1, RFwriteEnab,
	output reg [DSIZE-1:0] readData1_o, readData2_o, signE_8immed_o,
	output reg [2:0] WB_dest_rd_o,
	output reg [3:0] ALUop_o,
	output reg [1:0] Data1_muxCont_o, Data2_muxCont_o,
	output reg memWriteEnab_o, memEnab_o, sel_mem2RF_o,
	output reg sel_ALUsrc1_o, RFwriteEnab_o
	 );
	 


// ID:EX Pipeline register
always @ (posedge Clk)
	if (Rst) begin
		readData1_o <= 16'b0;		// RegFile Data 1 out
		readData2_o <= 16'b0;		// RegFile Data 2 out
		signE_8immed_o <= 16'b0;	// Sign extend value to EX stage
		WB_dest_rd_o <= 3'b0;		// RegFile write destination forwarded to WB stage (via EX stage0
		ALUop_o <= 4'b0;				// ALU operation to EX stage
		Data1_muxCont_o <= 2'b0; 
		Data2_muxCont_o <= 2'b0;
		memWriteEnab_o <= 1'b0;
		memEnab_o <= 1'b0;
		sel_mem2RF_o <= 1'b0;
		sel_ALUsrc1_o <= 1'b0;
		RFwriteEnab_o <= 1'b0;
		end
	else begin
		readData1_o <= readData1;		// RegFile Data 1 out
		readData2_o <= readData2;		// RegFile Data 2 out
		signE_8immed_o <= signE_8immed;	// Sign extend value to EX stage
		WB_dest_rd_o <= WB_dest_rd;	// RegFile write destination forwarded to WB stage (via EX stage0
		ALUop_o <= ALUop;					// ALU operation to EX stage
		Data1_muxCont_o <= Data1_muxCont; 
		Data2_muxCont_o <= Data2_muxCont;
		memWriteEnab_o <= memWriteEnab;
		memEnab_o <= memEnab;
		sel_mem2RF_o <= sel_mem2RF;
		sel_ALUsrc1_o <= sel_ALUsrc1;
		RFwriteEnab_o <= RFwriteEnab;
		end

endmodule

