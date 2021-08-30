//
// Created by boyLenPC on 2021/8/30.
//

#ifndef TEST01_HELLOC___LENTESTFUNC_H
#define TEST01_HELLOC___LENTESTFUNC_H


#include <string>
#include <vector>
#include "complex"
#include "LenTransplant/matlab_curvlet/nummat.hpp"
#include "LenTransplant/matlab_curvlet/fdct_usfft.hpp"


typedef std::complex<double> cpx;
typedef fdct_usfft_ns::NumMat<cpx> CpxNumMat1;


class LenTestFunc {
public:
    static CpxNumMat1 LenTransform_Pylist_2_CpxNumMat_beta(std::vector< std::vector<double> > md, CpxNumMat1 &cd);
    static int LenTestInt(int md);
    static int max(int num1, int num2);

};


#endif //TEST01_HELLOC___LENTESTFUNC_H
