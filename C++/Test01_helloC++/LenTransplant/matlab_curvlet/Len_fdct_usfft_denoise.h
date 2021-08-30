// boyLen C++
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include "fdct_usfft.hpp"
#include "nummat.hpp"
#include "complex"

typedef std::complex<double> cpx;
typedef fdct_usfft_ns::NumMat<cpx> CpxNumMat1;

class Len_fdct_usfft_denoise {
public:
    Len_fdct_usfft_denoise(std::string content);

    virtual ~Len_fdct_usfft_denoise();

    virtual void updateWord(std::string new_content);

    std::string getWord(void);

    int testFunc(int data1, double data2, char data3); // new added

    int LenTest_num(int data1, int data2);

    int LenTest_vector_double(const std::vector<double> &data1);

    int LenTest_list_double(std::list<double> &data1);

    std::list<double> LenTest_list_return_list(std::list<double> data1);

    const std::vector<double> LenTest_vector_return_vector(const std::vector<double> &data1);

    std::vector<double> LenTest_vector_return_vector_noconst(const std::vector<double> &data1);

    const std::vector<std::vector<double> >
    LenTest_fdct_usfft_denoise_v1(const std::vector<std::vector<double> > &data1);

    const std::vector<std::vector<double> >
    LenTest_fdct_usfft_denoise_v2(int N1, int N2, int nbscales, int nbangles_coarse, int allcurvelets,
                                  const std::vector<std::vector<double> > &X1);

    static void LenTransform_Pylist_2_CpxNumMat(std::vector<std::vector<double> > *&md, CpxNumMat1 &cd);

    static void LenTransform_Pylist_2_CpxNumMat_beta(std::vector<std::vector<double> > *&md, CpxNumMat1 &cd);

private:
    std::string m_content;
};
