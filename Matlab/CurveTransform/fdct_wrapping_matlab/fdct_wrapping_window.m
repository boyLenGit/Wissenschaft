function [wl,wr] = fdct_wrapping_window(x)

% fdct_wrapping_window.m - Creates the two halves of a C^inf compactly supported window
%
% Inputs
%   x       vector or matrix of abscissae, the relevant ones from 0 to 1
%
% Outputs
%   wl,wr   vector or matrix containing samples of the left, resp. right
%           half of the window
%
% Used at least in fdct_wrapping.m and ifdct_wrapping.m
%
% By Laurent Demanet, 2004
disp('fdct_wrapping_window');
disp(size(x));
disp(x);
wr = zeros(size(x));
wl = zeros(size(x));
x(abs(x) < 2^-52) = 0;
wr((x > 0) & (x < 1)) = exp(1-1./(1-exp(1-1./x((x > 0) & (x < 1)))));
wr(x <= 0) = 1;

wl((x > 0) & (x < 1)) = exp(1-1./(1-exp(1-1./(1-x((x > 0) & (x < 1))))));
wl(x >= 1) = 1;
normalization = sqrt(wl.^2 + wr.^2);
disp('boyLen1');
disp(wl.^2 + wr.^2);
disp('boyLen1');
disp(normalization);
x{909090990};

wr = wr ./ normalization;
wl = wl ./ normalization;

