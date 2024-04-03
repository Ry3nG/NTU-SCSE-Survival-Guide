% Author: Chng Eng Siong
% date: Aug 2022

function sSurface(B,A)

% compare your results using iLaplace vs rpk and lookup table
splane(roots(B),roots(A)); grid on;
title('Pole and Zeros of X(s)');
xlabel('real(s)')
ylabel('imag(s)')


%
% plotting the s-domain F(s)
%           to plot we need H(s)
zeros_RootsHs = roots(B);
poles_RootsHs = roots(A)   % the roots of A == -alpha, which is -sigma-j*omega
B = poly(zeros_RootsHs)
A = poly(poles_RootsHs)  % to get back A in power of s, the polynomial in power of s

start_x = min([-2.0, min(real(zeros_RootsHs)), min(real(poles_RootsHs))]) ; 
end_x = 2.0
start_y = min([-2, min(imag(zeros_RootsHs)), min(imag(poles_RootsHs))])-0.5;
end_y = abs(start_y)
end_x = 2.; step_x = 0.05;
[x,y]=meshgrid(start_x:step_x:end_x,start_y:step_x:end_y );  % we create a mesh of point in the surface of s
z_plane = x + j*y;  % as z_plane values which are complex

% Evaluate the numerator and denominator at every grid point
numVal = polyval(B,z_plane);
denVal = polyval(A,z_plane);

% .. so the Laplace-transform is the ratio of the two
HsVal = numVal ./ denVal;

% HsVal is ONLY defined at ROC
% hence we should zero the values at x-axis less then alpha!
maxRealPolesPos = max(real(poles_RootsHs))
HsVal_ROC = HsVal;
[nr nc] = size(x)
for chkX = 1:nr
    for chkY = 1:nc
        if x(chkX,chkY) < maxRealPolesPos
            HsVal_ROC(chkX,chkY) = 1e-30;
        end    
    end
end

% Sketching the surface of HsVal along the z-plane
% Note: vertical axis in dB (log scale) so zeros go to -Inf
figure
colormap jet
mesh(x, y, abs(HsVal))
shading interp
axis([start_x end_x start_y end_y -1 5])
title('|F(s)| (magnitude)');
xlabel('real(s)')
ylabel('imag(s)')
view([36 24])
hold on

figure
surfl(x, y, 10*log10(abs(HsVal).^2))
shading interp
colormap(gray)
axis([start_x end_x start_y end_y -30 30])
title('20*log_{10}|F(s)| (magnitude in dB)');
view([33 16])
hold on


% drawing lines alog the surface of Hs at the gx, gy (axis)
% gy_roc == roc for Hs
max_poleReal = real(max(poles_RootsHs))
xy_range = x(1,:);
gx = polyval(B,xy_range)./polyval(A,xy_range);
gy = polyval(B,j*xy_range)./polyval(A,j*xy_range);
plot3(xy_range, 0*xy_range, 20*log10(abs(gx)), 'b');
plot3(xy_range*0, xy_range, 20*log10(abs(gy)), 'b');

% ROC it is along and parallely to y axis, on the surface
gy_roc = polyval(B,max_poleReal+j*xy_range)./polyval(A,max_poleReal+j*xy_range);  % <------- ???
plot3(max_poleReal*ones(length(xy_range),1), xy_range, 20*log10(abs(gy_roc)), 'g--');

% Plot a 'flat' z-plane at height -30: axes and unit circle
plot3(xy_range*0, xy_range, -30*ones(1,length(xy_range)), 'b');
plot3(xy_range, 0*xy_range, -30*ones(1,length(xy_range)), 'b');
plot3(max_poleReal*ones(length(xy_range)), xy_range, -30*ones(1,length(xy_range)), 'g--');

%plot3(real(ww), imag(ww), -30*ones(1,length(ww)),'k')

% Add the actual poles and zeros on the 2D zplane
plot3(real(zeros_RootsHs), imag(zeros_RootsHs), [-30].*ones(length(real(zeros_RootsHs))), 'ob')
plot3(real(poles_RootsHs), imag(poles_RootsHs), [-30].*ones(length(real(poles_RootsHs))), 'xr')
xlabel('real axis (s)');
ylabel('imag axis (s)');
% Now try spin it in 3D to get a sense of the surface...
axis vis3d

figure
subplotInfo=133;radii=1; xV=0;yV=0; 
%plotcircle(fig_handle, subplotInfo, radii,xV,yV, 'k--')
axis([start_x end_x start_y end_y]) 
hold on;
max_poleReal = real(max(poles_RootsHs))
line([max_poleReal,max_poleReal], ylim, 'Color', 'g', 'LineWidth', 0.2, 'LineStyle','--'); % Draw line for ROC
line([0,0], ylim, 'Color', 'b', 'LineWidth', 0.2); % Draw line for Y axis.
line(xlim, [0,0], 'Color', 'b', 'LineWidth', 0.2); % Draw line for X axis.
plot(real(zeros_RootsHs), imag(zeros_RootsHs), 'ob')
plot(real(poles_RootsHs), imag(poles_RootsHs), 'xr')

xlabel('real axis (s)');
ylabel('imag axis (s)');
% Now try spiBing it in 3D to get a sense of the surface...
hold on
title('Pole zero plot of F(s)');


% Lets show ROC for H(s)
% its on the right handside

figure
x0=900; y0=230; width=350; height=300
set(gcf,'position',[x0,y0,width,height])

surfl(x, y, 10*log10(abs(HsVal_ROC).^2)); hold on;
plot3(xy_range*0, xy_range, -30*ones(1,length(xy_range)), 'b');
plot3(xy_range, 0*xy_range, -30*ones(1,length(xy_range)), 'b');
xlabel('real axis (s)');
ylabel('imag axis (s)');
title('Plot of F(s) in valid ROC ');
plot3(real(zeros_RootsHs), imag(zeros_RootsHs), [-30].*ones(length(real(zeros_RootsHs))), 'ob')
plot3(real(poles_RootsHs), imag(poles_RootsHs), [-30].*ones(length(real(poles_RootsHs))), 'xr')
plot3(xy_range, 0*xy_range, 20*log10(abs(gx)), 'b');
plot3(xy_range*0, xy_range, 20*log10(abs(gy)), 'b');

shading interp
colormap(gray)
axis([start_x end_x start_y end_y -30 30])
hold on



