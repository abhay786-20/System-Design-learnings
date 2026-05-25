// 1. Class Invariants : Class invariants are properties that are always true for a class.

#include<bits/stdc++.h>
using namespace std;

// class BankAccount {
//     protected : 
//         double balance;
//     public : 
//         BankAccount(double b){
//             if(b < 0){
//                 throw runtime_error("Balance cannot be negative");
//             }
//             balance = b;
//         }
//         virtual void withdraw(double amount){
//             if(amount > balance){
//                 throw runtime_error("Insufficient balance");
//             }
//             balance -= amount;
//             cout << "Withdrawing $" << amount <<" remaining balance is $" << balance << endl;
//         }
// };

// // Breaks the invariant of BankAccount class by allowing negative balance
// class CheatAccount : public BankAccount {
//     public : 
//         CheatAccount(double b) : BankAccount(b){
     
//         }
//         void withdraw(double amount) override {
//             if(amount > balance){
//                 throw runtime_error("Insufficient balance");
//             }
//             balance -= amount;
//             cout << "Withdrawing $" << amount <<" remaining balance is $" << balance << endl;
//         }
// };

// int main(){
//     BankAccount * ba = new BankAccount(1000);
//     ba->withdraw(500);
//     BankAccount * ca = new CheatAccount(1000);
//     ca->withdraw(1200);
// }


// 2.History Constraints 

class BankAccount {
    protected : 
        double balance;
    public : 
        BankAccount(double b){
            if(b < 0){
                throw runtime_error("Balance cannot be negative");
            }
            balance = b;
        }
        virtual void withdraw(double amount){
            if(amount > balance){
                throw runtime_error("Insufficient balance");
            }
            balance -= amount;
            cout << "Withdrawing $" << amount <<" remaining balance is $" << balance << endl;
        }
};

// Breaks the invariant of BankAccount class by allowing negative balance
class FixedDepositAccount : public BankAccount {
    public : 
        FixedDepositAccount(double b) : BankAccount(b){
     
        }
        // History constraint violation: FixedDepositAccount should not allow withdrawals, but it inherits the withdraw method from BankAccount which allows it.
        void withdraw(double amount) override {
                throw runtime_error("Withdrawal not allowed from Fixed Deposit Account");
        }
};
  

int main(){
    BankAccount * ba = new BankAccount(1000);
    ba->withdraw(500);
    BankAccount * fda = new FixedDepositAccount(1000);
    fda->withdraw(500);
}