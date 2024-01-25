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
    // The constructor initializes the TreeNode object with constant operations, resulting in O(1) time complexity.
};

class Tree
{
private:
    // Private Data Members
    TreeNode *root;

private:
    // Private Helper Functions
    int getSubSize(TreeNode *root); // returns the number of nodes in a sub tree
    /* This method recursively traverses the tree. In the worst case, it will visit all nodes, resulting in O(n). */

    TreeNode *furthestNode(TreeNode *start); // return the furthest node to a node
    /* This method has a nested loop, resulting in O(n^2) in the worst case. */

    void printSubTree(TreeNode *root, int depth); // prints a sub tree
    /* This method recursively traverses the tree. In the worst case, it will visit all nodes, resulting in O(n).*/

public:
    Tree(const string &greatAncestor);
    /* The constructor initializes the Tree object with a root containing the great ancestor,
     and the operations are constant, resulting in O(1) time complexity. */

    void addNode(const string &parentValue, const string &childValue); // adds a child to a parent
    /* The findNode method is called within addNode, and in the worst case, it traverses all nodes in the tree (O(n)).
    After finding the parent node, it also iterates through all the children of the parent to check for duplicates, 
    which in the worst case could be O(n), but since this is typically much less than the total number of nodes,
    it's often considered O(d) where d is the number of children of a node. 
    However, the dominant factor is the findNode traversal, hence O(n). */

    TreeNode *findNode(const string &value, TreeNode *node); // returns the pointer to the node with an specific value in a sub tree
    /* This method is a recursive depth-first search that in the worst case may visit all nodes in the tree if the node is not found or if it's the last one to visit.
    Therefore, its complexity is O(n). */
    void delNode(const string &value); // adds a child to a parent
    /* this method use "findNode" function to find the node first,
    and then deleting it involves removing it from the parent's children vector, which is O(n). */

    int getSize(); // returns the number of nodes in the tree
    /* The method uses getSubSize, which recursively traverses the entire tree, resulting in O(n). */

    int findHeight(); // returns the height of the tree
    /* The method uses "findSubHeight" , which recursively traverses the tree. 
    In the worst case, it will visit all nodes, resulting in O(n) */

    int findSubHeight(const string &value); // returns the height of the subtree
    /* This method recursively traverses the tree.
    In the worst case, it will visit all nodes, resulting in O(n). */

    bool isAncestor(const string &ancestor, const string &descendant); // returns whether one is the ancestor of the other
    /*  This method uses findNode twice, so the time complexity is O(n). */
    bool areSiblings(const string &person1, const string &person2); // returns whether they are siblings
    /* This method assumes constant-time access for parent's children, making it O(d), where d is the average number of children per node. */

    bool areCousins(const string &person1, const string &person2); // returns whether they are siblings
    /* Similar to areSiblings, this method assumes constant-time access for parent's children, 
    making it O(d), where d is the average number of children per node. */

    TreeNode *lowestCommonAncestor(const string &person1, const string &person2); // returns the lowest common ancestor
    /* This method uses findNode twice, and the worst-case time complexity is O(n). */
    vector<TreeNode *> diameter(); // returns the tree diameter
    /* This method uses furthestNode, which has a nested loop, resulting in O(n^2) in the worst case. */

    void printTree(); // prints the whole tree
    /* This method uses printSubTree, which recursively traverses the tree. In the worst case,
     it will visit all nodes, resulting in O(n). */

    void createJson(); // creates a json file of the tree in Breadth first order
    /* This method traverses the entire tree while creating a JSON representation, resulting in O(n). */
};