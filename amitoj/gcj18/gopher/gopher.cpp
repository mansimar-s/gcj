#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <exception>
#include <cmath>
using namespace std;

class TestFailed : public exception
{
    const char* what() { return " Test Failed\n";}
};

struct Cell
{
    int i;
    int j;
    bool dug;
    int score;

    Cell() : i(0), j(0), dug(false), score(0) {}
    
    void set(int a, int b) {
        i=a;
        j=b;
    }

    void deploy()
    {
        cout << i+5 << " " << j+5 << endl;
        //cerr << " Deployed at " << i << " " << j << endl;
    }

    bool read()
    {
        cin >> i >> j;
        if (i==-1 and j == -1)
            throw TestFailed();
        if(i==0 and j==0)
            return true;
        
        i-=5;
        j-=5;
        //cerr << "Read in " << i << " and " << j << endl;
        return false;
    }
};

class Grid
{
    Cell** matrix;
    int I;
    int J;

    public:
        Grid(int a, int b) : I(a), J(b)
        {
            matrix= new Cell*[I];
            for (int i = 0; i < I; ++i) {
                matrix[i] = new Cell[J];
                for (int j = 0; j<J; ++j) {
                    matrix[i][j].set(i,j);
                }
            }
        }

        ~Grid()
        {
            for (int i = 0; i < I; ++i) {
                delete[] matrix[i];
            }
            delete[] matrix;
        }

        Cell& next()
        {
            int best_score = 10;
            int best_i=0;
            int best_j=0;
            for (int i = 1; i < I-1; ++i) {
                for (int j = 1; j < J-1; ++j) {
                    if(matrix[i][j].score < best_score) {
                        best_score = matrix[i][j].score;
                        best_i = i;
                        best_j = j;
                    }
                }
            }
            return matrix[best_i][best_j];
        }

        bool update(int i, int j)
        {
            if(matrix[i][j].dug)
                return false;
            matrix[i][j].dug = true;
            for(int p = -1; p <= 1; ++p) {
                int ii = i+p;
                if(ii < 0 or ii >= I) continue;

                for(int q = -1; q <= 1; ++q) {
                    int jj = j+q;
                    if(jj < 0 or jj >= J) continue;
                    matrix[ii][jj].score += 1;
                }
            }
            return true;
        }

        bool attempt()
        {
            auto next_cell = next();
            next_cell.deploy();
            Cell n;
            if(n.read())
                return true;
            update(n.i, n.j);
            //print();
            return false;
        }

        void iterate()
        {
            for(int i = 0; i< 1000; ++i) {
                //cerr << "Attempt " << i << endl;
                if(attempt())
                    break;
            }
        }
        void print()
        {
            for (int i = 0; i < I; ++i) {
                for (int j = 0; j < J; ++j) {
                    if(matrix[i][j].dug)
                        cerr << "X";
                    else
                        cerr << ".";
                }
                cerr << "\n";
            }
        }
};



void solve()
{
    int A;
    cin >> A;

    //cerr << "\t It has " << A << " area \n";
    int I =0;
    int J =0;
    if (A == 20)
    {
        I = 5;
        J = 4;
    }
    else if (A == 200)
    {
        I = 15;
        J = 14;
    }
    else
    {
        double b = sqrt((double)A);
        I = (int)b;
        J = I;
        if(I*J < A)
            J+=1;
    }

    Grid g(I,J);
    //cerr << "\tCreated grid of size " <<I<<" X " << J << endl;
    g.iterate();
}

int main()
{
    int T;
    cin >> T;
    //cerr << "Total " << T << " testcases to be run"<< endl;
    for(int i = 0; i < T; ++i)
    {
        //cerr << "Running case " << i << endl;
        solve();
    }
    return 0;
}





