#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class stackNode {
    public:
    Node* data;
    stackNode* next;
};

class stack {
    public:
    stackNode* topp;

    stack() {
        topp = nullptr;
    }

    void push(Node* value) {
        stackNode* newNode = new stackNode();
        newNode->data = value;
        newNode->next = topp;
        topp = newNode;
    }

    bool isEmpty() {
        return topp == nullptr;
    }

    void pop() {
        if (isEmpty()) {
            return;
        }
        stackNode* temp = topp;
        topp = topp->next;
        delete temp;
    }

    Node* top() {
        if (isEmpty()) {
            return nullptr;
        }
        return topp->data;
    }
};

class queueNode {
    public:
    Node* data;
    queueNode* next;
};

class queue {
    public:
    queueNode* frontt;
    queueNode* rear;

    queue() {
        frontt = nullptr;
        rear = nullptr;
    }

    void push(Node* value) {
        queueNode* newNode = new queueNode;
        newNode->data = value;
        newNode->next = nullptr;

        if (rear == nullptr) {
            frontt = newNode;
            rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    bool isEmpty() {
        return frontt == nullptr;
    }

    void pop() {
        if (isEmpty()) {
            return;
        } else {
            queueNode* temp = frontt;
            frontt = frontt->next;
            if (frontt == nullptr) {
                rear = nullptr;
            }
            delete temp;
        }
    }

    Node* front() {
        if (isEmpty()) {
            return nullptr;
        }
        return frontt->data;
    }
};


Node* searchNode(Node* root, int value) {
    if (root == nullptr) return nullptr;
    Node* temp = root;
    while (temp != nullptr) {
        if (temp->data > value) {
            temp = temp->left;
        } else if (temp->data < value) {
            temp = temp->right;
        } else {
            return temp;
        }
    }
    return nullptr;
}

void searchThis(Node* root, int value) {
    if (searchNode(root, value)) {
        cout << "Node is present." << endl;
    } else {
        cout << "Node is not present." << endl;
    }
}

int heightOf(Node* root) {
    if (root == nullptr) return 0;
    return root->height;
}

int balanceFactor(Node* root) {
    if (root == nullptr) return 0;
    return heightOf(root->left) - heightOf(root->right);
}

Node* rotateRight(Node* root) {
    Node* child = root->left;
    Node* childRight = child->right;

    child->right = root;
    root->left = childRight;

    root->height = 1 + max(heightOf(root->left), heightOf(root->right));
    child->height = 1 + max(heightOf(child->left), heightOf(child->right));

    return child;
}

Node* rotateLeft(Node* root) {
    Node* child = root->right;
    Node* childLeft = child->left;

    child->left = root;
    root->right = childLeft;

    root->height = 1 + max(heightOf(root->left), heightOf(root->right));
    child->height = 1 + max(heightOf(child->left), heightOf(child->right));

    return child;
}

void breadthFirst(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot print! " << endl;
        return;
    }
    queue q;
    q.push(root);
    while (!q.isEmpty()) {
        Node* temp = q.front();
        q.pop();

        cout << temp->data << " ";
        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);
    }
    cout << endl;
}

void inOrder(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot print! " << endl;
        return;
    }

    stack s;
    s.push(root);
    Node* lastVisited = nullptr;
    while (!s.isEmpty()) {
        Node* current = s.top();
        s.pop();
        if (current->left && current->left != lastVisited && current->right != lastVisited) {
            s.push(current);
            s.push(current->left);
        } else if (current->right != nullptr && current->right != lastVisited) {
            cout << current->data << " ";
            s.push(current);
            s.push(current->right);
        } else if (current->right != lastVisited) {
            cout << current->data << " ";
        }
        lastVisited = current;
    }
}

void preOrder(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot print! " << endl;
        return;
    }
    Node* lastVisited = nullptr;
    stack s;
    s.push(root);
    while (!s.isEmpty()) {
        Node* current = s.top();
        s.pop();
        cout << current->data << " ";

        if (current->right) s.push(current->right);
        if (current->left) s.push(current->left);
    }
}

void postOrder(Node* root) {
    if (root == nullptr) {
        cout << "Tree is empty, cannot print! " << endl;
        return;
    }
    Node* lastVisited = nullptr;
    stack s;
    s.push(root);
    while (!s.isEmpty()) {
        Node* current = s.top();
        s.pop();
        if (current->left && current->left != lastVisited && current->right != lastVisited) {
            s.push(current);
            s.push(current->left);
        } else if (current->right && current->right != lastVisited) {
            s.push(current);
            s.push(current->right);
        } else if (current->left != lastVisited) {
            cout << current->data << " ";
        }
        lastVisited = current;
    }
}

void addNode(Node*& root, int value) {
    Node* newNode = new Node(value);
    if(searchNode(root, value)) {
        return;
    }

    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* parent = nullptr;
    Node* current = root;
    stack ancestors;

    while (current != nullptr) {
        parent = current;
        ancestors.push(parent);

        if (value < current->data) {
            current = current->left;
        } else if (value > current->data) {
            current = current->right;
        } else
            return;
    }

    if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    while (!ancestors.isEmpty()) {
        Node* temp = ancestors.top();
        ancestors.pop();

        temp->height = 1 + max(heightOf(temp->left), heightOf(temp->right));
        int bf = balanceFactor(temp);

//left left
        if (bf > 1 && value < temp->left->data) {
            if (!ancestors.isEmpty()) {
                if (ancestors.top()->left == temp)
                    ancestors.top()->left = rotateRight(temp);
                else if (ancestors.top()->right == temp)
                    ancestors.top()->right = rotateRight(temp);
            } else
                root = rotateRight(temp);
            break;
        }

//right right
        if (bf < -1 && value > temp->right->data) {
            if (!ancestors.isEmpty()) {
                if (ancestors.top()->right == temp)
                    ancestors.top()->right = rotateLeft(temp);
                else if (ancestors.top()->left == temp)
                    ancestors.top()->left = rotateLeft(temp);
            } else
                root = rotateLeft(temp);
            break;
        }

//left right
        if (bf > 1 && value > temp->left->data) {
            temp->left = rotateLeft(temp->left);
            if (!ancestors.isEmpty()) {
                if (ancestors.top()->left == temp)
                    ancestors.top()->left = rotateRight(temp);
                else if (ancestors.top()->right == temp)
                    ancestors.top()->right = rotateRight(temp);
            } else
                root = rotateRight(temp);
            break;
        }
        
//right left
        if (bf < -1 && value < temp->right->data) {
            temp->right = rotateRight(temp->right);
            if (!ancestors.isEmpty()) {
                if (ancestors.top()->right == temp)
                    ancestors.top()->right = rotateLeft(temp);
                else if (ancestors.top()->left == temp)
                    ancestors.top()->left = rotateLeft(temp);
            } else
                root = rotateLeft(temp);
            break;
        }
    }
}

int getOnlyInteger() {
    int x;
    while (1) {
        cin >> x;
        if (cin.fail() || x < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid Input, Try Again!";
        } else {
            break;
        }
    }
    return x;
}

int main() {
    int x;
    cout<<"Enter data of root: ";
    x = getOnlyInteger();
    Node *root = new Node(x);

    while (true) {
        cout <<endl<<"Enter the operation: 1- Search, 2- Add, 3- Breadth First, 4- inOrder, 5- preOrder, 6- postOrder, 0- Exit." <<endl;
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
            default:
                cout<<"Invalid operation, Try again."<<endl;
        }
    }
    return 0;
}