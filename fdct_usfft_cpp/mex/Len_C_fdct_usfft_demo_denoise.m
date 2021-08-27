disp(' ');
disp('fdct_usfft_demo_denoise.m -- Image denoising via curvelet thresholding');
disp(' ');

disp(' ');
disp('Denoising is achieved by hard-thresholding of the curvelet coefficients.');
disp('We select the thresholding at 3*sigma_jl for all but the finest scale');
disp('where it is set at 4*sigma_jl; here sigma_jl is the noise level of a');
disp('coefficient at scale j and angle l (equal to the noise level times');
disp('the l2 norm of the corresponding curvelet). There are many ways to compute');
disp('the sigma_jl''s, e.g. by computing the norm of each individual curvelet,');
disp('and in this demo, we use Monte Carlo simulations.');
disp(' ');

% fdct_usfft_demo_denoise.m -- Image denoising via curvelet thresholding

img = double(imread('Lena.jpg'));
n = size(img,1);
sigma = 20;
is_real = 0.01;

noisy_img = img + sigma*randn(n);

disp('Compute all thresholds');
X = randn(n);
tic; C = fdct_usfft(X,is_real); toc;

% Compute norm of curvelets (Monte Carlo)
E = cell(size(C));
for s=1:length(C)
    E{s} = cell(size(C{s}));
    for w=1:length(C{s})
        A = C{s}{w};
        E{s}{w} = median(abs(A(:) - median(A(:))))/.6745; % Estimate noise level with robust estimator
    end
end

% Take curvelet transform
disp(' ');
disp('Take curvelet transform: fdct_usfft');
tic; C = fdct_usfft(noisy_img,is_real); toc;
Ct = C;

% Apply thresholding
for s = 2:length(C)
    thresh = 3*sigma + sigma*(s == length(C));
    for w = 1:length(C{s})
        Ct{s}{w} = C{s}{w}.* (abs(C{s}{w}) > thresh*E{s}{w});
    end
end

% Take inverse curvelet transform
disp(' ');
disp('Take inverse transform of thresholded data: ifdct_usfft');

restored_img = real(ifdct_usfft(Ct,is_real));  % 曲波反变换，得到原始图

figure;
subplot(1,3,1); imagesc(img); colormap gray; axis('image');
title(sigma)
subplot(1,3,2); imagesc(noisy_img); colormap gray; axis('image');
title(is_real)
subplot(1,3,3); imagesc(restored_img); colormap gray; axis('image');
