% Lab Laplace Supplementary
% Q1
% Author: Chng Eng Siong
% date: Aug 2022

syms a t w0 phi
f_t = exp(-a*t)*cos(w0*t+phi)*heaviside(t)
F_s = laplace(f_t)
f_t_verify = ilaplace(F_s)  % the results show that iLaplace does not give the same close form representation
    % BUT the calculated value is the same
    % reason for difference is that cosh and sinh pops UP!
F_s2 = laplace(f_t_verify)  % This shows that the laplace of f_t_verify is same as f_t!!! :) strange


a = 0.1, b=0.2, k = 3, w0  = 2, phi =0.1*pi, t = 0:0.1:100;
y_t        = exp(-a*t).*cos(w0*t+phi).*heaviside(t);
y_t_verify = exp(-a*t).*cos(phi).*(cosh(t*w0*1i) + (sinh(t*w0*1i)*(a - (a*cos(phi) - w0*sin(phi))/cos(phi))*1i)/w0);
figure
plot(t, y_t,'r+'); hold on;
plot(t, y_t_verify,'g')
