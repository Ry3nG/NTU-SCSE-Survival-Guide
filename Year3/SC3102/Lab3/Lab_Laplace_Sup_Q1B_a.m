% Lab Laplace Supplementary
% Q1B_i
% Author: Chng Eng Siong
% date: Aug 2022

close all
clear all

syms a t
h_t = exp(-2*t)*heaviside(t);
x_t = 3*cos(4*pi*t)*heaviside(t);
Hs = laplace(h_t);
Xs = laplace(x_t);
Ys = Hs*Xs;
y_t = ilaplace(Ys);

t = 0:0.1:100;
figure
fplot(y_t,[0,5])

grid on;