
module multiplier(
   a,   //1st operand
   b,   //2nd operand
   out   //output
   );

   parameter DSIZE = 8;
   
   input [DSIZE-1:0] a, b;
   output [DSIZE-1:0] out;
   
assign out = a*b;

endmodule
   
       
