#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Barber
{
    long duration;
    long endTime;
    long id;

    bool operator < (const Barber& b)
    {
        if(endTime == b.endTime)
            return id >= b.id;
        else
            return endTime > b.endTime;
    }
};

long gcd(long l1, long l2)
{
    while(l1 != l2)
    {
        if(l2 > l1) l2-= l1;
        else l1 -= l2;
    }
    return l1;
}

long gcd(const vector<Barber>& b)
{
    long g =-1;
    for(auto it : b)
    {
        if(g == -1) g = it.duration;
        else g = gcd(g, it.duration);
        if(g == 1) break;
    }
    return g;
}

long lcm(const vector<Barber>& b, long limit)
{
    long hcf = gcd(b);
    long lcm = hcf;
    for(auto it : b)
    {
        lcm *= (it.duration/hcf);
        if(lcm > limit) return -1;
    }
    return lcm;
}

long customersHandledInLCM(const vector<Barber>&b, long limit)
{
    long LCM = lcm(b,limit);
    if(LCM == -1) return -1;

    long customers = 0;
    for(auto it : b)
    {
        customers += LCM/it.duration;
    }
    return customers;
}

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
        long B;
        in >> B;
        long N;
        in >> N;

        cout << "Solving case: " << (i+1) << endl;
        vector<Barber> barbers;
        for(long j = 0; j < B; ++j)
        {
            Barber b;
            in >> b.duration;
            b.endTime = b.duration;
            b.id = j+1;

            barbers.push_back(b);
        }
        out << "Case #" << (i+1) << ": ";
        if(B>= N)
        {
            out << N << endl;
            continue;
        }

        long customers = customersHandledInLCM(barbers, 1000000000L);
        if(customers != -1)
        {
            while(N> customers)
                N -= customers;
        }
        if(B>= N)
        {
            out << N << endl;
            continue;
        }

        make_heap(barbers.begin(), barbers.end());
        N-=B;
        while(--N)
        {
            if(!(N%10000000)) cout << "N = " << N << endl;
            pop_heap(barbers.begin(), barbers.end()); 
            barbers.back().endTime += barbers.back().duration;
            push_heap(barbers.begin(), barbers.end());
        }
        out << barbers.front().id << endl;
    }
    return 0;
}
