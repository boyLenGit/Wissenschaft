/*File: example.i*/
%module example

%{
#include "../../LenBridge/word.h"

%}

%include "std_vector.i"
namespace std {
    %template(VectorDouble) vector<double>;
}

%include "std_string.i"
%include "std_iostream.i"
%include "word.h"
%include "std_list.i"