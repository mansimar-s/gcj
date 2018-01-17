#include <iostream>
using namespace std;

class LinkedList
{
    private:
        struct Node
        {
            int data;
            Node* next;
            Node* prev;

            Node(int i) : data(i),next(NULL),prev(NULL) {}
        };

        Node* start;
        Node* end;

        LinkedList(const LinkedList&);
        LinkedList& operator = (const LinkedList&);

    public:
        LinkedList();
        ~LinkedList();

        LinkedList& operator << (int item);

        void print() const;
        void reverse();
        void merge(LinkedList& list2);
};

LinkedList::LinkedList() : start(NULL) {}

LinkedList::~LinkedList()
{
    Node* ptr = start;
    while(ptr) {
        Node* next = ptr->next;
        delete ptr;
        ptr = next;
    }
    start = NULL;
}

void LinkedList::print() const
{
    cout << "List is : " ;
    Node* ptr = start;
    while(ptr) {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}

LinkedList& LinkedList::operator << (int item)
{
    Node* n = new Node(item);
    //don't use doubly
    if(!start) start = n;
    else
    {
        Node* ptr = start;
        while(ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = n;
        //n->next = NULL; already take care of by Node's constructor
    }
}

void LinkedList::reverse()
{
    if(!start) return; // empty list

    Node* prev = NULL;
    Node* curr = start;
    Node* next = start->next;

    //if(!next) return; //Single element list

    while(next)
    {
        curr->next = prev;
        prev = curr;
        curr = next;
        next = next->next;
    }
    curr->next = prev;
    start = curr;
}

void LinkedList::merge(LinkedList& l2)
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


int main()
{
    LinkedList myList;
    int input = 0;
    cin >> input;
    while(!cin.eof())
    {
        myList << input;
        cin >> input;
    }

    myList.print();
    myList.reverse();
    cout << "After reverse\n";
    myList.print();
    cout <<"Enter second list ";
    LinkedList l2;
    cin.clear();
    cin >> input;
    while(!cin.eof())
    {
        l2 << input;
        cin >> input;
    }
    l2.print();
    cout << "Merging : \n";
    myList.reverse();
    myList.merge(l2);
    myList.print();
    l2.print();



}
