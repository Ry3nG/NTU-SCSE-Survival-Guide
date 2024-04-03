% Lab_Laplace_Sub_Q4, and Tutorial 4B, Q4B
% RLC circuit
% Author: Chng Eng Siong
% date: Aug 2022
%
close all 
clear all;

% See Tutorial Q4B, Q4A
%R = 5;   % check the value of R = 5, its in the tutorial
R = 1;   % check the value of R = 1, its in the lab

L = 1;
C = (1/6);

i_0 = 2;
y_0 = 1.5;
d_y_0 = i_0/C;

B = [y_0 (R/L)*y_0+d_y_0] 
A = [1 R/L (1/(L*C))];
% Using R = 5
%Y(s) = (1.5s+13.5)/(s^2+s+6)

[r,p,k] = residue(B,A)
% from the above, we can form y equation below
t=0:0.01:10;
y = r(1)*exp(p(1).*t)+r(2)*exp(p(2).*t);
figure;
plot(t,y); grid on;


