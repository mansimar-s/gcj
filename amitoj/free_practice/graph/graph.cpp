#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
using namespace std;
class Graph
{
    private:
        int size;
        bool directed;
        typedef vector<pair<int,int> > AdjacencyList;
        vector<AdjacencyList*> _graph;

        Graph(const Graph&);
        Graph& operator = (const Graph&);

    public:
        Graph(int n, bool d=false) : size(n),directed(d) {
            for(int i = 0; i < size; ++i) {
                _graph.push_back(new AdjacencyList());
            }
        }

        ~Graph() {
            for(int i = 0; i < size; ++i) {
                delete _graph[i];
            }
        }

        void addEdge(int from, int to, int cost = 1) { 
            //sanity check on from & to
            _graph[from]->push_back(make_pair(to,cost));
            if(!directed)
                _graph[to]->push_back(make_pair(from,cost));
        }


        void print();
        void shortestPathUsingDjikstra(int from, int to);
        void isBipartite();
        void greedyChromaticity();
        void primSpanningTree();
        void topologicalSort();
        void topoRecurse(int current, bool* visited, bool* inStack, stack<int>& result, bool& cycles);
};

void Graph::print()
{
    std::cout<<"Graph :: \n";
    int i = 0;
    for(const auto& ot : _graph)
    {
        cout << "\t" << i <<":";
        ++i;
        for(const auto& it : *ot)
        {
            cout << " ("<< it.first << "," << it.second << ")";
        }
        cout << endl;
    }
}

void Graph::isBipartite()
{
    bool bi = true;
    int* color = new int[size];
    for(int i = 0; i < size; ++i)
        color[i] = 0;

    std::list<int> pending;
    color[0] = 1; //assign first color
    pending.push_back(0);

    while(!pending.empty())
    {
        int current = pending.front();
        pending.pop_front();
        //color the neighbours
        for(const auto& it : *_graph[current]) 
        {
            int neighbour = it.first;
            if(color[neighbour] and (color[neighbour] == color[current])) 
            {
                //neighbour has same color
                bi = false;
                break;
            } 
            else if(!color[neighbour]) 
            {
                //neighbour has no color
                //color the neighbour in a different color
                color[neighbour] = (color[current] == 1) ? 2 : 1;
                pending.push_back(neighbour);
            }
        }
        if(!bi) break;
    }
    if(!bi)
    {
        cout <<"Graph is NOT bipartite\n";
        for(int i = 0; i < size; ++i)  cout <<" "<< color[i];
        cout <<"\n";
    }
    else
    {
        cout <<"Graph is Bipartite\n";
        cout << "Set 1: ";
        for(int i = 0; i < size; ++i) if(color[i] == 1) cout <<" "<<i;
        cout <<"\nSet 2: ";
        for(int i = 0; i < size; ++i) if(color[i] == 2) cout <<" "<<i;
        cout <<"\n";
    }
    delete[] color;
}

void Graph::greedyChromaticity()
{
    int* colors = new int[size];
    bool* available = new bool[size];
    for(int i = 0; i < size; ++i)
    {
        colors[i] = -1;
    }

    queue<int> pending;
    pending.push(0);

    while(!pending.empty())
    {
        int cur = pending.front();
        pending.pop();

        if(colors[cur] != -1) continue;
        for(int i = 0; i < size; ++i)
        {
            available[i] = true;
        }

        for(auto it : *_graph[cur]) 
        {
            int nxt = it.first;
            if(colors[nxt] == -1)
            {
                pending.push(nxt);
            }
            else 
            {
                available[colors[nxt]] = false;
            }
        }
        for(int i = 0; i < size; ++i)
        {
            if(available[i])
            {
                colors[cur] = i;
                break;
            }
        }
    }
    int M = -1;
    for(int i = 0; i<size; ++i)
        M = max(M,colors[i]);

    cout <<"Chromaticity is " << (M+1) << endl;
    delete[] colors;
    delete[] available;
}


void Graph::shortestPathUsingDjikstra(int from, int to)
{
    bool* visited = new bool[size];
    int*  cost = new int[size];
    int*  previous = new int[size];

    for(int i = 0; i < size; ++i) {
        visited[i] = false;
        cost[i] = 0;
        previous[i] = 0;
    }

    std::list<int> pending;
    pending.push_back(from);

    while(!pending.empty())
    {
        int current = pending.front();
        pending.pop_front(); 
        visited[current] = 1;

        for(auto it : *_graph[current]) {
            int i = it.first;
            if (i==current) continue; // avoid self loops
            if(visited[i]) continue;

            //check if connected
            int newCost = cost[current] + it.second;
            if((cost[i] == 0) or (cost[i] > newCost)) {
                cost[i] = newCost;
                previous[i] = current;
            }
            pending.push_back(i);
        }
    }

    std::cout << "Final cost from " << from << " to " << to << " is " << cost[to];
    std::cout << "\nFinal Path == " ;
    int s = to;
    while(s != from)
    {
        std::cout << s << "  ";
        s = previous[s];
    }
    std::cout << s << "\n";
    delete[] previous;
    delete[] cost;
    delete[] visited;
}

void Graph::primSpanningTree()
{
    bool* visited = new bool[size];
    bool* added = new bool[size];
    Graph g2(size);

    for(int i = 0; i < size; ++i) {
        added[i] = false;
        visited[i] = false;
    }

    std::list<int> pending;
    pending.push_back(0);
    added[0] = true;

    typedef pair<int, pair<int,int>> Edge;
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    while(!pending.empty())
    {
        int current = pending.back();
        pending.pop_back();
        if(visited[current]) continue;

        visited[current] = true;
        //iterate over the neighbours
        for(const auto& it : *_graph[current]) 
        {
            if(!added[it.first])
                pq.push(make_pair(it.second,make_pair(current,it.first)));
        }

        while(!pq.empty())
        {
            auto edge = pq.top();
            pq.pop();
            if(!added[edge.second.first] or !added[edge.second.second])
            {
                g2.addEdge(edge.second.first, edge.second.second, edge.first);
                added[edge.second.first] = true;
                added[edge.second.second] = true;
                pending.push_back(edge.second.first);
                pending.push_back(edge.second.second);
                break;
            }
        }
    }
    cout<<"======= Prim MST \n";
    g2.print();
}

void Graph::topoRecurse(int current, bool* visited, bool* inStack, stack<int>& result, bool& cycles)
{
    if(visited[current]) {
        cycles = true;
        return;
    }
    if(inStack[current]) return;;

    visited[current] = true;
    for(auto it : *_graph[current])
    {
        topoRecurse(it.first, visited, inStack, result, cycles);
        if(cycles) return;
    }
    result.push(current);
    visited[current] = false;
    inStack[current] = true;
}

void Graph::topologicalSort()
{
    bool* visited = new bool[size];
    bool* inStack = new bool[size];

    for(int i = 0; i < size; ++i) {
        visited[i] = false;
        inStack[i] = false;
    }

    stack<int> result;

    bool cycles = false;
    for(int i = 0; i < size; ++i) {
        topoRecurse(i,visited, inStack,result,cycles);
    }

    delete[] visited;
    delete[] inStack;

    if(cycles)
    {
        cout << " cycles detected in graph, should be DAG\n";
    }
    else
    {
        cout << "Topo sorting : ";
        while(!result.empty()) {
            int i = result.top();
            cout << i << " ";
            result.pop();
        }
        cout <<"\n";
    }
}

void tests(Graph& g)
{
    g.print();
    //no. of edges
    g.shortestPathUsingDjikstra(0,4);
    g.isBipartite();
    g.greedyChromaticity();
    g.primSpanningTree();
}

void g1()
{
    Graph g(6);
    g.addEdge(0,1,7);
    g.addEdge(0,2,9);
    g.addEdge(0,5,14);
    g.addEdge(1,2,10);
    g.addEdge(1,3,15);
    g.addEdge(2,3,11);
    g.addEdge(2,5,2);
    g.addEdge(3,4,6);
    g.addEdge(4,5,9);

    tests(g);
}

void g2()
{
    Graph g(7);
    g.addEdge(0,1,7);
    g.addEdge(0,2,9);
    g.addEdge(0,5,14);
    g.addEdge(1,2,10);
    g.addEdge(1,3,15);
    g.addEdge(2,3,11);
    g.addEdge(2,5,2);
    g.addEdge(3,6,3);
    g.addEdge(4,5,9);
    g.addEdge(6,4,3);

    tests(g);
}

void g3()
{
    Graph g1(5);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(1, 3);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);

    tests(g1);

    Graph g2(5);
    g2.addEdge(1, 2);
    g2.addEdge(1, 4);
    g2.addEdge(1, 0);
    g2.addEdge(3, 0);
    g2.addEdge(3, 4);
    g2.addEdge(3, 2);
    tests(g2);
}

void g4()
{
    Graph g(9);
    g.addEdge(0,1,4);
    g.addEdge(0,7,8);
    g.addEdge(1,7,11);
    g.addEdge(7,8,7);
    g.addEdge(1,2,8);
    g.addEdge(7,6,1);
    g.addEdge(6,8,6);
    g.addEdge(8,2,2);
    g.addEdge(6,5,2);
    g.addEdge(5,2,4);
    g.addEdge(3,2,7);
    g.addEdge(3,5,14);
    g.addEdge(5,4,10);
    g.addEdge(3,4,9);

    tests(g);
}

int main()
{

    g1();
    g2();
    g3();
    g4();

    Graph g(6,true);
    g.addEdge(4,0);
    g.addEdge(5,0);
    g.addEdge(5,2);
    g.addEdge(4,1);
    g.addEdge(2,3);
    g.addEdge(3,1);
    g.topologicalSort();

    Graph g1(4,true);
    g1.addEdge(0, 1);
    g1.addEdge(0, 2);
    g1.addEdge(1, 2);
    g1.addEdge(2, 0);
    g1.addEdge(2, 3);
    g1.addEdge(3, 3);
    g1.topologicalSort();
}

