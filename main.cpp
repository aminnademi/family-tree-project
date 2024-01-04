#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
    string data;
    vector<TreeNode *> children;

    TreeNode(const string &value) : data(value) {}
};

class Tree
{
private:
    TreeNode *root = new TreeNode("pedarJad");

    // void findPath(TreeNode *root, const string &target, vector<string> &path, vector<string> &resultPath)
    // {
    //     if (root == nullptr)
    //         return;

    //     path.push_back(root->data);

    //     if (root->data == target)
    //     {
    //         resultPath = path;
    //         return;
    //     }

    //     for (TreeNode *child : root->children)
    //     {
    //         findPath(child, target, path, resultPath);

    //         if (!resultPath.empty())
    //             return;
    //     }

    //     path.pop_back();
    // }

public:
    int findHeight() // returns the hight of the tree
    {
        return findSubHeight(root);
    }

    int findSubHeight(TreeNode *node) // returns the hight of the sub tree
    {
        if (node == nullptr)
            return 0;

        int maxHeight = 0;

        for (TreeNode *child : node->children)
        {
            int childHeight = findSubHeight(child);
            maxHeight = max(maxHeight, childHeight);
        }

        return maxHeight + 1;
    }

    TreeNode *findNode(const string &value, TreeNode *node) // returns the pointer to the node with an specific value
    {
        if (node->data == value)
        {
            return node;
        }

        for (TreeNode *i : node->children)
        {
            TreeNode *n = findNode(value, i);
            if (n != NULL)
            {
                return n;
            }
        }

        return NULL;
    }

    void addNode(const string &parentValue, const string &childValue) // adds a child to a parent
    {
        TreeNode *parentNode = findNode(parentValue, root);

        if (parentNode == NULL)
        {
            cout << "ERROR! no such parent exists\n";
            return;
        }

        TreeNode *childNode = new TreeNode(childValue);
        parentNode->children.push_back(childNode);
    }

    void delNode(const string &value) // adds a child to a parent
    {
        TreeNode *node = findNode(value, root);

        if (node == NULL)
        {
            cout << "ERROR! no such parent exists\n";
            return;
        }

        delete node;
        node = nullptr;
    }

    void printTree() // prints the whole tree
    {
        printSubTree(root, 0);
    }

    void printSubTree(TreeNode *root, int depth) // prints a sub tree
    {
        for (int i = 0; i < depth; ++i)
        {
            cout << "--";
        }

        cout << "|" << root->data << endl;

        for (TreeNode *child : root->children)
        {
            printSubTree(child, depth + 1);
        }
    }
};

int main()
{
    Tree tree;

    while (true)
    {
        string parent, child;
        cout << "Enter the parent values (enter 'exit' to exit): ";
        getline(cin, parent);
        if (parent == "exit")
        {
            break;
        }
        cout << "Enter the child values: ";
        getline(cin, child);
        tree.addNode(parent, child);
    }

    cout << "Tree structure:" << endl;
    tree.printTree();
}