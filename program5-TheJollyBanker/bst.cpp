#include "bst.h"

BST::BST()
{
	root = nullptr;
}

BST::~BST()
{
	Empty();
}

bool BST::Insert(Account* account)
{
	return InsertAccount(root, account);
}

bool BST::InsertAccount(Node*& node, Account* account)
{
    //empty node
    if (node == nullptr)
    {
        node = new Node;
        node->pAcct = account;
        node->left = nullptr;
        node->right = nullptr;
        return true;
    }
    else if (*account < *node->pAcct)
    {
        return InsertAccount(node->left, account);
    }
    else if (*account > * node->pAcct)
    {
        return InsertAccount(node->right, account);
    }
    else
    {
        return false;
    }
}

//get a specific account
bool BST::Retrieve(const int& id, Account*& account) const
{
    if (root == nullptr)
    {
        account = nullptr;
        return false;
    }
    else
    {
        return RetrieveAccount(root, id, account);
    }
}

bool BST::RetrieveAccount(Node* node, const int& id, Account*& account) const
{
    if (node == nullptr)
    {
        account = nullptr;
        return false;
    }

    if (id < node->pAcct->getID())
    {
        return RetrieveAccount(node->left, id, account);
    }
    else if (id > node->pAcct->getID())
    {
        return RetrieveAccount(node->right, id, account);
    }
    //found the account
    else
    {
        account = node->pAcct;
        return true;
    }
}

void BST::Display() const
{
    DisplayAccount(this->root);
}

void BST::DisplayAccount(Node* node) const
{
    if (node != nullptr)
    {
        DisplayAccount(node->left);
        cout << *node-> pAcct << endl;
        DisplayAccount(node->right);
    }
}

void BST::Empty()
{
    if (root != nullptr)
    {
        EmptyAccount(root);
        root = nullptr;
    }
}

void BST::EmptyAccount(Node*& node)
{
    if (node != nullptr)
    {
        EmptyAccount(node->left);
        EmptyAccount(node->right);
        delete node->pAcct;
        delete node;
    }
}

bool BST::isEmpty() const
{
    return root == nullptr;
}