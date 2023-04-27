// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2018.3 (win64) Build 2405991 Thu Dec  6 23:38:27 MST 2018
// Date        : Tue Feb 14 10:35:39 2023
// Host        : hpl-va025 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub f:/SC2103/Lab2/Lab2.srcs/sources_1/ip/Lab2_mem/Lab2_mem_stub.v
// Design      : Lab2_mem
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a35tcpg236-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "dist_mem_gen_v8_0_12,Vivado 2018.3" *)
module Lab2_mem(a, d, clk, we, spo)
/* synthesis syn_black_box black_box_pad_pin="a[5:0],d[7:0],clk,we,spo[7:0]" */;
  input [5:0]a;
  input [7:0]d;
  input clk;
  input we;
  output [7:0]spo;
endmodule
