#include <list>
#include <queue>
#include <iostream>
#include <fstream>
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
        long N;
        in >> N;
        
        cout << "Solving case : " << i<<endl;
        out << "Case #" << i+1 << ": ";
        if(!N) out << "INSOMNIA\n";
        else
        {
            bool myset[10] = {false};
            for(int j = 0; j < 10; ++j) myset[j] = false;
            long NN = N;
            while(1)
            {
                long num = NN;
                while(num)
                {
                    long digit = num%10;
                    num /= 10;
                    myset[digit] = true;
                }
                bool anyLeft = false;
                for(int j = 0; j < 10; ++j)
                {
                    if(!myset[j]) { anyLeft = true; break;}
                }
                if(!anyLeft)
                {
                    out << NN << endl;
                    break;
                }
                else
                {
                    NN += N;
                }
            }
        }
    }
    return 0;
}





