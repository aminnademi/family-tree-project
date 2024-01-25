#include <iostream>
#include "Tree.h"
#include "SHA-256Generator.h"

SHA256 sha256;

void Note()
{
    cout << "NOTE: Please pay attention to the case sensitivity and spacing in the names. "
         << "Even a slight difference, such as uppercase or lowercase letters or spaces, "
         << "can result in different hash values. Ensure accuracy to avoid errors in your task.\n";
}

void addFamilyMembers(Tree &tree, bool display) // for adding members to the tree
{
    cout << "Your family tree:\n";
    tree.printTree();
    cout << "Modifying the family tree:\n";
    if (display)
        Note();
        
    while (true)
    {
        string parent, child, parentHash, childHash;
        cout << "Enter the parent name (enter 'exit' to exit): ";
        getline(cin, parent);
        if (parent == "exit")
        {
            break;
        }
        cout << "Enter the child name: ";
        getline(cin, child);
        parentHash = sha256.calculateHash(parent);
        childHash = sha256.calculateHash(child);
        tree.addNode(parentHash, childHash);
    }

    cout << "Your family tree:\n";
    tree.printTree();
    tree.createJson();
}

void removeFamilyMembers(Tree &tree) // for removing members from the tree
{
    cout << "Your family tree:\n";
    tree.printTree();

    cout << "Modifying the family tree:\n";
    Note();
    while (true)
    {
        string individual, individualHash;
        cout << "Enter the individual name to remove (enter 'exit' to exit): ";
        getline(cin, individual);
        if (individual == "exit")
        {
            break;
        }
        individualHash = sha256.calculateHash(individual);
        tree.delNode(individualHash);
        cout << "Individual was removed\n";
    }

    cout << "Your family tree:\n";
    tree.printTree();
    tree.createJson();
}

void tools(Tree &tree) // menu of tree functionalities
{
    while (true)
    {
        cout << "1. Add more individuals\n"
             << "2. Remove individuals\n"
             << "3. Number of individuals\n"
             << "4. Number of generations\n"
             << "5. Ancestor check\n"
             << "6. Siblings check\n"
             << "7. Cousins check\n"
             << "8. Find lowest common ancestor\n"
             << "9. Find distance of the farthest descendant of a person\n"
             << "10. Find the furthest relatives\n"
             << "11. Print the family tree\n";
        cout << "Choose your task by entering 1 to 10 (enter 'exit' to exit):";
        string input;
        getline(cin, input);

        if (input == "exit")
        {
            cout << "Have a nice day!\n";
            return;
        }

        int choice = stoi(input);

        switch (choice)
        {
        case 1:
            addFamilyMembers(tree, true);
            break;

        case 2:
            removeFamilyMembers(tree);
            break;

        case 3:
            cout << tree.getSize() << "\n";
            break;

        case 4:
            cout << tree.findHeight() << "\n";
            break;

        case 5:
        {
            Note();
            string person1, person2, person1Hash, person2Hash;
            cout << "Enter the name of the ancestor: ";
            getline(cin, person1);
            cout << "Enter the name of the descendant: ";
            getline(cin, person2);
            person1Hash = sha256.calculateHash(person1);
            person2Hash = sha256.calculateHash(person2);
            if (tree.isAncestor(person1Hash, person2Hash))
                cout << "Yes! the first person is second person's ancestor\n";
            else
                cout << "No! the first person is not second person's ancestor\n";
        }
        break;

        case 6:
        {
            Note();
            string person1, person2, person1Hash, person2Hash;
            cout << "Enter the first person's name: ";
            getline(cin, person1);
            cout << "Enter the second person's name: ";
            getline(cin, person2);
            person1Hash = sha256.calculateHash(person1);
            person2Hash = sha256.calculateHash(person2);
            if (tree.areSiblings(person1Hash, person2Hash))
                cout << "Yes! They are siblings\n";
            else
                cout << "No! They are not siblings\n";
        }
        break;

        case 7:
        {
            Note();
            string person1, person2, person1Hash, person2Hash;
            cout << "Enter the first person's name: ";
            getline(cin, person1);
            cout << "Enter the second person's name: ";
            getline(cin, person2);
            person1Hash = sha256.calculateHash(person1);
            person2Hash = sha256.calculateHash(person2);
            if (tree.areCousins(person1Hash, person2Hash))
                cout << "Yes! They are cousins\n";
            else
                cout << "No! They are not cousins\n";
        }
        break;

        case 8:
        {
            Note();
            string person1, person2, person1Hash, person2Hash;
            cout << "Enter the first person's name: ";
            getline(cin, person1);
            cout << "Enter the second person's name: ";
            getline(cin, person2);
            person1Hash = sha256.calculateHash(person1);
            person2Hash = sha256.calculateHash(person2);
            cout << "'" << tree.lowestCommonAncestor(person1Hash, person2Hash)->data
                 << "' is their last common ancestor hash\n";
        }
        break;
        case 9:
        {
            int distance;
            string person, personHash;
            cout << "Enter the person's name: ";
            getline(cin, person);
            personHash = sha256.calculateHash(person);
            distance = tree.findSubHeight(personHash) - 1;
            if (distance != -1)
                cout << "The distance of the farthest descendant of this person is " << distance << "\n";
        }
        break;

        case 10:
        {
            vector<TreeNode *> print;
            print = tree.diameter();
            cout << "The furthest family members hash are '" << print[0]->data << "' and '" << print[1]->data << "'\n";
        }

        case 11:
            tree.printTree();
            break;

        default:
            cout << "Invalid input!\n";
            break;
        }
    }
}

Tree createTree() // creates a family tree by asking for the first member's name
{
    Note();
    cout << "Who is your first family member? \n";
    string name;
    getline(cin, name);
    string hash = sha256.calculateHash(name);
    return Tree(hash);
}

int main()
{
    Tree tree = createTree();
    addFamilyMembers(tree, false);
    tools(tree);
    return 0;
}