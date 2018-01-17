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
        cout << "Usage : "<<argv[0] <<" test.in test.out";
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
    for(int x = 0; x < T; ++x)
    {
        string s;
        in >> s;
        
        cout << "Solving case : " << x<<endl;
        out << "Case #" << x+1 << ": ";

        long counter[26];
        long digits[10];
        for(int i = 0; i < 26; ++i)
        {
            counter[i] = 0;
        }
        for(int i = 0; i < 10; ++i)
        {
            digits[i] = 0;
        }

        for(auto c :s)
        {
            counter[(int)(c-'A')]++;
        }

        digits[0] = counter['Z'-'A'];
        digits[2] = counter['W'-'A'];
        digits[4] = counter['U'-'A'];
        digits[6] = counter['X'-'A'];
        digits[8] = counter['G'-'A'];

        digits[1] = counter['O'-'A'] -digits[2] -digits[4]-digits[0];
        digits[3] = counter['H'-'A'] -digits[8];
        digits[5] = counter['F'-'A'] -digits[4];
        digits[7] = counter['S'-'A'] -digits[6];
        digits[9] = counter['N'-'A'] -digits[1] -digits[7];
        digits[9] = digits[9]/2;
        for(int i =0; i < 10; ++i)
        {
            for(int j = 0; j <digits[i]; ++j)
            {
                out << i;
            }
        }
        out<<endl;
    }
    return 0;
}





