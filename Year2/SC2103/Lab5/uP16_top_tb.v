`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   12:31:57 11/23/2018
// Design Name:   uP16_top
// Module Name:   C:/Users/asdouglas/Documents/work/Teaching/CE2003 Digital Systems Design/Xilinx/new_lab5/src/uP16_top_tb.v
// Project Name:  new_lab5
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: uP16_top
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module uP16_top_tb;

	// Inputs
	reg Clk;
	reg Rst;

	// Outputs
	wire [3:0] EX_ALUstatus_d;
	wire [17:0] IF_inst_d;
	wire [15:0] IF_currPC;

	// Instantiate the Unit Under Test (UUT)
	uP16_top uut (
		.Clk(Clk), 
		.Rst(Rst), 
		.EX_ALUstatus_d(EX_ALUstatus_d), 
		.IF_inst_d(IF_inst_d), 
		.IF_currPC(IF_currPC)
	);

	initial begin
		// Initialize Inputs
		Clk = 0;
		Rst = 1;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here
		#20 Rst = 0;
		#500000 $finish();    // this is a catchit. Use the runto button.

	end
	
	always #5 Clk = ~Clk;
      
endmodule

