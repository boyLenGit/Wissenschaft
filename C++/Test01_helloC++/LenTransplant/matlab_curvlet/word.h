#ifndef __WORD_H__
#define __WORD_H__

#include <string>
#include <iostream>
#include <vector>
#include <list>

class word
        {
        public:
            word(std::string content);
            virtual ~word();

            virtual void updateWord(std::string new_content);
            std::string getWord(void);

            int testFunc(int data1, double data2, char data3); // new added

            int LenTest_num(int data1, int data2);

            int LenTest_vector_double(const std::vector<double>& data1);

            int LenTest_list_double(std::list<double> &data1);

            std::list<double> LenTest_list_return_list(std::list<double> data1);

            const std::vector<double> LenTest_vector_return_vector(const std::vector<double>& data1);

        private:
            std::string m_content;
        };

#endif