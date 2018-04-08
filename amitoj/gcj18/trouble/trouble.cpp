#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
using namespace std;

typedef vector<int64_t> lint;

void troublesort(lint& L)
{
    bool done = false;
    while (not done) {
        done = true;
        for (long i = 0; i < L.size()-2; ++i) {
            if(L[i] > L[i+2]) {
                done = false;
                auto tmp = L[i];
                L[i] = L[i+2];
                L[i+2] = tmp;
            }
        }
    }
}

long troublesort_q(lint& L)
{
    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> even;
    priority_queue<int64_t, vector<int64_t>, greater<int64_t>> odd;
    for(long i =0; i < L.size(); ++i) {
        if(i%2 == 0) 
            even.push(L[i]);
        else
            odd.push(L[i]);
    }

    int64_t prev = -1;
    int64_t curr = -1;
    for(long i =0; i < L.size(); ++i) {
        if(i%2 == 0) {
            curr = even.top();
            even.pop();
        }
        else {
            curr = odd.top();
            odd.pop();
        }
        if(prev>curr)
            return i-1;
        prev = curr;
    }
    return -1;
}


void solve()
{
    int64_t N;
    cin >> N;
    lint L;
    L.reserve(N);
    for (int64_t i = 0; i < N; ++i) {
        int64_t Li;
        cin >> Li;
        L.push_back(Li);
    }

    auto res = troublesort_q(L);

    if(res == -1) cout << "OK\n";
    else cout << res << endl;
}

int main()
{
    static const int BufSize = 1024*1024;
    char* Buffer = new char[BufSize];
    cin.rdbuf()->pubsetbuf(Buffer, BufSize);
    int T;
    cin >> T;
    for(int i = 0; i < T; ++i)
    {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}



