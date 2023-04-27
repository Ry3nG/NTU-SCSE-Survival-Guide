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


module EX_Mem_PR #(parameter ISIZE=18, DSIZE=16) (
   input Clk, Rst, 
	//input memWriteEnab, memEnab, 			// not registered 
	input sel_mem2Reg, RFwriteEnab, 
	input [DSIZE-1:0] ALUresult,
	input [2:0] RFdest_rd, 
	input [3:0] ALUstatus,
	//output reg memWriteEnab_o, memEnab_o, 			// not registered 
	output reg sel_mem2Reg_o, RFwriteEnab_o, 
	output reg [DSIZE-1:0] ALUresult_o,
	output reg [2:0] RFdest_rd_o,
	output reg [3:0] ALUstatus_o
	 );


// ID:EX Pipeline register
always @ (posedge Clk)
	if (Rst) begin
		sel_mem2Reg_o <= 1'b0;			// control signal to mux in Mem stage
		RFwriteEnab_o <= 1'b0;			// control to RF
		ALUresult_o <= 16'b0;			// output data
		RFdest_rd_o <= 3'b0;				// RegFile write destination 
		ALUstatus_o <= 4'b0;				// ALU status
		end
	else begin
		sel_mem2Reg_o <= sel_mem2Reg;	// control signal to mux in Mem stage
		RFwriteEnab_o <= RFwriteEnab;	// control to RF
		ALUresult_o <= ALUresult;		// output data
		RFdest_rd_o <= RFdest_rd;		// RegFile write destination 
		ALUstatus_o <= ALUstatus;		// ALU status
		end

endmodule

