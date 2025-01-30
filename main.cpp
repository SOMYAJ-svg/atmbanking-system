//ATM BANKING SYSTEM
#include<iostream>
#include<vector>
#include<limits>
#include<string>
using namespace std;

class BANKACC {
protected:
    string name;
    int accno;
    float balance;
    vector<string> transactions;

public:
    BANKACC(string n = "SOMYA", int accno = 12215709, float balance = 100000) {
        this->name = n;
        this->accno = accno;
        this->balance = balance;
        cout << "\nATM BANKING ME AAPKA SWAGAT HAI, " << name << "!\n";
    }

    ~BANKACC() {
        cout << "\nATM BANKING ISTEMAAL KRNE KE LIYE SHUKRIYA!\n";
    }

    void recordTransaction(string msg) {
        if (transactions.size() == 5) {
            transactions.erase(transactions.begin());
        }
        transactions.push_back(msg);
    }

    void depositpaisa(float amt) {
        if (amt > 0) {
            balance += amt;
            cout << "Rs. " << amt << " deposited successfully!\n";
            recordTransaction("DEPOSITED: " + to_string(amt));
        } else {
            cout << "Invalid amount!\n";
        }
    }

    void withdrawpaisa(float amt) {
        if (amt > 0 && balance >= amt) {
            balance -= amt;
            cout << "Rs. " << amt << " withdrawn successfully!\n";
            recordTransaction("WITHDRAWN: " + to_string(amt));
        } else {
            cout << "Insufficient balance!\n";
        }
    }

    void displaydetails() {
        cout << "\n---- Account Details ----\n";
        cout << "Account Holder Name: " << name << endl;
        cout << "Account Number: " << accno << endl;
        cout << "Account Balance: " << balance << endl;
        cout << "Transaction History:\n";
        for (int i = 0; i < transactions.size(); i++) {
            cout << i + 1 << ". " << transactions[i] << endl;
        }
        cout << "\n------------\n";
    }

    void miniStatement() {
        cout << "\n---- Mini Statement ----\n";
        int start = max(0, (int)transactions.size() - 5);
        for (int i = start; i < transactions.size(); i++) {
            cout << i + 1 << ". " << transactions[i] << endl;
        }
        if (transactions.empty()) {
            cout << "No transactions!\n";
        }
        cout << "\n------------\n";
    }
};

class SavingsAcc : public BANKACC {
protected:
    float savings;

public:
    SavingsAcc(string name, int accno, float balance) : BANKACC(name, accno, balance) {
        savings = 0;
    }

    void depositSavings(float amt) {
        if (amt > 0 && amt <= balance) {
            savings += amt;
            balance -= amt;
            cout << "Rs. " << amt << " transferred to savings successfully!\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    void withdrawSavings(float amt) {
        if (amt > 0 && savings >= amt) {
            savings -= amt;
            cout << "Rs. " << amt << " withdrawn from savings successfully!\n";
        } else {
            cout << "Invalid amount!\n";
        }
    }

    void displaySavings() {
        cout << "\nSavings Account Holder Name: " << name << endl;
        cout << "Account Number: " << accno << endl;
        cout << "Account Balance: " << balance << endl;
        cout << "Savings Balance: " << savings << endl;
        cout << "\n------------\n";
    }
};

class ATM : public SavingsAcc {
private:
    int pin;

public:
    ATM(string name, int accno, float balance, int pin) : SavingsAcc(name, accno, balance) {
        this->pin = pin;
    }

    bool authenticate() {
        int pin1, attempts = 3;
        while (attempts > 0) {
            cout << "Enter your ATM PIN: ";
            cin >> pin1;
            if (pin1 == pin) {
                cout << "Authentication successful!\n";
                return true;
            } else {
                attempts--;
                cout << "Invalid PIN! Remaining attempts: " << attempts << endl;
            }
        }
        cout << "Authentication failed! PIN blocked!\n";
        return false;
    }
    void withdrawpaisa(float amt)  {
    if (amt > 0 && amt <= balance) {
        balance -= amt;
        cout << "₹" << amt << " withdrawn successfully!\n";
        recordTransaction("Withdrew ₹" + to_string(amt));

        if (amt < 500) {
            balance -= 25;
            cout << "₹25 fine charged for withdrawing less than ₹500.\n";
            recordTransaction("Fine ₹25 for small withdrawal.");
        }
    } else {
        cout << "Insufficient balance or invalid amount!\n";
    }
}
};

int main() {
    string name;
    int accno, pin;
    float balance;

    // Taking user details
    cout << "Enter your Name: ";
    cin.ignore(); // Ignore newline character from previous input
    getline(cin, name);
    
    cout << "Enter your Account Number: ";
    cin >> accno;
    
    cout << "Enter your Initial Balance: ";
    cin >> balance;
    
    cout << "Set your ATM PIN: ";
    cin >> pin;

    ATM userAcc(name, accno, balance, pin);

    // Authenticate before allowing access
    if (!userAcc.authenticate()) {
        cout << "EXITING DUE TO AUTHENTICATION FAILURE\n";
        return 0;
    }

    int choice;
    float amount;
    do {
        cout << "\nATM Menu:\n";
        cout << "1. Deposit\n2. Withdraw Money\n3. Transfer to Savings\n4. Display Savings\n5. Check Account Balance\n6. Mini Statement\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the amount to deposit: ";
                cin >> amount;
                userAcc.depositpaisa(amount);
                break;
            case 2:
                cout << "Enter the amount to withdraw: ";
                cin >> amount;
                userAcc.withdrawpaisa(amount);
                break;
            case 3:
                cout << "Enter the amount to transfer to savings: ";
                cin >> amount;
                userAcc.depositSavings(amount);
                break;
            case 4:
                userAcc.displaySavings();
                break;
            case 5:
                userAcc.displaydetails();
                break;
            case 6:
                userAcc.miniStatement();
                break;
            case 7:
                cout << "Exiting the ATM...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
