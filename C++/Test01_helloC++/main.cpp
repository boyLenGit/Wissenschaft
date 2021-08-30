#include <iostream>
#include "vector"
#include "LenTestFunc.h"
using namespace std;

int max2(int num1, int num2);
fdct_usfft_ns::CpxNumMat LenTransform_Pylist_2_CpxNumMat_beta2(std::vector< std::vector<double> > md, CpxNumMat1 &cd);



int main() {
    std::vector<double> vector1{1.2, 3.4, 5.4};
    std::vector<std::vector<double> > vector2v_1{{1.2, 3.4, 5.4},
                                                 {1.2, 3.4, 5.4},
                                                 {1.2, 3.4, 5.4},
                                                 {1.2, 3.4, 5.4}};
    std::vector<std::vector<double> > vector2v_2{{1.2, 3.4, 5.4},
                                                 {1.2, 3.4, 5.4},
                                                 {1.2, 3.4, 5.4},
                                                 {1.2, 3.4, 5.4}};
    int size1v = vector2v_1.size();
    int size2v = vector2v_1[0].size();
    std::cout << size2v << std::endl;

    CpxNumMat1 MatX1;
    CpxNumMat1 result1;
    //result1 = LenTestFunc::LenTransform_Pylist_2_CpxNumMat_beta(vector2v_2, MatX1);

    fdct_usfft_ns::CpxNumMat result2;
    //result2 = max2(10, 25);
    result2 = LenTransform_Pylist_2_CpxNumMat_beta2(vector2v_2, result1);
    //result2 = LenTestFunc::LenTestInt(10);
    std::cout << result2 << std::endl;

    return 0;
}


int max2(int num1, int num2)
{
    // 局部变量声明
    int result;

    if (num1 > num2)
        result = num1;
    else
        result = num2;

    return result;
}


CpxNumMat1 LenTransform_Pylist_2_CpxNumMat_beta2(std::vector< std::vector<double> > md, CpxNumMat1 &cd) {
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