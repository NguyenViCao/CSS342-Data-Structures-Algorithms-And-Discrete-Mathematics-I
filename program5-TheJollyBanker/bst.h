#ifndef BST_H_
#define BST_H_
#include <iostream>
#include "account.h"

using namespace std;

class BST
{
public:
	BST();
	~BST();

	bool Insert(Account* account);

    // retrieve object, first parameter is the ID of the account 
    // second parameter holds pointer to found object, NULL if not found 
    bool Retrieve(const int&, Account*&) const;

    // displays the contents of a tree to cout 
    void Display() const;
    void Empty();
    bool isEmpty() const;

private:
    struct Node
    {
        Account* pAcct;
        Node* right;
        Node* left;
    };
    Node* root;
    bool InsertAccount(Node*& node, Account* account);
    bool RetrieveAccount(Node* node, const int& id, Account*& account) const;
    void DisplayAccount(Node* node) const;
    void EmptyAccount(Node*& node);
};
#endif