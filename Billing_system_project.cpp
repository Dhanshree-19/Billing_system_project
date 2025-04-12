#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class shopping {
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu() {
    int choice;
    string email, password;

    while (true) {
        cout << "\t\t\t\t________________________________________\n";
        cout << "\t\t\t\t          SuperMarket Main Menu         \n";
        cout << "\t\t\t\t________________________________________\n";
        cout << "\t\t\t\t|  1) Administrator   |\n";
        cout << "\t\t\t\t|  2) Buyer           |\n";
        cout << "\t\t\t\t|  3) Exit            |\n";
        cout << "\n\t\t\t Please select: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\t\t\t Please Login \n";
            cout << "\t\t\t Enter Email: ";
            cin >> email;
            cout << "\t\t\t Password: ";
            cin >> password;

            if (email == "riya@gmail.com" && password == "riya@123") {
                administrator();
            } else {
                cout << "Invalid email/password\n";
            }
            break;
        case 2:
            buyer();
            break;
        case 3:
            exit(0);
        default:
            cout << "Please select from the given options.\n";
        }
    }
}

void shopping::administrator() {
    int choice;
    while (true) {
        cout << "\n\n\t\t\t Administrator Menu\n";
        cout << "\t\t\t 1) Add the product\n";
        cout << "\t\t\t 2) Modify the product\n";
        cout << "\t\t\t 3) Delete the product\n";
        cout << "\t\t\t 4) Back to main menu\n";
        cout << "\n\t Please enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            rem();
            break;
        case 4:
            return; // Back to main menu
        default:
            cout << "Invalid choice!\n";
        }
    }
}

void shopping::buyer() {
    int choice;
    while (true) {
        cout << "\t\t\t Buyer\n";
        cout << "\t\t\t 1) Buy product\n";
        cout << "\t\t\t 2) Go back\n";
        cout << "\t\t\t Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            receipt();
            break;
        case 2:
            return; // Back to main menu
        default:
            cout << "Invalid choice\n";
        }
    }
}

void shopping::add() {
    fstream data;
    int token = 0;
    int c;
    float p, d;
    string n;

    cout << "\n\n\t\t\t Add new product\n";
    cout << "\n\t Product code: ";
    cin >> pcode;
    cin.ignore();
    cout << "\n\t Name of the product: ";
    getline(cin, pname);
    cout << "\n\t Price: ";
    cin >> price;
    cout << "\n\t Discount: ";
    cin >> dis;

    data.open("database.txt", ios::in);
    if (data.fail()) {
        data.close();
        data.open("database.txt", ios::app | ios::out);
        data << pcode << " " << pname << " " << price << " " << dis << "\n";
        cout << "\n\t\t Record inserted.\n";
    } else {
        while (data >> c >> n >> p >> d) {
            if (c == pcode) {
                token = 1;
                break;
            }
        }
        data.close();

        if (token == 1) {
            cout << "\n\t Product code already exists. Try again.\n";
        } else {
            data.open("database.txt", ios::app | ios::out);
            data << pcode << " " << pname << " " << price << " " << dis << "\n";
            cout << "\n\t\t Record inserted.\n";
        }
    }
    data.close();
}

void shopping::edit() {
    fstream data, data1;
    int pkey, c;
    float p, d;
    string n;
    int token = 0;

    cout << "\n\t\t\t Modify the record\n";
    cout << "\n\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\t File doesn't exist.\n";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        while (data >> pcode >> pname >> price >> dis) {
            if (pkey == pcode) {
                cout << "\n\t Product new code: ";
                cin >> c;
                cin.ignore();
                cout << "\n\t Name of the product: ";
                getline(cin, n);
                cout << "\n\t Price: ";
                cin >> p;
                cout << "\n\t Discount: ";
                cin >> d;
                data1 << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\t\t Record edited.\n";
                token = 1;
            } else {
                data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\t Record not found.\n";
        }
    }
}

void shopping::rem() {
    fstream data, data1;
    int pkey, token = 0;

    cout << "\n\t Delete product\n";
    cout << "\n\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\t File doesn't exist.\n";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        while (data >> pcode >> pname >> price >> dis) {
            if (pcode == pkey) {
                cout << "\n\t Product deleted successfully.\n";
                token = 1;
            } else {
                data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\t Record not found.\n";
        }
    }
}

void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);

    if (!data) {
        cout << "\n\t File doesn't exist.\n";
    } else {
        cout << "\n\n|_____________________________________________________________________\n";
        cout << "ProNo\t\t\tName\t\tPrice\n";
        cout << "|_____________________________________________________________________\n";

        while (data >> pcode >> pname >> price >> dis) {
            cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        }
        data.close();
    }
}

void shopping::receipt() {
    fstream data;
    int arrc[100], arrq[100];
    char choice;
    int c = 0;
    float discount, amount = 0, total = 0;

    cout << "\n\n\t\t\t\t RECEIPT\n";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty database.\n";
    } else {
        list();
        cout << "\n________________________________________\n";
        cout << "          Please place the order        \n";
        cout << "________________________________________\n";

        do {
            cout << "\n\nEnter product code: ";
            cin >> arrc[c];
            cout << "\nEnter the product quantity: ";
            cin >> arrq[c];
            c++;

            cout << "\nDo you want to buy another product? (y/n): ";
            cin >> choice;
        } while (choice == 'y');

        cout << "\n\n\t\t\t____________________________________RECEIPT_________________________________________\n";
        cout << "Product No\t\t Product Name\t\t Product Quantity\t\t Price\t\t Amount\t\t Amount with Discount \n";

        for (int i = 0; i < c; i++) {
            data.clear();
            data.seekg(0);
            while (data >>pcode>> pname>> price >> dis) {
                if (pcode == arrc[i]) {
                    amount = price * arrq[i];
                    discount = amount - (amount * dis / 100);
                    total += discount;
                    cout << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t\t" << amount << "\t\t" << discount << "\n";
                }
            }
        }
        data.close();
    }
    cout << "\n\n_____________________________________________________________________\n";
    cout << " Total Amount: " << total << "\n";
}

int main() {
    shopping s;
    s.menu();
    return 0;
}
