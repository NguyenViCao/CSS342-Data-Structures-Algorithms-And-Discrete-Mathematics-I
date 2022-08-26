#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <iostream>
#include <vector>
#include <string>
#include "fund.h"

using namespace std;

class Account
{
    friend ostream& operator<<(ostream& stream, const Account& account);

public:
    Account();
    Account(string firstName, string lastName, int id);
    ~Account();

    //setters
    void setFunds();
    bool setData(const Transaction& transaction);

    //getters
    string getName() const;
    string getFirstName() const;
    string getLastName() const;
    int getID() const;
    Fund getFund(const int& index) const;

    //add a amount of money to a fund
    bool AddFund(int index, int amount);
    //add transaction history for each fund
    bool AddHistory(Transaction transaction, int index);
    //display the fund's history of transactions
    void DisplayFundHistory(const int& index) const;
    //display whole account's history of transactions
    void DisplayAccountHistory() const;
    //reduce money from specific fund
    bool ReduceFund(Transaction* transaction, int index, int amount);

    // overloading operator
    bool operator<(const Account& other) const;
    bool operator>(const Account& other) const;
    bool operator==(const Account& other) const;
    bool operator!=(const Account& other) const;

private:
    string first_name_;
    string last_name_;
    int id_;
    Fund funds_[10];
};
#endif