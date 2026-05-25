#include <iostream>
#include <string>
using namespace std;

// ---------- Custom Exception ----------
class FraudException : public exception {
    string msg;
public:
    FraudException(string m) : msg(m) {}
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

// ---------- Account ----------
class Account {
private:
    string name;
    int pin;
    double balance;
public:
    static int totalAccounts;

    Account(string n="Unknown", int p=0000, double b=0) {
        name = n;
        pin = p;
        balance = (b < 0 ? 0 : b);
        totalAccounts++;
    }

    double getBalance() const { return balance; }
    string getName() const { return name; }

    bool verifyPin(int p) const { return p == pin; }

    void deposit(double amt) {
        if (amt <= 0) throw FraudException("Invalid deposit amount");
        balance += amt;
    }

    virtual void withdraw(double amt) {
        if (amt <= 0) throw FraudException("Invalid withdraw amount");
        if (amt > balance) throw FraudException("Withdrawal exceeds balance");
        balance -= amt;
    }

    virtual void showInfo() const {
        cout << "\nAccount Holder: " << name
             << "\nBalance: " << balance << endl;
    }

    virtual ~Account() {}
};
int Account::totalAccounts = 0;

// ---------- SavingAccount (single + hierarchical) ----------
class SavingAccount : public Account {
protected:
    double dailyLimit;
public:
    SavingAccount(string n, int p, double b, double limit = 50000)
        : Account(n,p,b), dailyLimit(limit) {}

    void withdraw(double amt) override {
        if (amt > dailyLimit)
            throw FraudException("Withdrawal exceeds daily limit");
        Account::withdraw(amt);
    }

    void showInfo() const override {
        cout << "\n[Saving Account]";
        Account::showInfo();
        cout << "Daily Limit: " << dailyLimit << endl;
    }
};

// ---------- HighSecurityAccount (multi-level) ----------
class HighSecurityAccount : public SavingAccount {
    int failedAttempts;
public:
    HighSecurityAccount(string n, int p, double b, double limit = 80000)
        : SavingAccount(n,p,b,limit), failedAttempts(0) {}

    void login(int userPin) {
        if (!verifyPin(userPin)) {
            failedAttempts++;
            if (failedAttempts >= 3)
                throw FraudException("Account locked! Multiple wrong PIN attempts");
            throw FraudException("Wrong PIN!");
        }
        failedAttempts = 0; // success
    }

    int getFailedAttempts() const { return failedAttempts; }

    void showInfo() const override {
        cout << "\n[High Security Account]";
        Account::showInfo();
        cout << "Failed Attempts: " << failedAttempts << endl;
    }
};

// ---------- Transaction ----------
class Transaction {
public:
    string type;
    double amount;
    string location;
    int time24; // 0-23

    Transaction(string t="withdraw", double a=0,
                string l="Home", int tm=12)
        : type(t), amount(a), location(l), time24(tm) {}
};

// ---------- SecurityEngine (polymorphism) ----------
class SecurityEngine {
public:
    // simple overloaded versions
    void detect(int amount) {
        if (amount > 100000)
            throw FraudException("Large suspicious transaction detected!");
    }

    void detect(int amount, string location) {
        if (location != "Home" && amount > 50000)
            throw FraudException("Unusual location + big amount!");
    }

    void detect(int amount, string location, int time24) {
        if (time24 >= 0 && time24 <= 5 && location != "Home")
            throw FraudException("Night-time suspicious activity from unknown location!");
    }
};

// ---------- MAIN: simple text interface ----------
int main() {
    HighSecurityAccount hs("Aina", 1234, 90000);
    SecurityEngine engine;

    cout << "=== Bank Theft Detection System (BTDS) ===\n";
    hs.showInfo();

    while (true) {
        cout << "\n1. Login"
             << "\n2. Withdraw (simulate transaction)"
             << "\n3. Show Account Info"
             << "\n0. Exit"
             << "\nEnter choice: ";

        int choice;
        cin >> choice;

        if (choice == 0) break;

        try {
            if (choice == 1) {
                int p;
                cout << "Enter PIN: ";
                cin >> p;
                hs.login(p);           // yahan se Wrong PIN / lock exception
                cout << "Login successful.\n";
            }
            else if (choice == 2) {
                double amount;
                string location;
                int time24;

                cout << "Enter amount: ";
                cin >> amount;
                cout << "Enter location (Home / Unknown): ";
                cin >> location;
                cout << "Enter time (0-23): ";
                cin >> time24;

                Transaction tx("withdraw", amount, location, time24);

                // yahan pe tum sir ko step-by-step dikha sakti ho
                engine.detect(tx.amount);                        // amount rule
                engine.detect(tx.amount, tx.location);           // location rule
                engine.detect(tx.amount, tx.location, tx.time24);// time + loc rule

                hs.withdraw(tx.amount); // balance & daily limit check
                cout << "Withdrawal successful.\n";
            }
            else if (choice == 3) {
                hs.showInfo();
            }
            else {
                cout << "Invalid choice.\n";
            }
        }
        catch (FraudException &e) {
            cout << "\nALERT (Exception Raised): " << e.what() << "\n";
        }
    }

    cout << "\nProgram ended.\n";
    return 0;
}
