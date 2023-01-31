`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    13:16:40 11/15/2018 
// Design Name: 
// Module Name:    top_FSM 
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
module top_FSM( input clk, rst, fifty, dollar, cancel, 
					 input sel,
                output insert_coin, money_return, dispense,
					 output sClk,
					 output [3:0] anode_L,
					 output [6:0] seg_L);
	 
	 wire [1:0] st;
	 
	 lab1_FSM U1 (.clk(sClk), .rst(rst), .fifty(fifty), .dollar(dollar), .cancel(cancel),
						.insert_coin(insert_coin), .money_return(money_return), .dispense(dispense), .st(st));
	 clkgen   U5 (.clk_in(clk), .clk_out(sClk));
	 seven_seg U6 (.a({2'b00,st}), .clk(clk), .rst(rst), .sel(sel), .anode_L(anode_L), .seg_L(seg_L));

endmodule

