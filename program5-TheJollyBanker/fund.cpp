#include "fund.h"
#include "transaction.h"

Fund::Fund()
{
    fund_balance_ = 0;
    linked_fund_ = -1;
    has_linked_ = false;
}

Fund::~Fund() 
{
}

void Fund::setName(string name)
{
    fund_name_ = name;
}

void Fund::setFund(int balance)
{
    fund_balance_ = balance;
}

void Fund::setLink(bool link)
{
    has_linked_ = link;
}

void Fund::setLinkedFund(int fund)
{
    linked_fund_ = fund;
}

string Fund::getName() const
{
    return fund_name_;
}

int Fund::getBalance() const
{
    return fund_balance_;
}

//get the linked fund's index of the fund
int Fund::getLinkedFund() const
{
    return linked_fund_;
}

int Fund::getHistoryCount() const {
    return history_.size();
}

void Fund::DisplayHistory() const
{
    for (int i = 0; i < history_.size(); i++) {
        cout << "  " << history_.at(i) << endl;
    }
}

bool Fund::AddHistory(Transaction transaction)
{
    history_.push_back(transaction);
    return true;
}

//return if fund has linked
bool Fund::HasLinked()
{
    return has_linked_;
}

void Fund::AddMoney(int amount)
{
    fund_balance_ += amount;
}

void Fund::ReduceMoney(int amount)
{
    fund_balance_ -= amount;
}