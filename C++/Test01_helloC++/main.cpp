#include <iostream>
#include "vector"

int main() {
    std::vector<double> vector1{1.2, 3.4, 5.4};
    std::vector< std::vector<double> > vector2v_1{{1.2, 3.4, 5.4}, {1.2, 3.4, 5.4}, {1.2, 3.4, 5.4}, {1.2, 3.4, 5.4}};
    int size1v = vector2v_1.size();
    int size2v = vector2v_1[0].size();
    std::cout << size2v << std::endl;
    return 0;
}
