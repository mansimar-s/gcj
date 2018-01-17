#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;
typedef pair<string,string> PP;

PP minimize(string c, string j, char status, int i = 0)
{
    if(i >= c.length()) return make_pair(c,j);

    if(c[i] != '?' and j[i] != '?') return minimize(c,j, status, i+1);

    if(c[i] == '?' and j[i] == '?')
    {
        if(status == 'E')
        {
            c[i] = 
        }
    }
}

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
    for(int i = 0; i < T; ++i)
    {
        string C;
        in >> C;
        string J;
        in>>J;
        PP minimize(C,J, 'E');
        
            lst.push_back(make_pair(f,s));
            {
                if(first.find(f) ==first.end())
                    first.insert(make_pair(f,1));
                else
                    first[f]++;
                if(second.find(s) ==second.end())
                    second.insert(make_pair(s,1));
                else
                    second[s]++;
            }
        }

            for(auto it : lst)
            {
                if(first[it.first] > 1 and second[it.second] > 1)
                {
                    first[it.first]--;
                    second[it.second]--;
                    ++duplicates;
                }
            }
        

        cout << "Solving case : " << i<<endl;
        out << "Case #" << i+1 << ": " <<duplicates << endl;
    }
    return 0;
}





