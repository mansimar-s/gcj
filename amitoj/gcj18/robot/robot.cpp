#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int64_t evaluate(const string& s)
{
    int64_t strength = 1;
    int64_t damage = 0;
    for (char c: s) {
        if(c=='C')
            strength <<= 1;
        else
            damage += strength;
    }
    return damage;

}

void solve()
{
    int64_t D =0;
    cin >> D;

    string P;
    cin >> P;

    int64_t swaps = 0;
    while(evaluate(P) > D) {
        auto res = P.rfind("CS");
        if(res == string::npos) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        P.replace(res,2,"SC");
        swaps += 1;
    }
    cout << swaps << endl;

}

int main()
{
    int T;
    cin >> T;
    for(int i = 0; i < T; ++i)
    {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}





