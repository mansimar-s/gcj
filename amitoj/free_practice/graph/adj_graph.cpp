#include <iostream>
#include <list>
#include <vector>

class Graph
{

    private:
        int** gMatrix;
        int size;

        Graph(const Graph&);
        Graph& operator = (const Graph&);

    public:
        Graph(int n) : size(n) {
            gMatrix = new int*[size];
            for(int i = 0; i < size; ++i) {
                gMatrix[i] = new int[size];
            }
        }

        ~Graph() {
            for(int i = 0; i < size; ++i) {
                delete[] gMatrix[i];
            }
            delete[] gMatrix;
        }

        void addEdge(int cost, int from, int to) { 
            //sanity check on from & to
            gMatrix[from][to] = cost;
            gMatrix[to][from] = cost;
        }


        void print();
        void shortestPathUsingDjikstra(int from, int to);
};

void Graph::print()
{
    std::cout<<"Graph :: \n";
    for(int i =0; i < size; ++i)
    {
        if(i==0)
        {
            std::cout << "-   ";
            for(int j = 0; j<size; ++j)
            {
                std::cout << (char)('A' + j) << "   ";
            }
            std::cout << std::endl;
        }

        std::cout << (char)('A' + i) << "   ";
        for(int j =0; j < size; ++j)
        {
            std::cout << gMatrix[i][j] << "   ";
        }
        std::cout << std::endl;
    }
}

static int min(int i, int j) { return (i<j)?i:j; }

void Graph::shortestPathUsingDjikstra(int from, int to)
{
    int* visited = new int[size];
    int* costs = new int[size];
    int* previous = new int[size];

    for(int i = 0; i<size; ++i) {
        visited[i] = 0;
        costs[i] = 0;
        previous[i] = 0;
    }

    std::list<int> pending;
    pending.push_back(from);
    while(!pending.empty())
    {
        int current = pending.front();
        pending.pop_front(); 
        visited[current] = 1;

        for(int i = 0; i < size; ++i) {
            if (i==current) continue; // avoid self loops
            if(visited[i]) continue;

            //check if connected
            if(gMatrix[current][i]) {
                int newCost = costs[current] + gMatrix[current][i];
                if((costs[i] == 0) or (costs[i] > newCost)) {
                    costs[i] = newCost;
                    previous[i] = current;
                }
                pending.push_back(i);
            }
        }
    }

    std::cout << "Final cost from " << from << " to " << to << " is " << costs[to];
    std::cout << "\nFinal Path == " ;
    int s = to;
    while(s != from)
    {
        std::cout << s << "  ";
        s = previous[s];
    }
    std::cout << s << "\n";
}


int main()
{

    int num_vertex = 0;
    std::cin >> num_vertex;

    Graph g(num_vertex);

    for (int i = 0; i<num_vertex; ++i)
    {
        for(int j = 0; j<=i; ++j)
        {
            int cost = 0;
            std::cin >> cost;
            g.addEdge(cost, i, j);
        }
    }

    g.print();
    //no. of edges
    g.shortestPathUsingDjikstra(0,4);
}



