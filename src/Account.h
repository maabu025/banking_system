#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
using namespace std;

class Account {
private:
    int accountNumber;
    string accountHolder;
    double balance;
    string accountType;

public:
    // Constructors
    Account();
    Account(int accNum, string holder, double bal, string type);

    // Getters
    int getAccountNumber() const;
    string getAccountHolder() const;
    double getBalance() const;
    string getAccountType() const;

    // Setters
    void setAccountHolder(string holder);
    void setAccountType(string type);

    // Banking operations
    bool deposit(double amount);
    bool withdraw(double amount);
    void displayAccount() const;

    // File operations
    string toFileString() const;
    static Account fromFileString(const string& line);
};

#endif