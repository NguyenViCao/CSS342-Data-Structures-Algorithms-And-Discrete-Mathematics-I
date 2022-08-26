#ifndef VENDING_BANK_H_
#define VENDING_BANK_H_
#include<string>
using namespace std;

// id_ is a unique identifier for the VendingBankmuch like a serial number
class VendingBank
{
public:
	//constructor
	VendingBank();
	VendingBank(int id);
	VendingBank(int id, double dollars, double quarters, double dimes, double nickles, double pennies);

	//getters-setters
	int id() const;
	int dollars() const;
	int quarters() const;
	int dimes() const;
	int nickles() const;
	int pennies() const;
	double price() const;
	double payment();
	double change();
	

	//Action (verb)
	bool IsEmpty(int item_);
	bool ReturnItem();										// if customer wants to return the item
	int AddPayment();
	double CalculatePayment();
	double CalculateChange(int item_);						// calculate change for the return item
	double CalculateReturn(double cost_, double received_);

	//overloads for comparison
	bool operator==(VendingBank& vending_bank) const;
	bool operator!=(VendingBank& vending_bank) const;
	VendingBank operator+(VendingBank& vending_bank) const;
	VendingBank& operator+=(VendingBank& vending_bank);
	VendingBank operator-(VendingBank& vending_bank) const;
	VendingBank& operator-=(VendingBank& vending_bank);

	//overloads for streams
	friend ostream& operator<<(ostream& stream, const VendingBank& vending_bank);
	friend istream& operator>>(istream& stream, VendingBank& vending_bank);

private:
	int id_;
	int dollars_, quarters_, dimes_, nickkles_, pennies_;
	int item_;
	double item_price_;
	double total_;
	double change_;
};
#endif