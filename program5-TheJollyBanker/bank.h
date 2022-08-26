#ifndef BANK_H
#define BANK_H
#include <iostream>
#include <fstream>
#include <queue>
#include "transaction.h"
#include "bst.h"

using namespace std;

class Bank
{
public:

    Bank();
    ~Bank();

    void ReadFromFile(const string& file_name);
    void Display();

private:
    queue<Transaction> transactions_queue_;
    BST accounts;
    void ProcessTransaction();
};
#endif