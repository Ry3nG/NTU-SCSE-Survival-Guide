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

module Mem_stage #(parameter ISIZE=18, DSIZE=16) (
     input Clk, 
     //input Rst, 
	 input [DSIZE-1:0] ALUResult,
	 input [9:0] ALUResult_mem,		  // not registered, from EX stage
	 input [DSIZE-1:0] readData1,				// not registered, from EX stage
	 input memWriteEnab, memEnab, 			// not registered, from EX stage
	 input sel_mem2reg,  
	 output [DSIZE-1:0] WB_writeData
    );

// Note the Mem and WB stages represent a single stage (Mem) as WB occurs on the clock 
//    at the end of the Mem stage and as such there is no need for a seperate WB stage.

	wire [DSIZE-1:0] memData_out;


	// module instantiations
	// Data Memory
	D_mem DM_1 (
		.Data_out(memData_out),
		.Data_in(readData1),	 
		.Add_In(ALUResult_mem[9:0]), 
		.Write_Enab(memWriteEnab), 
		.Enable(memEnab),
		.Clk_In(Clk)
	);


	
	// wire assignments
	// Mux S4
	assign WB_writeData = (sel_mem2reg) ? memData_out : ALUResult; 
	


endmodule

