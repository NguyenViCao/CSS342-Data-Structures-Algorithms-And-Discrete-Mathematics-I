#include "account.h"
#include "transaction.h"

Account::Account()
{
    first_name_ = DefaultValue::String;
    last_name_ = DefaultValue::String;
    id_ = DefaultValue::Number;
    setFunds();
}

Account::Account(string firstName, string lastName, int id)
{
    first_name_ = firstName;
    last_name_ = lastName;
    id_ = id;
    setFunds();
}

Account::~Account()
{
}

void Account::setFunds()
{
    funds_[0].setName("Money Market");
    funds_[0].setLink(true);
    funds_[0].setLinkedFund(1);
    funds_[1].setName("Prime Money Market");
    funds_[1].setLink(true);
    funds_[1].setLinkedFund(0);
    funds_[2].setName("Long-Term Bond");
    funds_[2].setLink(true);
    funds_[2].setLinkedFund(3);
    funds_[3].setName("Short-Term Bond");
    funds_[3].setLink(true);
    funds_[3].setLinkedFund(2);
    funds_[4].setName("500 Index Fund");
    funds_[5].setName("Capital Value Fund");
    funds_[6].setName("Growth Equity Fund");
    funds_[7].setName("Growth Index Fund");
}

bool Account::setData(const Transaction& transaction)
{
    first_name_ = transaction.getFirst();
    last_name_ = transaction.getLast();
    id_ = transaction.getID();
    return true;
}

string Account::getFirstName() const
{
    return first_name_;
}

string Account::getLastName() const 
{
    return last_name_;
}

int Account::getID() const
{
    return id_;
}

string Account::getName() const {
    return first_name_ + " " + last_name_;
}

Fund Account::getFund(const int& index) const {
    return funds_[index];
}

bool Account::AddFund(int index, int amount)
{
    funds_[index].AddMoney(amount);
    return true;
}

bool Account::AddHistory(Transaction transaction, int index)
{
    return funds_[index].AddHistory(transaction);
}

void Account::DisplayFundHistory(const int& index) const
{
    cout << funds_[index].getName() << ": $" << funds_[index].getBalance() << endl;
    funds_[index].DisplayHistory();
}

void Account::DisplayAccountHistory() const
{
    for (int index = 0; index < 10; index++)
    {
        if (funds_[index].getHistoryCount() > 0)
        {
            cout << funds_[index].getName() << ": $" << funds_[index].getBalance() << endl;
            funds_[index].DisplayHistory();
        }
    }
}

bool Account::ReduceFund(Transaction* transaction, int index, int amount)
{

    //valid transaction
    if (funds_[index].getBalance() >= amount)
    {
        funds_[index].ReduceMoney(amount);
        return true;
    }

    //inbalance amount, use linked funds to cover 
    if (funds_[index].getBalance() < amount)
    {
        int remaining = amount - funds_[index].getBalance();
        // use the linked fund to cover the remaining
        if (funds_[index].HasLinked() && funds_[funds_[index].getLinkedFund()].getBalance() >= remaining)
        {
            transaction->setAmount(funds_[index].getBalance());                 //adjust the amount taken from targeted fund
            funds_[index].setFund(0);

            funds_[funds_[index].getLinkedFund()].ReduceMoney(remaining);       //take remaining from linked fund
            Transaction RemainTransaction = *transaction;
            RemainTransaction.setAmount(remaining);
            RemainTransaction.setFund(funds_[index].getLinkedFund());
            AddHistory(RemainTransaction, funds_[index].getLinkedFund());       //add history transaction of the remaining for linked fund

            return true;
        }
    }
    return false;
}

bool Account::operator<(const Account& other) const
{
    return id_ < other.id_;
}

bool Account::operator>(const Account& other) const
{
    return id_ > other.id_;
}

bool Account::operator==(const Account& other) const
{
    return id_ == other.id_;
}

bool Account::operator!=(const Account& other) const
{
    return id_ != other.id_;
}

ostream& operator<<(ostream& stream, const Account& account)
{
    stream << account.first_name_ << " " << account.last_name_ << " Account ID: " << account.id_ << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << "  " << account.getFund(i).getName() << ": $" << account.getFund(i).getBalance() << endl;
    }
    return stream;
}