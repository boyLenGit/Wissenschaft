#include "Len_fdct_usfft_denoise.h"
#include "vector"
#include "fdct_usfft.hpp"
#include "mexaux.hpp"
#include "../../LenTransplant/matlab_curvlet/Len_fdct_usfft_denoise.h"

// CTRL+ALT+L  格式化代码
// CTRL+ALT+I  自动缩进    （我主要是找这个功能，其他的没有试过）


Len_fdct_usfft_denoise::Len_fdct_usfft_denoise(std::string content) : m_content(content) {
}

Len_fdct_usfft_denoise::~Len_fdct_usfft_denoise() {
}

void Len_fdct_usfft_denoise::updateWord(std::string new_content) {
    m_content = new_content;
}

std::string Len_fdct_usfft_denoise::getWord(void) {
    return m_content;
}

int Len_fdct_usfft_denoise::testFunc(int data1, double data2, char data3){
    std::cout << "data1: " << data1 << "\n";
    std::cout << "data2: " << data2 << "\n";
    std::cout << "data3: " << data3 << "\n";
    return 100;
}

int Len_fdct_usfft_denoise::LenTest_num(int data1, int data2) {
    return data1 + data2;
}

int Len_fdct_usfft_denoise::LenTest_vector_double(const std::vector<double> &data1) {
    return data1.size();
}

int Len_fdct_usfft_denoise::LenTest_list_double(std::list<double> &data1) {
    return data1.size();
}

std::list<double> Len_fdct_usfft_denoise::LenTest_list_return_list(std::list<double> data1) {
    return data1;
}

const std::vector<double> Len_fdct_usfft_denoise::LenTest_vector_return_vector(const std::vector<double> &data1) {
    return data1;
}

std::vector<double> Len_fdct_usfft_denoise::LenTest_vector_return_vector_noconst(const std::vector<double> &data1) {
    return data1;
}

const std::vector< std::vector<double> > Len_fdct_usfft_denoise::LenTest_fdct_usfft_denoise_v1(const std::vector< std::vector<double> > &data1) {
    return data1;
}

const std::vector< std::vector<double> > Len_fdct_usfft_denoise::LenTest_fdct_usfft_denoise_v2(int N1, int N2, int nbscales, int nbangles_coarse, int allcurvelets, const std::vector< std::vector<double> > &X1) {

    fdct_usfft_ns::CpxNumMat MatX1;
    LenTransform_Pylist_2_CpxNumMat();
    std::vector< std::vector<CpxNumMat> > X1_return;
    fdct_usfft_ns::fdct_usfft(N1, N2, nbscales, nbangles_coarse, allcurvelets, MatX1, X1_return);
    return X1_return;
}


inline void LenTransform_Pylist_2_CpxNumMat(const mxArray *&md, CpxNumMat &cd){
    int m = md.size(); //矩阵的行
    int n = md[0].size(); //矩阵的列
}
