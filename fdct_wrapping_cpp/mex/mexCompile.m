

mex ../src/fdct_wrapping_param_mex.cpp ../src/fdct_wrapping_param.cpp -L../src/libfdct_wrapping.a -L../src/libfftw.a
mex -I../src ../src/fdct_wrapping_mex.cpp ../src/fdct_wrapping.cpp -L../src/libfftw.a -L../src/libfdct_wrapping.a
%mex ../src/ifdct_wrapping_mex.cpp ../src/ifdct_wrapping.cpp -L../src/libfdct_wrapping.a -L../src/libfftw.a