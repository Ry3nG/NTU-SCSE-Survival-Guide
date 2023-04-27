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

module EX_stage #(parameter ISIZE=18, DSIZE=16) (
     //input Clk, Rst,
	 input [DSIZE-1:0] readData1, readData2,
	 input [DSIZE-1:0] Mem_ALUresult, WB_result,			
	 input [DSIZE-1:0] signE_8immed,
	 input [3:0] ALUop,
	 input [1:0] Data1_muxCont, Data2_muxCont,
	 input sel_ALUsrc1, 
	 output [3:0] ALUstatus,
	 output [DSIZE-1:0] ALUresult
    );


	wire [DSIZE-1:0] IN_data1, IN_data2, ALU_data1, ALU_data2;


	// module instantiations
	// ALU
	ALU EX_1 (
		.ALUData1(ALU_data1), 
		.ALUData2(ALU_data2),
		.ALUControl(ALUop),
		.ALUResult(ALUresult),
		.ALUFlag(ALUstatus)
		);
	
	
	// Muxes at input of ALU
	// First is ReadData 1, second is ReadData2
	assign IN_data1 = (sel_ALUsrc1) ? signE_8immed : readData1; 	// Mux to select RegFile_Data1 (sel_ALUsrc1=0) or SignE_8immed inputs	
	assign IN_data2 = readData2; 	// No Mux to select RegFile_Data2 
	// Then Data Forwarding Muxes. First is ReadData 1, second is ReadData2
	assign ALU_data1 = (Data1_muxCont == 1 )? Mem_ALUresult : (Data1_muxCont == 2 )? WB_result : IN_data1;
	assign ALU_data2 = (Data2_muxCont == 1 )? Mem_ALUresult : (Data2_muxCont == 2 )? WB_result : IN_data2;
	
endmodule			// End of EX_stage module 





// The ALU
module ALU #(parameter ISIZE=18, DSIZE=16)(
	input [DSIZE-1:0] ALUData1, ALUData2,
	input [3:0] ALUControl,
	output [3:0] ALUFlag,
	output reg [DSIZE-1:0] ALUResult
	);

	// define ALU codes
	parameter NOP=0, ADD=1, SUB=2, AND=3, OR=4, NAND=5, NOR=6, XOR=7, NOT=8, MOV=10, LLI=11, LUI=12;
	
	reg carry;
		
	always @ *
		begin
			//Carry = 0;
			case(ALUControl)
				NOP		:	ALUResult = 16'b0;
				ADD		:	{carry, ALUResult} = ALUData1 + ALUData2;
				SUB		:	{carry, ALUResult} = ALUData1 - ALUData2;
				AND		:	ALUResult = ALUData1 & ALUData2;
				OR			:	ALUResult = ALUData1 | ALUData2;
				NAND		:	ALUResult = ~(ALUData1 & ALUData2);
				NOR		:	ALUResult = ~(ALUData1 | ALUData2);
				XOR		:	ALUResult = ALUData1 ^ ALUData2;
				NOT		:  ALUResult = ~ALUData2;
				MOV		:	ALUResult = ALUData2;
				LLI		:	ALUResult = ALUData1;
				LUI		:	ALUResult = {ALUData1[7:0], ALUData2[7:0]};
				default	:	ALUResult = 0;				
			endcase
		end
	

		// Assign ALU Flags LSB to MSB
		//Z, GTZ, LTZ, Carry, (OvFlow, etc: Later)
		assign ALUFlag[0] = (ALUResult == 0) ? 1'b1 : 1'b0;
		assign ALUFlag[1] = ((ALUResult != 0) && (ALUResult[DSIZE-1] == 0)) ? 1'b1 : 1'b0;
		assign ALUFlag[2] = (ALUResult[DSIZE-1] == 1) ? 1'b1 : 1'b0;
		assign ALUFlag[3] = 1'b0;		// fix this later

endmodule		// End of ALU module


