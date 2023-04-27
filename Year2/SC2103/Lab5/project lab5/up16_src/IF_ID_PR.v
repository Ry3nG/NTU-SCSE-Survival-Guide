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


module IF_ID_PR #(parameter ISIZE=18, DSIZE=16) (
    input Clk, Rst, 
	 input [DSIZE-1:0] PCplus1,
	 input [ISIZE-1:0] inst,
	 output reg [DSIZE-1:0] PCplus1_o,
	 output reg [ISIZE-1:0] inst_o 
	 );


// IF:ID Pipeline register
always @ (posedge Clk)
	if (Rst) begin
		inst_o <= 18'b0;		// The current Instruction 
		PCplus1_o <= 16'b0;		// The next PC
		end
	else begin
		inst_o <= inst;		// The current Instruction 
		PCplus1_o <= PCplus1;	// The next PC	
		end

endmodule


