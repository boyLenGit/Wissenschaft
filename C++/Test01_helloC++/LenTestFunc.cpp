//
// Created by boyLenPC on 2021/8/30.
//

#include "LenTestFunc.h"
#include <string>
#include <vector>
#include "complex"
#include "LenTransplant/matlab_curvlet/nummat.hpp"
#include "LenTransplant/matlab_curvlet/fdct_usfft.hpp"
using namespace std;


typedef std::complex<double> cpx;
typedef fdct_usfft_ns::NumMat<cpx> CpxNumMat1;


CpxNumMat1 LenTestFunc::LenTransform_Pylist_2_CpxNumMat_beta(std::vector< std::vector<double> > md, CpxNumMat1 &cd) {
    int m = md.size(); //矩阵的行
    int n = md[0].size(); //矩阵的列
    double *xr = md;
    double *xi = md;
    cd.resize(m, n);
    if (xr != NULL && xi != NULL) {
        int cnt = 0;
        for (int j = 0; j < n; j++)
            for (int i = 0; i < m; i++) {
                cd(i, j) = cpx(xr[cnt], xi[cnt]);
                cnt++;
            }
    } else if (xr != NULL && xi == NULL) {
        int cnt = 0;
        for (int j = 0; j < n; j++)
            for (int i = 0; i < m; i++) {
                cd(i, j) = cpx(xr[cnt], 0);
                cnt++;
            }
    } else if (xr == NULL && xi != NULL) {
        int cnt = 0;
        for (int j = 0; j < n; j++)
            for (int i = 0; i < m; i++) {
                cd(i, j) = cpx(0, xi[cnt]);
                cnt++;
            }
    }
    return cd;
}


int LenTestFunc::LenTestInt(int md) {
    return 0;
}


static int LenTestFunc::max(int num1, int num2) {
    // 局部变量声明
    int result;

    if (num1 > num2)
        result = num1;
    else
        result = num2;

    return result;
}
