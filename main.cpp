#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class BankAccount {
    int acNo;
    string name;
    double balance;
public:
    void createAccount() {
        cout << "\nEnter Account Number: "; cin >> acNo;
        cout << "Enter Account Holder Name: "; cin.ignore(); getline(cin, name);
        cout << "Enter Initial Deposit Amount: "; cin >> balance;
        cout << "\n[Success] Account Created Successfully!\n";
    }
    void displayAccount() const {
        cout << left << setw(15) << acNo << setw(25) << name << "$" << balance << endl;
    }
    int getAccountNo() const { return acNo; }
};

void createNewAccount() {
    BankAccount ac;
    ac.createAccount();
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(BankAccount));
    outFile.close();
}

void displayAllAccounts() {
    BankAccount ac;
    ifstream inFile("accounts.dat", ios::binary);
    if (!inFile) {
        cout << "\n[Error] No accounts found!\n";
        return;
    }
    cout << "\n====================================================\n";
    cout << left << setw(15) << "Acc No." << setw(25) << "Name" << "Balance" << endl;
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount))) {
        ac.displayAccount();
    }
    inFile.close();
}

int main() {
    int choice;
    while (true) {
        cout << "\n--- NEXT-GEN BANKING SYSTEM ---" << endl;
        cout << "1. Open New Account\n2. View All Accounts\n3. Exit\n";
        cout << "Enter Choice: "; cin >> choice;
        if (choice == 1) createNewAccount();
        else if (choice == 2) displayAllAccounts();
        else if (choice == 3) break;
        else cout << "\nInvalid Choice!\n";
    }
    return 0;
}
