// ------------- GENERAL TREE ORDERING -------------
// Purpose: The objective of this code is to convert the input values of a general tree
// into inorder, postorder, and preorder traversals.
// Authors: 
//   - Pelinsu Kaleli
//   - Bulut Demir
//   - Umut Boray Demir
//------------------------------------------------------

#include <iostream>
#include <vector>
#include <stack>

using namespace std;
class Node {
public:
    int data;
    vector<Node*> children;
    Node() {}
    Node(int val) {
        data = val;
    }
};

Node* insertNode(Node* root, int parent, int child){
    if (root == nullptr)
    {
        root = new Node();
        root->data = parent;
        Node* temp = new Node();
        temp->data = child;
        root->children.push_back(temp);
        return root;
    }
    if (root->data == parent)
    {
        Node* temp = new Node();
        temp->data = child;
        root->children.push_back(temp);
        return root;
    }
    for (int i = 0; i < root->children.size(); i++)
    {
        root->children[i] = insertNode(root->children[i], parent, child);
    }
    return root;
}

Node* createTree(string input)
{
    Node* root = nullptr;
    int i = 0;
    while (i < input.length())
    {
        if (input[i] == '(')
        {
            i++;
            int parent = 0;
            while (input[i] != ';')
            {
                parent = parent * 10 + (input[i] - '0');
                i++;
            }
            i++;
            int child = 0;
            while (input[i] != ')')
            {
                if (input[i] == ',')
                {
                    root = insertNode(root, parent, child);
                    child = 0;
                    i++;
                    continue;
                }
                child = child * 10 + (input[i] - '0');
                i++;
            }
            root = insertNode(root, parent, child);
        }
        i++;
    }
    return root;
}


void postorder(Node* root, vector<int>& result) {
    if (root == nullptr) return;


    for (Node* child : root->children) {
        postorder(child, result);
    }


    result.push_back(root->data);
}

void preorder(Node* root, vector<int>& result)
{
    if (root == nullptr) return;
    
    result.push_back(root->data);

    for (Node* child : root->children)
    {
        preorder(child,result);
    }
}

void inorder(Node* root, vector<int>& result) {
    if (root == nullptr) return;


    if (root->children.size() == 0)
        result.push_back(root->data);
    else
    {
        inorder(root->children[0], result);
        root->children.erase(root->children.begin());
        result.push_back(root->data);
        for (Node* child : root->children)
        {
            inorder(child, result);
        }
    }

}

void controlInput(string& input) {
    stack<char> control;
    int treeCount = 0;
    for (size_t i = 0; i < input.length(); i++)
    {
        if (input[i] == '(' || input[i] == ')')
            control.push(input[i]);
    }

    while (!control.empty())
    {
        if (control.top() != ')')
        {
            throw out_of_range("Tree error");
        }
        control.pop();
        if (control.top() != '(')
        {
            throw out_of_range("Tree error");

        }
        control.pop();
        treeCount++;
    }
}

void printResult(vector<int>& result) {       
    
    for (int n : result)
    {
        cout << n << ",";
    }
    cout << endl;
}


int main()
{
    string input;
    Node* root;
    vector<int> result;

    cout << "Enter the tree: ";
    cin >> input;

    controlInput(input);
    root = createTree(input);

    postorder(root,result);
    printResult(result);

    result.clear();

    preorder(root, result);
    printResult(result);

    result.clear();

    inorder(root, result);
    printResult(result);

}