#include "bank.h"
#include <string>
#include <fstream>

using namespace std;

Bank::Bank()
{
}

Bank::~Bank()
{
}

void Bank::ReadFromFile(const string& file_name)
{
    ifstream file;
    file.open(file_name);

    if (!file.is_open())
    {
        cout << "Could not read file " << endl;
    }

    string transactionInfo;

    while (!file.eof())
    {

        //read each line
        getline(file, transactionInfo, '\n');

        //create new transaction
        Transaction* a_stransaction = new Transaction();

        a_stransaction->setData(transactionInfo);

        //put transaction in queue
        transactions_queue_.push(*a_stransaction);

        delete a_stransaction;
    }
    file.close();
    ProcessTransaction();
}

void Bank::ProcessTransaction()
{

    // process all transaction until queue empty
    while (!transactions_queue_.empty())
    {
        transactions_queue_.front().Process(accounts);
        transactions_queue_.pop();
    }
}


void Bank::Display()
{
    cout << endl;
    cout << "FINAL BALANCES:" << endl;
    accounts.Display();
}