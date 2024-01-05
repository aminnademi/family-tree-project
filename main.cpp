#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

using namespace std;

struct TreeNode
{
    string data;
    vector<TreeNode *> children;
    TreeNode *parent;
    int depth;

    TreeNode(const string &value, TreeNode *Parent = nullptr, const int &Depth = 0) : data(value), parent(Parent),
                                                                                      depth(Depth) {}
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

    TreeNode *findNode(const string &value, TreeNode *node) // returns the pointer to the node with an specific value in a sub tree
    {
        if (node == nullptr)
            return nullptr;

        if (node->data == value)
            return node;

        for (TreeNode *i : node->children)
        {
            TreeNode *n = findNode(value, i);
            if (n != nullptr)
                return n;
        }

        return nullptr;
    }

    bool isAncestor(const string &ancestor, const string &descendant) // returns whether one is the ancestor of the other
    {
        TreeNode *Ancestor = findNode(ancestor, root);
        if (Ancestor == nullptr)
        {
            cout << "Ancestor didn't exist!\n";
            return NULL;
        }
        TreeNode *Descendant = findNode(descendant, Ancestor);
        if (Descendant != nullptr)
            return true;
        return false;
    }

    bool areSiblings(const string &person1, const string &person2) // returns whether they are siblings
    {
        TreeNode *Person1 = findNode(person1, root);
        if (Person1 == nullptr)
        {
            cout << "First person didn't exist!\n";
            return NULL;
        }
        for (TreeNode *i : Person1->parent->children)
        {
            if (i->data == person2)
                return true;
        }
        return false;
    }

    bool areCousins(const string &person1, const string &person2) // returns whether they are siblings
    {
        TreeNode *Person1 = findNode(person1, root);
        if (Person1 == nullptr)
        {
            cout << "First person didn't exist!\n";
            return NULL;
        }
        for (TreeNode *i : Person1->parent->children)
        {
            if (i->data == person2)
                return false;
        }
        TreeNode *Person2 = findNode(person2, root);
        if (Person2 == nullptr)
        {
            cout << "Second person didn't exist!\n";
            return NULL;
        }
        if (Person1->depth == Person2->depth)
            return true;
        return false;
    }

    TreeNode *lowestCommonAncestor(const string &person1, const string &person2) // returns the lowest common ancestor
    {
        TreeNode *Person1 = findNode(person1, root);
        if (Person1 == nullptr)
        {
            cout << "First person didn't exist!\n";
            return nullptr;
        }
        TreeNode *Person2 = findNode(person2, root);
        if (Person2 == nullptr)
        {
            cout << "Second person didn't exist!\n";
            return nullptr;
        }
        Person1 = Person1->parent;
        Person2 = Person2->parent;
        while (Person1->depth != Person2->depth)
        {
            if (Person1->depth > Person2->depth)
                Person1 = Person1->parent;
            else
                Person2 = Person2->parent;
        }
        while (true)
        {
            if (Person1->data == Person2->data)
                return Person1;
            Person1 = Person1->parent;
            Person2 = Person2->parent;
        }
    }

    void addNode(const string &parentValue, const string &childValue) // adds a child to a parent
    {
        TreeNode *parentNode = findNode(parentValue, root);
        if (parentNode == nullptr)
        {
            cout << "Parent didn't exist!\n";
            return;
        }

        TreeNode *childNode = new TreeNode(childValue, parentNode, parentNode->depth + 1);
        parentNode->children.push_back(childNode);
        size++;
    }

    void delNode(const string &value) // adds a child to a parent
    {
        TreeNode *node = findNode(value, root);

        if (node == nullptr)
        {
            cout << "The person didn't exist\n";
            return;
        }
        for (size_t i = 0; i < node->parent->children.size(); i++)
        {
            if (node->parent->children[i]->data == value)
                node->parent->children.erase(node->parent->children.begin() + i);
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
        if (root == nullptr)
            return;

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

    void createJson() // creates a json file of the tree in Breadth first order
    {
        if (root == nullptr)
            return;

        deque<TreeNode *> queue;
        ofstream file("tree_data.json");

        file << "{\n";
        queue.push_back(root);
        while (queue.size() > 0)
        {
            TreeNode *tmp = queue.front();
            queue.pop_front();
            file << "\"" << tmp->data << "\": [";
            for (int j = 0; j < tmp->children.size(); j++)
            {
                TreeNode *i = tmp->children[j];
                if (j == tmp->children.size() - 1)
                    file << "\"" << i->data << "\"";
                else
                    file << "\"" << i->data << "\", ";
                queue.push_back(i);
            }
            if (queue.size() == 0)
                file << "]";
            else
                file << "], ";
        }
        file << "\n}";
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
    tree.createJson();
}