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
    // the constructor initializes the "TreeNode" object with constant operations, resulting in O(1) time complexity.
};

class Tree
{
private:
    // Private Data Members
    TreeNode *root;

private:
    // Private Helper Functions
    int getSubSize(TreeNode *root); // returns the number of nodes in a sub tree
    /* this is a recursive method that traverses the entire subtree from a specific node to count all its children.
    if our specific node is the root, it visits each node once, hence O(n). */

    TreeNode *furthestNode(TreeNode *start); // return the furthest node to a node
    /* this method has a nested loop, resulting in O(n^2) in the worst case. */

    void printSubTree(TreeNode *root, int depth); // prints a sub tree
    /* this method recursively traverses the tree. In the worst case, it will visit all nodes, resulting in O(n). */

public:
    Tree(const string &greatAncestor);
    /* the constructor initializes the Tree object with a root containing the great ancestor,
     and the operations are constant, resulting in O(1) time complexity. */

    void addNode(const string &parentValue, const string &childValue); // adds a child to a parent
    /* at first this method use "findNode" to traverses tree and in all nodes in the tree (O(n)).
    after finding the parent node, it also iterates through all the children of the parent to check for duplicates, 
    which in the worst case could be O(n), but since this is typically much less than the total number of nodes,
    it's often considered O(d) where d is the number of children of a node. 
    however, the dominant factor is the findNode traversal, hence O(n). */

    TreeNode *findNode(const string &value, TreeNode *node); // returns the pointer to the node with an specific value in a sub tree
    /* this method is a recursive depth-first search that in the worst case may visit all nodes in the tree
    if the node is not found or if it's the last one to visit. Therefore, its complexity is O(n). */

    void delNode(const string &value); // adds a child to a parent
    /* this method use "findNode" function to find the node first,
    and then deleting it involves removing it from the parent's children vector, which is O(n). */

    int getSize(); // returns the number of nodes in the tree
    /* it calls "getSubSize", which traverses the entire tree to count all nodes,
    thus touching each node exactly once. This results in a complexity of O(n). */

    int findHeight(); // returns the height of the tree
    /* both of "findHeight" and "findSubHeight" methods potentially traverse the entire tree 
    in the case where the tree is highly unbalanced (e.g., a linked list shape).
    even though the "findSubHeight" is called recursively, each call only traverses the subtree of a given node, 
    but in the worst case, this can still involve visiting all nodes. */

    int findSubHeight(const string &value); // returns the height of the subtree

    bool isAncestor(const string &ancestor, const string &descendant); // returns whether one is the ancestor of the other
    /* this method uses "findNode" twice. The first call to locate the ancestor is O(n),
    and the second call to find the descendant from the ancestor could be another O(n) operation in the worst case,
    leading to a complexity of O(n).*/
    
    bool areSiblings(const string &person1, const string &person2); // returns whether they are siblings
    /* this method calls "findNode" (O(n)) and then possibly iterates over all children of the parent node, which is O(c).
    since O(n) is the dominant factor, the overall complexity is O(n). */

    bool areCousins(const string &person1, const string &person2); // returns whether they are siblings
    /* this method calls "findNode" twice (2*O(n)), and then compares the depths and parents of the two nodes.
    the dominant term is the findNode calls, so the overall complexity is O(n). */

    TreeNode *lowestCommonAncestor(const string &person1, const string &person2); // returns the lowest common ancestor
    /* this method calls findNode twice (2*O(n)), then potentially traverses up the tree from each node until it finds the common ancestor.
    In the worst case, this could traverse nearly the entire tree (e.g., if the tree is a linked list), so the complexity is O(n). */
    
    vector<TreeNode *> diameter(); // returns the tree diameter
    /* This method uses furthestNode, which has a nested loop, resulting in O(n^2) in the worst case. */

    void printTree(); // prints the whole tree
    /* this method performs a simple traversal of the entire tree, calling "printSubTree" recursively for each child node.
    Each node is visited and printed once, resulting in O(n). */

    void createJson(); // creates a json file of the tree in breadth first order
    /* This method traverses the entire tree while creating a JSON representation, resulting in O(n). */
};