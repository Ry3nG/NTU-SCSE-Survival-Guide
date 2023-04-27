`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 14.02.2023 10:31:41
// Design Name: 
// Module Name: Lab2_top
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


module Lab2_top(
    input clk,
    input rst,
    input write_en,
    input save_data,
    input show_reg,
    input [7:0] d_in,
    output [7:0] d_out
    );
    
    reg [7:0] reg_d;
    wire [7:0] mem_d;
    
    // Instantiate the Lab2_mem module
    Lab2_mem U1 (
  .a(d_in[5:0]),      // input wire [5 : 0] a
  .d(reg_d),      // input wire [7 : 0] d
  .clk(clk),  // input wire clk
  .we(write_en),    // input wire we
  .spo(mem_d)  // output wire [7 : 0] spo
);

always @ (posedge clk)
    if (rst) reg_d <= 0;
    else if (save_data) reg_d <= d_in;
    
/*
    always @(posedge clk or posedge rst) begin
        if(rst) begin
            reg_d <= 8'h0;
        end else if (save_data) begin
            reg_d <= d_in;
        end
    end
    */
    
    assign d_out = (show_reg) ? mem_d : reg_d;
    
endmodule
