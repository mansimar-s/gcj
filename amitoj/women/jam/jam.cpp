#include <list>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
    if(argc < 3)
    {
        cout << "Usage : jam test.in test.out";
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
        int N;
        in >> N;
        int twoN = (N << 1);

        cout << "Solving case : " << i;
        out << "Case #" << i+1 << ":";
        queue<long, list<long> > price;
        for(int j = 0; j < twoN; ++j)
        {
            long p;
            in >> p;

            if(price.empty() or (price.front() != p))
            {
                //selling price
                out << " " << p;
                long op = p/3;
                op <<= 2;
                price.push(op);
            }
            else
            {
                price.pop();
            }
        }
        out << endl;
        cout << endl;
    }
    return 0;
}





