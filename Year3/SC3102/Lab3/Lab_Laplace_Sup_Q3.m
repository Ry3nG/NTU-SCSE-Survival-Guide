% Lab_Laplace_Sub_Q3
% H(s) = (s+1)/(s+a)
% Author: Chng Eng Siong
% date: Aug 2022

close all 
clear all;
B = [1 6];     % (s+6)
A = [1 5 6];  % (s^2+5s+6)

%Q3a
% from the pole/zero plot, the poles are ALL on the LHS, hence 
% the system is stable.
% the pole nearest to the jW axis is at -2
sSurface(B,A); 


%Q3b) plot the impulse response
[r,p,k] = residue(B,A)  % 
% therefore we get r=[-3,4], p = [-3,-2], k=[] for this question
% Then, we perform inverse laplce transform of
% H(s) = -3/(s+3) + 4/(s+2)
% h(t) = -3e^-2t + 4e^-2t
t = 0:0.01:3
h = -3*exp(-2.*t)+4*exp(-2.*t)
figure;
plot(t,h,'g'); grid on;hold on;
