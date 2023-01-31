//Module:   clock generator
//Function: divides the 100MHz clock by 2^25 to give a slow clock of around 1/3 s period

module clkgen( input    clk_in,
               output   clk_out );

reg [27:0] counter = 28'd0;

always @(posedge clk_in)
begin
    counter <= counter + 1'b1;
end

assign clk_out = counter[27];
//assign seg_clk = counter[20];

endmodule