#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

bool validateString(const string& s, const vector<string>& v)
{
    for(vector<string>::const_iterator it = v.begin(); it != v.end(); ++it)
    {
        if(s.find(*it) != s.npos)
        {
            //cout <<"Found match for " << s << "\n" << *it << endl;
            return false;
        }
    }
    return true;
}

string generateRandomString()
{
    vector<char> remaining;
    char c = 65;
    for(int i = 0; i < 26; i++)
    {
        remaining.push_back(c);
        c++;
    }

    string s;
    for(int i = 25; i >= 0; --i)
    {
        int k = rand() % (i+1);
        char a[2];
        a[0] = remaining[k];
        a[1] = '\0';
        s.append(a);
        remaining.erase(remaining.begin()+k);
    }
    return s;
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

    cout << "Generating random strings\n";
    vector<string> randoms;
    for(int i = 0; i < 10000; ++i)
    {
        string s = generateRandomString();
        randoms.push_back(s);
    }

    int T;
    in >> T;
    for(int i = 0; i < T; ++i)
    {
        int N;
        in >> N;

        cout << "Solving case " << i+1 << endl;
        out << "Case #" << i+1 << ": ";
        vector<string> passwords;
        bool found = false;
        for(int k = 0; k < N; ++k) 
        {
            string s;
            in >> s;
            if(s.size() == 1)
            {
                found = true;
            }
            passwords.push_back(s);
        }

        if(found)
        {
            out << "IMPOSSIBLE" << endl;
            continue;
        }

        for(int i = 0; i < 10000; ++i)
        {
            string s1 = randoms[i];
            if(validateString(s1, passwords))
            {
                out << s1 << endl;
                found = true;
                break;
            }
        }

        if(!found)
            out << "IMPOSSIBLE" << endl;
    }
    return 0;
}





