#include <iostream>
#include<limits>
using namespace std ;

class heap {
    public:
    int size;
    int *arr;
    int totalsize;

    heap(int n) {
        arr = new int[n+1];
        size = 0;
        totalsize = n;
    }

    void insert(int data) {
        if (size >= totalsize)
        {
            cout<<"Heap is full! "<<endl;
            return;
        }
        size++;
        arr[size] = data;
    }


    void heapify(int *arr, int n) {
        int index = n;
        while (index>1)
        {
            int parent = index/2;
            if (arr[parent] < arr[index]) {
                swap(arr[parent],arr[index]);
            }
            index--;
        } 
    }


    void heapsort() {
        if (size == 0)
        {
            cout<<"Heap is empty, cannot sort!"<<endl;
            return;
        }
        int *temp = new int[size+1];
        for (int i = 1; i <= size; i++)
        {
            temp[i] = arr[i];
        }
        int t = size;
        while (t>1)
        {
            heapify(temp, t);
            swap(temp[1],temp[t]);
            t--;
        }
        

        cout<<"Heap after sorting:";
        for (int i = 1; i <= size; i++)
        {
            cout<<temp[i]<<" ";
        }
        cout<<endl;
    }

    void deleteNode() {
        if (size == 0) {
            cout<<"Heap is empty! "<<endl;
            return;
        }
        arr[1] = arr[size];
        size--;
        heapify(arr, size);
    }

    void print() {
        if (size == 0) {
            cout << "Heap is empty! "<<endl;
            return;
        }
        for (int i = 1; i <= size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
} ;

int main() {
    int n;
    cout << "Enter the total size of the heap: ";

     while (!(cin >> n)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');  
            cout<<"Invalid input"<<endl;
            cout<<"Enter integer constants"<<endl;
     }
    if (n <= 0) {
        cout << "Heap size must be greater than 0"<<endl;
        return 0;
    }

    heap h1(n);
    int operation;

    while (operation != 5) {
        cout << "Enter the operation: 1-Insert, 2-Delete, 3-Print, 4-Heap sort, 5-Exit";
        cin >> operation;

        switch (operation) {
        case 1: {
            int data;
            cout << "Enter the value to insert: ";
            cin >> data;
            h1.insert(data);
            break;
        }
        case 2:{
            h1.deleteNode();
            cout << "Root deleted "<<endl;
            break;
        }
        case 3:{
            cout << "Heap: ";
            h1.print();
            break;
        }
        case 4:{
            h1.heapsort();
            break;
        }
        case 5:{
            cout << "Exit ";
            break;
        }
        default:
            cout << "Invalid operation, please try again.";
        }
    }
    return 0;
}