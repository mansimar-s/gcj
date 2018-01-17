#include <list>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
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
        long D,K,N;
        in >> D;
        in >> K;
        in >> N;

        int clockwise = 1;

        if(K%2 == 0)
            clockwise = -1;

        //cout << "Solving case : " << i;

        out << "Case #" << i+1 << ": ";
        long moves = N % (D>>1);
        long kl = K+1;
        long kr = K-1;
        
        kl += clockwise * 2 * moves;
        kr += clockwise * 2 * moves;
        cout << "unp " << kl << " " << kr << endl; 
        if(kl < 1) kl += D;
        if(kr < 1) kr += D;
        if(kl > D) kl -= D;
        if(kr > D) kr -= D;
        out << kl << " " << kr << endl;
    }
    return 0;
}





