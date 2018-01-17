#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <set>
using namespace std;

struct Appt
{
    int i;
    int j;
    int unhappiness;
    Appt(int x, int y, int u) : i(x), j(y), unhappiness(u) {}
    bool operator < (const Appt& s) { return unhappiness < s.unhappiness;}
    void red() { --unhappiness;}
};

int solve(int R, int C,int N)
{
    //fill
    vector<set<Appt*>* > aa;
    for(int i =0; i <5; ++i)
    {
        aa.push_back(new set<Appt*>());
    }

    Appt*** apps = new Appt**[R];
    for(int i = 0; i < R; ++i)
    {
        apps[i] = new Appt*[C];
        for(int j = 0; j<C; ++j)
        {
            int u = 4;
            if(i == 0) --u;
            if(i == R-1) --u;
            if(j == 0) --u;
            if(j == C-1) --u;
            apps[i][j] = new Appt(i,j,u);            
            aa[u]->insert(apps[i][j]);
        }
    }

    int Rem = R*C - N;
    for(int i = 0; i < Rem; ++i)
    {
        set<Appt*>* from = NULL;
        for(int k = 4; k >=0; --k)
        {
            if(!aa[k]->empty())
            {
                from = aa[k];
                break;
            }
        }
        if(!from) break;

        Appt* app = *(from->begin());
        aa[app->unhappiness]->erase(app);
        app->unhappiness = 0;
        aa[app->unhappiness]->insert(app);

        //left n
        if(app->i>0)
        {
            Appt* l = apps[app->i-1][app->j];
            if(l->unhappiness)
            {
                aa[l->unhappiness]->erase(l);
                l->red();
                aa[l->unhappiness]->insert(l);
            }
        }
        //upper n
        if(app->j>0)
        {
            Appt* l = apps[app->i][app->j-1];
            if(l->unhappiness)
            {
                aa[l->unhappiness]->erase(l);
                l->red();
                aa[l->unhappiness]->insert(l);
            }
        }
        //right
        if(app->i<R-1)
        {
            Appt* l = apps[app->i+1][app->j];
            if(l->unhappiness)
            {
                aa[l->unhappiness]->erase(l);
                l->red();
                aa[l->unhappiness]->insert(l);
            }
        }
        //lower
        if(app->j<C-1)
        {
            Appt* l = apps[app->i][app->j+1];
            if(l->unhappiness)
            {
                aa[l->unhappiness]->erase(l);
                l->red();
                aa[l->unhappiness]->insert(l);
            }
        }
    }

    //cleanup
    for(int i =0; i <5; ++i)
    {
        delete aa[i];
    }
    int total = 0;
    
    for(int i = 0; i < R; ++i)
    {
        for(int j = 0; j<C; ++j)
        {
            cout << apps[i][j]->unhappiness << "\t";
            total += apps[i][j]->unhappiness;
            delete apps[i][j];
        }
        cout << endl;
        delete[] apps[i];
    }
    delete[] apps;
    return total>>1;
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

    int T;
    in >> T;
    for(int i = 0; i < T; ++i)
    {
        int R,C,N;
        in >> R;
        in >> C;
        in >> N;

        cout << "Solving case : " << i << endl;;

        out << "Case #" << i+1 << ": ";
        out << solve(R,C,N) << endl;
    }
    return 0;
}





