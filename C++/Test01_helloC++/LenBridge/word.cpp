#include "word.h"
// CTRL+ALT+L  格式化代码
// CTRL+ALT+I  自动缩进    （我主要是找这个功能，其他的没有试过）


word::word(std::string content) : m_content(content) {
}

word::~word() {}

void word::updateWord(std::string new_content) {
    m_content = new_content;
}

std::string word::getWord(void) {
    return m_content;
}