module multB(input [5:0] a, b, input [9:0] Pin, output [11:0] P);

	wire [5:0] pp4, pp5;
	wire [5:0] PP4;		// the Partial Products
	wire [6:0] PP5;		// last PP has extra bit
	wire [6:0] Isum4;	// The Intermediate Sums

	// generate partial products
	assign pp4 = b & {6{a[4]}};
	assign PP4 = {~pp4[5], pp4[4:0]};
	assign pp5 = b & {6{a[5]}};
	assign PP5 = {1'b1, pp5[5], ~pp5[4:0]};
	
	// The adders (the Intermediate Sums)	
	assign Isum4 = PP4 + Pin[9:4];		// Remember (Isum4[0]) TO P[4]
	assign P[11:5] = PP5 + Isum4[6:1];	// P has an extra bit for the carry
	// add the LSBs to P (Isum4[0] and the 4 LSBs of Pin)
	assign P[4:0] = {Isum4[0], Pin[3:0]};
	
endmodule

