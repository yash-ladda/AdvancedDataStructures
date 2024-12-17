#include <iostream>
#include <queue>
#include <stack>
#include <limits>
using namespace std;

class Node {
    public:
    int data;
    Node* left;
    Node* mid;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        mid = nullptr;
        right = nullptr;
    }
};


Node* searchNode(Node* &root, int value) {
    if(root==nullptr) {
        return nullptr;
    }
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
        if(temp->mid) q.push(temp->mid);
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


void addNode(Node* &root, int value, int parentValue, int location) {
    Node *newNode = new Node(value);
    if(root==nullptr) {
        root = newNode;
        return;
    }
    Node *parent = searchNode(root, parentValue);
    if (parent == nullptr) {
        cout << "Parent not found!" << endl;
        delete newNode;
        return;
    }
    if(location==1) {
        parent->left = newNode;
        return;
        }
    else if(location==2) {
        parent->mid = newNode;
        return;
        }
    else if(location==3) {
        parent->right = newNode;
        return;
        }
    else cout<<"Enter valid location :)"<<endl;
}


void breadthFirst(Node* &root) {
    if(root==nullptr) {
        cout<<"Tree is empty, cannot print! "<<endl;
        return;
    }
    queue <Node*> q;
    q.push(root);
    while(!q.empty()) {
           Node* temp = q.front();
           q.pop();
           cout<<temp->data<<" ";
           if(temp->left) q.push(temp->left);
           if(temp->mid) q.push(temp->mid);
           if(temp->right) q.push(temp->right);
    }
}


void inOrder(Node* root) {
    if(root == nullptr) {
        cout<<"Tree is empty, cannot print! "<<endl;
        return;
    }

    if(root->left) {
        inOrder(root->left);
    }

    cout<<root->data<< " ";

    if(root->mid) {
        inOrder(root->mid); 
    }

    if(root->right) {
        inOrder(root->right);
    }
}

void preOrder(Node* root) {
    if(root==nullptr) {
        cout<<"Tree is empty, cannot print! ";
        return;
    }

    cout<<root->data<<" ";

    if(root->left) {
        preOrder(root->left);
    }

    if(root->mid) {
        preOrder(root->mid);
    }

    if(root->right) {
        preOrder(root->right);
    }
}

void postOrder(Node* root) {
    if(root == nullptr) {
        cout<<"Tree is empty, cannot print! ";
        return;
    }

    if(root->left) {
        postOrder(root->left);
    }

    if(root->mid) {
        postOrder(root->mid);
    }

    if(root->right) {
        postOrder(root->right);
    }

    cout<<root->data<<" ";
}

Node* leafNode(Node* &root) {
    if(root==nullptr) return nullptr;
    queue <Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if(temp->left==nullptr && temp->mid==nullptr && temp->right==nullptr) {
            return temp;
        }

        if(temp->left) q.push(temp->left);
        if(temp->mid) q.push(temp->mid);
        if(temp->right) q.push(temp->right);
    }
    return nullptr;
}


Node* findParent(Node* &root, int value) {
    if(root==nullptr) return nullptr;

    queue <Node*> q;
    q.push(root);

    while(!q.empty()) {
        Node* temp = q.front();
        q.pop();

        if((temp->left && temp->left->data == value) || (temp->mid && temp->mid->data==value) || (temp->right && temp->right->data==value)) {
            return temp;
        }

        if(temp->left) q.push(temp->left);
        if(temp->mid) q.push(temp->mid);
        if(temp->right) q.push(temp->right);
    }
    return nullptr;
}


void deleteNode(Node* &root, int value) {
    Node* nodeToDelete = searchNode(root, value);
    Node* nodeParent = findParent(root, nodeToDelete->data);
    Node* leaf = leafNode(nodeToDelete);
    Node* leafParent = findParent(root, leaf->data);

//handling leaf node
if(nodeToDelete->left==nullptr && nodeToDelete->mid==nullptr && nodeToDelete->right==nullptr) {
    if(nodeParent->left && nodeParent->left->data==value) {
        nodeParent->left = nullptr;
    }
    else if(nodeParent->mid && nodeParent->mid->data==value) {
        nodeParent->mid = nullptr;
    }
    else {
        nodeParent->right = nullptr;
    }
    delete nodeToDelete;
    return;
}

//handling root node or middle node
  
    //swapping variables of leaf node and node to delete
    int x = nodeToDelete->data;
    nodeToDelete->data = leaf ->data;
    leaf->data = x;

    Node* sNode = searchNode(root,leaf->data);
    Node* sParent = findParent(root,leaf->data);

    if(sParent->left && sParent->left->data==sNode->data){
        sParent->left= NULL;
        delete sNode;
        return;
    }
    else if(sParent->mid && sParent->mid->data==sNode->data){
        sParent->mid=NULL;
        delete sNode;
        return;
    }
    else{
        sParent->right = NULL;
        delete sNode;
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
    cout << "Enter data of root: ";
    x = getOnlyInteger();  

    Node *root = new Node(x);

    while (true) {
        cout<<endl<<"Enter the operation: 1- Search, 2- Add, 3- Breadth First, 4- inOrder, 5- preOrder, 6- postOrder, 7- Delete, 0- Exit."<<endl;
        int operation = getOnlyInteger(); 

        if (operation == 0) {
            break;  
        }

        switch (operation) {
            case 1: {
                int value;
                cout << "Enter data to search: ";
                value = getOnlyInteger();  
                searchThis(root, value);   
                break;
            }
            case 2: {
                int noOfValues1;
                cout << "How many nodes to be added? ";
                noOfValues1 = getOnlyInteger(); 
                for (int i = 0; i < noOfValues1; i++) {
                    int value1, parentValue1, position1;
                    cout << endl << "Enter value to be added, value of parent, and position: ";
                    value1 = getOnlyInteger();     
                    parentValue1 = getOnlyInteger(); 
                    position1 = getOnlyInteger();  
                    addNode(root, value1, parentValue1, position1);  
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
                int noOfValues2;
                cout << "How many nodes to be deleted? ";
                noOfValues2 = getOnlyInteger();  
                for (int i = 0; i < noOfValues2; i++) {
                    cout << "Enter value to be deleted: ";
                    int value2 = getOnlyInteger();  
                    deleteNode(root, value2);  
                }
                break;
            }
            default: {
                cout << "Invalid operation. Try again." << endl; 
                break;
            }
        }
    }
    return 0;
}