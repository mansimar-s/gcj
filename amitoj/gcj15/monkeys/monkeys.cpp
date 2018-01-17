#include <list>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct SfxTree
{
    int count;
    SfxTree* kids[26];

    SfxTree() {
        count = 0;
        for(int i =0; i<26; ++i)
            kids[i] = NULL;
    }

    ~SfxTree() {
        for(int i =0; i<26; ++i)
        {
            delete kids[i];
        }
    }


    int insert(const char* str)
    {
        if(!*str)
        {
            ++count;
        }
        else
        {
            int id = *str - 'A';
            if(!kids[id])
                kids[id] = new SfxTree();

            kids[id]->insert(str+1);
        }
        return 0;
    }

    int lookup(const char* str,int depth)
    {
        if(!*str)
        {
            return -1;
        }
        else
        {
            int id = *str - 'A';
            if(count > 0)
                return max(depth, kids[id]->lookup(str+1,depth+1));
            else
                return kids[id]->lookup(str+1,depth+1);

        }
    }
};

double solve(int K, int L, int S, string letters, string word)
{
    const char* w = word.c_str();
    SfxTree sfx;
    for(unsigned int i = 0; i < L; ++i)
    {
        sfx.insert(w+i);
    }
    int max = sfx.lookup(w,0);
    int words = 0;
    if(max > 0)
    {
        int remL = S - L;
        int reuse = L - max;
        int moreWords = remL/reuse;
        words = 1+moreWords;
    }
    else
        words = S/L;

    int distrib[26] = {0};
    const char* l = letters.c_str();
    for(unsigned int i = 0; i < K; ++i)
    {
        ++distrib[l[i] - 'A'];
    }
    double prob = 1;
    for(int i = 0; i < L; ++i)
    {
        int ll = distrib[w[i] - 'A' ];
        prob *= (double)ll/K;
    }
    prob *= (S-L+1);

    cout << "Max words = " << words << " prob = " << prob;
    return prob>0 ? (words - prob): 0;
    return 0;
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
        int K,L,S;
        in >> K;
        in >> L;
        in >> S;

        string letters;
        string word;
        in >> letters;
        in >> word;

        cout << "Solving case: " << (i+1) << endl;
        out << "Case #" << (i+1) << ": ";
        out << solve(K,L,S,letters,word) << endl;
    }
    return 0;
}
