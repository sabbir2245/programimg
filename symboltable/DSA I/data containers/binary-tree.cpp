#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <stack>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int value)
    {
        data = value;
        left = right = nullptr;
    }
};

class BinaryTree
{
public:
    Node *root;

    BinaryTree()
    {
        root = nullptr;
    }

    Node *insert(Node *node, int value)
    {
        Node *newnode = new Node(value);
        if (node == nullptr)
        {
            return newnode;
        }
        if (value < node->data)
        {
            node->left = insert(node->left, value);
        }
        else
        {
            node->right = insert(node->right, value);
        }
        return node;
    }

    void inorder(Node *node)
    {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    void preorder(Node *root)
    {
        if (root == nullptr)
            return;
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
    void postorder(Node *root)
    {
        if (root == nullptr)
            return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }

    int numberOfNodes(Node *node)
    {
        if (node == nullptr)
            return 0;
        return 1 + numberOfNodes(node->left) + numberOfNodes(node->right);
    }

    int countNodesInRange(Node *root, int low, int high)
    {
        if (root == nullptr)
            return 0;
        if (root->data >= low && root->data <= high)
            return 1 + countNodesInRange(root->left, low, high) + countNodesInRange(root->right, low, high);
        else if (root->data < low)
            return countNodesInRange(root->right, low, high);
        else
            return countNodesInRange(root->left, low, high);
    }
    void inorder(Node *root, unordered_set<int> &s)
    {
        if (root == nullptr)
            return;
        inorder(root->left, s);
        s.insert(root->data);
        inorder(root->right, s);
    }

    int countPairs(Node *root1, Node *root2, int x)
    {
        unordered_set<int> s;
        inorder(root1, s);
        int count = 0;

        stack<Node *> stack;
        Node *curr = root2;

        while (curr || !stack.empty())
        {
            while (curr)
            {
                stack.push(curr);
                curr = curr->left;
            }
            curr = stack.top();
            stack.pop();

            if (s.find(x - curr->data) != s.end())
                count++;

            curr = curr->right;
        }

        return count;
    }
    Node *sortedArrayToBST(vector<int> &arr, int start, int end)
    {
        if (start > end)
            return nullptr;
        int mid = (start + end) / 2;
        Node *root = new Node(arr[mid]);
        root->left = sortedArrayToBST(arr, start, mid - 1);
        root->right = sortedArrayToBST(arr, mid + 1, end);
        return root;
    }
    int kthSmallest(Node *root, int k)
    {
        int count = 0, result = -1;
        Node *curr = root;

        while (curr)
        {
            if (curr->left == nullptr)
            {
                count++;
                if (count == k)
                    result = curr->data;
                curr = curr->right;
            }
            else
            {
                Node *pred = curr->left;
                while (pred->right && pred->right != curr)
                    pred = pred->right;

                if (pred->right == nullptr)
                {
                    pred->right = curr;
                    curr = curr->left;
                }
                else
                {
                    pred->right = nullptr;
                    count++;
                    if (count == k)
                        result = curr->data;
                    curr = curr->right;
                }
            }
        }
        return result;
    }

    Node *deleteNode(Node *root, int key)
    {
        if (!root)
            return root;
        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else
        {
            if (!root->left)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (!root->right)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            Node *temp = root->right;
            while (temp->left)
                temp = temp->left;
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    int height(Node *node)
    {
        if (node == nullptr)
            return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    bool search(Node *node, int value)
    {
        if (node == nullptr)
            return false;
        if (node->data == value)
            return true;
        if (value < node->data)
        {
            return search(node->left, value);
        }
        else
        {
            return search(node->right, value);
        }
    }

    Node *findMin(Node *node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
        }
        return node;
    }

    int findMax(Node *node)
    {
        if (node == nullptr)
            return -1;
        while (node->right != nullptr)
        {
            node = node->right;
        }
        return node->data;
    }

    Node *deleteNode(Node *root, int key)
    {
        if (root == nullptr)
        {
            return root;
        }

        if (key < root->data)
        {
            root->left = deleteNode(root->left, key);
        }
        else if (key > root->data)
        {
            root->right = deleteNode(root->right, key);
        }
        else
        {
            if (root->left == nullptr)
            {
                Node *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }

            Node *temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    void printTree(Node *root, int space = 0, int height = 10)
    {
        if (root == nullptr)
        {
            return;
        }

        space += height;
        printTree(root->left, space);
        cout << endl;
        for (int i = height; i < space; i++)
        {
            cout << " ";
        }
        cout << root->data << "\n";
        printTree(root->right, space);
    }

    void clearTree(Node *root)
    {
        if (root == nullptr)
        {
            return;
        }
        clearTree(root->left);
        clearTree(root->right);
        delete root;
    }

    bool pathToNode(Node *root, int key, vector<int> &path)
    {
        if (root == nullptr)
        {
            return false;
        }

        path.push_back(root->data);

        if (root->data == key)
        {
            return true;
        }

        if (pathToNode(root->left, key, path))
        {
            return true;
        }

        if (pathToNode(root->right, key, path))
        {
            return true;
        }

        path.pop_back();
        return false;
    }
};

int main()
{
    BinaryTree tree;

    tree.root = tree.insert(tree.root, 50);
    tree.insert(tree.root, 30);
    tree.insert(tree.root, 70);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 40);
    tree.insert(tree.root, 60);
    tree.insert(tree.root, 80);
    tree.insert(tree.root, 100);
    tree.insert(tree.root, 19);
    tree.insert(tree.root, 50);

    cout << "In-order traversal: ";
    tree.inorder(tree.root);
    cout << endl;
    tree.printTree(tree.root);

    cout << "Number of nodes: " << tree.numberOfNodes(tree.root) << endl;
    cout << "Height of the tree: " << tree.height(tree.root) << endl;

    int searchValue = 40;
    cout << "Is " << searchValue << " present in the tree? " << (tree.search(tree.root, searchValue) ? "Yes" : "No") << endl;

    cout << "Minimum value in the tree: " << tree.findMin(tree.root)->data << endl;
    cout << "Maximum value in the tree: " << tree.findMax(tree.root) << endl;

    int key = 40;
    vector<int> path;
    if (tree.pathToNode(tree.root, key, path))
    {
        cout << "Path to node " << key << ": ";
        for (int node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "Node " << key << " not found in the tree." << endl;
    }

    cout << "Tree cleared." << endl;
    tree.clearTree(tree.root);
    tree.root = nullptr;

    return 0;
}
