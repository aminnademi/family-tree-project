#include "include/Tree.h"
#include <filesystem>

#define RED "\033[31m"
#define CYAN "\033[36m"

using namespace std;

TreeNode::TreeNode(const string &name, TreeNode *Parent, const int &Depth) : data(name), parent(Parent), depth(Depth) {}

Tree::Tree(const string &greatAncestor) : root(new TreeNode(greatAncestor)) { createJson(); }

void Tree::addNode(const string &parentName, const string &childName)
{
    TreeNode *parentNode = findNode(parentName, root);
    if (parentNode == nullptr)
    {
        cout << RED << "Parent didn't exist!\n";
        return;
    }
    for (TreeNode *i : parentNode->children)
    {
        if (i->data == childName)
        {
            cout << RED << "This parent already has a child with this information!\n";
            return;
        }
    }
    TreeNode *childNode = new TreeNode(childName, parentNode, parentNode->depth + 1);
    parentNode->children.push_back(childNode);
}

TreeNode *Tree::findNode(const string &name, TreeNode *node)
{
    if (node == nullptr)
        return nullptr;

    if (node->data == name)
        return node;

    for (TreeNode *i : node->children)
    {
        TreeNode *n = findNode(name, i);
        if (n != nullptr)
            return n;
    }

    return nullptr;
}

void Tree::delNode(const string &name)
{
    TreeNode *node = findNode(name, root);

    if (node == nullptr)
    {
        cout << RED << "The person didn't exist\n";
        return;
    }
    for (size_t i = 0; i < node->parent->children.size(); i++)
    {
        if (node->parent->children[i]->data == name)
            node->parent->children.erase(node->parent->children.begin() + i);
    }
    delete node;
    node = nullptr;
}

int Tree::getSize()
{
    return getSubSize(root);
}

int Tree::findHeight()
{
    return findSubHeight(root->data);
}

int Tree::findSubHeight(const string &name)
{
    TreeNode *node = findNode(name, root);
    if (node == nullptr)
    {
        cout << RED << "The person didn't exist\n";
        return 0;
    }

    int maxHeight = 0;

    for (TreeNode *child : node->children)
    {
        int childHeight = findSubHeight(child->data);
        maxHeight = max(maxHeight, childHeight);
    }

    return maxHeight + 1;
}

bool Tree::isAncestor(const string &ancestor, const string &descendant)
{
    TreeNode *Ancestor = findNode(ancestor, root);
    if (Ancestor == nullptr)
    {
        cout << RED << "Ancestor didn't exist!\n";
        return NULL;
    }
    TreeNode *Descendant = findNode(descendant, Ancestor);
    if (Descendant != nullptr)
        return true;
    cout << RED << "Descendant didn't exist!\n";
    return false;
}

bool Tree::areSiblings(const string &person1, const string &person2)
{
    TreeNode *Person1 = findNode(person1, root);
    if (Person1 == nullptr)
    {
        cout << RED << "First person didn't exist!\n";
        return NULL;
    }
    for (TreeNode *i : Person1->parent->children)
    {
        if (i->data == person2)
            return true;
    }
    return false;
}

bool Tree::areCousins(const string &person1, const string &person2)
{
    TreeNode *Person1 = findNode(person1, root);
    if (Person1 == nullptr)
    {
        cout << RED << "First person didn't exist!\n";
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
        cout << RED << "Second person didn't exist!\n";
        return NULL;
    }
    if (Person1->depth == Person2->depth)
        return true;
    return false;
}

TreeNode *Tree::lowestCommonAncestor(const string &person1, const string &person2)
{
    TreeNode *Person1 = findNode(person1, root);
    if (Person1 == nullptr)
    {
        cout << RED << "First person didn't exist!\n";
        return nullptr;
    }
    TreeNode *Person2 = findNode(person2, root);
    if (Person2 == nullptr)
    {
        cout << RED << "Second person didn't exist!\n";
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

vector<TreeNode *> Tree::diameter()
{
    vector<TreeNode *> temp;
    TreeNode *head = furthestNode(root);
    TreeNode *tail = furthestNode(head);
    temp.push_back(head);
    temp.push_back(tail);

    return temp;
}

void Tree::printTree()
{
    cout << endl;
    printSubTree(root, 0);
    cout << endl;
}

void Tree::createJson()
{
    if (root == nullptr)
        return;

    deque<TreeNode *> queue;
    filesystem::path cwd = filesystem::current_path();
    ofstream file(cwd.string() + "/../data/tree_data.json");

    file << "{\n";
    file << "\"size\": " << findHeight() << ", ";
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
    file.close();
}

int Tree::getSubSize(TreeNode *root)
{
    if (root == nullptr)
        return 0;

    int size = 0;
    for (TreeNode *i : root->children)
        size += getSubSize(i);

    return size + 1;
}

TreeNode *Tree::furthestNode(TreeNode *start)
{
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
        if (len < c)
        {
            len = c;
            furthest = work;
        }
        if (work->parent != p and work->parent != nullptr)
        {
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
    return furthest;
}

void Tree::printSubTree(TreeNode *root, int depth)
{
    cout << CYAN;
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