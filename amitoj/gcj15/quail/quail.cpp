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
        long Y;
        long N;
        vector<long> P;
        vector<long> S;

        in >> Y;
        in >> N;

        long temp;
        long fastest = -1;
        long fastestSpeed = -1;
        for(long j = 0; j < N; ++j)
        {
            in >> temp;
            P.push_back(temp);
        }
        for(long j = 0; j < N; ++j)
        {
            in >> temp;
            S.push_back(temp);
            if(temp > fastestSpeed)
            {
                fastestSpeed = temp;
                fastest = j;
            }
        }

        int sign = 1;
        if(P[fastest] < 0)
            sign = -1;
       
        double tmax = 0;
        for(long j = 0; j < N; ++j) {
            if((sign > 0 and P[j] < 0) or (sign < 0 and P[j] > 0)) continue;
            double t = (double)(sign*P[j]) /(Y-S[j]);
            cout << "Catching quail " << j  << " will take " << t << "seconds\n";
            tmax = max(t, tmax);
        }
        cout << "After one phase " << sign << " time = " << tmax << " dist = " << (tmax*Y)<< endl;
        double tone = tmax;

        sign = -sign;
        double extra = tmax*Y;
        tmax = 0;
        for(long j = 0; j < N; ++j) {
            if((sign > 0 and P[j] < 0) or (sign < 0 and P[j] > 0)) continue;
            double t = (double)(sign*P[j] + extra + tone*S[j]) /(Y-S[j]);
            cout << "Catching quail " << j  << " will take " << t << "seconds\n";
            tmax = max(t, tmax);
        }
        cout << "After two phase " << sign << " time = " << tmax << " dist = " << (tmax*Y - extra - extra)<< endl;

        tmax += tone;
        cout << "Solving case: " << (i+1) << endl;
        out << "Case #" << (i+1) << ": ";
        out << tmax << endl;
    }
    return 0;
}
