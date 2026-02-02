#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Product {
private:
    int id;
    string name;
    int quantity;
    float price;

public:
    Product(int i, string n, int q, float p) {
        id = i;
        name = n;
        quantity = q;
        price = p;
    }

    int getId() {
        return id;
    }

    void display() {
        cout << "ID: " << id
             << " | Name: " << name
             << " | Qty: " << quantity
             << " | Price: " << price << endl;
    }

    void updateQuantity(int q) {
        quantity = q;
    }

    string toFileString() {
        return to_string(id) + " " + name + " " +
               to_string(quantity) + " " + to_string(price);
    }
};

vector<Product> inventory;

void loadFromFile() {
    inventory.clear();
    ifstream file("inventory.txt");

    int id, qty;
    float price;
    string name;

    while (file >> id >> name >> qty >> price) {
        inventory.push_back(Product(id, name, qty, price));
    }

    file.close();
}

void saveToFile() {
    ofstream file("inventory.txt");

    for (auto &p : inventory) {
        file << p.toFileString() << endl;
    }

    file.close();
}

void addProduct() {
    int id, qty;
    float price;
    string name;

    cout << "Enter Product ID: ";
    cin >> id;
    cout << "Enter Product Name: ";
    cin >> name;
    cout << "Enter Quantity: ";
    cin >> qty;
    cout << "Enter Price: ";
    cin >> price;

    inventory.push_back(Product(id, name, qty, price));
    saveToFile();

    cout << "Product Added Successfully!\n";
}

void viewProducts() {
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }

    for (auto &p : inventory) {
        p.display();
    }
}

void updateProduct() {
    int id, qty;
    cout << "Enter Product ID to update: ";
    cin >> id;

    for (auto &p : inventory) {
        if (p.getId() == id) {
            cout << "Enter New Quantity: ";
            cin >> qty;
            p.updateQuantity(qty);
            saveToFile();
            cout << "Product Updated!\n";
            return;
        }
    }

    cout << "Product Not Found.\n";
}

void deleteProduct() {
    int id;
    cout << "Enter Product ID to delete: ";
    cin >> id;

    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i].getId() == id) {
            inventory.erase(inventory.begin() + i);
            saveToFile();
            cout << "Product Deleted!\n";
            return;
        }
    }

    cout << "Product Not Found.\n";
}

int main() {
    loadFromFile();
    int choice;

    do {
        cout << "\n--- Inventory Management System ---\n";
        cout << "1. Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Update Product Quantity\n";
        cout << "4. Delete Product\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: updateProduct(); break;
            case 4: deleteProduct(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }
    } while (choice != 5);

    return 0;
}
