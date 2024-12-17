#include <iostream>
#include <climits>
#include <limits>
#include <stack>
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

int main() {
    int order;
    cout << "Enter no. of vertices: ";
    order = getOnlyInteger();
    if(order==0) {
        cout<<"Graph is empty! "<<endl;
        return 0;
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
    
    //taking input of all vertex values
    string mapping[order];
    for(int i=0;i<order;i++) {
        cout<<"Enter value of vertex "<<i+1<<": ";
        cin>>mapping[i];
    } //value input taken

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
        return 0;
    }
}

    int operation;
    while(1) {
    cout<<"Enter the operation: 1- Find Shortest Path, 2- Show graph, 0- Exit: ";
    operation = getOnlyInteger();
    if(operation==0) {
        return 0;
    }

   else if(operation==1)  {
    string source, desti;
    cout<<"Enter start and end: ";
    cin>>source>>desti;

    int start=-1, end=-1;

        for(int i=0;i<order;i++) {
                if(mapping[i]==source) start = i;
                if(mapping[i]==desti)   end = i;
        }
        while(1) {
        if(start==-1 || end==-1) {
        cout<<"Enter valid start and end: ";
        cin>>source>>desti;
        }
        else {
            break;
        }
    }
    
    int nodes[order];         //distance
    bool visited[order];      //visited or not
    int predecessor[order];   //predecessor
    

    for (int i = 0; i < order; i++) {
        nodes[i] = INT_MAX;    //distances infinity initially
        visited[i] = false;    //all nodes unvisited
        predecessor[i] = -1;   //no predecessor at starting
    }
    
    nodes[start] = 0;  


    for (int count = 0; count < order; count++) {
        int minDistance = INT_MAX;
        int currentNode = -1;

        for (int i = 0; i < order; i++) {
            if (!visited[i] && nodes[i] < minDistance) {
                minDistance = nodes[i];
                currentNode = i;
            }
        }

        if (currentNode == -1) break;

        visited[currentNode] = true;

        for (int i = 0; i < order; i++) {
            if (graph[currentNode][i] != 0 && !visited[i]) {  
                int newDistance = nodes[currentNode] + graph[currentNode][i];

                if (newDistance < nodes[i]) {
                    nodes[i] = newDistance;
                    predecessor[i] = currentNode;  
                }
            }
        }
    }

    cout << "Shortest path from node "<< mapping[start] <<" to node "<< mapping[end] <<" is:"<< endl;

    if (nodes[end] == INT_MAX) {
        cout << "No path found." << endl;
    } else {
        stack<int> path;
        int currentNode = end;

        while (currentNode != -1) {
            path.push(currentNode);
            currentNode = predecessor[currentNode];
        }

        cout << "Path: ";
        while (!path.empty()) {
            cout << mapping[path.top()] << " ";
            path.pop();
        }
        cout<<endl<< "Minimum distance: " << nodes[end] << endl;
      }
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
    return 0;
}