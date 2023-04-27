`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:51:23 03/27/2013 
// Design Name: 
// Module Name:    uP16_AtlysImplementation 
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
module uP16_BASYS3_top(
    input clk, rst, sel,
	output [3:0] I_Status,
	//output [17:0] I_IF_ID_Inst_out, 
	output [6:0] seg_L,
    output [3:0] anode_L    

	 );

	wire [15:0] I_IF_currPC;

	// instantiale modules
	uP16_top Imp1 (
		// Inputs
		.Clk(sClk), .Rst(rst),
		// Outputs
		.EX_ALUstatus_d(I_Status), 		// output [7:0] Status,
		.IF_inst_d(I_IF_ID_Inst_out), 		// output [17:0] IF_ID_Inst_out,
		.IF_currPC(I_IF_currPC)			// output [15:0] IF_currPC
   		);

	 clkgen   Imp2 (.clk_in(clk), .clk_out(sClk));
	 seven_seg Imp3 (.a(I_IF_currPC), .clk(clk), .rst(rst), .sel(sel), .anode_L(anode_L), .seg_L(seg_L));



endmodule






