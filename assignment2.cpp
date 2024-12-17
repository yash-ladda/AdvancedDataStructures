#include <iostream>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

class Node {
    public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};


Node *searchNode(Node *root, int value) {
    if(root==nullptr) return nullptr;
    queue <Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node *temp = q.front();
        q.pop();
        if(temp->data==value) {
            return temp;
        }
        else {
        if(temp->left) q.push(temp->left);
        if(temp->right) q.push(temp->right);
    }
    }
    return nullptr;
}

void searchThis(Node* &root, int val){
    if(root==NULL){
        cout<<"Tree is empty"<<endl;
        return;
    }
    if(searchNode(root,val)!=NULL){
        cout<<"Node is Found"<<endl;
    }
    else{
        cout<<"Node Not found"<<endl;
    }
}


Node* findParent(Node* &root, int value) {
    if(root==nullptr) return nullptr;

    queue <Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if((temp->left && temp->left->data == value) || (temp->right && temp->right->data==value)) {
            return temp;
        }

        if(temp->left) q.push(temp->left);
        if(temp->right) q.push(temp->right);
    }
    return nullptr;
}


void addNode(Node *root, int value) {
    Node *newNode = new Node(value);
    if(root==nullptr) {
        root = newNode;
        return;
    }
    queue <Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node *temp = q.front();
        q.pop();
        if(temp->left==nullptr) {
            temp->left = newNode;
            return;
        }
        else if(temp->left) {
            q.push(temp->left);
        }

        if(temp->right==nullptr) {
            temp->right = newNode;
            return;
        }
        else if(temp->right) {
            q.push(temp->right);
        }
    }
}


void inOrder(Node *root) {
    if(root==nullptr) {
        cout<<"Tree is empty, cannot print! "<<endl;
        return;
    }

    stack <Node*> s;
    s.push(root);
    Node* lastVisited = nullptr;
    while(!s.empty()) {
        Node *current = s.top();
        s.pop();
        if(current->left && current->left!=lastVisited && current->right!=lastVisited) {
            s.push(current);
            s.push(current->left);
        }
        else if(current->right!=nullptr && current->right!=lastVisited) {
            cout<<current->data<<" ";
            s.push(current);
            s.push(current->right);
        } 
        else if(current->right!=lastVisited) {
            cout<<current->data<<" ";
        }
        lastVisited = current;
    }
}


void preOrder(Node* root) {
    if(root==nullptr) {
        cout<<"Tree is empty, cannot print! "<<endl;
        return;
    }
    Node *lastVisited = nullptr;
    stack <Node*> s;
    s.push(root);
    while(!s.empty()) {
        Node *current = s.top();
        s.pop();
        if(current->left && current->left!=lastVisited && current->right!=lastVisited) {
            cout<<current->data<<" ";
            s.push(current);
            s.push(current->left);
        }
        else if(current->right && current->right!=lastVisited) {
            s.push(current);
            s.push(current->right);
        }
        else if(current->right!=lastVisited) {
            cout<<current->data<<" ";
        }
        lastVisited = current;
    }
}


void postOrder(Node *root) {
    if(root==nullptr) {
        cout<<"Tree is empty, cannot print! "<<endl;
        return;
    }
    Node *lastVisited = nullptr;
    stack <Node*> s;
    s.push(root);
    while(!s.empty()) {
        Node *current = s.top();
        s.pop();
        if(current->left && current->left!=lastVisited && current->right!=lastVisited) {
            s.push(current);
            s.push(current->left);
        }
        else if(current->right && current->right!=lastVisited) {
            s.push(current);
            s.push(current->right);
        }
        else if(current->left!=lastVisited) {
            cout<<current->data<<" ";
        }
        else if(current->left==nullptr && current->right==nullptr && findParent(root, current->data)==nullptr) {
            cout<<current->data<<" ";
            return;
        }
        lastVisited = current;
    }
}


void breadthFirst(Node *root) {
    if(root==nullptr) {
        cout<<"Tree is empty, cannot print! "<<endl;
        return;
    }
    queue <Node*> q;
    q.push(root);
    while(!q.empty()) {
        Node *temp = q.front();
        q.pop();

    cout<<temp->data<<" ";
    if(temp->left) q.push(temp->left);
    if(temp->right) q.push(temp->right);
    }
}


Node* leafNode(Node* &root) {
    if(root==nullptr) return nullptr;
    queue <Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if(temp->left==nullptr && temp->right==nullptr) {
            return temp;
        }
else {

        if(temp->left) q.push(temp->left);
        if(temp->right) q.push(temp->right);
}    
    }
    return nullptr;
}


void deleteNode(Node* root, int value) {
    Node* nodeToDelete = searchNode(root, value);
    Node* parent = findParent(root, nodeToDelete->data);

    if(nodeToDelete->left==nullptr && nodeToDelete->right==nullptr) {
        if(parent->left && parent->left->data==nodeToDelete->data) {
            parent->left = nullptr;
            delete nodeToDelete;
            return;
        }
        else {
            parent->right = nullptr;
            delete nodeToDelete;
            return;
        }
    }
    
    Node* leaf = leafNode(nodeToDelete);
    Node* leafParent = findParent(root, leaf->data);

    int x = nodeToDelete->data;
    nodeToDelete->data = leaf->data;
    leaf->data = x;

    if(leafParent->left && leafParent->left->data==leaf->data) {
        leafParent->left = nullptr;
        delete leaf;
        return;
    }
    else{
        leafParent->right = nullptr;
        delete leaf;
        return;
    }
}

int getOnlyInteger() {
    int x;
    while(1) {
        cin>>x;
        if(cin.fail() || x<0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please give integer. ";
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
        cout <<endl<<"Enter the operation: 1- Search, 2- Add, 3- Breadth First, 4- inOrder, 5- preOrder, 6- postOrder, 7- delete, 0- Exit." <<endl;
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
                cout<<"How many nodes to be added? ";
                noOfValues1 = getOnlyInteger();
                for (int i = 0; i < noOfValues1; i++) {
                    cout <<endl<<"Enter value to be added: ";
                    value1 = getOnlyInteger();
                    addNode(root, value1);
                }
                break;
            }
            case 3: {
                breadthFirst(root);
                break;
            }
            case 4: {
                inOrder(root);
                break;
            }
            case 5: {
                preOrder(root);
                break;
            }
            case 6: {
                postOrder(root);
                break;
            }
            case 7: {
                int noOfValues2, value2;
                cout << "How many nodes to be deleted? ";
                noOfValues2 = getOnlyInteger();
                for (int i = 0; i < noOfValues2; i++) {
                    cout << "Enter value to be deleted: ";
                    value2 = getOnlyInteger();
                    deleteNode(root, value2);
                }
                break;
            }
            default:
                cout<<"Invalid operation. Try again."<<endl;
        }
    }
    return 0;
}