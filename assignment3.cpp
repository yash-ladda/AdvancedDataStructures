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


Node* searchNode(Node* root, int value) {
    if(root==nullptr) return nullptr;
    Node* temp = root;
    while(temp!=nullptr) {
    if(temp->data > value) {
        temp = temp->left;
    }
    else if(temp->data < value) {
        temp = temp->right;
    }
    else {
        return temp;
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

void addNode(Node* &root, int value) {
    Node *newNode = new Node(value);
    if(searchNode(root, newNode->data)!=nullptr) {
        cout<<"Node is already present, enter unique value.";
        return;
    }
    if(root==nullptr) {
        root=newNode;
        return;
    }
    Node *parent = nullptr;
    Node *current = root;
    while(current!=nullptr) {
        if(current->data > value) {
            parent = current;
            current = current->left;
        }
        else if(current->data < value) {
            parent = current;
            current = current->right;
        }
    }
    if(parent->data > value) {
        parent->left = newNode;
        return;
    }
    else if(parent->data < value) {
        parent->right = newNode;
        return;
    }
}

Node* findParent(Node* root, int value) {
    if(root==nullptr) return nullptr;
    Node *current = root;
    Node * parent = nullptr;

    while(current!=nullptr) {
        parent = current;
        if(current->data==value) return parent;
        else if(current->data < value) {
            current = current->right;
        }
        else if(current->data > value) {
            current = current->left;
        } 
    }
    return nullptr;
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
        else if(current->left==nullptr && current->right==nullptr && findParent(root, current->data)==nullptr) {
            cout<<current->data<<" ";
            return;
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
        cout<<current->data<<" ";

        if(current->right) s.push(current->right);
        if(current->left) s.push(current->left);
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


void deleteNode(Node* &root, int value) {
    if(root==nullptr) {
        cout<<"Tree is empty, cannot delete! "<<endl;
        return;
    }
    Node *nodeToDelete = searchNode(root, value);
    Node *parent = findParent(root, value);

    //handling leaf node
    if(nodeToDelete->left==nullptr && nodeToDelete->right==nullptr) {
            if(parent->left && parent->left->data == value) {
                parent->left = nullptr;
                delete nodeToDelete;
                return;
            }
            else if(parent->right && parent->right->data == value) {
                parent->right = nullptr;
                delete nodeToDelete;
                return;
            }
    }

    //handling node with 1 child
    else if((nodeToDelete->left && nodeToDelete->right==nullptr) || (nodeToDelete->left==nullptr && nodeToDelete->right)) {
    if(nodeToDelete->left) {
        if(parent->left  && parent->left->data==nodeToDelete->data) {
            parent->left = nodeToDelete->left;
            nodeToDelete->left = nullptr;
            delete nodeToDelete;
            return;
        }
        else if(parent->right && parent->right->data==nodeToDelete->data) {
            parent->right = nodeToDelete->left;
            nodeToDelete->left = nullptr;
            delete nodeToDelete;
            return;
        }
        }
    else if(nodeToDelete->right){
        if(parent->left && parent->left->data==nodeToDelete->data) {
            parent->left = nodeToDelete->right;
            nodeToDelete->right = nullptr;
            delete nodeToDelete;
            return;
        }
        else if(parent->right && parent->right->data==nodeToDelete->data) {
            parent->right = nodeToDelete->right;
            nodeToDelete->right = nullptr;
            delete nodeToDelete;
            return;
        }
    }
    }

    //handling node with 2 child
    Node* temp = nodeToDelete->right;
    Node* tp = temp;
    while(temp->left!=nullptr) {
        tp = temp;
        temp = temp->left;
    }

    //condi 1
    if(nodeToDelete->right == temp ) {
        nodeToDelete->data = temp->data;
        nodeToDelete->right = temp->right;
        temp->right = nullptr;
        delete temp;
        return;
    }
  
    //condi 2
    else {
        nodeToDelete->data = temp->data;
        tp->left = temp->right;
        temp->right = nullptr;
        delete temp;
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
                cout << "How many nodes to be deleted ? ";
                noOfValues2 = getOnlyInteger();
                for (int i = 0; i < noOfValues2; i++) {
                    cout << "Enter value to be deleted: ";
                    value2 = getOnlyInteger();
                    deleteNode(root, value2);
                }
                break;
            }
            default:
                cout<<"Invalid operation, Try again."<<endl;
        }
    }
    return 0;
}