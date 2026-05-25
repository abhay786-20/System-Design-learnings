// 1   PreCondition Rule : Condition to follow before running the method.
// 2   PostCondition Rule : A child class should not violate the parent class post conditions.

#include<bits/stdc++.h>
using namespace std;

class User {
public:
    // Precondition: Password must be at least 8 characters long
    virtual void setPassword(string password) {
        if (password.length() < 8) {
            throw invalid_argument("Password must be at least 8 characters long!");
        }
        cout << "Password set successfully" << endl;
    }
};

class AdminUser : public User {
public:
    // Precondition: Password must be at least 6 characters
    void setPassword(string password) override {
        if (password.length() < 6) { 
            throw invalid_argument("Password must be at least 6 characters long!");
        }
        cout << "Password set successfully" << endl;
    }
};

class Car {
protected:
    int speed;    

public:
    Car() {
        speed = 0;
    }
    
    void accelerate() {
        cout << "Accelerating" << endl;
        speed += 20;
    }

    //PostCondition : Speed must reduce after brake
    virtual void brake() {
        cout << "Applying brakes" << endl;
        speed -= 20;
    }
};

// Subclass can strengthen postcondition - Does not violate LSP
class HybridCar : public Car {
private:
    int charge;

public:

    HybridCar() : Car() {
        charge = 0;
    }

    // PostCondition : Speed must reduce after brake
    // PostCondition : Charge must increase.
    void brake() {
        cout << "Applying brakes" << endl;
        speed -= 20;
        charge += 10;
    }
};




int main() {
    User* user = new AdminUser();
    user->setPassword("Admin1");  // Works fine: AdminUser allows shorter passwords

    Car* hybridCar = new HybridCar();
    hybridCar->brake();  // Works fine: HybridCar reduces speed and also increases charge.

    //Client feels no difference in substituting Hybrid car in place of Car.

    return 0;
}