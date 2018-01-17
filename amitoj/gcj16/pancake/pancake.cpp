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
    for(int i = 0; i < T; ++i)
    {
        string s;
        in >> s;
        
        cout << "Solving case : " << i<<endl;
        out << "Case #" << i+1 << ": ";

        long iteration = 0;
        while(1)
        {
            auto it = s.find_last_of('-');
            if(it == string::npos)
            {
                out<< iteration << endl;
                break;
            }

            auto fit = s.find_first_of('-');
            --fit;
            if(fit != string::npos and (fit < it))
            {
                //additional flip
                string sub = s.substr(0,1+fit );
                for(auto k = sub.begin(); k != sub.end(); ++k)
                {
                    if(*k == '-') *k = '+';
                    else *k = '-';
                }

                reverse(sub.begin(), sub.end());
                s.replace(0, 1+fit, sub);
                ++iteration;
                //cout << "After Flip a " << fit << " "<< iteration << " " << s << endl;
            }
            {
                //single flip
                string sub = s.substr(0,1+it );
                for(auto k = sub.begin(); k != sub.end(); ++k)
                {
                    if(*k == '-') *k = '+';
                    else *k = '-';
                }

                reverse(sub.begin(), sub.end());
                s.replace(0, 1+it, sub);
                ++iteration;
                //cout << "After Flip b " << it << " "<< iteration << " " << s << endl;
            }
        }
    }
    return 0;
}





