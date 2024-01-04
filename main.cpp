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

    // int findHeight(TreeNode *node)
    // {
    //     if (node == nullptr)
    //         return 0;

    //     int maxHeight = 0;

    //     for (TreeNode *child : node->children)
    //     {
    //         int childHeight = findHeight(child);
    //         maxHeight = max(maxHeight, childHeight);
    //     }

    //     return maxHeight + 1;
    // }

public:
    TreeNode *findNode(const string &value, TreeNode *node) // returns the pointer to the node with an specific value
    {
        if (node->data == value)
        {
            return node;
        }

        for (size_t i = 0; i < node->children.size(); i++)
        {
            TreeNode *n = findNode(value, node->children[i]);
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

    void printTree()
    {
        printSubTree(root, 0);
    }

    void printSubTree(TreeNode *root, int depth)
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
        cout << "Enter parent and child node values (enter 'exit' to exit): ";
        cin >> parent;

        if (parent == "exit")
        {
            break;
        }

        cin >> child;
        tree.addNode(parent, child);
    }

    cout << "Tree structure:" << endl;
    tree.printTree();
}