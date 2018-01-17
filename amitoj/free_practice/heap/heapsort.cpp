#include <iostream>
#include <vector>

using namespace std;

class Heap
{
    vector<int> arr;
    int size;

    public:
    Heap() : size(0) {}
        void insert(int i) { arr.push_back(i); ++size;}
        void print() const { 
            cout << "Array is : " ;
            for(auto it = arr.begin(); it != arr.end(); ++it)
                cout << *it << " "; 
            cout <<endl;
        }

        int checkRange(int i) { return (i < (size)? i : -1);}
        int parent(int i) {return checkRange((i-1)>>1);}
        int left(int i) { return checkRange((i<<1)+1);}
        int right(int i) { return checkRange((i+1)<<1);}

        void swap(int i, int j) { int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp; }
        void heapify(int node);
        void siftDown(int node);
        void sort();
};

void Heap::heapify(int node)
{
    if(node < 0) return;
    int l = left(node);
    int r = right(node);

    heapify(l);
    heapify(r);
    siftDown(node);
}

void Heap::siftDown(int node)
{
    if(node < 0) return;
    int l = left(node);
    int r = right(node);


    int larger = node;
    if(l>0 and arr[node] < arr[l])
        larger = l;
    if(r>0 and arr[larger] < arr[r])
        larger = r;

    if(larger != node)
    {
        swap(node, larger);
        siftDown(larger);
    }
}

void Heap::sort()
{
    heapify(0);

    cout<<"after heapifiation \n";
    print();
    while(size)
    {
        swap(0,--size);
        siftDown(0);
    }
}


int main()
{
    cout << "Enter numbers : \n";
    int input;
    cin >> input;
    Heap heap;
    while(cin.good())
    {
        heap.insert(input);
        cin >> input;
    }
    heap.print();
    heap.sort();
    heap.print();
}
