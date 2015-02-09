//
//  main.cpp
//  hw2_0346005
//
//  Created by Shawn on 2/9/2015.
//  Copyright (c) 2014 Shawn. All rights reserved.
//
//kruskal, heapsort and insertion sort
//final version

#include <iostream>
#include <cstdio>
#define edges 40
const int MaxRow = 40;
const int infinity = 100000;
//int a[MaxRow][MaxRow]; //the matrix we want to load
int sortBy;

using namespace std;

struct edge
{
    int i;//node
    int j;//node
    int cost;
    void setCost(int&,int&,int&);
    void operator=(const edge &e )
    {
        i = e.i;
        j = e.j;
        cost = e.cost;
    }
    bool operator<(const edge& e) //default for cost
    {
        if(sortBy==1)
            return i<e.i;
        else if(sortBy==2)
            return j<e.j;
        else
            return cost<e.cost;
    }
    bool operator>(const edge& e) //default for cost
    {
        if(sortBy==1)
            return i>e.i;
        else if(sortBy==2)
            return j>e.j;
        else
            return cost>e.cost;
    }
};

void edge::setCost(int& node1,int& node2,int& c)
{
    cost = c;
    i = node1;
    j = node2;
}
int upperBound(int i)
{
    int upper;
    if (i%2==0)upper = i/2;
    else upper = i/2+1;
    return upper;
}
void showEdgeCost(edge* const array,int const edge)
{
    for (int i =1; i<=edge; i++)
    {cout <<"\n("<<array[i].i<<","<<array[i].j<<","<<array[i].cost<<")";}
}

//giving array of edge and # of edges, return sorted edge array based on cost
void heapSort(edge* array, int edge)
{
    int upper; //# of leaf
    upper=upperBound(edge);
    
    //build the heap first
    //* _ _ _ _ _
    for (int i = edge; i > 0; i--) {
        array[i]=array[i-1];
    }
    
    //cout <<"\nheap sort initialize #  of edge "<<edge<<endl;
    
    //the first entry is not 0 yet
    //showEdgeCost(array, edge);
    for (int j = upper-1; j>0; j--) //loops only node that is not leaf
    {
        
        for (int k=j*2; k<=edge; k*=2)//bubble down, keep comparing kids then swaps until has no childs
        {
            if (k==edge&&edge%2==0) //special case only has one child
            {
                if (array[k/2]<array[k]) {
                    swap(array[k/2], array[k]);
                    break;
                }
                else break;
            }
            if (array[k]>array[k+1]) //left bigger than right
            {
                if (array[k/2]<array[k]) {
                    swap(array[k/2], array[k]);
                    //will go to left
                }
                else break;
            }
            else //right equal or bigger than left
            {
                if (array[k/2]<array[k+1]) {
                    swap(array[k/2], array[k+1]);
                    k= k+1;
                }
                else break;
            }
        }//inner for
    }//end for
    //cout <<"\nAfter building the max heap"<<endl;
    //showEdgeCost(array, edge);
    //start heap sort
    for (int i = edge; i > 1; i--) {
        swap(array[1], array[i]); //swap max at the first with the end enty
        int j= 1;//root of subtree
        //only fix the nodes that is not leaf
        while(j<=upperBound(i-1))//size of max heap will decrease by one node
        {
            if (j==upperBound(i-1))
            {
                if((i-1)%2==1)
                    break;//upperbound node has no child
                else //upperbound node only has one left child
                {
                    if(array[j]<array[2*j])
                    {
                        swap(array[j],array[2*j]);
                        //j= 2*j; //for consistency
                    }
                    break;
                }
            }
            //choose bigger of childs if parent < childs then swap
            else if (array[2*j]>array[2*j+1])//compare child choose big
            {
                if (array[j]<array[2*j])//parent less than child
                {
                    swap(array[j], array[2*j]);
                    j=2*j;
                }
                else break;//stop here
            }
            else
            {
                if (array[j]<array[2*j+1])//parent less than child
                {
                    swap(array[j], array[2*j+1]);
                    j=2*j+1;
                }
                else break;//stop here
            }
            
        }//end while
    }
    cout <<"\nAfter heap sort";
    showEdgeCost(array, edge);
    cout <<endl<<"after sorting...";
}


//set the cost of edge and return #of edges
int sortCost(struct edge* edge,int const count,int (&matrix)[MaxRow][MaxRow])
{
    //list of edges
    int k=0;
    for (int i=0; i<count; i++) {
        for (int j=0; j<count ; j++) {
            
            if (matrix[i][j]!=infinity && j>i) //rull out circle and same edge
            {
                edge[k++].setCost(i,j,matrix[i][j]);
                //cout << i<<" "<<j<<" "<<matrix[i][j];
                //cout <<endl;
            }
        }
    }
    return k;
    
}

//write strings to different rows of matrix
void writeMatrix(char* myString,int (&a)[MaxRow][MaxRow],int row)
{
    int j = 0;
    int i = 0;
    //5 x x -3 x x x x\r\n row =0
    while(myString[j]!='\r'&&myString[j]!='\0') {
        if(myString[j]== 'x')
        {
            a[row][i] = infinity;
            i++;
            j++;
        }
        else if(myString[j]==' ')
            j++;
        else //5 -3 16 ...
        {
            int k=0,number;
            char input[10];
            while(myString[j]!=' '&& myString[j]!='\r'&& myString[j]!='\0')
                input[k++]=myString[j++];
            input[k]='\0';
            sscanf(input, "%d",&number);
            a[row][i]= number;i++;
            
        }
    }//end while
}


//if cannot union mean a new tree is formed
//if we can union then the node in the input edges must overlapped
//after union 2 tree become 1 and the root of one tree must change
//no matter which it is ok


//how to know if there is a cycle

//two new node in the different tree must not form a cycle(the node must add in before)
//two new node in the same tree(have the same root when we union those) will have a cycle
//after we find out it will form a cycle we should delete the edge we want to add
//(the two node also should be added in before)

int collect[40]={};
void initialize()
{
    for (int i =0; i< 40; i++) {
        collect[i]= i;
    }
}
int Find(int x) {return x == collect[x] ? x : (collect[x] = Find(collect[x]));}

bool Union(int i, int j)
{
    if(collect[i]!=collect[j])//is not add before
    {
        collect[Find(i)]=collect[Find(j)];
        return 1;
    }
    return 0;
}

void kruskal(const edge *array,int const edge ,int const nodes,struct edge *MST)
{
    //this array is X -3 -1 0  1  1  2 3 3 biggest
    //              0 1  2  3  4  5  6 7 8 edge
    int EdgeInSet=0; //edges in the spanning tree
    int usedEdge = 1; //heap sort array start from 1 less than edge list
    initialize();
    cout <<"after kruskal\n";
    cout <<"number of nodes"<<nodes<<endl;
    //int cost = 0;
    int mst =0;
    while (EdgeInSet < nodes-1 && usedEdge < edge) //set's edge less than nodes -1 && edge no empty
    {
        
        if (Find(array[usedEdge].i)==Find(array[usedEdge].j))//formed sircle, discard
        {
            usedEdge++;
            continue;
        }
        bool success= 0;
        success = Union(array[usedEdge].i,array[usedEdge].j);
        EdgeInSet+=success;
        if (success == 1) {
            cout<<"("<<array[usedEdge].i<<","<<array[usedEdge].j<<","<<array[usedEdge].cost<<")"<<endl;
            MST[mst++] = array[usedEdge];
        }
        usedEdge++; //every time we union the edge in the edge list -1
    }//end while
    if (edge==0 || EdgeInSet!= nodes-1) {
        cout <<" no spanning tree.\n";
    }
    cout <<"the number of used edge is "<<EdgeInSet<<endl;
}

int mstCost(struct edge *MST,int const edge)
{
    int cost = 0;
    for (int i =0; i < edge; ++i) {
        cost += MST[i].cost;
    }
    return cost;
}

void showMatrix(int const count, int const (&a)[MaxRow][MaxRow])
{
    for (int i =0; i<count; i++) {
        for(int j=0;j<count;j++)
            cout<<a[i][j]<<" ";
        cout<<endl;
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    FILE* file;
    char myString[100];
    char File[20];
    cout << "input FIle name "<<endl;
    cin >>File;
    file = fopen(File, "r");
    if (file == NULL) {
        perror("Error opening the file");
    }
    else
    {
        int a[MaxRow][MaxRow]; //the matrix we want to load
        int count = 0;//# of rows and #of nodes

        while (!feof(file))
        {
            fgets(myString, 100, file);
            fputs(myString, stdout);
            writeMatrix(myString, a, count);
            count++;
        }//end while
        cout <<"\n"<<count<<endl;
        
        fclose(file);
        showMatrix(count, a);
        
        struct edge edge[edges];
        int totalEdge;
        int totalCost = 0;
        totalEdge = sortCost(edge,count, a);
        cout << "total edge is "<<totalEdge;
        heapSort(edge,totalEdge);
        cout <<endl<<"for kruskal\n";
        cout <<"the # of edge is "<<totalEdge<<" the # of node is "<<count<<endl;
        struct edge MST[edges];
        kruskal(edge, totalEdge, count, MST);
        totalCost = mstCost(MST,count-1);
        cout <<"Total Cost:"<<totalCost;
        sortBy=1;//used for heap sort
        heapSort(MST, count-1);
        
    }//end else
    return 0;
}


/*
 
 void insertionSort(edge *array,int edge ) //need array start from 0
 {
 int i=0;
 struct edge sorted[edges];
 sorted[i]=array[0];
 cout <<endl;
 //cout <<sorted[0].i<<" "<<sorted[0].j<<" "<<sorted[0].cost<<"for prove";
 for (int i =1; i < edge; i++) {
 for(int j =i-1;j >= 0;j--)
 {
 if(array[i].cost<sorted[j].cost)
 {
 sorted[j+1]=sorted[j];
 if(j==0)
 sorted[0]=array[i];
 
 }
 else
 {
 sorted[j+1] = array[i];
 break; //tricky one~ no need to compare now so break the loop
 }
 }
 
 }
 cout <<endl;
 for (int i =0; i<edge; i++)
 {cout <<sorted[i].i<<" "<<sorted[i].j<<" "<<sorted[i].cost<<endl;}
 
 }
 */
