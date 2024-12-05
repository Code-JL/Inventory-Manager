#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std; // Using the standard namespace

// Class representing an item
class Item {
private:
	// Member variables
	string name;                      // Item name (stored in lowercase)
	string description;               // Item description
	string imagePath;       // Path to a photo
	int amount;                       // Item quantity

	// Helper function to convert string to lowercase
	string toLowerCase(const string& str) const {
		string lowerStr = str;
		transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
		return lowerStr;
	}

public:
	// Constructor
    Item(const string& itemName, 
        const string& itemDescription, 
        int itemAmount, 
        const string& itemImagePath)
        : name(toLowerCase(itemName)), 
        description(itemDescription), 
        amount(itemAmount), 
        imagePath(itemImagePath) {}

	// Setter for the name (stored in lowercase)
	void setName(const string& itemName) {
		name = toLowerCase(itemName);
	}

	// Getter for the name
	string getName() const {
		return name;
	}

	// Setter for the description
	void setDescription(const string& itemDescription) {
		description = itemDescription;
	}

	// Getter for the description
	string getDescription() const {
		return description;
	}

	// Setter for the image path
	void setImage(const string& itemImagePath) {
		imagePath = itemImagePath;
	}

	// Getter for the image path
	string getImage() const {
		return imagePath;
	}

	// Setter for the amount
	void setAmount(int itemAmount) {
		amount = itemAmount;
	}

	// Getter for the amount
	int getAmount() const {
		return amount;
	}

	// Display the item's details (Temp)
	void display() const {
		cout << "Name: " << name << "\n"
		     << "Description: " << description << "\n"
		     << "Amount: " << amount << "\n"
		     << "Image: " << imagePath << "\n";
	}
};

int main() {

	vector<Item> items;
	items.emplace_back("Laptop", "A high-performance laptop.", 5, "images/laptop.jpg");

	while (true) {
		cout << "What would you like to do? (1: Read items, 2: Add an item, 0: Exit): ";
		int choice;
		cin >> choice;

		if (choice == 1) {
			if (items.empty()) {
				cout << "No items to display.\n";
			} else {
				for (const auto &item : items) {
					item.display();
				}
			}
		} else if (choice == 2) {
			string name, description, image;
			int amount;

			cout << "Enter item name: ";
			cin.ignore();
			getline(cin, name);

			cout << "Enter item description: ";
			getline(cin, description);

			cout << "Enter item amount: ";
			cin >> amount;

			cout << "Enter item image path: ";
			cin.ignore();
			getline(cin, image);

			items.emplace_back(name, description, amount, image);
			cout << "Item added successfully!\n";
		} else if (choice == 0) {
			cout << "Exiting program. Goodbye!\n";
			break;
		} else {
			cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}

