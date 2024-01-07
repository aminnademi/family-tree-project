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

public:
    int getSize() // returns the number of nodes in the tree
    {
        return getSubSize(root);
    }

    int getSubSize(TreeNode *root) // returns the number of nodes in a sub tree
    {
        if (root == nullptr)
            return 0;

        int size = 0;
        for (TreeNode *i : root->children)
            size += getSubSize(i);

        return size + 1;
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
        cout << "Descendant didn't exist!\n";
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

    TreeNode *lastCommonAncestor(const string &person1, const string &person2) // returns the lowest common ancestor
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
        cout << value << " was removed\n";
    }

    void printTree() // prints the whole tree
    {
        cout << endl;
        printSubTree(root, 0);
        cout << endl;
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

    vector<TreeNode *> diameter() // returns the tree diameter
    {
        TreeNode *head = furthestNode(root);
        cout << endl
             << head->data << endl;
        TreeNode *tail = furthestNode(head);
        cout << endl
             << tail->data << endl;
        vector<TreeNode *> ans;
        ans.push_back(head);
        ans.push_back(tail);
        return ans;
    }

    TreeNode *furthestNode(TreeNode *start) // return the furthest node to a node
    {
        // int size = getSize();
        // bool visited[size];
        // for (int i = 0; i < size; i++)
        // {
        //     visited[i] = false;
        // }
        TreeNode *furthest;
        int len = 0;

        deque<int> cost;
        deque<TreeNode *> nodeQue;
        deque<TreeNode *> previous;
        cost.push_back(0);
        nodeQue.push_back(start);
        previous.push_back(nullptr);

        while (nodeQue.size() > 0)
        {
            TreeNode *work = nodeQue.front();
            nodeQue.pop_front();
            TreeNode *p = previous.front();
            previous.pop_front();
            int c = cost.front();
            cost.pop_front();
            cout << "working on " << work->data << endl;
            if (len < c)
            {
                len = c;
                furthest = work;
            }
            // cout << "here p is " << p->data << endl;
            if (work->parent != p and work->parent != nullptr)
            {
                // cout << p->data << " and " << work->parent->data << endl;
                cout << "in parent " << work->data << endl;
                nodeQue.push_back(work->parent);
                previous.push_back(work);
                cost.push_back(c + 1);
            }
            for (TreeNode *i : work->children)
            {
                if (i != p and i != nullptr)
                {
                    nodeQue.push_back(i);
                    previous.push_back(work);
                    cost.push_back(c + 1);
                }
            }
        }
        // cout << furthest->data;
        cout << "this";
        return furthest;
    }

    // int subDiameterLength(TreeNode *root, int *h) // returns a sub tree diameter
    // {
    //     vector<int> heights;
    //     int maximum = 0;
    //     for (int i = 0; i < root->children.size(); i++)
    //     {
    //         heights.push_back(0);
    //         maximum = max(maximum, subDiameter(root->children[i], &heights[i]));
    //     }
    //     int m1 = 0, m2 = 0;
    //     for (int i : heights)
    //     {
    //         int t = i;
    //         if (t > m2)
    //             swap(m2, t);
    //         if (t > m1)
    //             swap(m1, t);
    //     }
    //     *h += m2 + 1;
    //     maximum = max(maximum, m1 + m2 + 1);
    //     return maximum;
    // }
};

void removeFamilyMembers(Tree &tree) // for removing members from the tree
{
    cout << "Your family tree: " << endl;
    tree.printTree();

    cout << "Modifing the family tree: \n";
    while (true)
    {
        string individual;
        cout << "Enter the individual name (enter 'exit' to exit): ";
        getline(cin, individual);
        if (individual == "exit")
        {
            break;
        }
        tree.delNode(individual);
    }

    cout << "Your family tree: " << endl;
    tree.printTree();
    tree.createJson();
}

void addFamilyMembers(Tree &tree) // for adding members to the tree
{
    cout << "Your family tree: " << endl;
    tree.printTree();

    cout << "Modifing the family tree: \n";
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

    cout << "Your family tree: " << endl;
    tree.printTree();
    tree.createJson();
}

void tools(Tree &tree) // menu of tree functionalities
{
    while (true)
    {
        cout << "1. Number of individuals\n"
             << "2. Number of generations\n"
             << "3. Find the furthest relatives\n"
             << "4. Ancestor check\n"
             << "5. Siblings check\n"
             << "6. Cousins check\n"
             << "7. Find last common ancestor\n"
             << "8. Add more individuals\n"
             << "9. Remove individuals\n"
             << "10. Print the family tree\n";
        cout << "Choose your task by entering 1 to 10 (enter 'exit' to exit): ";
        string input;
        getline(cin, input);
        if (input == "exit")
        {
            cout << "Have a nice day!\n";
            return;
        }
        else if (input == "1")
        {
            cout << tree.getSize() << endl;
        }
        else if (input == "2")
        {
            cout << tree.findHeight() << endl;
        }
        // else if (input == "3")
        // {
        //     cout << "The furthest family members are " << tree.diameter() << " members apart" << endl;
        // }
        else if (input == "4")
        {
            string a, d;
            cout << "Enter the name of the ancestor: ";
            getline(cin, a);
            cout << "Enter the name of the descendant: ";
            getline(cin, d);
            if (tree.isAncestor(a, d))
                cout << "Yes! " << a << " is " << d << "'s ancestor" << endl;
            else
                cout << "No! " << a << " is not " << d << "'s ancestor" << endl;
        }
        else if (input == "5")
        {
            string a, b;
            cout << "Enter the first person's name: ";
            getline(cin, a);
            cout << "Enter the second person's name: ";
            getline(cin, b);
            if (tree.areSiblings(a, b))
                cout << "Yes! "
                     << "They are siblings." << endl;
            else
                cout << "No! "
                     << "They are not siblings." << endl;
        }
        else if (input == "6")
        {
            string a, b;
            cout << "Enter the first person's name: ";
            getline(cin, a);
            cout << "Enter the second person's name: ";
            getline(cin, b);
            if (tree.areCousins(a, b))
                cout << "Yes! "
                     << "They are cousins." << endl;
            else
                cout << "No! "
                     << "They are not cousins." << endl;
        }
        else if (input == "7")
        {
            string a, b;
            cout << "Enter the first person's name: ";
            getline(cin, a);
            cout << "Enter the second person's name: ";
            getline(cin, b);
            cout << tree.lastCommonAncestor(a, b)->data
                 << "is their last common ancestor" << endl;
        }
        else if (input == "8")
        {
            addFamilyMembers(tree);
        }
        else if (input == "9")
        {
            removeFamilyMembers(tree);
        }
        else if (input == "10")
        {
            tree.printTree();
        }
        else
        {
            cout << "Invalid input!\n";
        }
    }
}

int main()
{
    Tree tree;
    addFamilyMembers(tree);
    tools(tree);
    vector<TreeNode *> print;
    print = tree.diameter();
    cout << print[0]->data << print[1]->data;
    return 0;
}