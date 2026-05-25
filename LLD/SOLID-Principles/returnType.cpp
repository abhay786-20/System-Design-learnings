#include<bits/stdc++.h>
using namespace std;

class Animal {
    
};

class Dog : public Animal {
    
};


class Parent {
    public : 
    virtual Animal* getAnimal() {
        cout<<"Parent returning an Animal instance"<<endl;
        return new Animal();
    }
};


class Child : public Parent {
    public : 
    Dog* getAnimal() override {
        cout<<"Child returning an Dog instance"<<endl;
        return new Dog();
    }
};

class Client {
    private :
    Parent* p;
    public :
    Client(Parent* p){
        this->p = p;
    }
    void printAnimal(){
         p->getAnimal();;
    }
};

int main() {

    Parent * p = new Child();
    Parent * p1 = new Parent();
    Client * c = new Client(p);
    Client * c1 = new Client(p1);
    c->printAnimal();
    c1->printAnimal();
    return 0;       
}