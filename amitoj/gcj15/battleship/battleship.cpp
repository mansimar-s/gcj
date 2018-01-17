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
        int R,C,W;
        in >> R;
        in >> C;
        in >> W;

        cout << "Solving case: " << (i+1) << endl;
        int perRow = C/W;
        int lastRow = perRow+W;
        if (C%W == 0) --lastRow;
        if(lastRow>C) lastRow = C;
        
        out << "Case #" << (i+1) << ": ";
        out << (perRow*(R-1) + lastRow) << endl;
    }
    return 0;
}
