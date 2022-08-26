#ifndef FUND_H_
#define FUND_H_
#include <iostream>
#include <vector>

using namespace std;

class Transaction;

class Fund
{
public:
    Fund();
    ~Fund();

    //setters
    void setName(string name);
    void setFund(int balance);
    void setLink(bool link); //see if there is a linked fund for this fund
    void setLinkedFund(int fund); //set the linked fund for this fund

    //getters
    string getName() const;
    int getBalance() const;
    //get the linked fund's index of this fund
    int getLinkedFund() const;
    int getHistoryCount() const;

    void DisplayHistory() const;
    bool AddHistory(Transaction transaction);
    //return if fund has linked fund
    bool HasLinked();
    void AddMoney(int amount);
    void ReduceMoney(int amount);

private:
    string fund_name_;
    int fund_balance_;
    int linked_fund_;
    bool has_linked_;
    vector<Transaction> history_;
};
#endif