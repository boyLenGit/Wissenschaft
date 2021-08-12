function restored_RawData = Len_ifdct_wrapping(segy_data)
disp('fdct_wrapping_demo_denoise_enhanced.m - Image denoising using Curvelets');
disp('This is an extension of the file fdct_wrapping_demo_denoise.m')
disp('We try different tricks to obtain better image denoising: (1) curvelets');
disp('at the finest scale, (2) complex block thresholding, (3) cycle spinning,');
disp('(4) ell-1 iterations. The user can fine-tune some parameters, see the');
disp('beginning of the code.')
disp('By Laurent Demanet, 2005');

RawData = segy_data; % 读取数据
[dim_input_1, ~]=size(RawData); % dim_input_1输入数据的维度;

% Tuning parameters
sigma = 0.1*255;            % 噪声方差为10%。？？？生成高斯噪声为什么要用
finest = 1;                 % 1: curvelets at finest scale, 2: wavelets at finest scale
nbscales = log2(dim_input_1) - 3;
nbangles_coarse = 8;        %
nsigmas_coarse = 2.2;       % 阈值与sigmas_coarse*sigma在所有尺度(最细尺度除外)成正比 threshold proportional to nsigmas_coarse*sigma at all scales except finest
nsigmas_fine = 2.5;         % 在最细尺度上与sigma成比例的阈值 threshold proportional to nsigmas_fine*sigma at finest scale
nshifts = 1;                % 在旋转周期中考虑的平移数(每个维度) number of translations (per dimension) considered in the cycle-spinning
nell1 = 0;                  % ell-1迭代次数 number of ell-1 iterations
neighb_weight = 0.5;        % 对于群阈值，赋予相邻曲波的权值 for group thresholding, weight assigned to neighboring curvelets
tuning_neighb = 0.6;        % 对于群阈值，用于重正化系数加权和的平方的参数 for group thresholding, parameter used to renormalize the weighted sum of coefficients squared
% Don't forget that you can choose between diagonal real, diagonal complex, and block complex thersholding by uncommenting portions of the code
% 不要忘记，您可以通过取消代码部分的注释，在对角线真实值、对角线复杂值和块复杂值之间进行选择

% 生成噪声数据
noisy_RawData = segy_data;

% get L2norm, put into E
F = ones(dim_input_1,dim_input_1);  % ones:创建全部为 1 的数组
X = fftshift(ifft2(F)) * sqrt(numel(F)); % 函数prod(size(F))= M*N；    %二维快速傅里叶逆变换ifft2    %fftshift将零频分量移到频谱中心
disp('计算L2标准型Computing L^2 norms ...');
tic;
C = fdct_wrapping(X,0,finest,nbscales,nbangles_coarse); % fdct_wrapping:快速离散曲波变换

E = cell(size(C));
for s=1:length(C)
    E{s} = cell(size(C{s}));
    for w=1:length(C{s})
        A = C{s}{w};
        E{s}{w} = sqrt(sum(sum(A.*conj(A))) / numel(A));
    end
end

disp('计算参数Computing parameters ...');  % 计算参数
[X_rows, X_cols, F_rows, F_cols, N_rows, N_cols] = fdct_wrapping_param(C,dim_input_1,dim_input_1);

% Cycle spinning 循环旋转
n = 0;
restored_RawData = 0;
for xshift = 1:nshifts
    for yshift = 1:nshifts
        
        shift_RawData = circshift(noisy_RawData,[xshift yshift]);
        n = n + 1;
        
        disp(['直接转换Direct transform, shift nr. ',num2str(n),' ...']);
        C = fdct_wrapping(shift_RawData,0,finest,nbscales,nbangles_coarse);  % fdct_wrapping:快速离散曲波变换
        
        % 阈值Thresholding
        disp('阈值Thresholding ...')
        thresh = nsigmas_coarse * sigma;
        for j = 1:length(C)
            if j == length(C), thresh = nsigmas_fine * sigma; end
            for l = 1:length(C{j})
                
                thresh_jl = thresh*E{j}{l};
                
                % Uncomment for 'diagonal real thresholding'
                %                recjl = real(C{j}{l});
                %                imcjl = imag(C{j}{l});
                %                recjl = recjl .* (abs(recjl) > thresh_jl);
                %                imcjl = imcjl .* (abs(imcjl) > thresh_jl);
                %                C{j}{l} = recjl + sqrt(-1)*imcjl;
                
                % Uncomment for 'diagonal complex thresholding'
                %                modcjl = abs(C{j}{l});
                %                argcjl = C{j}{l} ./ modcjl;
                %                modcjl = modcjl .* (modcjl > thresh_jl);
                %                C{j}{l} = argcjl .* modcjl;
                
                % Uncomment for 'block complex thresholding'
                modcjl = abs(C{j}{l});
                argcjl = C{j}{l} ./ modcjl;
                rowstep = dim_input_1/N_rows{j}{l};
                colstep = dim_input_1/N_cols{j}{l};
                evenquad = ~mod(ceil(l*4/length(C{j})),2);
                if evenquad
                    if (j == 1) || (finest==2 && j==nbscales), fcolsjl = 1; else fcolsjl = F_cols{j}{l};
                    end
                    rowshift = - round(F_rows{j}{l}/fcolsjl * rowstep);
                    testcjl = sqrt(modcjl.^2 + neighb_weight*(circshift(modcjl,[1 0]).^2 + circshift(modcjl,[-1 0]).^2 + ...
                        circshift(modcjl,[rowshift 1]).^2 + circshift(modcjl, [-rowshift -1]).^2));
                else
                    if (j == 1) || (finest==2 && j==nbscales), frowsjl = 1; else frowsjl = F_rows{j}{l};
                    end
                    colshift = - round(F_cols{j}{l}/frowsjl * colstep);
                    testcjl = sqrt(modcjl.^2 + neighb_weight*(circshift(modcjl,[0 1]).^2 + circshift(modcjl,[0 -1]).^2 + ...
                        circshift(modcjl,[1 colshift]).^2 + circshift(modcjl, [-1 -colshift]).^2));
                end
                testcjl = testcjl ./ sqrt(1+4*neighb_weight*tuning_neighb);
                modcjl = modcjl .* (testcjl > thresh_jl);
                C{j}{l} = argcjl .* modcjl;
                
            end
        end
        
        disp('反变换Inverse transform ...');
        temp_restored = real(ifdct_wrapping(C,0,dim_input_1,dim_input_1));
        
        % L1 iterations
        
        for nupdate = 1:nell1
            nupdate
            disp(['Direct transform, within ell-1 iteration, shift nr.',num2str(n),' ...']);
            D = fdct_wrapping(temp_restored,0,finest,nbscales,nbangles_coarse);
            disp('Thresholding ...');
            thresh = nsigmas_coarse * sigma;
            for j = 1:length(C)
                if j == length(C), thresh = nsigmas_fine * sigma; end
                for l = 1:length(C{j})
                    thresh_jl = thresh*E{j}{l};
                    
                    % Uncomment for 'diagonal real thresholding'
                    %                    redjl = real(D{j}{l});
                    %                    imdjl = imag(D{j}{l});
                    %                    recjl = real(C{j}{l});
                    %                    imcjl = imag(C{j}{l});
                    %                    redjl = (recjl - redjl) .* (abs(recjl) > thresh_jl);
                    %                    imdjl = (imcjl - imdjl) .* (abs(imcjl) > thresh_jl);
                    %                    D{j}{l} = redjl + sqrt(-1)*imdjl;
                    
                    % Uncomment for 'diagonal complex thresholding'
                    %                    modcjl = abs(C{j}{l});
                    %                    moddjl = abs(D{j}{l});
                    %                    argcjl = C{j}{l} ./ (modcjl+1e-16);
                    %                    argdjl = D{j}{l} ./ (moddjl+1e-16);
                    %                    moddjl = (modcjl - moddjl) .* (modcjl > thresh_jl);
                    %                    D{j}{l} = argdjl .* moddjl;
                    
                    % Uncomment for 'block complex thresholding'
                    modcjl = abs(C{j}{l});
                    moddjl = abs(D{j}{l});
                    argcjl = C{j}{l} ./ (modcjl+1e-16);
                    argdjl = D{j}{l} ./ (moddjl+1e-16);
                    rowstep = dim_input_1/N_rows{j}{l};
                    colstep = dim_input_1/N_cols{j}{l};
                    evenquad = ~mod(ceil(l*4/length(C{j})),2);
                    if evenquad
                        if (j == 1) || (finest==2 && j==nbscales), fcolsjl = 1; else fcolsjl = F_cols{j}{l};
                        end
                        rowshift = - round(F_rows{j}{l}/fcolsjl * rowstep);
                        testcjl = sqrt(modcjl.^2 + neighb_weight*(circshift(modcjl,[1 0]).^2 + circshift(modcjl,[-1 0]).^2 + ...
                            circshift(modcjl,[rowshift 1]).^2 + circshift(modcjl, [-rowshift -1]).^2));
                    else
                        if (j == 1) || (finest==2 && j==nbscales), frowsjl = 1; else frowsjl = F_rows{j}{l};
                        end
                        colshift = - round(F_cols{j}{l}/frowsjl * colstep);
                        testcjl = sqrt(modcjl.^2 + neighb_weight*(circshift(modcjl,[0 1]).^2 + circshift(modcjl,[0 -1]).^2 + ...
                            circshift(modcjl,[1 colshift]).^2 + circshift(modcjl, [-1 -colshift]).^2));
                    end
                    testcjl = testcjl ./ sqrt(1+4*neighb_weight*tuning_neighb);
                    moddjl = (modcjl - moddjl) .* (testcjl > thresh_jl);
                    D{j}{l} = argdjl .* moddjl;
                    
                end
            end
            disp('Inverse transform ...')
            temp_update = real(ifdct_wrapping(D,0,dim_input_1,dim_input_1));
            max(max(abs(temp_update)))
            temp_restored = temp_restored + temp_update;
        end
        
        temp_restored = circshift(temp_restored,[-xshift, -yshift]);
        restored_RawData = (n-1)/n*restored_RawData + 1/n*temp_restored;
        
    end
end

MSE = sum(sum((RawData-restored_RawData).^2))/dim_input_1^2;
PSNR = 20*log10(255/sqrt(MSE));
disp(['PSNR = ',num2str(PSNR)]);
disp(['Time elapsed = ',num2str(toc)]);

figure(1); clf; imagesc(RawData); colormap gray; axis('image');
title('Original Image')
figure(2); clf; imagesc(noisy_RawData); colormap gray; axis('image');
title('Noisy Image')
figure(3); clf; imagesc(restored_RawData); colormap gray; axis('image');
title('Restored image');

end
