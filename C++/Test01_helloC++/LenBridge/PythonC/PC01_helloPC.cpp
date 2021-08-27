#include "word.h"


word::word(std::string content) : m_content(content)
{
}

word::~word()
{}

void word::updateWord(std::string new_content)
{
    m_content = new_content;
}

std::string word::getWord(void)
{
    return m_content;
}