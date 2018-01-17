#include <iostream>
#include <stack>
#include <list>
#include <cstdio>
#include <cmath>
using namespace std;

class Tree
{
    public:
        int data;
        Tree* left;
        Tree* right;

        Tree(const Tree&);
        Tree& operator = (const Tree&);

    public:
        Tree(int i) : data(i),left(NULL),right(NULL) {}
        ~Tree() { delete left; delete right ; }

        Tree& operator << (int item);

        void print() const;
        void draw() const;
        int depth() const;
        int floor(Tree*, int) const;
        int predecessor(Tree*, int) const;
        void inorder(Tree* root) const;
        //void merge(Tree& list2);
};

/*
template<class T>
T max(T a,T b) { return a > b ? a : b; }

template<class T>
T min(T a,T b) { return a < b ? a : b; }
*/

int Tree::predecessor(Tree* root, int v) const
{
    if(!root) return v;
    if(v < root->data)
    {
        return predecessor(root->left, v);
    }
    else if(v == root->data)
    {
        int pred = predecessor(root->left,v);
        if(pred < v) return pred;
        else return root->data;
    }
    else
    {
        int pred = predecessor(root->right,v);
        if(pred > root->data and pred < v) return pred;
        else return root->data;
    }
}
int Tree::floor(Tree* root, int v) const
{
    if(root->data == v) return v;
    else if(root->data > v)
    {
        if(root->left)
            return floor(root->left, v);
        else
            return root->data;
    }
    else
    {
        if(root->right)
        {
            int fl = floor(root->right,v);
            if(fl>v) return root->data;
            else return fl;
        }
        else
            return root->data;
    }
}

void Tree::print() const
{
    cout << data << " ";
    if(left) left->print();
    if(right) right->print();
}

void Tree::draw() const
{
    list<const Tree*> *q = new list<const Tree*>();
    list<const Tree*> *qn = new list<const Tree*>();

    q->push_back(this);

    int dp = depth();
    for(int i = 0; i < dp; ++i)
    {
        int padding = pow(2, (dp - i -2)) ;
        if(padding>0)
        {
        //    padding += 2;
        }
        while(!q->empty())
        {
            const Tree* node = q->front();
            q->pop_front();
            for(int j = 0; j < padding; ++j) printf("   ");

            if(node)
                printf("%3d",node->data);
            else
                printf(" - ");

            qn->push_back(node ? node->left : NULL);
            qn->push_back(node ? node->right : NULL);
        }
        printf("\n");
        list<const Tree*> *temp = q;
        q = qn;
        qn = temp;
    }
}

int Tree::depth() const
{
    if(!this) return 0;

    int lDepth = left->depth();
    int rDepth = right->depth();

    return ((lDepth > rDepth) ? lDepth : rDepth) + 1;
}

Tree& Tree::operator << (int item)
{
    if(item < data)
    {
        if(left)
            *left << item;
        else
        {
            left = new Tree(item);
        }
    }
    else
    {
        if(right)
            *right << item;
        else
        {
            right = new Tree(item);
        }
    }
}

/*
void Tree::merge(Tree& l2)
{
    Node* l1Ptr = this->start;
    Node* l2Ptr = l2.start;

    l2.start = NULL; // l2 is gonna be consumed

    Node* current = NULL;
    while(l1Ptr and l2Ptr)
    {
        if(l1Ptr->data < l2Ptr->data )
        {
            if(current)
                current->next = l1Ptr;
            current = l1Ptr;

            l1Ptr = l1Ptr->next;
        }
        else
        {
            if(current)
                current->next = l2Ptr;
            current = l2Ptr;

            l2Ptr = l2Ptr->next;
        }
        if(!start) start = current;
    }

    if(l1Ptr)
    {
        if(current)
            current->next = l1Ptr;
        else 
            start = l1Ptr;
    }

    if(l2Ptr)
    {
        if(current)
            current->next = l2Ptr;
        else 
            start = l2Ptr;
    }


    //assuming ascending order sort

}
*/

Tree* findNode (Tree* root, int data)
{
    Tree* ptr = root;

    while(ptr)
    {
        if(ptr->data == data) return ptr;
        if(data < ptr->data) ptr = ptr->left;
        else ptr = ptr->right;
    }
    return NULL;
}

typedef list<Tree*> TStack;

bool findPath(Tree* root, Tree* element, TStack* tstack)
{
    if(!root) return false;

    tstack->push_back(root);
    if(root == element)
    {
        return true;
    }
    else
    {
        bool status = findPath(root->left, element, tstack) or findPath(root->right, element, tstack);
        if(!status)
            tstack->pop_back();
        return status;
    }
}

void printNodesAtDepth(Tree* root, int depth)
{
    if(!root) return;

    if(depth == 0) 
    {
        cout << root->data << " ";
        return;
    }
    else if (depth > 0)
    {
        printNodesAtDepth(root->left, depth-1);
        printNodesAtDepth(root->right, depth-1);
    }
}

Tree* findCommonAncestor(Tree* root, Tree* first, Tree* second)
{
    TStack nodeStack1;
    TStack nodeStack2;

    if(!findPath(root, first, &nodeStack1)) return NULL;
    if(!findPath(root, second, &nodeStack2)) return NULL;

    auto i1 = nodeStack1.begin();
    auto i2 = nodeStack2.begin();
    Tree* prev = NULL;
    for(; i1 != nodeStack1.end() and i2 != nodeStack2.end(); ++i1,++i2)
    {
        if(*i1 == *i2)
        {
            prev = *i1;
        }
        else
            break;
    }
    return prev;
}

Tree* findCommonAncestor(Tree* root, int first, int second)
{
    Tree* ptr = root;

    while(ptr)
    {
        if(ptr->data == first and ptr->data == second)
            return ptr;

        if(first < ptr->data and second < ptr->data)
            ptr = ptr->left;
        else if(first > ptr->data and second > ptr->data)
            ptr = ptr->right;
        else
            break;
    }
    return ptr;
}

void Tree::inorder(Tree* root) const
{
    stack<Tree*> st;

    cout << "Inorder : " ;
    while(1)
    {
        if(root)
        {
            st.push(root);
            root = root->left;
        }
        else if(st.empty())
        {
            break;
        }
        else
        {
            root = st.top();
            st.pop();
            cout << " " << root->data;
            root = root->right;
        }
    }
    cout << "\n";
}

int main()
{
    Tree* myTree = NULL;
    int input = 0;
    cout << "Enter tree elements\n";
    cin >> input;
    while(!cin.eof())
    {
        if(!myTree) 
            myTree = new Tree(input);
        else
            *myTree << input;

        cin >> input;
    }
    if(myTree)
    {
        myTree->print();
        cout << endl;
        myTree->draw();
        cout << endl;
        cout << "Depth = " << myTree->depth() << endl;
    }

    cin.clear();
    int f,s;
    cout << "Enter first element \n";
    cin >> f;
    cout << "Enter second element \n";
    cin >> s;

    Tree* ff = findNode(myTree, f);
    Tree* ss = findNode(myTree, s);

    Tree* common1 = findCommonAncestor(myTree, ff, ss);
    Tree* common2 = findCommonAncestor(myTree, f, s);
    if(!common2 or !common1) 
        cout <<"somebody is null "<< common1 << " c " << common2 << endl;
    else if(common2 == common1)
        cout << "Same result by both methods = " << common1->data << endl;
    else
        cout <<"Different result by 2 menthods :( " << common1->data << "  " << common2->data << endl;


    for(int i = -1; i <= 20; ++i)
        cout << i <<" : " << myTree->predecessor(myTree,i) << endl; 

    myTree->inorder(myTree);

}
