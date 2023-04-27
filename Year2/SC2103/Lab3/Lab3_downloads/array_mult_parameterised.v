`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:41:46 09/04/2019 
// Design Name: 
// Module Name:    six_bit_array_mult 
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


module array_mult #(parameter SIZE=8)(input [SIZE-1:0] a, b, output reg [2*SIZE-1:0] P);

	reg [SIZE-1:0] index, index1;		// index for FOR loops
	reg [SIZE-1:0] pp_tmp, P_tmp;		// these are needed as cannot access individual bits of memory
	reg [SIZE:0] PP_tmp;				// this is needed as you cannot access individual bits of memory
	reg [SIZE-1:0] pp [0:SIZE-1];		// For Multiplicand masked by Multiplier bits
	reg [SIZE:0] PP [0:SIZE-1];		// allow extra bit. Will ignore for all except last Partial Product
	reg [SIZE:0] Isum [0:SIZE-1];		// intermediate PP Sums.

	// generate partial products
	always @ *
	begin
      for(index=0; index<SIZE; index=index+1)	// Multiplicand masked by Multiplier bits
			pp[index] = a & {SIZE{b[index]}};
      for(index=0; index<SIZE; index=index+1) 
		begin
			pp_tmp = pp[index];
			if (index == 0)
				// add in the MSB 1 for first PP
				PP[index] = {1'b1, ~pp_tmp[SIZE-1], pp_tmp[SIZE-2:0]};
			else if (index == SIZE-1)
				// Invert last PP and add in the MSB 1
				PP[index] = {1'b1, pp_tmp[SIZE-1], ~pp_tmp[SIZE-2:0]};
			else
				PP[index] = {1'b0, ~pp_tmp[SIZE-1], pp_tmp[SIZE-2:0]};
		end  
   	end
	
	// generate intermediate sums and result (P)
	always @ *
	begin
      Isum[0]=PP[0];
		for(index1=1; index1<SIZE; index1=index1+1)	// sum up PPs
		begin
			PP_tmp = Isum[index1-1];
			Isum[index1] = PP[index1] + PP_tmp[SIZE:1]; // add PP[i] + PP[i-1]
			P_tmp[index1-1] = PP_tmp[0];	// LSB of each Isum TO P (P0 to SIZE-2)
		end
		
		// Now generate result (P)
		P = {Isum[SIZE-1], P_tmp[SIZE-2:0]}; 
		
	end
	
endmodule


