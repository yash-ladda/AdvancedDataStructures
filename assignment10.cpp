#include <iostream>
#include <stack>
#include <queue>
#include <limits>
using namespace std;


void addKey(int arr[], int data, int mod) {
        int index = data%mod;
        for(int i=0;i<mod;i++) {
            if(arr[i]==data) {
                cout<<"Element present"<<endl;
                return;
            }
        }
        
        for(int i=index;i<mod;i++) {          
            if(arr[i]==-1) {
                arr[i] = data;
                return;
            }
        }
        cout<<"Hash table is full! "<<endl;
}


void deleteKey(int arr[], int data, int mod) {
    int index = data%mod;
    for(int i=index;i<mod;i++) {
        if(arr[i]==data) {
            arr[i] = -1;
            return;
        }
    }
    cout<<"Data not found! "<<endl;
}

void getData(int arr[], int data, int mod) {
          int index = data%mod;
          for(int i=index;i<mod;i++) {
            if(arr[i]==data) {
                   cout<<data<<" is present at index "<<i<<endl;
                   return;
            }
}
cout<<"Data is not present! "<<endl;
}

void print(int arr[], int mod) {
    for(int i=0;i<mod;i++) {
        if(arr[i]!=-1) {
            cout<<arr[i]<<" ";
        }
    }
    cout<<endl;
}

int getOnlyInteger() {
    int x;
    while(1) {
        cin>>x;
        if(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please give integer. ";
        }
        else return x;
    }
}

int main() {
    int mod;
    cout<<"Enter the mod value: ";
    mod = getOnlyInteger();

    int arr[mod];
    for(int i=0;i<mod;i++) {
        arr[i]=-1;
    }

while(true) {
    int operation;
    cout<<"Enter the operation: 1- Add, 2- Delete, 3- Search, 4- Print, 0- Exit: ";
    operation = getOnlyInteger();

    if(operation==0) break;

    switch (operation) {
            case 1: {
                int data;
                cout<<"Enter the data: ";
                data = getOnlyInteger();
                addKey(arr, data, mod);
                break;
            }
            case 2: {
                int data;
                cout<<"Enter the data to be deleted: ";
                data = getOnlyInteger();
                deleteKey(arr, data, mod);
                break;
            }
            case 3: {
                int data;
                cout<<"Enter the data to search: ";
                data = getOnlyInteger();
                getData(arr, data, mod);
                break;
            }
            case 4: {
                print(arr, mod);
                break;
            }
            default:
                cout<<"Invalid operation. Try again."<<endl;
        }
}
}