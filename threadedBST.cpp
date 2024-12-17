#include <iostream>
#include <limits>
using namespace std;

class Node {
    public:
    int data;
    Node* left;
    Node* right;
    bool isThreaded;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
        isThreaded = false;
    }
};


Node* searchNode(Node* root, int value) {
    if(root==nullptr) {
        return nullptr;
    }

    Node* current = root;
    while(current->left!=nullptr) {
        current = current->left;
    }

    while(current!=nullptr) {
        if(current->data = value) {
            return current;
        }
        else if(current->isThreaded) {
            current = current->right;
        }
        else {
            current = current->right;
            while(current!=nullptr && current->left!=nullptr) {
                current = current->left;
            }
        }
    }
    return nullptr;
}


void searchThis(Node* root, int value) {
    if(searchNode(root, value)) {
        cout<<"Node is present."<<endl;
        return;
    }
    else cout<<"Node is not present."<<endl;
}


void addNode(Node* root, int value) {
    if(searchNode(root, value)) {
        cout<<"Node is already present! "<<endl;
        return;
    }
    
    Node* newNode = new Node(value);

    if(root==nullptr) {
        root = newNode;
        return;
    }
    
    Node* current = root;
    Node* parent = nullptr;

    while(current!=nullptr) {
        parent = current;
        if(current==nullptr || current->isThreaded) break;
        if(current->data == value) return;
        else if(current->data < value) {
            current = current->right;
        }
        else current = current->left;
    }   //parent found here
 
 //want to add newnode at left of parent
    if(value < parent->data) {
        parent->left = newNode;
        newNode->right = parent;
        newNode->isThreaded = true;
    }   //added to left


 //want to add newnode at right of parent
    else {
        if(value > parent->data || parent->isThreaded) {
          newNode->right = parent->right;
          newNode->isThreaded = true;
          parent->isThreaded = false;
        }
        parent->right = newNode;
    }   //added to right
}


void inOrder(Node* root) {
    if(root==nullptr) {
        cout<<"Tree is empty, cannot print! ";
        return;
    }

    Node* current = root;
    while(current->left!=nullptr) {
        current = current->left;
    }

    while(current!=nullptr) {
        cout<<current->data<<" ";

        if(current->isThreaded) {
            current = current->right;
        }

        else {
            current = current->right;
            while(current!=nullptr && current->left!=nullptr) {
                current = current->left;
            }
        }
    }
}


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
    int x;
    cout<<"Enter data of root: ";
    x = getOnlyInteger();
    Node *root = new Node(x);

    while (true) {
        cout <<endl<<"Enter the operation: 1- Search, 2- Add, 3- inOrder, 0- Exit." <<endl;
        int operation;
        operation = getOnlyInteger();

        if (operation == 0) {
            break;
        }

        switch (operation) {
            case 1: {
                int value;
                cout<<"Enter data to search: ";
                value = getOnlyInteger();
                searchThis(root, value);
                break;
            }
            case 2: {
                int noOfValues1, value1;
                cout<<"How many nodes to be added ? ";
                noOfValues1 = getOnlyInteger();
                for (int i = 0; i < noOfValues1; i++) {
                    cout <<endl<<"Enter value to be added: ";
                    value1 = getOnlyInteger();
                    addNode(root, value1);
                }
                break;
            }
            case 3: {
                inOrder(root);
                break;
            }
            default:
                cout<<"Invalid operation, Try again."<<endl;
        }
    }
    return 0;
}