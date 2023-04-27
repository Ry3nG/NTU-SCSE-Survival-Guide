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

module IF_stage #(parameter ISIZE=18, DSIZE=16) (
    input Clk, Rst, sel_PC,
	 input [DSIZE-1:0] alt_PC,
	 output [ISIZE-1:0] inst,
	 output reg [DSIZE-1:0] currPC,	// not used in subsequent modules
	 output [DSIZE-1:0] PCplus1
	 );


	wire [DSIZE-1:0] nextPC;


// module instantiations
//Instruction memory
	I_mem IF_1 (
			.Data_Out(inst),			// output [17 : 0] data out
    		.Add_In(nextPC[9:0]),	    // input [9 : 0] address 		
    		.Clk_In(Clk)				// input clock
   	);


// generate next PC logic

	assign PCplus1 = currPC + 1;
	assign nextPC = sel_PC ? alt_PC : PCplus1;


// PC
always @ (posedge Clk)
	if (Rst) currPC <= 16'hFFFF;	//if (Rst) IF_currPC <= 16'b0;	// use -1 as Memory address is using IF_nextPC
	else currPC <= nextPC;


endmodule


