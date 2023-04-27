module array_mult_6bit (input [5:0] a, b, output [11:0] P);

	wire [5:0] pp0, pp1, pp2, pp3, pp4, pp5;
	wire [5:0] PP0, PP1, PP2, PP3, PP4;	// the Partial Products
	wire [6:0] PP5;		// The last Partial Product has extra bit
	wire [6:0] Isum1, Isum2, Isum3, Isum4;	// The Intermediate Sums

	// generate partial products
	assign pp0 = b & {6{a[0]}};
	assign PP0 = {1'b1,~pp0[5], pp0[4:1]};  // LSB (pp0[0]=a0a0) TO P[0]
	assign pp1 = b & {6{a[1]}};
	assign PP1 = {~pp1[5], pp1[4:0]};
	assign pp2 = b & {6{a[2]}};
	assign PP2 = {~pp2[5], pp2[4:0]};
	assign pp3 = b & {6{a[3]}};
	assign PP3 = {~pp3[5], pp3[4:0]};
	assign pp4 = b & {6{a[4]}};
	assign PP4 = {~pp4[5], pp4[4:0]};
	assign pp5 = b & {6{a[5]}};
	assign PP5 = {1'b1, pp5[5], ~pp5[4:0]};
	
	// The adders (the Intermediate Sums)	// Remember (pp0[0]) TO P[0]
	assign Isum1 = PP1 + PP0;		// Remember (Isum1[0]) TO P[1]
	assign Isum2 = PP2 + Isum1[6:1];	// Remember (Isum2[0]) TO P[2]
	assign Isum3 = PP3 + Isum2[6:1];	// Remember (Isum3[0]) TO P[3]
	assign Isum4 = PP4 + Isum3[6:1];	// Remember (Isum4[0]) TO P[4]
	assign P[11:5] = PP5 + Isum4[6:1];	// P has an extra bit for the carry
	// add the LSBs to P
	assign P[4:0] = {Isum4[0], Isum3[0], Isum2[0], Isum1[0], pp0[0]};
	
endmodule

