//
//  main.cpp
//  binomial_heap
//
//  Created by Shawn on 1/2/15.
//  Copyright (c) 2015 Shawn. All rights reserved.
// for ta
#include <iostream>
#include <queue>
#include <stdio.h>
#include <stack>
#include <fstream>
#include <sstream>


using namespace std;

class Node{
public:
    Node* child;
    Node* sibling;
    Node* parent;
    int value;
    int degree;
    Node(int key){
        value = key;
        degree = 0;
        child = nullptr;
        parent = nullptr;
        sibling = nullptr;
    }
    Node()/*implement by yourself.*/
    {
        value = 0;
    }
};
class BinomialHeap
{
private:
    Node *head;
public:
    Node* insert(Node*,int);
    Node* deleteMin(Node*);
    Node* reverseList(Node*);
    void bLink(Node*,Node*);
    int getMin(Node*);
    int size(Node*);
    Node* bHeapUnion(Node*,Node*);
    Node* binomialMerge(Node*,Node*);
    void print(bool mode,Node*);//preoder or BFS
    BinomialHeap()
    {
        head = nullptr;
    }
    
    Node * createHeap()
    {
        BinomialHeap h;
        return h.head;
    }
    
    Node * gethead()
    {
        return head;
    }
    ~BinomialHeap();
};


BinomialHeap::~BinomialHeap()
{
    //cout <<"\ndelete nodes \n";
    
    if (head ==nullptr) {
        return;
    }
    stack<Node*> s1;
    s1.push(head);
    
    while (!s1.empty())
    {
        Node* front = s1.top();
        
        //cout <<front->value<<" ";
        s1.pop();
        
        if (front->sibling!=NULL) {
            s1.push(front->sibling);
        }
        
        if(front->child!=NULL)
        {
            s1.push(front->child);
        }
        delete front;
        
    }
    
    //cout <<"\ndelete nodes has do something \n";
    
}

int BinomialHeap::size(Node*head) //using DFS
{
    int count =0;
    
    stack<Node*> s1;
    s1.push(head);
    while (!s1.empty())
    {
        Node* front = s1.top();
        count++;
        s1.pop();
        if (front->sibling!=NULL) {
            {
                s1.push(front->sibling);
            }
        }
        if(front->child!=NULL)
        {
            s1.push(front->child);
        }
    }
    return count;
}


Node* BinomialHeap::deleteMin(Node*head)
{
    if (head == nullptr) {
        cout << "nothing to delete"<<endl;
        return nullptr;
    }
    Node* iter;
    Node* minptr = nullptr;
    Node* y = nullptr;//the one before minptr
    minptr = head;
    iter = head;
    while (iter->sibling!=nullptr) {
        if (iter->sibling->value < minptr->value) {
            y = iter;
            minptr = iter->sibling;
        }
        iter = iter->sibling;
    }
    //if(y!=NULL)
    //cout <<y->value<<"is before mini";
    if (y ==nullptr) {
        head = minptr->sibling; //head is minptr
    }
    else //min at middle of heaps
        y->sibling = minptr->sibling; //connect the two list
    //cout <<"print want combined\n";
    //if (head!=NULL)
    //this->print(1,head);
    
    BinomialHeap* reverse = new BinomialHeap();
    if (minptr->child!=nullptr) {
        reverse->head = reverseList(minptr->child);
        minptr->child->sibling = nullptr;
    }
    //cout <<"print reverse\n";
    //reverse.print(1,reverse.head);
    head = bHeapUnion(reverse->head, head);
    delete minptr;
    return head;
    
}

int BinomialHeap::getMin(Node*head)
{
    int min = head->value;
    Node* x;
    //Node* y = NULL;
    x =  head;
    while (x!=NULL) {
        if (x->value < min) {
            min = x->value;
            //            y = x;
        }
        x = x->sibling;
    }
    return min;
}


Node* BinomialHeap::reverseList(Node*head)
{
    Node* current = head;
    Node* previous = NULL;
    while (current) {
        Node* r = previous;
        previous = current;
        current = current->sibling;
        previous->sibling = r;
    }
    head = previous;
    return head;
}

void BFS(Node*head)
{
    
    queue<Node*> q1;
    q1.push(head);
    
    cout <<"BFS\n";
    while (!q1.empty())
    {
        Node* temp =nullptr;
        temp = q1.back()->sibling;
        Node* left = q1.front()->child;
        cout <<q1.front()->value<<" ";
        while (temp!=NULL) {
            {
                q1.push(temp);
                temp = temp->sibling;
            }
        }
        q1.pop();
        
        if(left!=NULL)
        {
            q1.push(left);
        }
        
    }
}

void DFS(Node*head)
{
    stack<Node*> s1;
    s1.push(head);
    
    cout <<"\nDFS \n";
    while (!s1.empty())
    {
        Node* front = s1.top();
        cout <<front->value<<" ";
        s1.pop();
        
        if (front->sibling!=NULL) {
            s1.push(front->sibling);
        }
        
        if(front->child!=NULL)
        {
            s1.push(front->child);
        }
    }
    cout <<endl;
}


void BinomialHeap::print(bool mode,Node*head)
{
    if (head == NULL) {
        cout <<"this heap is empty";
        return;
    }
    if (mode==1) //BFS
    {
        BFS(head);
    }
    else if (mode==0) {
        DFS(head);
    }
    
}

//input heap's head
Node* BinomialHeap::insert(Node*H,int value)
{
    Node* heap = createHeap();
    Node* node = new Node(value);
    heap = node;
    H = bHeapUnion(H, heap);
    return H;
}

void BinomialHeap::bLink(Node*y, Node*z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree+1;
}

Node* BinomialHeap::binomialMerge(Node*h1,Node*h2)
{
    Node * sortedH = createHeap();
    if (h1!= NULL) {
        if (h2!=NULL) {
            //choose run on which list
            if (h1->degree < h2->degree) {
                sortedH = h1;
            }
            else
            {
                sortedH = h2;
                h2 = h1;
                h1 = sortedH;
            }
        }
        else//iterh2 == null
            return h1;
    }
    else//iterh1 == null
        return h2;
    //use iterator, we add the smaller to the sorted
    while (h1->sibling!=NULL&&h2!=NULL ) {
        //sortedH is still at h1
        if(h1->sibling->degree > h2->degree)
        {
            Node *temp = h1->sibling;
            h1->sibling = h2;
            h2 = temp;
            
        }//sortedH is still at h1
        else //iterh2->degree < iterh1->degree
        {
            h1 = h1->sibling;
        }
    }//end while
    if (h1->sibling == NULL) {
        h1->sibling =h2;
    }
    
    
    return sortedH;
}

Node* BinomialHeap::bHeapUnion(Node*h1,Node*h2) //return a new Unionheap
{
    Node* H = createHeap();
    H = binomialMerge(h1, h2);
    //cout <<"after merge";
    //print(1,H);
    //print(0,H);
    if (H==NULL) {
        return H;
    }
    Node* prev_x;
    Node* x;
    Node* next_x;
    prev_x =  NULL;
    x = H;
    next_x = x->sibling;
    while (next_x!=NULL) {
        if ((x->degree!=next_x->degree)||(next_x->sibling!=NULL&&next_x->sibling->degree==x->degree)) {
            prev_x = x; //case 1 and 2
            x = next_x; //case 1 and 2
        }
        else
        {
            if(x->value<=next_x->value)//case 3
            {
                x->sibling = next_x->sibling;
                bLink(next_x, x);
            }
            else  //case 4
            {
                if(prev_x==NULL) //when H == x
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                bLink(x, next_x);
                x = next_x;
            }
            
        }
        next_x = x->sibling; //for every case
    }//end while
    //cout <<"after Union";
    //print(1,H);
    //print(0,H);
    //cout <<endl;
    
    //cout <<"head is "<<H->value;
    return H;   //need to deallocate it
}


//read integers to heap array
void readFile(ifstream& input, int &nodes, int* heap)
{
    
    // The getline function will read characters until a newline character is seen.
    string line;
    getline(input, line);
    cout << line << endl;
    nodes = stoi(line); //only one integer
    string line2;
    getline(input, line2);
    istringstream buffer(line2);
    for (int i =0; i < nodes; i++) { //need to read array of integers check binomialheap4 to see
        //different ways
        int value;
        buffer >> value >>ws;
        heap[i] = value;
        printf("%d ",heap[i]);
    }
    cout <<endl;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    ifstream input;
    char File[300];
    cout << "input FIle name "<<endl;
    cin >>File;
    input.open(File);
        // Read the file line by line
        int heap_1[300];
        int heap_2[300];
        int nodes1 = 0;
        int nodes2 = 0;
    
        readFile(input,nodes1,heap_1);
        readFile(input,nodes2,heap_2);
    
        BinomialHeap h1;
        BinomialHeap h2;
        Node* head1 = h1.gethead();
        Node* head2 = h2.gethead();
        
        for (int i =0; i<nodes1; i++) {
            head1 = h1.insert(head1,heap_1[i]);  //h1 is the original tree
            
        }
        cout <<"------h1------\n";
        h1.print(0,head1);
        h1.print(1,head1);
        
        for (int i =0; i<nodes2; i++) {
            head2 = h2.insert(head2,heap_2[i]);
            
        }
        cout <<"\n------h2------\n";
        h2.print(0,head2);
        h2.print(1,head2);
        
        BinomialHeap* h3 = new BinomialHeap();
        
        Node* head3 = h3->gethead();
        head3 = h3->bHeapUnion(head1, head2);
        cout <<"\n------Union------\n";
        h3->print(0,head3);
        h3->print(1,head3);
        cout <<"\n-------Delete min = ";
        cout <<h3->getMin(head3)<<"-------\n";
        head3 = h3->deleteMin(head3);
        h3->print(0, head3);
        h3->print(1, head3);
        
        
        cout <<"\n-------Delete min = ";
        cout <<h3->getMin(head3)<<"-------\n";
        head3 = h3->deleteMin(head3);
        h3->print(0, head3);
        h3->print(1, head3);
        
        cout <<"\nBinomialheap mean "<<h3->getMin(head3)<<"\n";
        cout <<"Binomialheap size "<<h3->size(head3)<<"\n";
    
        /*
        cout <<"\n-------Delete min = ";
        cout <<h3->getMin(head3)<<"-------\n";
        head3 = h3->deleteMin(head3);
        h3->print(0, head3);
        h3->print(1, head3);
        delete h3;
         */
    // Close our stream and reset the fact that it has failed.
    input.close();
    input.clear();

    
    return 0;
}


