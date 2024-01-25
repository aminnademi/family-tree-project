#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <fstream>

using namespace std;

struct TreeNode
{
    string data;
    int depth;
    TreeNode *parent;
    vector<TreeNode *> children;

    TreeNode(const string &name, TreeNode *Parent = nullptr, const int &Depth = 0);
    // the constructor initializes the "TreeNode" object with constant operations.
};

class Tree
{
private:
    // Private Data Members
    TreeNode *root;

private:
    // Private Functions
    int getSubSize(TreeNode *root); // returns the number of nodes in a sub tree
    /* this is a recursive method that traverses the entire subtree from a specific node to count all its children.
    if our specific node is the root, it visits each node once, hence O(n). */

    TreeNode *furthestNode(TreeNode *start); // return the furthest node from another node
    /* this method does a BFS over the tree, hence O(n)*/

    void printSubTree(TreeNode *root, int depth); // prints a sub tree
    /* this method recursively traverses the tree (DFS), hence O(n). */

public:
    Tree(const string &greatAncestor);
    /* the constructor initializes the Tree object with a root containing the great ancestor,
     and the operations are constant, hence O(1). */

    void addNode(const string &parentValue, const string &childValue); // adds a child to a parent
    /* at first this method use "findNode" to traverses the tree: O(n).
    after finding the parent node, it also iterates through all the children of the parent to check for duplicates,
    which in the worst case could be O(n), but since this is typically much less than the total number of nodes,
    we can consider it O(n2) in which n2 << n, hence it is considered O(n). */

    TreeNode *findNode(const string &value, TreeNode *node); // returns the pointer to the node with an specific value in a sub tree
    /* this method is a DFS which in the worst case may visit all nodes in the tree, hence O(n) */

    void delNode(const string &value); // removes a child and its childrens and further generation
    /* this method use "findNode" function to find the node first,
    and then deleting it involves removing it from the parent's children vector, hence O(n). */

    int getSize(); // returns the number of nodes in the tree
    /* it calls "getSubSize", which traverses the entire tree to count all nodes,
    thus touching each node exactly once. This results in a complexity of O(n). */

    int findHeight(); // returns the height of the tree
    /* calls "findSubHeight" method which traverse the tree, potentially, entirely. hence O(n) */

    int findSubHeight(const string &value); // returns the height of the subtree
    /* traverse the tree, potentially, entirely. hence O(n) */

    bool isAncestor(const string &ancestor, const string &descendant); // returns whether one is the ancestor of the other or not
    /* this method uses "findNode" twice. The first call to locate the ancestor and the second call to
    find the descendant from the ancestor, since the second search starts from the Ancestor node and the search is a DFS
    operation in the worst case won't traves the tree more than once, hence O(n).*/

    bool areSiblings(const string &person1, const string &person2); // returns whether they are siblings or not
    /* this method calls "findNode" and then iterates over all children of the parent node, the number of the parent's
    children are << n, hence O(n). */

    bool areCousins(const string &person1, const string &person2); // returns whether they are cousins or not
    /* this method calls "findNode" twice (2*O(n)), and then compares the depths and parents of the two nodes.
    the dominant term is the findNode calls, hence O(n). */

    TreeNode *lowestCommonAncestor(const string &person1, const string &person2); // returns the lowest common ancestor
    /* this method calls findNode twice (2*O(n)), then traverses up the tree from each node until it finds a common ancestor.
    In the worst case, this could traverse the depth of a tree in addition, hence still O(n). */

    vector<TreeNode *> diameter(); // returns the tree diameter
    /* This method uses furthestNode twice, which traverse the tree potentially entirely, hence o(n) */

    void printTree(); // prints the whole tree
    /* calls printSubTree from the root, hence O(n). */

    void createJson(); // creates a json file of the tree with BFS
    /* This method traverses the entire tree while creating a JSON representation, hence O(n). */
};