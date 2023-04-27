`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 18.01.2021 15:59:31
// Design Name: 
// Module Name: Lab2_imp
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Lab2_imp(input clk, rst, write_en, save_data, show_reg, sel,
                input [7:0] d_in, 
                output sClk,
				output [3:0] anode_L,
				output [6:0] seg_L);
	 
	 wire [7:0] tmp_data;
	 
	 // Instantiate your Lab2_top module here. Connect d_out to tmp_data.
      Lab2_top U1 (
      .clk(clk),
      .rst(rst),
      .write_en(write_en),
      .save_data(save_data),
      .show_reg(show_reg),
      .d_in(d_in),
      .d_out(tmp_data)
    );
    
	 clkgen   U5 (.clk_in(clk), .clk_out(sClk));
	 seven_seg U6 (.a(tmp_data), .clk(clk), .rst(rst), .sel(sel), .anode_L(anode_L), .seg_L(seg_L));

endmodule

