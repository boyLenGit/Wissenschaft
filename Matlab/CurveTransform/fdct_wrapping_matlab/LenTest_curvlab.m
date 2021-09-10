clc;clear;
img = double(imread('Lena.jpg'));
[C,LenTV] = fdct_wrapping(img,0,2);
C