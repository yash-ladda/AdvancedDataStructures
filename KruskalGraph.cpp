#include <iostream>
#include <limits.h>
#include <algorithm>
using namespace std;

int getOnlyInteger() {
    int x;
    while(1) {
        cin>>x;
        if(cin.fail() || x<0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please give positive integer. ";
        }
        else return x;
    }
}

int findRoot(int parent[], int i) {
    if (parent[i] == i) {
        return i;
    }
    return parent[i] = findRoot(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int x, int y) {
    int rootX = findRoot(parent, x);
    int rootY = findRoot(parent, y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

bool isCycle(int parent[], int rank[], int v1, int v2) {
    int rootV1 = findRoot(parent, v1);
    int rootV2 = findRoot(parent, v2);

    if (rootV1 == rootV2) {
        return true;
    }

    unionSets(parent, rank, v1, v2);
    return false;
}

void KruskalMST() {
    int order;
    cout << "Enter no. of vertices: ";
    order = getOnlyInteger();

    if(order==0) {
        cout<<"Graph is empty, no need to find mst."<<endl;
        return;
    }

    int** graph = new int*[order];
    for (int i = 0; i < order; i++) {
        graph[i] = new int[order]();
    }

    for(int i=0;i<order;i++) {
        for(int j=0;j<order;j++) {
            graph[i][j]=0;
        }
    }

    string mapping[order];
    for(int i=0;i<order;i++) {
        cout<<"Enter value of vertex "<<i+1<<": ";
        cin>>mapping[i];
    }

    for (int i = 0; i < order; i++) {
    for (int j = i + 1; j < order; j++) {
        int temp;
        cout << "Enter weight of edge " << mapping[i] << ", " << mapping[j] << ": ";
        temp = getOnlyInteger();
        graph[i][j] = temp;
        graph[j][i] = temp;
    }

    int zeros = 0;
    for (int k = 0; k < order; k++) {
        if (graph[i][k] == 0) zeros++;
    }

    if (zeros == order) {
        cout << "Graph not connected. Node " << mapping[i] << " has no edges." << endl;
        return;
    }
}

int operation;
    while(1) {
    cout<<"Enter the operation: 1- Find Shortest Path, 2- Show graph, 0- Exit: ";
    operation = getOnlyInteger();
    if(operation==0) {
        return;
    }

   else if(operation==1)  {

    int edges[order * 2] = {0}; 
    bool isVisited[order][order] = {false}; 
    int minDist = 0; 
    int n = 0;

    int parent[order], rank[order];
    for (int i = 0; i < order; i++) {
        parent[i] = i; 
        rank[i] = 0; 
    }

    while (n < order - 1) { 
        int vertex1 = -1, vertex2 = -1;
        int small = INT_MAX;

        for (int i = 0; i < order; i++) {
            for (int j = i + 1; j < order; j++) {
                if (graph[i][j] < small && !isVisited[i][j] && graph[i][j] != 0) {
                    small = graph[i][j];
                    vertex1 = i;
                    vertex2 = j;
                }
            }
        }

        isVisited[vertex1][vertex2] = true;
        isVisited[vertex2][vertex1] = true;

        if (isCycle(parent, rank, vertex1, vertex2)==false) {
            edges[n * 2] = vertex1;
            edges[n * 2 + 1] = vertex2;
            minDist += small;
            n++;
        }
    }

    cout << "Minimum spanning tree: ";
    for (int i = 0; i < n * 2; i++) {
        if (i % 2 == 0) {
            cout << mapping[edges[i]] << " - ";
        } else {
            cout << mapping[edges[i]] << ", ";
        }
    }

    cout << endl << "Minimum cost of the spanning tree is: " << minDist << endl;
}

else if(operation==2) {
     for(int i=0;i<order;i++) {
        for(int j=0;j<order;j++) {
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
}

else cout<<"Enter valid operation! "<<endl;

}
}
int main() {
    KruskalMST();
    return 0;
}