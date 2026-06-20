#include <bits/stdc++.h>
using namespace std;

class Order {
private:
    string email;
    string phone;
    string slackChannel;

public:
    Order(string e, string p, string s)
        : email(e), phone(p), slackChannel(s) {}

    string getEmail() const { return email; }
    string getPhone() const { return phone; }
    string getSlackChannel() const { return slackChannel; }

    ~Order() {
        cout << "Order destroyed" << endl;
    }
};

class OrderObserver {
public:
    virtual void update(const Order& order) = 0;

    virtual ~OrderObserver() {
        cout << "OrderObserver destroyed" << endl;
    }
};

class EmailOrderObserver : public OrderObserver {
public:
    void update(const Order& order) override {
        cout << "Emailing order details to "
             << order.getEmail() << endl;
    }

    ~EmailOrderObserver() {
        cout << "EmailOrderObserver destroyed" << endl;
    }
};

class SMSOrderObserver : public OrderObserver {
public:
    void update(const Order& order) override {
        cout << "Sending order details to "
             << order.getPhone() << endl;
    }

    ~SMSOrderObserver() {
        cout << "SMSOrderObserver destroyed" << endl;
    }
};

class SlackOrderObserver : public OrderObserver {
public:
    void update(const Order& order) override {
        cout << "Posting order details to "
             << order.getSlackChannel() << endl;
    }

    ~SlackOrderObserver() {
        cout << "SlackOrderObserver destroyed" << endl;
    }
};

class OrderSubject {
private:
    vector<OrderObserver*> observers;

public:
    void subscribe(OrderObserver* observer) {
        observers.push_back(observer);
    }

    void unsubscribe(OrderObserver* observer) {
        observers.erase(
            remove(observers.begin(),
                   observers.end(),
                   observer),
            observers.end()
        );
    }

    void notify(const Order& order) {
        for (auto observer : observers) {
            observer->update(order);
        }
    }

    ~OrderSubject() {
        cout << "OrderSubject destroyed" << endl;

        // Since OrderSubject owns observers,
        // clean them up here.
        for (auto observer : observers) {
            delete observer;
        }

        observers.clear();
    }
};

int main() {
    Order* order = new Order(
        "user@example.com",
        "+919876543210",
        "#engineering"
    );

    OrderSubject* orderSubject = new OrderSubject();

    orderSubject->subscribe(
        new EmailOrderObserver()
    );

    orderSubject->subscribe(
        new SMSOrderObserver()
    );

    orderSubject->subscribe(
        new SlackOrderObserver()
    );

    orderSubject->notify(*order);

    delete order;
    delete orderSubject;

    return 0;
}