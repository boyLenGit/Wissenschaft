file1='E:\Research\data\Segy\CMP_INL2000_stk_org_gain.SEGY'
[seismic,text_header1,binary_header1]=read_segy_file(file1);
s_cplot(seismic,{'time_lines',[]})% ����segy��ͼ

segy_trace=double(seismic.traces); %����ֵȫ��ת��Ϊdouble˫����
[M,N]=size(segy_trace) %�������ݵĳ��ȣ����ﷵ����2��ά�ȵĳ���
%N = 512;

sigma = 0.05*max(max(segy_trace)); % �õ����������е����ֵ������max����Ϊ����������Ƕ�ά�ģ���һ��max�õ�����ÿ�������ֵ��������һ�����飬�ڶ��β���һ����ֵ��           % noise stdev is 10%
len_max_1 = max(segy_trace);

% Tuning parameters���ڲ���
is_real=1;     %   is_real:Type of the transform�����任������;  0:complex-valued curvelets��ֵ�����任;  1:real-valued curvelets��ֵ�����任
finest = 1;                 % 1: curvelets at finest scale��ѱ�������  2: wavelets at finest scale��ϸ�߶�С��
nbscales=ceil(log2(min(M,N))- 3); %ceil:����������������
nbangles_coarse = 16;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
nsigmas_coarse = 2.2;       % threshold proportional to nsigmas_coarse*sigma at all scales except finest
nsigmas_fine =5;            % threshold proportional to nsigmas_fine*sigma at finest scale
nshifts = 1;                % number of translations (per dimension) considered in the cycle-spinning
nell1 = 0;                  % number of ell-1 iterations
neighb_weight = 0.5;        % for group thresholding, weight assigned to neighboring curvelets
tuning_neighb = 0.6;        % for group thresholding, parameter used to renormalize the weighted sum of coefficients squared
% Don't forget that you can choose between diagonal real, diagonal complex��and block complex thersholding by uncommenting portions of the code

noise = randn(M,N) * sigma; % sigma��segy.trace�е����ֵ��һ����ֵ��  %randn:��̬�ֲ��������
noisy_segy_trace = segy_trace;

% get L2norm, put into E 
F = ones(M,N);  % ones:����ȫ��Ϊ 1 ������
X = fftshift(ifft2(F)) * sqrt(prod(size(F))); % ����prod(size(F))= M*N��    %��ά���ٸ���Ҷ��任ifft2    %fftshift����Ƶ�����Ƶ�Ƶ������
disp('Computing L^2 norms ...'); % ��ʾ������ֵ
tic;
C = fdct_wrapping(X,is_real,finest,nbscales,nbangles_coarse); % ����C++

E = cell(size(C));
for s=1:length(C)
  E{s} = cell(size(C{s}));
  for w=1:length(C{s})
    A = C{s}{w};
    E{s}{w} = sqrt(sum(sum(A.*conj(A))) / prod(size(A)));%ANNA:here what to compute?
  end
end

disp('Computing parameters ...');
[X_rows, X_cols, F_rows, F_cols, N_rows, N_cols] = fdct_wrapping_param(C,M,N);

% Cycle spinning
n = 0;
restored_segy_trace = 0;
for xshift = 1:nshifts
  for yshift = 1:nshifts
    
    shift_segy_trace = circshift(noisy_segy_trace,[xshift yshift]);
    n = n + 1;
    
    disp(['Direct transform, shift nr. ',num2str(n),' ...']);
    C = fdct_wrapping(shift_segy_trace,is_real,finest,nbscales,nbangles_coarse);
    
    % Thresholding
    disp('Thresholding ...')
    thresh = nsigmas_coarse * sigma;
    for j = 1:length(C)
      if j == length(C), thresh = nsigmas_fine * sigma; end;
      for l = 1:length(C{j})
        
        thresh_jl = thresh*E{j}{l};
        
        % Uncomment for 'diagonal real thresholding'
                       recjl = real(C{j}{l});     
                       imcjl = imag(C{j}{l});
                       recjl = recjl .* (abs(recjl) > thresh_jl);
                       imcjl = imcjl .* (abs(imcjl) > thresh_jl);
                       C{j}{l} = recjl + sqrt(-1)*imcjl;                
        
        % Uncomment for 'diagonal complex thresholding'
%                        modcjl = abs(C{j}{l});     
%                        argcjl = C{j}{l} ./ modcjl;
%                        modcjl = modcjl .* (modcjl > thresh_jl);
%                        C{j}{l} = argcjl .* modcjl;
        
%         % Uncomment for 'block complex thresholding'
%         modcjl = abs(C{j}{l});          
%         argcjl = C{j}{l} ./ modcjl;
%         rowstep = N/N_rows{j}{l};
%         colstep = N/N_cols{j}{l};
%         evenquad = ~mod(ceil(l*4/length(C{j})),2);
%         if evenquad,
%           if (j == 1)|(finest==2 & j==nbscales), fcolsjl = 1; else fcolsjl = F_cols{j}{l}; end;
%           rowshift = - round(F_rows{j}{l}/fcolsjl * rowstep);
%           testcjl = sqrt(modcjl.^2 + neighb_weight*(circshift(modcjl,[1 0]).^2 + circshift(modcjl,[-1 0]).^2 + ...
%                                                     circshift(modcjl,[rowshift 1]).^2 + circshift(modcjl, [-rowshift -1]).^2));
%         else
%           if (j == 1)|(finest==2 & j==nbscales), frowsjl = 1; else frowsjl = F_rows{j}{l}; end;
%           colshift = - round(F_cols{j}{l}/frowsjl * colstep);
%           testcjl = sqrt(modcjl.^2 + neighb_weight*(circshift(modcjl,[0 1]).^2 + circshift(modcjl,[0 -1]).^2 + ...
%                                                     circshift(modcjl,[1 colshift]).^2 + circshift(modcjl, [-1 -colshift]).^2));
%         end;
%         testcjl = testcjl ./ sqrt(1+4*neighb_weight*tuning_neighb);
%         modcjl = modcjl .* (testcjl > thresh_jl);
%         C{j}{l} = argcjl .* modcjl;
        
      end
    end
    
    disp('Inverse transform ...');
    temp_restored = real(ifdct_wrapping(C,0,M,N));
    
    % L1 iterations
    
    for nupdate = 1:nell1
      nupdate
      disp(['Direct transform, within ell-1 iteration, shift nr.',num2str(n),' ...']);
      D = fdct_wrapping(temp_restored,is_real,finest,nbscales,nbangles_coarse);
      disp('Thresholding ...');
      thresh = nsigmas_coarse * sigma;
      for j = 1:length(C)
        if j == length(C), thresh = nsigmas_fine * sigma; end;
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
          rowstep = N/N_rows{j}{l};
          colstep = N/N_cols{j}{l};
          evenquad = ~mod(ceil(l*4/length(C{j})),2);
          if evenquad,
            if (j == 1)|(finest==2 & j==nbscales), fcolsjl = 1; else fcolsjl = F_cols{j}{l}; end;
            rowshift = - round(F_rows{j}{l}/fcolsjl * rowstep);
            testcjl = sqrt(modcjl.^2 + neighb_weight*(circshift(modcjl,[1 0]).^2 + circshift(modcjl,[-1 0]).^2 + ...
                                                      circshift(modcjl,[rowshift 1]).^2 + circshift(modcjl, [-rowshift -1]).^2));
          else
            if (j == 1)|(finest==2 & j==nbscales), frowsjl = 1; else frowsjl = F_rows{j}{l}; end;
            colshift = - round(F_cols{j}{l}/frowsjl * colstep);
            testcjl = sqrt(modcjl.^2 + neighb_weight*(circshift(modcjl,[0 1]).^2 + circshift(modcjl,[0 -1]).^2 + ...
                                                      circshift(modcjl,[1 colshift]).^2 + circshift(modcjl, [-1 -colshift]).^2));
          end;
          testcjl = testcjl ./ sqrt(1+4*neighb_weight*tuning_neighb);
          moddjl = (modcjl - moddjl) .* (testcjl > thresh_jl);
          D{j}{l} = argdjl .* moddjl;
          
        end
      end
      disp('Inverse transform ...')
      temp_update = real(ifdct_wrapping(D,0,M,N));
      max(max(abs(temp_update)))
      
      temp_restored = temp_restored + temp_update;
    end;
    
    temp_restored = circshift(temp_restored,[-xshift, -yshift]);
    restored_segy_trace = (n-1)/n*restored_segy_trace + 1/n*temp_restored;
    
  end
end

MSE = sum(sum((segy_trace-restored_segy_trace).^2))/N^2;
PSNR = 20*log10(255/sqrt(MSE));
disp(['PSNR = ',num2str(PSNR)]);
disp(['Time elapsed = ',num2str(toc)]);


s_spectrum(segy_trace,restored_segy_trace,{'plot','amp'},{'frequencies',0,150},{'padding',128}, ...
                   {'timezero','best'},{'scale','power'},{'normalize','amplitude'})
 legend('original','denoised')
 output=s_convert(restored_segy_trace,0,2);
filename='F:\seismicData\curveletANNA20210727����3.sgy';
write_segy_file(output,filename);
