/*File: example.i*/
%module example

%{
#include "Len_fdct_usfft_denoise.h"
%}

%include "std_vector.i"
namespace std {
    %template(VectorDouble) vector<double>;
    %template(VecVecdouble) vector< vector<double> >;
}

%include "std_string.i"
%include "std_iostream.i"
%include "Len_fdct_usfft_denoise.h"
%include "std_list.i"