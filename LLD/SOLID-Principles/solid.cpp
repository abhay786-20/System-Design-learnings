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

class ShoppingCartSaver{
    private : 
        ShoppingCart * cart;
    public :
        ShoppingCartSaver(ShoppingCart * c){
            this->cart = c;
        }
        void saveTODb(){
            cout << "Saving to DB" << endl;
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

    ShoppingCartSaver * scs = new ShoppingCartSaver(sc);
    scs->saveTODb();
    return 0;       
}