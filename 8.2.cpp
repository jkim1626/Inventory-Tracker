#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

// Structure to store inventory data
struct InventoryItem
{
    string itemName;
    int quantityOnHand;
    double wholesaleCost;
    double retailCost;
};

// Function prototypes
void addRecordToFile(const string &);
void displayRecordFromFile(const string &, const string &);
void changeRecordInFile(const string &);
void displayAllRecords(const string &);
void prepareReport(const string &);

int main()
{
    string filename = "inventory.txt"; // Change this to the desired filename

    int choice;

    do
    {
        cout << "Menu:\n"
             << "1. Add new record\n"
             << "2. Display specific record\n"
             << "3. Change a record\n"
             << "4. Display all records\n"
             << "5. Prepare a report\n"
             << "0. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addRecordToFile(filename);
            break;
        case 2:
        {
            cin.ignore(); // Clear the newline character from the previous input
            string itemName;
            cout << "Enter the name or first few letters of the item: ";
            getline(cin, itemName);
            displayRecordFromFile(filename, itemName);
        }
        break;
        case 3:
            changeRecordInFile(filename);
            break;
        case 4:
            displayAllRecords(filename);
            break;
        case 5:
            prepareReport(filename);
            break;
        case 0:
            cout << "Exiting the program.\n";
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}

void addRecordToFile(const string &filename)
{
    ofstream outFile(filename, ios::app);

    if (!outFile.is_open())
    {
        cerr << "Error: Unable to open the file for writing.\n";
        return;
    }

    InventoryItem newItem;

    cout << "Enter item name: ";
    cin.ignore(); // Clear the newline character from the previous input
    getline(cin, newItem.itemName);

    cout << "Enter quantity on hand: ";
    cin >> newItem.quantityOnHand;

    cout << "Enter wholesale cost: ";
    cin >> newItem.wholesaleCost;

    cout << "Enter retail cost: ";
    cin >> newItem.retailCost;

    // Input validation
    if (newItem.quantityOnHand < 0 || newItem.wholesaleCost < 0 || newItem.retailCost < 0)
    {
        cerr << "Error: Invalid input. Quantities and costs cannot be less than 0.\n";
        return;
    }

    outFile
        << newItem.itemName << " "
        << newItem.quantityOnHand << " "
        << newItem.wholesaleCost << " "
        << newItem.retailCost << endl;

    cout << "Record added successfully.\n";
    outFile.close();
}

void displayRecordFromFile(const string &filename, const string &itemName)
{
    ifstream inFile(filename);

    if (!inFile.is_open())
    {
        cerr << "Error: Unable to open the file for reading.\n";
        return;
    }

    InventoryItem currentItem;

    bool found = false;

    while (inFile >> currentItem.itemName >> currentItem.quantityOnHand >> currentItem.wholesaleCost >> currentItem.retailCost)
    {
        // Check if the item name contains the input substring
        if (currentItem.itemName.find(itemName) != string::npos)
        {
            found = true;
            cout << "Item Name: " << currentItem.itemName << endl;
            cout << "Quantity on Hand: " << currentItem.quantityOnHand << endl;
            cout << "Wholesale Cost: $" << fixed << setprecision(2) << currentItem.wholesaleCost << endl;
            cout << "Retail Cost: $" << fixed << setprecision(2) << currentItem.retailCost << endl;
            cout << "------------------------\n";
        }
    }

    if (!found)
    {
        cout << "No matching records found.\n";
    }

    inFile.close();
}

void changeRecordInFile(const string &filename)
{
    ifstream inFile(filename);
    ofstream tempFile("temp.txt");

    if (!inFile.is_open() || !tempFile.is_open())
    {
        cerr << "Error: Unable to open the file for reading or writing.\n";
        return;
    }

    InventoryItem currentItem;
    string itemNameToChange;
    bool changed = false;

    cout << "Enter the name of the item to change: ";
    cin.ignore(); // Clear the newline character from the previous input
    getline(cin, itemNameToChange);

    while (inFile >> currentItem.itemName >> currentItem.quantityOnHand >> currentItem.wholesaleCost >> currentItem.retailCost)
    {
        if (currentItem.itemName == itemNameToChange)
        {
            cout << "Enter the new record:\n";

            cout << "Enter item name: ";
            cin.ignore(); // Clear the newline character from the previous input
            getline(cin, currentItem.itemName);

            cout << "Enter quantity on hand: ";
            cin >> currentItem.quantityOnHand;

            cout << "Enter wholesale cost: ";
            cin >> currentItem.wholesaleCost;

            cout << "Enter retail cost: ";
            cin >> currentItem.retailCost;

            // Input validation
            if (currentItem.quantityOnHand < 0 || currentItem.wholesaleCost < 0 || currentItem.retailCost < 0)
            {
                cerr << "Error: Invalid input. Quantities and costs cannot be less than 0.\n";
                return;
            }

            changed = true;
        }

        tempFile << currentItem.itemName << " "
                 << currentItem.quantityOnHand << " "
                 << currentItem.wholesaleCost << " "
                 << currentItem.retailCost << endl;
    }

    if (!changed)
    {
        cout << "No matching record found for the item name: " << itemNameToChange << endl;
    }
    else
    {
        cout << "Record changed successfully.\n";
    }

    inFile.close();
    tempFile.close();

    // Rename tempFile to the original filename
    if (remove(filename.c_str()) != 0)
    {
        cerr << "Error: Unable to remove the original file.\n";
        return;
    }

    if (rename("temp.txt", filename.c_str()) != 0)
    {
        cerr << "Error: Unable to rename the temporary file.\n";
    }
}

void displayAllRecords(const string &filename)
{
    ifstream inFile(filename);

    if (!inFile.is_open())
    {
        cerr << "Error: Unable to open the file for reading.\n";
        return;
    }

    InventoryItem currentItem;

    cout << left << setw(20) << "Item Name"
         << setw(20) << "Quantity on Hand"
         << setw(20) << "Wholesale Cost"
         << setw(20) << "Retail Cost" << endl;
    cout << "-------------------------------------------------------------\n";

    while (inFile >> currentItem.itemName >> currentItem.quantityOnHand >> currentItem.wholesaleCost >> currentItem.retailCost)
    {
        cout << left << setw(20) << currentItem.itemName
             << setw(20) << currentItem.quantityOnHand
             << setw(20) << "$" << fixed << setprecision(2) << currentItem.wholesaleCost
             << setw(20) << "$" << fixed << setprecision(2) << currentItem.retailCost << endl;
    }

    inFile.close();
}

void prepareReport(const string &filename)
{
    ifstream inFile(filename);

    if (!inFile.is_open())
    {
        cerr << "Error: Unable to open the file for reading.\n";
        return;
    }

    InventoryItem currentItem;
    double totalWholesaleValue = 0.0;
    double totalRetailValue = 0.0;
    int totalQuantity = 0;

    while (inFile >> currentItem.itemName >> currentItem.quantityOnHand >> currentItem.wholesaleCost >> currentItem.retailCost)
    {
        totalWholesaleValue += currentItem.wholesaleCost * currentItem.quantityOnHand;
        totalRetailValue += currentItem.retailCost * currentItem.quantityOnHand;
        totalQuantity += currentItem.quantityOnHand;
    }

    cout << "Report:\n"
         << "a. Total Wholesale Value of Inventory: $" << fixed << setprecision(2) << totalWholesaleValue << endl
         << "b. Total Retail Value of Inventory: $" << fixed << setprecision(2) << totalRetailValue << endl
         << "c. Total Quantity of All Values in the Inventory: " << totalQuantity << endl;

    inFile.close();
}
