#ifndef __WORD_H__
#define __WORD_H__

#include <string>

class Len_fdct_usfft_denoise
        {
        public:
            Len_fdct_usfft_denoise(std::string content);
            virtual ~Len_fdct_usfft_denoise();

            virtual void updateWord(std::string new_content);
            std::string getWord(void);

        private:
            std::string m_content;
        };

#endif