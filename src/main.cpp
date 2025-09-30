#include <iostream>
#include "Bank.h"

using namespace std;

void displayMenu() {
    cout << "\n=======================================" << endl;
    cout << "       BANKING MANAGEMENT SYSTEM       " << endl;
    cout << "=======================================" << endl;
    cout << "1.  Create New Account" << endl;
    cout << "2.  Deposit Money" << endl;
    cout << "3.  Withdraw Money" << endl;
    cout << "4.  Check Balance" << endl;
    cout << "5.  View All Accounts" << endl;
    cout << "6.  Update Account" << endl;
    cout << "7.  Delete Account" << endl;
    cout << "8.  Exit" << endl;
    cout << "=======================================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Bank bank;
    int choice;

    cout << "\n*** Welcome to the Banking System ***\n" << endl;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                bank.createAccount();
                break;
            case 2:
                bank.deposit();
                break;
            case 3:
                bank.withdraw();
                break;
            case 4:
                bank.checkBalance();
                break;
            case 5:
                bank.viewAllAccounts();
                break;
            case 6:
                bank.updateAccount();
                break;
            case 7:
                bank.deleteAccount();
                break;
            case 8:
                cout << "\nThank you for using our Banking System!" << endl;
                cout << "Goodbye!\n" << endl;
                return 0;
            default:
                cout << "\nInvalid choice! Please try again." << endl;
        }
    }

    return 0;
}