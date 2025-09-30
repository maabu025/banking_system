#include "Account.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// Default constructor
Account::Account() {
    accountNumber = 0;
    accountHolder = "";
    balance = 0.0;
    accountType = "Savings";
}

// Parameterized constructor
Account::Account(int accNum, string holder, double bal, string type) {
    accountNumber = accNum;
    accountHolder = holder;
    balance = bal;
    accountType = type;
}

// Getters
int Account::getAccountNumber() const {
    return accountNumber;
}

string Account::getAccountHolder() const {
    return accountHolder;
}

double Account::getBalance() const {
    return balance;
}

string Account::getAccountType() const {
    return accountType;
}

// Setters
void Account::setAccountHolder(string holder) {
    accountHolder = holder;
}

void Account::setAccountType(string type) {
    accountType = type;
}

// Deposit money
bool Account::deposit(double amount) {
    if (amount <= 0) {
        cout << "Invalid amount! Must be greater than 0." << endl;
        return false;
    }
    balance += amount;
    cout << "Deposit successful! New balance: $" << fixed << setprecision(2) << balance << endl;
    return true;
}

// Withdraw money
bool Account::withdraw(double amount) {
    if (amount <= 0) {
        cout << "Invalid amount! Must be greater than 0." << endl;
        return false;
    }
    if (amount > balance) {
        cout << "Insufficient funds! Current balance: $" << fixed << setprecision(2) << balance << endl;
        return false;
    }
    balance -= amount;
    cout << "Withdrawal successful! New balance: $" << fixed << setprecision(2) << balance << endl;
    return true;
}

// Display account details
void Account::displayAccount() const {
    cout << "\n========================================" << endl;
    cout << "           ACCOUNT DETAILS              " << endl;
    cout << "========================================" << endl;
    cout << "Account Number  : " << accountNumber << endl;
    cout << "Account Holder  : " << accountHolder << endl;
    cout << "Account Type    : " << accountType << endl;
    cout << "Balance         : $" << fixed << setprecision(2) << balance << endl;
    cout << "========================================\n" << endl;
}

// Convert account to string for file storage
string Account::toFileString() const {
    stringstream ss;
    ss << accountNumber << "," << accountHolder << "," << balance << "," << accountType;
    return ss.str();
}

// Create account from file string
Account Account::fromFileString(const string& line) {
    stringstream ss(line);
    string token;
    int accNum;
    string holder, type;
    double bal;

    getline(ss, token, ',');
    accNum = stoi(token);

    getline(ss, holder, ',');

    getline(ss, token, ',');
    bal = stod(token);

    getline(ss, type, ',');

    return Account(accNum, holder, bal, type);
}