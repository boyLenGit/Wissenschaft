#include "word.h"
#include "vector"
// CTRL+ALT+L  格式化代码
// CTRL+ALT+I  自动缩进    （我主要是找这个功能，其他的没有试过）


word::word(std::string content) : m_content(content) {
}

word::~word() {
}

void word::updateWord(std::string new_content) {
    m_content = new_content;
}

std::string word::getWord(void) {
    return m_content;
}

int word::testFunc(int data1, double data2, char data3){
    std::cout << "data1: " << data1 << "\n";
    std::cout << "data2: " << data2 << "\n";
    std::cout << "data3: " << data3 << "\n";
    return 100;
}

int word::LenTest_num(int data1, int data2) {
    return data1 + data2;
}

int word::LenTest_vector_double(const std::vector<double> &data1) {
    return data1.size();
}

int word::LenTest_list_double(std::list<double> &data1) {
    return data1.size();
}

std::list<double> word::LenTest_list_return_list(std::list<double> data1) {
    return data1;
}

const std::vector<double> word::LenTest_vector_return_vector(const std::vector<double> &data1) {
    return data1;
}
