#include <iostream>  // for standard I/O operations
#include <fstream>   // for file operations
#include <iomanip>   // for formatted output
#include <string>    // for string operations

using namespace std;

// Structure to store inventory data
struct InventoryItem {
    string itemName;          // Name of the inventory item
    int quantityOnHand;       // Quantity available in inventory
    double wholesaleCost;     // Wholesale cost of the item
    double retailCost;        // Retail cost of the item
};

// Function prototypes
void addRecordToFile(const string &);
void displayRecordFromFile(const string &, const string &);
void changeRecordInFile(const string &);
void displayAllRecords(const string &);
void prepareReport(const string &);

int main() {
    string filename = "inventory.txt"; // Filename for storing inventory data

    int choice; // Variable to store user's menu choice

    // Display menu and process user's choice in a loop until the user chooses to exit
    do {
        // Display menu options
        cout << "Menu:\n"
             << "1. Add new record\n"
             << "2. Display specific record\n"
             << "3. Change a record\n"
             << "4. Display all records\n"
             << "5. Prepare a report\n"
             << "0. Exit\n"
             << "Enter your choice: ";
        cin >> choice; // Read user's choice

        // Process user's choice
        switch (choice) {
        case 1:
            addRecordToFile(filename); // Add a new record to the file
            break;
        case 2: {
            cin.ignore(); // Clear the newline character from the previous input
            string itemName;
            cout << "Enter the name or first few letters of the item: ";
            getline(cin, itemName); // Read the item name or partial name
            displayRecordFromFile(filename, itemName); // Display the specified record
        }
        break;
        case 3:
            changeRecordInFile(filename); // Change an existing record in the file
            break;
        case 4:
            displayAllRecords(filename); // Display all records from the file
            break;
        case 5:
            prepareReport(filename); // Prepare and display a report from the file
            break;
        case 0:
            cout << "Exiting the program.\n"; // Exit the program
            break;
        default:
            cout << "Invalid choice. Please enter a valid option.\n"; // Handle invalid menu choices
        }
    } while (choice != 0); // Continue the loop until the user chooses to exit

    return 0;
}

// Function to add a new record to the file
void addRecordToFile(const string &filename) {
    ofstream outFile(filename, ios::app); // Open the file in append mode

    // Check if the file is open
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open the file for writing.\n";
        return;
    }

    InventoryItem newItem; // Create a new inventory item

    // Prompt user for item details
    cout << "Enter item name: ";
    cin.ignore(); // Clear the newline character from the previous input
    getline(cin, newItem.itemName); // Read item name

    cout << "Enter quantity on hand: ";
    cin >> newItem.quantityOnHand; // Read quantity on hand

    cout << "Enter wholesale cost: ";
    cin >> newItem.wholesaleCost; // Read wholesale cost

    cout << "Enter retail cost: ";
    cin >> newItem.retailCost; // Read retail cost

    // Input validation to ensure values are non-negative
    if (newItem.quantityOnHand < 0 || newItem.wholesaleCost < 0 || newItem.retailCost < 0) {
        cerr << "Error: Invalid input. Quantities and costs cannot be less than 0.\n";
        return;
    }

    // Write the new item details to the file
    outFile
        << newItem.itemName << " "
        << newItem.quantityOnHand << " "
        << newItem.wholesaleCost << " "
        << newItem.retailCost << endl;

    cout << "Record added successfully.\n"; // Confirm successful addition
    outFile.close(); // Close the file
}

// Function to display a specific record from the file based on item name or partial name
void displayRecordFromFile(const string &filename, const string &itemName) {
    ifstream inFile(filename); // Open the file for reading

    // Check if the file is open
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open the file for reading.\n";
        return;
    }

    InventoryItem currentItem; // Create an inventory item to hold data read from the file
    bool found = false; // Flag to check if a matching record is found

    // Read and display each record that matches the item name or partial name
    while (inFile >> currentItem.itemName >> currentItem.quantityOnHand >> currentItem.wholesaleCost >> currentItem.retailCost) {
        // Check if the item name contains the input substring
        if (currentItem.itemName.find(itemName) != string::npos) {
            found = true; // Set the flag to true if a match is found
            // Display the matching record
            cout << "Item Name: " << currentItem.itemName << endl;
            cout << "Quantity on Hand: " << currentItem.quantityOnHand << endl;
            cout << "Wholesale Cost: $" << fixed << setprecision(2) << currentItem.wholesaleCost << endl;
            cout << "Retail Cost: $" << fixed << setprecision(2) << currentItem.retailCost << endl;
            cout << "------------------------\n";
        }
    }

    // Display a message if no matching records are found
    if (!found) {
        cout << "No matching records found.\n";
    }

    inFile.close(); // Close the file
}

// Function to change an existing record in the file
void changeRecordInFile(const string &filename) {
    ifstream inFile(filename); // Open the file for reading
    ofstream tempFile("temp.txt"); // Open a temporary file for writing

    // Check if the files are open
    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "Error: Unable to open the file for reading or writing.\n";
        return;
    }

    InventoryItem currentItem; // Create an inventory item to hold data read from the file
    string itemNameToChange; // Name of the item to be changed
    bool changed = false; // Flag to check if a record was changed

    // Prompt user for the name of the item to change
    cout << "Enter the name of the item to change: ";
    cin.ignore(); // Clear the newline character from the previous input
    getline(cin, itemNameToChange); // Read the item name

    // Read and process each record
    while (inFile >> currentItem.itemName >> currentItem.quantityOnHand >> currentItem.wholesaleCost >> currentItem.retailCost) {
        // Check if the current item's name matches the input name
        if (currentItem.itemName == itemNameToChange) {
            // Prompt user for new item details
            cout << "Enter the new record:\n";

            cout << "Enter item name: ";
            cin.ignore(); // Clear the newline character from the previous input
            getline(cin, currentItem.itemName); // Read new item name

            cout << "Enter quantity on hand: ";
            cin >> currentItem.quantityOnHand; // Read new quantity on hand

            cout << "Enter wholesale cost: ";
            cin >> currentItem.wholesaleCost; // Read new wholesale cost

            cout << "Enter retail cost: ";
            cin >> currentItem.retailCost; // Read new retail cost

            // Input validation to ensure values are non-negative
            if (currentItem.quantityOnHand < 0 || currentItem.wholesaleCost < 0 || currentItem.retailCost < 0) {
                cerr << "Error: Invalid input. Quantities and costs cannot be less than 0.\n";
                return;
            }

            changed = true; // Set the flag to true if a record was changed
        }

        // Write the current item (changed or unchanged) to the temporary file
        tempFile << currentItem.itemName << " "
                 << currentItem.quantityOnHand << " "
                 << currentItem.wholesaleCost << " "
                 << currentItem.retailCost << endl;
    }

    // Display a message if no matching record was found
    if (!changed) {
        cout << "No matching record found for the item name: " << itemNameToChange << endl;
    } else {
        cout << "Record changed successfully.\n"; // Confirm successful change
    }

    inFile.close(); // Close the input file
    tempFile.close(); // Close the temporary file

    // Rename the temporary file to the original filename
    if (remove(filename.c_str()) != 0) {
        cerr << "Error: Unable to remove the original file.\n";
        return;
    }

    if (rename("temp.txt", filename.c_str()) != 0) {
        cerr << "Error: Unable to rename the temporary file.\n";
    }
}

// Function to display all records from the file
void displayAllRecords(const string &filename) {
    ifstream inFile(filename); // Open the file for reading

    // Check if the file is open
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open the file for reading.\n";
        return;
    }

    InventoryItem currentItem; // Create an inventory item to hold data read from the file

    // Display the table header
    cout << left << setw(20) << "Item Name"
         << setw(20) << "Quantity on Hand"
         << setw(20) << "Wholesale Cost"
         << setw(20) << "Retail Cost" << endl;
    cout << "-------------------------------------------------------------\n";

    // Read and display each record from the file
    while (inFile >> currentItem.itemName >> currentItem.quantityOnHand >> currentItem.wholesaleCost >> currentItem.retailCost) {
        cout << left << setw(20) << currentItem.itemName
             << setw(20) << currentItem.quantityOnHand
             << setw(20) << "$" << fixed << setprecision(2) << currentItem.wholesaleCost
             << setw(20) << "$" << fixed << setprecision(2) << currentItem.retailCost << endl;
    }

    inFile.close(); // Close the file
}

// Function to prepare a report from the file
void prepareReport(const string &filename) {
    ifstream inFile(filename); // Open the file for reading

    // Check if the file is open
    if (!inFile.is_open()) {
        cerr << "Error: Unable to open the file for reading.\n";
        return;
    }

    InventoryItem currentItem; // Create an inventory item to hold data read from the file
    double totalWholesaleValue = 0.0; // Total wholesale value of inventory
    double totalRetailValue = 0.0; // Total retail value of inventory
    int totalQuantity = 0; // Total quantity of all items in inventory

    // Read and process each record to calculate totals
    while (inFile >> currentItem.itemName >> currentItem.quantityOnHand >> currentItem.wholesaleCost >> currentItem.retailCost) {
        totalWholesaleValue += currentItem.wholesaleCost * currentItem.quantityOnHand; // Calculate total wholesale value
        totalRetailValue += currentItem.retailCost * currentItem.quantityOnHand; // Calculate total retail value
        totalQuantity += currentItem.quantityOnHand; // Calculate total quantity
    }

    // Display the report
    cout << "Report:\n"
         << "a. Total Wholesale Value of Inventory: $" << fixed << setprecision(2) << totalWholesaleValue << endl
         << "b. Total Retail Value of Inventory: $" << fixed << setprecision(2) << totalRetailValue << endl
         << "c. Total Quantity of All Values in the Inventory: " << totalQuantity << endl;

    inFile.close(); // Close the file
}
