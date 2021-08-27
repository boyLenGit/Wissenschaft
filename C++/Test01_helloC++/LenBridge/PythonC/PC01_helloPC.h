#ifndef __WORD_H__
#define __WORD_H__

#include <string>

class word
        {
        public:
            word(std::string content);
            virtual ~word();

            virtual void updateWord(std::string new_content);
            std::string getWord(void);

        private:
            std::string m_content;
        };

#endif