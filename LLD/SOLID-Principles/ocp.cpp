#include<bits/stdc++.h>
using namespace std;

// Product Class
class Product {
public:
    string name;
    double price;   
    Product  (string n, double p) {
        this->name = n;
        this->price = p;

    }
};

// Shopping Cart Class - violated one 
class ShoppingCart {
private:
    vector<Product*> cart;
public:
    void addProduct(Product* p) {
        cart.push_back(p);
    }
    
    const vector<Product*>& getProducts() const {
        return cart;
    }

    // 1.Calculate the total price 
    double getTotalPrice() const {
        double total = 0;
        for (Product* p : cart) {
            total += p->price;
        }
        return total;
    }

    // 2.Print invoice - violating single responsibility principle
    // void printInvoice() const {
    //     cout << "Invoice:" << endl;
    //     for (Product* p : cart) {
    //         cout << p->name << ": $" << p->price << endl;
    //     }
    //     cout << "Total: $" << getTotalPrice() << endl;
    // }

    // // 3.Save to database - violating single responsibility principle
    // void saveTODb() {
    //     cout << "Saving to DB" << endl;
    // }

};


class ShoppingCartPrinter{
    private : 
        ShoppingCart * cart;
    public :
        ShoppingCartPrinter(ShoppingCart * c){
            this->cart = c;
        }
        void printInvoice(){
            cout << "Invoice:" << endl;
            for (Product* p : cart->getProducts()) {
                cout << p->name << ": $" << p->price << endl;
            }
            cout << "Total: $" << cart->getTotalPrice() << endl;
        }
};

// class ShoppingCartSaver{
//     private : 
//         ShoppingCart * cart;
//     public :
//         ShoppingCartSaver(ShoppingCart * c){
//             this->cart = c;
//         }

//         // 3.Save to database - violating single responsibility principle and open closed principle as well
//         void saveTODb(){
//             cout << "Saving to DB" << endl;
//         }

//         void saveToFile(){
//             cout << "Saving to File" << endl;
//         }

//         void saveToDBAndFile(){
//             cout << "Saving to DB and File" << endl;
//         }
// };


class Persistent {
    private :
    ShoppingCart * cart;
    public :
    virtual void saveTODb() = 0;
};

class SaveTOMySQL : public Persistent {
    public :
    void saveTODb() override {
        cout << "Saving to MySQL DB" << endl;
    }
};  

class SaveToFile : public Persistent {
    public :
    void saveTODb() override {
        cout << "Saving to File" << endl;
    }
};

class SaveToDBAndFile : public Persistent {
    public :
    void saveTODb() override {
        cout << "Saving to DB and File" << endl;
    }
};

int main() {

    ShoppingCart * sc = new ShoppingCart();
    sc->addProduct(new Product("iPhone", 1000));
    sc->addProduct(new Product("MacBook", 2000));
    sc->addProduct(new Product("Mouse", 50));
    sc->getTotalPrice();

    ShoppingCartPrinter * scp = new ShoppingCartPrinter(sc);
    scp->printInvoice();

    // Parent class pointer can point to any of the child 
    // class object and call the overridden method of that class at runtime.
    // This is called runtime polymorphism.
     Persistent * p1 = new SaveTOMySQL();
        p1->saveTODb();
    Persistent * p2 = new SaveToFile();
        p2->saveTODb();
    Persistent * p3 = new SaveToDBAndFile();
        p3->saveTODb();
    return 0;       
}