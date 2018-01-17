#include <cstdio>
#include <iostream>
using namespace std;

long ways(int N)
{
    if(N < 3) return 0;
    if(N==3) return 1;
    if(N==5) return 1;
    if(N==10) return 1;
    long r =ways(N-10) + ways(N-5) + ways(N-3);
    cout << "For " << N << " ways = " << r << endl;
    return r;
}

int main()
{
    int N = 13;
    cout << "No. of ways to achieve score = " << N << " is " << ways(N) << endl;
}
