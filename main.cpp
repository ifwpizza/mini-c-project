#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

int readInt(const string& prompt) {
    string s;
    int x;
    while (true) {
        cout << prompt;
        getline(cin, s);
        stringstream ss(s);
        if (ss >> x && ss.eof()) return x;
        cout << "Jada Masti hai? 😭, number likh\n";
    }
}

string readName(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);

        if (s.empty()) {
            cout << "Name cannot be empty\n";
            continue;
        }

        bool valid = true;
        for (char c : s) {
            if (!isalpha(c) && c != ' ') {
                valid = false;
                break;
            }
        }

        if (valid) return s;
        cout << "tera naaam bhi number me likhta hai?🤣\n";
    }
}

float readFloat(const string& prompt) {
    string s;
    float x;
    while (true) {
        cout << prompt;
        getline(cin, s);
        stringstream ss(s);
        if (ss >> x && ss.eof()) return x;
        cout << "Jada Masti hai? 😭, number likh\n";
    }
}


class Product {
    int id;
    string name;
    int quantity;
    float price;

public:
    Product(int i, string n, int q, float p)
        : id(i), name(n), quantity(q), price(p) {}

    int getId() const { return id; }
    void setQuantity(int q) { quantity = q; }

    void display() const {
        cout << id << " | " << name << " | " << quantity << " | " << price << endl;
    }

    string serialize() const {
        return to_string(id) + "|" + name + "|" +
               to_string(quantity) + "|" + to_string(price);
    }

    static bool tryDeserialize(const string& line, Product& out) {
        try {
            string a,b,c,d;
            stringstream ss(line);
            if (!getline(ss,a,'|')) return false;
            if (!getline(ss,b,'|')) return false;
            if (!getline(ss,c,'|')) return false;
            if (!getline(ss,d,'|')) return false;

            int id = stoi(a);
            int qty = stoi(c);
            float price = stof(d);

            out = Product(id,b,qty,price);
            return true;
        }
        catch (...) {
            return false;
        }
    }
};

vector<Product> inventory;

bool idExists(int id) {
    for (auto &p : inventory)
        if (p.getId() == id) return true;
    return false;
}

void loadFile() {
    inventory.clear();
    ifstream f("inventory.txt");
    string line;

    while (getline(f,line)) {
        if (line.empty()) continue;
        Product p(0,"",0,0);
        if (Product::tryDeserialize(line,p))
            inventory.push_back(p);
    }
}

void saveFile() {
    ofstream f("inventory.txt");
    for (auto &p : inventory)
        f << p.serialize() << endl;
}

void addProduct() {
    int id = readInt("Enter ID: ");
    if (idExists(id)) {
        cout << "ID is already in nasa's db\n";
        return;
    }

    string name = readName("Enter Name: ");
    int qty = readInt("Enter Quantity: ");
    float price = readFloat("Enter Price: ");
    inventory.push_back(Product(id,name,qty,price));
    saveFile();
    cout << "kar diya update\n";
}

void viewProducts() {
    if (inventory.empty()) {
        cout << "Inventory empty\n";
        return;
    }
    for (auto &p : inventory) p.display();
}

void updateProduct() {
    int id = readInt("Enter ID: ");
    for (auto &p : inventory) {
        if (p.getId() == id) {
            int q = readInt("firse update kar raha hai 😭: ");
            p.setQuantity(q);
            saveFile();
            cout << "yooooo update kar diya\n";
            return;
        }
    }
    cout << "Product nhi mila\n";
}

void deleteProduct() {
    int id = readInt("Enter ID: ");
    for (int i=0;i<inventory.size();i++) {
        if (inventory[i].getId()==id) {
            inventory.erase(inventory.begin()+i);
            saveFile();
            cout << "Deleted\n";
            return;
        }
    }
    cout << "Product nhi mila\n";
}

int main() {
    loadFile();

    while (true) {
        cout << "\nInventory Management System\n";
        cout << "1 Add\n2 View\n3 Update\n4 Delete\n5 Exit\n";
        int c = readInt("Choice: ");

        if (c==1) addProduct();
        else if (c==2) viewProducts();
        else if (c==3) updateProduct();
        else if (c==4) deleteProduct();
        else if (c==5) break;
        else cout << "Invalid choice\n";
    }

    return 0;
}
