% fdct_wrapping_demo_denoise.m -- Image denoising using Curvelets
clc;
% LenTest

% LenTest

img = double(imread('Lena.jpg'));
n = size(img,1);
sigma = 20;        
is_real = 1; 

noisy_img = img + sigma*randn(n);

disp('Compute all thresholds');
F = ones(n);
X = fftshift(ifft2(F)) * sqrt(prod(size(F)));
tic, C = fdct_wrapping(X,0,2); toc;

% Compute norm of curvelets (exact)
E = cell(size(C));
for s=1:length(C)
  E{s} = cell(size(C{s}));
  for w=1:length(C{s})
    A = C{s}{w};
    E{s}{w} = sqrt(sum(sum(A.*conj(A))) / prod(size(A)));
  end
end

% Take curvelet transform

disp(' ');
disp('Take curvelet transform: fdct_wrapping');
tic; C = fdct_wrapping(noisy_img,1,2); toc;

% Apply thresholding
Ct = C;
for s = 2:length(C)
  thresh = 3*sigma + sigma*(s == length(C));
  for w = 1:length(C{s})
    Ct{s}{w} = C{s}{w}.* (abs(C{s}{w}) > thresh*E{s}{w});
  end
end

% Take inverse curvelet transform 
disp(' ');
disp('Take inverse transform of thresholded data: ifdct_wrapping');
tic; restored_img = real(ifdct_wrapping(Ct,1)); toc;

subplot(1,3,1); imagesc(img); colormap gray; axis('image');
subplot(1,3,2); imagesc(noisy_img); colormap gray; axis('image');
subplot(1,3,3); imagesc(restored_img); colormap gray; axis('image');
