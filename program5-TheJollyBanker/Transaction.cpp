#include "transaction.h"

Transaction::Transaction()
{
    transaction_type_ = DefaultValue::Character;
    first_name = DefaultValue::String;
    last_name = DefaultValue::String;
    account_id_ = DefaultValue::Number, fund_ = DefaultValue::Number;
    to_account_ = DefaultValue::Number, to_fund_ = DefaultValue::Number;
    amount_ = DefaultValue::Number;
    isFailed = false;
}

Transaction::~Transaction() 
{
};

void Transaction::setType(char ch)
{
    transaction_type_ = ch;
}

void Transaction::setAmount(int amount)
{
    amount_ = amount;
}
void Transaction::setFund(int fund)
{
    fund_ = fund;
}

void Transaction::setData(string& info)
{
    this->command = info;

    //tokenizing string
    stringstream ss(info);
    string word;

    while (ss >> word)
    {
        words.push_back(word);
    }
}

bool Transaction::CheckData()
{
    //bad input
    if (words.size() == 0 || words.size() > 4)
    {
        return false;
    }
    transaction_type_ = (char)words.at(0).at(0);

    // Check for valid information
    if (transaction_type_ == TransactionType::Open)
    {
        if (words.size() != 4)
        {
            cout << "ERROR: Incorrect input. Transaction refused!" << endl;
            return false;
        }
        first_name = words.at(3);
        last_name = words.at(2);
        account_id_ = stoi(words.at(1));
        return true;
    }

    else if (transaction_type_ == TransactionType::Deposit || transaction_type_ == TransactionType::Withdraw)
    {
        if (words.size() != 4 || stoi(words.at(2)) < 0 || stoi(words.at(2)) > 7)
        {
            cout << "ERROR: Transaction \"";
            for (int i = 0; i < words.size(); i++)
            {
                cout << words.at(i) << " ";
            }
            cout << "\" failed to process. Transaction information missing." << endl;
            return false;
        }
        fund_ = stoi(words.at(2));
        account_id_ = stoi(words.at(1));
        amount_ = stoi(words.at(3));
        return true;
    }

    else if (transaction_type_ == TransactionType::Transfer)
    {
        if (words.size() != 6 || stoi(words.at(2)) < 0 || stoi(words.at(2)) > 7
            || stoi(words.at(4)) < 0 || stoi(words.at(4)) > 7)
        {
            cout << "ERROR: Transaction \"";
            for (int i = 0; i < words.size(); i++)
            {
                cout << words.at(i) << " ";
            }
            cout << "\" failed to process. Transaction information missing." << endl;
            return false;
        }
        fund_ = stoi(words.at(2));
        account_id_ = stoi(words.at(1));
        amount_ = stoi(words.at(5));
        to_fund_ = stoi(words.at(4));
        to_account_ = stoi(words.at(3));
        return true;
    }

    else if (transaction_type_ == TransactionType::History)
    {
        if (words.size() != 2)
        {
            cout << "ERROR: Transaction \"";
            for (int i = 0; i < words.size(); i++)
            {
                cout << words.at(i) << " ";
            }
            cout << "\" failed to process. Transaction information missing." << endl;
            return false;
        }
        account_id_ = stoi(words.at(1));
        return true;
    }

    else if (transaction_type_ == TransactionType::HistoryFund)
    {
        if (words.size() != 3)
        {
            cout << "ERROR: Transaction \"";
            for (int i = 0; i < words.size(); i++)
            {
                cout << words.at(i) << " ";
            }
            cout << "\" failed to process. Transaction information missing." << endl;
            return false;
        }
        account_id_ = stoi(words.at(1));
        fund_ = stoi(words.at(2));
        return true;
    }

    // not defined type
    cout << "ERROR: Transaction \"";
    for (int i = 0; i < words.size(); i++)
    {
        cout << words.at(i) << " ";
    }
    cout << "\" cannot process. Missing transaction information." << endl;
    return false;
}

int Transaction::getID() const
{
    return account_id_;
}

int Transaction::getTargetID() const
{
    return to_account_;
}

string Transaction::getFirst() const
{
    return first_name;
}

string Transaction::getLast() const
{
    return last_name;
}

bool Transaction::Process(BST& accounts)
{
    //invalid transaction
    if (!CheckData())
    {
        return false;
    }
    Account* check_account;

    //valid transactionS
    if (transaction_type_ == TransactionType::Open)
    {
        //invalid number
        if (account_id_ < 0 || account_id_ > 9999)
        {
            cout << "ERROR: Invalid ID number \"" << account_id_ << "\". Can not open account" << endl;
            return false;
        }
        Account* a_account = new Account();    // create new account
        a_account->setData(*this);

        // account already exist, delete duplicate
        if (!Open(accounts, a_account))
        {
            delete a_account;
            a_account = nullptr;
            return false;
        }
        return true;
    }

    //check for valid id
    if (!accounts.Retrieve(account_id_, check_account))
    {
        cout << "ERROR: Account " << account_id_ << " not found. Cannot retrieve!" << endl;
        return false;
    }

    if (transaction_type_ == TransactionType::Deposit)
    {
        return Deposit(check_account);
    }

    else if (transaction_type_ == TransactionType::Withdraw)
    {
        return Withdraw(check_account);
    }

    else if (transaction_type_ == TransactionType::Transfer)
    {
        Account* check_target;
        // check valid target id
        if (accounts.Retrieve(to_account_, check_target) == false)
        {
            cout << "ERROR: Account " << to_account_ << " not found. Cannot transfer!" << endl;
            return false;
        }
        return Transfer(check_account, check_target);
    }

    else if (transaction_type_ == TransactionType::History)
    {
        return History(check_account);
    }

    else if (transaction_type_ == TransactionType::HistoryFund)
    {
        return HistoryFund(check_account);
    }

    else
        return false;
}

bool Transaction::Open(BST& accounts, Account* a_account)
{
    if (!accounts.Insert(a_account))
    {
        //duplicate account
        cout << "ERROR: Account " << account_id_ << " is already taken. Cannot open!" << endl;
        return false;
    }
    return true;
}

bool Transaction::Deposit(Account* account)
{
    if (amount_ < 0)
    {
        cout << "ERROR: Transaction \"" << *this << "\" request negative amount of money. Cannot deposit!" << endl;

        isFailed = true;
        account->AddHistory(*this, fund_);
        return false;
    }

    //successful transaction
    if (account->AddFund(fund_, amount_))
    {
        account->AddHistory(*this, fund_);
        return true;
    }
    return false;
}

bool Transaction::Withdraw(Account* account)
{
    //negative amount
    if (amount_ < 0)
    {
        cout << "ERROR: Transaction \"" << *this << "\" request negative amount of money. Cannot withdraw!" << endl;

        isFailed = true;
        account->AddHistory(*this, fund_);
        return false;
    }

    //successful transaction
    if (account->ReduceFund(this, fund_, amount_))
    {
        account->AddHistory(*this, fund_);
        return true;
    }

    //failed transaction
    cout << "ERROR: Not enough funds to withdraw $" << amount_ << " from " <<
        account->getName() << " " << account->getFund(fund_).getName() << endl;

    isFailed = true;
    account->AddHistory(*this, fund_);
    return false;
}

bool Transaction::Transfer(Account* account, Account* target)
{
    if (amount_ < 0)
    {
        cout << "ERROR: Transaction \"" << *this << "\" request to transfer negative amount of money. Cannot transfer!" << endl;

        isFailed = true;
        account->AddHistory(*this, fund_);
        return false;
    }
    //transfer to same fund
    if (account_id_ == to_account_ && fund_ == to_fund_)
    {
        cout << "ERROR: Transaction \"" << *this << "\" is not valid. Cannot transfer!" << endl;

        isFailed = true;
        account->AddHistory(*this, fund_);
        return false;
    }

    //success transaction
    if (account->ReduceFund(this, fund_, amount_))
    {
        account->AddHistory(*this, fund_);

        // add history for targeted account
        target->AddFund(to_fund_, amount_);
        target->AddHistory(*this, to_fund_);
        return true;
    }

    //failed transaction
    cout << "ERROR: Not enough money to transfer $" << amount_ << " from " <<
        account->getName() << " " << account->getFund(fund_).getName() << " to " <<
        target->getName() << " " << target->getFund(fund_).getName() << endl;

    isFailed = true;
    account->AddHistory(*this, fund_);
    return false;
}

bool Transaction::History(Account* account)
{
    cout << endl;
    cout << "Transaction History for " << account->getName() << " by fund." << endl;
    account->DisplayAccountHistory();
    return true;
}

bool Transaction::HistoryFund(Account* account)
{
    cout << endl;
    cout << "Transaction History for " << account->getName() << " ";
    account->DisplayFundHistory(fund_);
    return true;
}

ostream& operator<<(ostream& stream, const Transaction& transaction)
{
    if (transaction.transaction_type_ == TransactionType::Open)
    {
        stream << transaction.transaction_type_ << " " << transaction.account_id_ << " " << transaction.last_name
            << " " << transaction.first_name;
    }

    else if (transaction.transaction_type_ == TransactionType::Deposit || transaction.transaction_type_ == TransactionType::Withdraw)
    {
        stream << transaction.transaction_type_ << " " << transaction.account_id_ << " " << transaction.fund_ << " " << transaction.amount_;
    }

    else if (transaction.transaction_type_ == TransactionType::Transfer)
    {
        stream << transaction.transaction_type_ << " " << transaction.account_id_ << " " << transaction.fund_ << " " << transaction.to_account_ << " "
            << transaction.to_fund_ << " " << transaction.amount_;
    }

    else if (transaction.transaction_type_ == TransactionType::History)
    {
        stream << transaction.transaction_type_ << " " << transaction.account_id_;
    }

    else if (transaction.transaction_type_ == TransactionType::HistoryFund)
    {
        stream << transaction.transaction_type_ << " " << transaction.account_id_ << " " << transaction.fund_;
    }
    // invalid type
    else
    {
        stream << transaction.command;
    }

    if (transaction.isFailed)
    {
        stream << " (Failed)";
    }
    return stream;
}