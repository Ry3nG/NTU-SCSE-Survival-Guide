`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 31.01.2023 10:48:01
// Design Name: 
// Module Name: lab1_FSM_tb
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


module lab1_FSM_tb;
    reg clk, rst, fifty, dollar, cancel;
    wire [1:0] st;
    
    //DUT
    lab1_FSM DUT(
    .clk(clk),
    .rst(rst),
    .fifty(fifty),
    .dollar(dollar),
    .cancel(cancel),
    .st(st),
    .insert_coin(insert_coin),
    .money_return(money_return),
    .dispense(dispense)
    );
    
    always #5 clk = ~clk;
    
    //initial
    initial begin
        clk = 0; rst = 1; fifty = 0; dollar = 0; cancel = 0;
        #10 rst = 0;    // to INIT (0) state
        #10 fifty = 1;    // to S50c (1) state
        #10 fifty = 0;
        #10 fifty = 1;    // to VEND (2) state
        #10 fifty = 0;
        #20 rst = 1;    // RESET, to INIT (0) state
        #10 rst = 0;
        #10 dollar = 1;    // to  VEND (2) state
        #10 dollar = 0;
        #20 rst = 1;    // RESET, to INIT (0) state
        #10 rst = 0;
        #10 fifty = 1;    // to S50c (1) state
        #10 fifty = 0;
        #10 dollar = 1;    // to RETURN (3) state
        #10 dollar = 0;    // to INIT (0) state
        #20 fifty = 1;    // to S50c (1) state
        #10 fifty = 0;
        #10 cancel = 1;    // to RETURN (3) state
        #10 cancel = 0;    // to INIT (0) state
        
        #20 $finish;
    end
    
endmodule
