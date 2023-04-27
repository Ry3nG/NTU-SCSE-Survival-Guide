`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 			NTU
// Engineer: 			Doug
// 
// Create Date:    	Nov 2014 
// Design Name: 
// Module Name:    	IF_stage 
// Project Name: 	uP16_5Stage
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

module Mem_WB_PR #(parameter DSIZE=16) (
    input Clk, Rst, 
	 input [DSIZE-1:0] WB_writeData,
	 output reg [DSIZE-1:0] WB_writeData_o
    );
// Note this stage is only used for data forwarding.

// Mem:WB Pipeline register
always @ (posedge Clk)
	if (Rst) begin
		WB_writeData_o <= 16'b0;			
		end
	else begin
		WB_writeData_o <= WB_writeData;	
		end
endmodule

