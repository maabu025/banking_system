#include "Bank.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// Constructor
Bank::Bank() {
    nextAccountNumber = 1001;
    dataFile = "../data/accounts.txt";
    loadAccounts();
}

// Destructor
Bank::~Bank() {
    saveAccounts();
}

// Load accounts from file
void Bank::loadAccounts() {
    ifstream file(dataFile);
    if (!file.is_open()) {
        return; // File doesn't exist yet
    }

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            Account acc = Account::fromFileString(line);
            accounts.push_back(acc);
            if (acc.getAccountNumber() >= nextAccountNumber) {
                nextAccountNumber = acc.getAccountNumber() + 1;
            }
        }
    }
    file.close();
}

// Save accounts to file
void Bank::saveAccounts() {
    ofstream file(dataFile);
    if (!file.is_open()) {
        cout << "Error: Could not save accounts!" << endl;
        return;
    }

    for (const auto& acc : accounts) {
        file << acc.toFileString() << endl;
    }
    file.close();
}

// Generate new account number
int Bank::generateAccountNumber() {
    return nextAccountNumber++;
}

// Find account by account number
Account* Bank::findAccount(int accountNumber) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accountNumber) {
            return &acc;
        }
    }
    return nullptr;
}

// Create new account
void Bank::createAccount() {
    string name, type;
    double initialDeposit;

    cout << "\n--- Create New Account ---" << endl;
    cout << "Enter account holder name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter account type (Savings/Current): ";
    getline(cin, type);

    cout << "Enter initial deposit: $";
    cin >> initialDeposit;

    if (initialDeposit < 0) {
        cout << "Invalid initial deposit!" << endl;
        return;
    }

    int accNum = generateAccountNumber();
    Account newAccount(accNum, name, initialDeposit, type);
    accounts.push_back(newAccount);

    cout << "\nAccount created successfully!" << endl;
    cout << "Your account number is: " << accNum << endl;
    saveAccounts();
}

// Deposit money
void Bank::deposit() {
    int accNum;
    double amount;

    cout << "\n--- Deposit Money ---" << endl;
    cout << "Enter account number: ";
    cin >> accNum;

    Account* acc = findAccount(accNum);
    if (acc == nullptr) {
        cout << "Account not found!" << endl;
        return;
    }

    cout << "Enter amount to deposit: $";
    cin >> amount;

    if (acc->deposit(amount)) {
        saveAccounts();
    }
}

// Withdraw money
void Bank::withdraw() {
    int accNum;
    double amount;

    cout << "\n--- Withdraw Money ---" << endl;
    cout << "Enter account number: ";
    cin >> accNum;

    Account* acc = findAccount(accNum);
    if (acc == nullptr) {
        cout << "Account not found!" << endl;
        return;
    }

    cout << "Enter amount to withdraw: $";
    cin >> amount;

    if (acc->withdraw(amount)) {
        saveAccounts();
    }
}

// Check balance
void Bank::checkBalance() {
    int accNum;

    cout << "\n--- Check Balance ---" << endl;
    cout << "Enter account number: ";
    cin >> accNum;

    Account* acc = findAccount(accNum);
    if (acc == nullptr) {
        cout << "Account not found!" << endl;
        return;
    }

    acc->displayAccount();
}

// View all accounts
void Bank::viewAllAccounts() {
    if (accounts.empty()) {
        cout << "\nNo accounts found!" << endl;
        return;
    }

    cout << "\n========================================" << endl;
    cout << "          ALL BANK ACCOUNTS             " << endl;
    cout << "========================================" << endl;
    cout << left << setw(10) << "Acc No." 
         << setw(20) << "Holder" 
         << setw(12) << "Type" 
         << setw(12) << "Balance" << endl;
    cout << "----------------------------------------" << endl;

    for (const auto& acc : accounts) {
        cout << left << setw(10) << acc.getAccountNumber()
             << setw(20) << acc.getAccountHolder()
             << setw(12) << acc.getAccountType()
             << "$" << fixed << setprecision(2) << acc.getBalance() << endl;
    }
    cout << "========================================\n" << endl;
}

// Delete account
void Bank::deleteAccount() {
    int accNum;

    cout << "\n--- Delete Account ---" << endl;
    cout << "Enter account number: ";
    cin >> accNum;

    auto it = find_if(accounts.begin(), accounts.end(),
                      [accNum](const Account& acc) {
                          return acc.getAccountNumber() == accNum;
                      });

    if (it == accounts.end()) {
        cout << "Account not found!" << endl;
        return;
    }

    cout << "Are you sure you want to delete this account? (y/n): ";
    char confirm;
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        accounts.erase(it);
        cout << "Account deleted successfully!" << endl;
        saveAccounts();
    } else {
        cout << "Deletion cancelled." << endl;
    }
}

// Update account
void Bank::updateAccount() {
    int accNum;

    cout << "\n--- Update Account ---" << endl;
    cout << "Enter account number: ";
    cin >> accNum;

    Account* acc = findAccount(accNum);
    if (acc == nullptr) {
        cout << "Account not found!" << endl;
        return;
    }

    cout << "\nWhat do you want to update?" << endl;
    cout << "1. Account Holder Name" << endl;
    cout << "2. Account Type" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    cin.ignore();
    if (choice == 1) {
        string newName;
        cout << "Enter new name: ";
        getline(cin, newName);
        acc->setAccountHolder(newName);
        cout << "Name updated successfully!" << endl;
    } else if (choice == 2) {
        string newType;
        cout << "Enter new account type: ";
        getline(cin, newType);
        acc->setAccountType(newType);
        cout << "Account type updated successfully!" << endl;
    } else {
        cout << "Invalid choice!" << endl;
        return;
    }

    saveAccounts();
}