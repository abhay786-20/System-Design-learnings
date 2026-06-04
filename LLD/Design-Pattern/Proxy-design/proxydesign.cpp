// Protection Proxy Design Pattern Example in C++

#include <iostream>
#include <string>

using namespace std;

// Interface for Document Reader
class IDocumentReader {
public:
    virtual void unlockPDF(string filePath, string password) = 0;
    virtual ~IDocumentReader() = default;
};

// Concrete Class: Reads the PDF (simulated)
class RealDocumentReader : public IDocumentReader {
public:
    void unlockPDF(string filePath, string password) override {
        cout << "[RealDocumentReader] Unlocking PDF at: " << filePath << "\n";
        cout << "[RealDocumentReader] PDF unlocked successfully with password: " << password << "\n";
        cout << "[RealDocumentReader] Displaying PDF content...\n";
    }
};

// User class with membership status
class User {
public:
    string name;
    bool premiumMembership;
    
    User(string name, bool isPremium) {
        this->name = name;
        this->premiumMembership = isPremium;
    }
};

// Proxy Class: Controls access to RealDocumentReader
class DocumentProxy : public IDocumentReader {
    RealDocumentReader* realReader;
    User* user;
    
public:
    DocumentProxy(User* user) {
        realReader = new RealDocumentReader();
        this->user = user;
    }

    void unlockPDF(string filePath, string password) override {
        if (!user->premiumMembership) {
            cout << "[DocumentProxy] Access denied. Only premium members can unlock PDFs.\n";
            return;
        }

        // Forwarding the request to the real reader
        realReader->unlockPDF(filePath, password);
    }

    ~DocumentProxy() {
        delete realReader;
    }
};

// Client code
int main() {

    User* user1 = new User("Rohan", false);  // Non Premium User
    User* user2 = new User("Rashmi", true);  // premium user

    cout << "== Rohan (Non-Premium) tries to unlock PDF ==\n";
    IDocumentReader* docReader = new DocumentProxy(user1);
    docReader->unlockPDF("protected_document.pdf", "secret123");
    delete docReader;

    cout << "\n== Rashmi (Premium) unlocks PDF ==\n";
    docReader = new DocumentProxy(user2);
    docReader->unlockPDF("protected_document.pdf", "secret123");
    delete docReader;

    return 0;
}


// Remote Proxy Design Pattern Example in C++

#include<iostream>
#include<string>

using namespace std;

class IDataService {
public:
    virtual string fetchData() = 0;
    virtual ~IDataService() = default;
};

class RealDataService : public IDataService {
public:
    RealDataService() {
        // Imagine this connects to a remote server or loads heavy resources.
        cout << "[RealDataService] Initialized (simulating remote setup)\n";
    }
    string fetchData() override {
        return "[RealDataService] Data from server";
    }
};

// Remote proxy
class DataServiceProxy : public IDataService {
private:
    RealDataService* realService = nullptr;

public:
    DataServiceProxy() {
        realService = new RealDataService();
    }

    string fetchData() override {
        cout << "[DataServiceProxy] Connecting to remote service...\n";
        return realService->fetchData();
    }
};

int main() {
    IDataService* dataService = new DataServiceProxy();
    dataService->fetchData();
}
    

// Virtual Proxy Design Pattern Example in C++

#include<iostream>
#include<string>

using namespace std;

class IImage { 
public:
    virtual void display() = 0;
    virtual ~IImage() = default;
};

class RealImage : public IImage {
    string filename;
public:
    RealImage(string file) {
        this->filename = file;
        // Heavy Operation
        cout << "[RealImage] Loading image from disk: " << filename << "\n";
    }

    void display() override {
        cout << "[RealImage] Displaying " << filename << "\n";
    }
};
    
class ImageProxy : public IImage {
    RealImage* realImage;
    string filename;
public:
    ImageProxy(string file) {
        this->filename = file;
        realImage = nullptr;
    }

    void display() override {
        // Lazy initialization of RealImage
        if (!realImage) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }
};

int main() {

    IImage* image1 = new ImageProxy("sample.jpg");
    image1->display();

    
}
    