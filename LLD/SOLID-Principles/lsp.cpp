#include<bits/stdc++.h>
using namespace std;

// LSP Violation: FDAccount cannot be substituted for Account without breaking the functionality of the program.
// class Account {
//     public : 
//         virtual void deposit() = 0;
//         virtual void withdraw() = 0;
// };

// class SavingsAccount : public Account {
//     public : 
//         void deposit() {
//             cout << "Depositing to Savings Account" << endl;
//         }
//         void withdraw() {
//             cout << "Withdrawing from Savings Account" << endl;
//         }
// };

// class CurrentAccount : public Account {
//     public : 
//         void deposit() {
//             cout << "Depositing to Current Account" << endl;
//         }
//         void withdraw() {
//             cout << "Withdrawing from Current Account" << endl;
//         }
// };

// class FDAccount : public Account {
//     public : 
//         void deposit() {
//             cout << "Depositing to FD Account" << endl;
//         }
//         void withdraw() {
//              throw runtime_error("Withdrawal not allowed from FD Account");
//         }
// };

// class BankClient{
//     private : 
//         vector<Account*> accounts;

//     public :

//     BankClient(vector<Account*> a){
//         this->accounts = a;
//     }
//     void processAccount(){
//         for (Account* a : accounts) {
//             a->deposit();
//             try{
//                 a->withdraw();
//             } catch (const runtime_error& e) {
//                 cout << e.what() << endl;
//             }
//         }
//     }
// };



// Abstract class for accounts that only allow deposits, adhering to LSP.
class DepositOnlyAccount {
    public :
     virtual void deposit() = 0;
};     

// Abstract class for accounts that allow both deposits and withdrawals, adhering to LSP.
class WithdrawableAccount : public DepositOnlyAccount {
    public :
     virtual void withdraw() = 0;
};


class SavingsAccount : public WithdrawableAccount {
    public : 
        void deposit() {
            cout << "Depositing to Savings Account" << endl;
        }
        void withdraw() {
            cout << "Withdrawing from Savings Account" << endl;
        }
};

class CurrentAccount : public WithdrawableAccount {
    public : 
        void deposit() {
            cout << "Depositing to Current Account" << endl;
        }
        void withdraw() {
            cout << "Withdrawing from Current Account" << endl;
        }
};

class FDAccount : public DepositOnlyAccount {
    public : 
        void deposit() {
            cout << "Depositing to FD Account" << endl;
        }
        void withdraw() {
             throw runtime_error("Withdrawal not allowed from FD Account");
        }
};

class BankClient{
    private : 
        vector<DepositOnlyAccount*> accounts;
        vector<WithdrawableAccount*> accounts1;

    public :

    BankClient(vector<DepositOnlyAccount*> a, vector<WithdrawableAccount*> a1){
        this->accounts = a;
        this->accounts1 = a1;
    }
    void processAccount(){
       for (DepositOnlyAccount* a : accounts) {
            a->deposit();
        }
        for (WithdrawableAccount* a : accounts1) {
            a->deposit();
            a->withdraw();
        }
    }
};





int main() {

    // LSP Violation: FDAccount cannot be substituted for Account without breaking the functionality of the program.
    // vector<Account*> accounts;
    // accounts.push_back(new SavingsAccount());
    // accounts.push_back(new CurrentAccount());
    // accounts.push_back(new FDAccount());
    // BankClient * bc = new BankClient( accounts);
    // bc->processAccount();

    // Adhering to LSP: FDAccount is not used in a context where it cannot be substituted for Account without breaking the functionality of the program.
    vector<DepositOnlyAccount*> accounts;
    accounts.push_back(new SavingsAccount());
    accounts.push_back(new CurrentAccount());
    accounts.push_back(new FDAccount());
    BankClient * bc = new BankClient(accounts, vector<WithdrawableAccount*>());
    bc->processAccount();
    vector<WithdrawableAccount*> accounts1;
    accounts1.push_back(new SavingsAccount());
    accounts1.push_back(new CurrentAccount());
    BankClient * bc1 = new BankClient( accounts, accounts1);
    bc1->processAccount();

    return 0;       
}