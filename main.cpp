#include <iostream>
#include <vector>

using namespace std;

struct TreeNode
{
    string data;
    vector<TreeNode *> children;
    TreeNode *parent;

    TreeNode(const string &value, TreeNode *Parent = NULL) : data(value) { parent = Parent; }
};

class Tree
{
private:
    TreeNode *root = new TreeNode("pedarJad");
    size_t size = 1;

public:
    int getSize() // returns the number of nodes in the tree
    {
        return size;
    }

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
        if (node == NULL)
            return;

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

    bool isAncestor(const string &ancestor, const string &descendant) // returns if one is the ancestor of the other
    {
        TreeNode *Ancestor = findNode(ancestor, root);
        TreeNode *Descendant = findNode(descendant, Ancestor);
        if (Descendant != NULL)
            return true;
        return false;
    }

    void addNode(const string &parentValue, const string &childValue) // adds a child to a parent
    {
        TreeNode *parentNode = findNode(parentValue, root);

        if (parentNode == NULL)
        {
            cout << "ERROR! no such parent exists\n";
            return;
        }

        TreeNode *childNode = new TreeNode(childValue, parentNode);
        parentNode->children.push_back(childNode);
        size++;
    }

    void delNode(const string &value) // adds a child to a parent
    {
        TreeNode *node = findNode(value, root);

        if (node == NULL)
        {
            cout << "ERROR! no such node exists\n";
            return;
        }
        for (size_t i = 0; i < node->parent->children.size(); i++)
        {
            if (node->parent->children[i]->data == value)
            {
                node->parent->children.erase(node->parent->children.begin() + i);
            }
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