#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;
public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void setItem(string item) { Item = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }

    string getItem() { return Item; }
    int getRate() { return Rate; }
    int getQuant() { return Quantity; }
};

// Function to add an item
void addItem(Bill b) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("D:/Bill.txt", ios::app);
            if (!out) {
                cout << "\tError: File Can't Open!" << endl;
            } else {
                out << b.getItem() << " " << b.getRate() << " " << b.getQuant() << endl;
                cout << "\tItem Added Successfully" << endl;
            }
            out.close();
            Sleep(3000);
        } else if (choice == 2) {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            Sleep(3000);
        }
    }
}

// Function to print bill
void printBill() {
    system("cls");
    int count = 0;
    bool close = false;
    while (!close) {
        system("cls");
        int choice;
        cout << "\t1. Add To Bill" << endl;
        cout << "\t2. Close Session" << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item Name: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("D:/Bill.txt");
            ofstream out("D:/Bill_Temp.txt");

            string itemName;
            int itemRate, itemQuant;
            bool found = false;

            while (in >> itemName >> itemRate >> itemQuant) {
                if (item == itemName) {
                    found = true;
                    if (quant <= itemQuant) {
                        int amount = itemRate * quant;
                        cout << "\t Item | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << "\t " << itemRate << "\t " << quant << "\t " << amount << endl;
                        int newQuant = itemQuant - quant;
                        out << itemName << " " << itemRate << " " << newQuant << endl;
                        count += amount;
                    } else {
                        cout << "\tSorry, only " << itemQuant << " left for " << itemName << "!" << endl;
                        out << itemName << " " << itemRate << " " << itemQuant << endl;
                    }
                } else {
                    out << itemName << " " << itemRate << " " << itemQuant << endl;
                }
            }

            if (!found) {
                cout << "\tItem Not Found!" << endl;
            }

            in.close();
            out.close();

            remove("D:/Bill.txt");
            rename("D:/Bill_Temp.txt", "D:/Bill.txt");
            Sleep(3000);
        } else if (choice == 2) {
            close = true;
            cout << "\tCalculating Total..." << endl;
            Sleep(2000);
        }
    }

    system("cls");
    cout << "\n\n";
    cout << "\t----------------------------------" << endl;
    cout << "\t Total Bill: Rs. " << count << endl;
    cout << "\t----------------------------------" << endl;
    cout << "\tThank You For Shopping!" << endl;
    Sleep(5000);
}

// Main function
int main() {
    Bill b;
    bool exit = false;

    while (!exit) {
        system("cls");
        int val;

        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t1. Add Item" << endl;
        cout << "\t2. Print Bill" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\tEnter Your Choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");
            addItem(b);
        } else if (val == 2) {
            printBill();
        } else if (val == 3) {
            system("cls");
            exit = true;
            cout << "\tExiting..." << endl;
            Sleep(2000);
        } else {
            cout << "\tInvalid Choice! Try Again." << endl;
            Sleep(2000);
        }
    }

    return 0;
}
