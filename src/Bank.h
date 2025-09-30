#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include <vector>
#include <string>

using namespace std;

class Bank {
private:
    vector<Account> accounts;
    int nextAccountNumber;
    string dataFile;

    void loadAccounts();
    void saveAccounts();

public:
    Bank();
    ~Bank();

    void createAccount();
    void deposit();
    void withdraw();
    void checkBalance();
    void viewAllAccounts();
    void deleteAccount();
    void updateAccount();
    
    Account* findAccount(int accountNumber);
    int generateAccountNumber();
};

#endif