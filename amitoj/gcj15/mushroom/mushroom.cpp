#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
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
        long N;
        in >> N;
        long rate = 0;
        long sum = 0;
        int prev = 0;
        vector<long> mush;
        for (long j = 0; j < N; ++j)
        {
            long m;
            in >> m;
            mush.push_back(m);
            if(m < prev)
            {
                long diff = prev - m;
                sum += diff;
                rate = max(rate, diff);
            }
            prev = m;
        }
        long constEaten = 0;
        for (long j = 0; j < N-1; ++j)
        {
            constEaten += min(mush[j], rate);
        }

        out << "Case #" << (i+1) << ": ";
        out << sum << " " << constEaten << endl;
    }
    return 0;
}





