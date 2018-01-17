#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;
typedef map<string,long> Dict ;

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
        Dict first;
        Dict second;

        int w;
        in >> w;
        long duplicates = 0;
        list<pair<string,string>> lst;
        for(int j =0; j < w; ++j)
        {
            string f;
            in >> f;
            string s;
            in>>s;
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





