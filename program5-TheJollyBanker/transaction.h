#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <sstream>
#include <queue>
#include <string>
#include "account.h"
#include "bst.h"

using namespace std;

namespace DefaultValue
{
    static const char Character = '!';
    static string const String = "!";
    static const int Number = -1;
}

enum TransactionType : char
{
    Open = 'O',
    Deposit = 'D',
    Withdraw = 'W',
    Transfer = 'T',
    History = 'A',
    HistoryFund = 'F'
};

class Transaction
{
    friend ostream& operator<<(ostream& stream, const Transaction&);

public:
    Transaction();
    ~Transaction();

    //getters
    string getFirst() const;
    string getLast() const;
    //char getType() const;
    int getID() const;
    int getTargetID() const;

    //setters
    void setType(char);
    void setAmount(int);
    void setData(string&);
    void setFund(int);

    //use function
    bool Open(BST& accounts, Account* a_account);
    bool Deposit(Account* account);
    bool Withdraw(Account* account);
    bool Transfer(Account* account, Account* target);
    bool History(Account* account);
    bool HistoryFund(Account* account);
    bool Process(BST& accounts);

private:
    char transaction_type_;
    string first_name, last_name;
    int account_id_, fund_;
    int to_account_, to_fund_;
    int amount_;
    bool isFailed;
    string command;

    //tokenize input string
    vector<string> words;

    //check if input data valid
    bool CheckData();
};
#endif