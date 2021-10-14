clc;clear;
img = double(imread('barbara512.jpg'));
[C,LenTV] = fdct_wrapping(img,0,2);
result = ifdct_wrapping(C,1);