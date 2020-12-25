#include <iostream>
#include "vec.h"
#include <vector>;
using namespace std;

int main()
{

    std::vector<vec> V;
    V.push_back(vec{1,2,3});

    vec c[2] = {vec{1,2,3}, vec{4,5,6}};
    vec a{3,5,1};
    mat A, B;
    A.Translation(a);
    B.Translation(vec(-1,2,3));
    mat C = mat(vec(1,1,1));
    mat X(a);
    vec d(C);
    return 0;
}
