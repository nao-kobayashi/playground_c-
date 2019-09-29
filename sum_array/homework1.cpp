// * Convert this program to C++
// * change to C++ io
// * change to one line comments
// * change defines of constants to const
// * change array to vector<>
// * inline any short function

#include <iostream>
#include <vector>

using namespace std;
const int N = 40;

inline void sum(int& accm, vector<int> d)
{
    for (int i = 0; i < d.size(); i++)
    {
        accm += d[i];
    }
}


int main()
{
    int i;
    int accum = 0;
    vector<int> data(N);

    for(i = 0; i < N; ++i)
        data[i] = i;

    sum(accum, data);
    cout << "sum is " << accum << endl;

    return 0;
}