#include <iostream>
using namespace std;

class MySQLDatabase {  // Low-level module
public:
    void saveToSQL(string data) {
        cout << "Executing SQL Query: INSERT INTO users VALUES('" << data << "');" << endl;
    }
};

class MongoDBDatabase {  // Low-level module
public:
    void saveToMongo(string data) {
        cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
    }
};

class UserService {  // High-level module (Tightly coupled)
private:
    MySQLDatabase sqlDb;  // Direct dependency on MySQL
    MongoDBDatabase mongoDb;  // Direct dependency on MongoDB

public:
    void storeUserToSQL(string user) {
        // MySQL-specific code
        sqlDb.saveToSQL(user);  
    }

    void storeUserToMongo(string user) {
        // MongoDB-specific code
        mongoDb.saveToMongo(user);  
    }
};

int main() {
    UserService service;
    service.storeUserToSQL("Aditya");
    service.storeUserToMongo("Rohit");
}



// DIP Adhered

#include <iostream>
using namespace std;

// Abstraction (Interface)
class Database {
public:
    virtual void save(string data) = 0; // Pure virtual function
};

// MySQL implementation (Low-level module)
class MySQLDatabase : public Database {
public:
    void save(string data) override {
        cout << "Executing SQL Query: INSERT INTO users VALUES('" << data << "');" << endl;
    }
};

// MongoDB implementation (Low-level module)
class MongoDBDatabase : public Database {
public:
    void save(string data) override {
        cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
    }
};

// High-level module (Now loosely coupled)
class UserService {
private:
    Database* db;  // Dependency Injection

public:
    UserService(Database* database) {  
        db = database;
    }
    
    void storeUser(string user) {
        db->save(user);
    }
};

int main() {
    MySQLDatabase mysql;
    MongoDBDatabase mongodb;

    UserService service1(&mysql);
    service1.storeUser("Aditya");

    UserService service2(&mongodb);
    service2.storeUser("Rohit");
}