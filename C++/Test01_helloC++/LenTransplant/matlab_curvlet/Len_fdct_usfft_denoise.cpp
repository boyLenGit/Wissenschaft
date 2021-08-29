#include "Len_fdct_usfft_denoise.h"
#include "vector"
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
