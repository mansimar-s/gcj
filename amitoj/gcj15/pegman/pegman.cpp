#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Cell
{
    char dir;
    bool l;
    bool r;
    bool u;
    bool d;

    Cell() : dir('.'), l(true),r(true),u(true),d(true) {}
    int count()
    {
        if (dir == '.') return 0;
        if(!l and !r and !u and !d) return -1;
        if(l and dir == '<') return 0;
        if(r and dir == '>') return 0;
        if(u and dir == '^') return 0;
        if(d and dir == 'v') return 0;
        return 1;
    }
};

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
        int R,C;
        in >> R;
        in >> C;

        cout << "Solving case: " << (i+1) << endl;
        Cell** grid = new Cell*[R];
        for(int j = 0; j < R; ++j)
        {
            string row;
            in >> row;
            grid[j] = new Cell[C];
            for(int k = 0; k < C; ++k)
                grid[j][k].dir = row[k];
        }
        
        for(int c=0;c<C;++c)
        {
            //top row
            for(int r=0; r < R; ++r)
            {
                if(grid[r][c].dir != '.')
                {
                    grid[r][c].u = false;
                    break;
                }
            }
            //bottom row
            for(int r=R-1; r >=0; --r)
            {
                if(grid[r][c].dir != '.')
                {
                    grid[r][c].d = false;
                    break;
                }
            }
        }

        for(int r=0;r<R;++r)
        {
            //left row
            for(int c=0; c < C; ++c)
            {
                if(grid[r][c].dir != '.')
                {
                    grid[r][c].l = false;
                    break;
                }
            }
            //bottom row
            for(int c=C-1; c >=0; --c)
            {
                if(grid[r][c].dir != '.')
                {
                    grid[r][c].r = false;
                    break;
                }
            }
        }


        int tot = 0;
        for(int j = 0; j < R; ++j)
        {
            if(tot >=0)
            {
                for(int k = 0; k < C; ++k)
                {
                    int cc = grid[j][k].count();
                    if(cc < 0)
                    {
                        tot = -1;
                        break;
                    }
                    else tot+=cc;
                }
            }
            delete[] grid[j];
        }
        delete[] grid;
        out << "Case #" << (i+1) << ": ";
        if(tot < 0)
            out << "IMPOSSIBLE" << endl;
        else
            out << tot << endl;

    }
    return 0;
}
