#include <list>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

static long*** ThreeDArr_true;
static long*** ThreeDArr_false;

static const long prime = 1000000007LL;
long getPossibles(long C, long V, long L, bool consonantOk)
{
    if(consonantOk and (ThreeDArr_true[C][V][L] != -1))
        return ThreeDArr_true[C][V][L];

    if(!consonantOk and (ThreeDArr_false[C][V][L] != -1))
        return ThreeDArr_false[C][V][L];

    if(L==1) {
        if(consonantOk) {
            ThreeDArr_true[C][V][L] = C+V;
            return C+V;
        } else {
            ThreeDArr_false[C][V][L] = V;
            return V;
        }
    }

    long possibC = 0;
    if(consonantOk)
    {
        long wConsonant  = getPossibles(C,V,L-1,false);
        possibC = wConsonant*C;
    }

    long possibV = getPossibles(C,V,L-1,true) * V;
    long possib = (possibC + possibV)%prime;

    //cout << "For C = " << C << " V = " << V << " L = "<< L << " con" << consonantOk << " possibs = " << possib << " PossibC = " << possibC << " PossibV = " << possibV << endl;
    if(consonantOk) {
        ThreeDArr_true[C][V][L] = possib;
        return possib;
    }else {
        ThreeDArr_false[C][V][L] = possib;
        return possib;
    }
    return possib;
}

int main(int argc, char** argv)
{
    ThreeDArr_false = new long**[51];
    ThreeDArr_true = new long**[51];
    for(int i = 0; i <= 50; ++i)
    {
        ThreeDArr_false[i] = new long*[51];
        ThreeDArr_true[i] = new long*[51];
        for(int j = 0; j <= 50; ++j)
        {
            ThreeDArr_false[i][j] = new long[501];
            ThreeDArr_true[i][j] = new long[501];
            for(int k = 0; k <= 500; ++k)
            {
                ThreeDArr_false[i][j][k] = -1;
                ThreeDArr_true[i][j][k] = -1;
            }
        }
    }

    if(argc < 3)
    {
        cout << "Usage : prog test.in test.out";
        return 0;
    }
    cout << argv[0] << " " << argv[1] << " " << argv[2] << endl;

    ifstream in(argv[1]);
    if(!in.is_open()) {
        cout << "Failed to open " << argv[1] << endl;
        return 0;
    }

    ofstream out(argv[2]);
    if(!out.is_open()) {
        cout << "Failed to open " << argv[2] << endl;
        return 0;
    }

    int T;
    in >> T;
    for(int i = 0; i < T; ++i)
    {
        long C,V,L;
        in >> C;
        in >> V;
        in >> L;

        cout << "Solving case " << i+1 << endl;
        out << "Case #" << i+1 << ": ";
        out << getPossibles(C,V,L,false) << endl;
    }
    return 0;
}





