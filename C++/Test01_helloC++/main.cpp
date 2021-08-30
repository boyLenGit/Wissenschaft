#include <iostream>
#include "vector"
#include "LenTestFunc.h"
#include "LenTest/matlab_curvlet_testmex2cpp/matrix.h"
using namespace std;

int max2(int num1, int num2);
void LenTransform_Pylist_2_CpxNumMat_beta2(std::vector< std::vector<double> > md, CpxNumMat1 &cd);



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

    std::vector<std::vector<double> > vector2v_3{{1.2, 3.4, 5.4},
                                                 {1.2, 3.4, 5.4},
                                                 {1.2, 3.4, 5.4},
                                                 {1.2, 3.4, 5.4}};
    int size1v = vector2v_1.size();
    int size2v = vector2v_1[0].size();
    std::cout << size2v << std::endl;

    CpxNumMat1 MatX1;
    CpxNumMat1 result1;
    fdct_usfft_ns::CpxNumMat result2;
    LenTransform_Pylist_2_CpxNumMat_beta2(vector2v_2, result1);
    std::cout << result1 << std::endl;


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


void LenTransform_Pylist_2_CpxNumMat_beta2(std::vector< std::vector<double> > md, CpxNumMat1 &cd) {
    int m = md.size(); //矩阵的行
    int n = md[0].size(); //矩阵的列
    std::cout << m << std::endl;
    std::cout << n << std::endl;

    int a1 = 10;
    int (*b1) = &a1;

    int cnt = 0;
    for (int j = 0; j < n; j++)
        for (int i = 0; i < m; i++) {
            std::cout << i << std::endl;
            cd(i, j) = cpx(*b1, *b1); // 这里出了问题
            cnt++;
        }
    //return cd;

}