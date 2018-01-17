#include <list>
#include <vector>

class Graph
{
    public:
        class Edge;
        class Vertex;
        typedef std::list<Edge*> EdgeList;
        typedef std::vector<Edge*> EdgeVector;
        typedef std::vector<Vertex*> VertexVector;

        class Vertex
        {
            int id_;
            bool visited_;
            EdgeList edges_;

            public:
             Vertex(int id) : id_(id) {}
             void addEdge(Edge* e) { edges_.push_back(e); }
             const EdgeList& getEdges() const { return EdgeList; }

             bool isVisited() const { return visited_; }
             void markVisited(bool v=true) { visited_ = v; }
        };

        class Edge
        {
            int cost_;
            Vertex* first_;
            Vertex* second_;

            public:
             Edge(int cost, Vertex* f, Vertex* s) : cost_(cost), first_(f), second_(s) {}
             Vertex* first() const { return first_; }
             Vertex* second() const{ return second_;}
        };

    private:
        EdgeVector edges_;
        VertexVector vertices_;

        Graph(const Graph&);
        Graph& operator = (const Graph&);

    public:
        Graph() {}
        ~Graph();

        void addEdge(int from, int to) { 
            //sanity check on from & to
            Edge* e = new Edge(getVert(from), getVertex(to));
            edges_.push_back(e); 
            e.first()->addEdge(e);
            e.second()->addEdge(e);
        }

        void addVertex(int id) { vertices_.push_back(new Vertex(id)); }

        Vertex* getVertex(int id) const { return vertices_.at(id); }

        const VertexVector& getVertices() const { return VertexVector; }
        const EdgeVector& getEdges() const { return EdgeVector; }

        void print();
};

void Graph::print()
{


int main()
{
    Graph g;

    int num_vertex = 0;
    cin >> num_vertex;

    for (int i = 0; i<num_vertex; ++i)
    {
        g.addVertex(i);
    }

    for (int i = 0; i<num_vertex; ++i)
    {
        for(int j = 0; j<=i; ++j)
        {
            int cost = 0;
            cin >> cost;
            g.addVertex(cost, i, j);
        }
    }

    g.print();


    //no. of edges
}



