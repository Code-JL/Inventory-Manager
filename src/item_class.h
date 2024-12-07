#ifndef ITEM_CLASS_H
#define ITEM_CLASS_H

#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// Declaration of the toLowerCase function
string toLowerCase(const string& str);

// Class representing an item
class Item {
private:
    // Member variables
    string name;                // Item name (stored in lowercase)
    string description;         // Item description
    string imagePath;           // Path to a photo
    int amount;                 // Item quantity

public:
    // Constructor
    Item(const string& itemName, const string& itemDescription, int itemAmount, const string& itemImagePath);

    // Setter and getter for name
    void setName(const string& itemName);
    string getName() const;

    // Setter and getter for description
    void setDescription(const string& itemDescription);
    string getDescription() const;

    // Setter and getter for image path
    void setImage(const string& itemImagePath);
    string getImage() const;

    // Setter and getter for amount
    void setAmount(int itemAmount);
    int getAmount() const;

    // Display the item's details
    void display() const;

    // Increment and decrement item quantity
    void increment();
    void decrement();

    // Equality operator
    bool operator==(const Item& other) const;
};

#endif // ITEM_CLASS_H
