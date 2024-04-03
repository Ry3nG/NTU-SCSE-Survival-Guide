% Author: Chng Eng Siong
% date: Aug 2022

function H_Omega(B,A)
omegaRange = -1:0.01:1
% Evaluate the numerator and denominator at every grid point
numVal = polyval(B,j*omegaRange);
denVal = polyval(A,j*omegaRange);

% .. so the Laplace-transform is the ratio of the two
HsVal = numVal ./ denVal;
% Sketching the surface of HsVal along the z-plane
% Note: vertical axis in dB (log scale) so zeros go to -Inf
figure(1)
plot(omegaRange, abs(HsVal))
title('|F(s)| (magnitude)');
xlabel('omega')
ylabel('|F(s)| (magnitude)')
hold on

figure(2)
plot(omegaRange, 10*log10(abs(HsVal).^2))
title('20*log_{10}|F(s)| (magnitude in dB)');
xlabel('omega')
ylabel('20*log_{10}|F(s)| (magnitude)')
hold on

