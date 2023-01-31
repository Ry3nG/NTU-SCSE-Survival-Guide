`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 31.01.2023 10:29:46
// Design Name: 
// Module Name: lab1_FSM
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


module lab1_FSM(
    input clk, rst, fifty, dollar, cancel,
    output reg insert_coin, money_return, dispense, output reg [1:0]st 
    );
    parameter INIT = 0, S50c=1, VEND=2, RETURN=3;
    
    reg [1:0] nst; // declare next state variable
    
   //reg[1:0] st; // declare current state variable
    
    always @(posedge clk) begin
        if(rst) begin
            st<=INIT;
         end else begin
            st <= nst;
         end
     end
     
    always @* begin
        nst = st;
        case(st)
            INIT: begin
                    insert_coin =1;
                    money_return =0;
                    dispense =0;
                    if(fifty) nst = S50c;
                    if(dollar) nst = VEND;
                   // nst = INIT;
                end
            S50c: begin
                    insert_coin=1;
                    money_return=0;
                    dispense=0;
                    if(fifty) nst = VEND;
                    if(dollar) nst = RETURN;
                    if(cancel) nst = RETURN;
                    //nst = S50c;
                end
             VEND: begin
                    insert_coin = 0;
                    money_return =0;
                    dispense = 1;
                    //nst = VEND;
                end
             RETURN: begin
                    insert_coin = 0;
                    money_return = 1;
                    dispense = 0;
                    nst = INIT;
                end
             endcase
         end
                
endmodule
