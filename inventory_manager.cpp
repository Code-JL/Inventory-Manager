#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <filesystem>

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

void saveItemsToFile(const vector<Item> &items, const string &filePath) {
	// Ensure the "save" directory exists
	filesystem::create_directory("save");

	ofstream file(filePath);
	if (!file.is_open()) {
		cout << "Error: Could not open file for saving.\n";
		return;
	}

	for (const auto &item : items) {
		file << item.getName() << "," << item.getDescription() << "," << item.getAmount() << "," << item.getImage() << "\n";
	}

	file.close();
	cout << "Items saved successfully to " << filePath << endl;
}

// Function to load items from a CSV file
void loadItemsFromFile(vector<Item> &items, const string &filePath) {
	ifstream file(filePath);
	if (!file.is_open()) {
		cout << "Error: Could not open file for loading.\n";
		return;
	}

	string line;
	while (getline(file, line)) {
		size_t pos = 0;
		vector<string> fields;

		// Split the line by commas
		while ((pos = line.find(',')) != string::npos) {
			fields.push_back(line.substr(0, pos));
			line.erase(0, pos + 1);
		}
		fields.push_back(line); // Add the last field

		// Ensure the line has the correct number of fields
		if (fields.size() == 4) {
			items.emplace_back(fields[0], fields[1], stoi(fields[2]), fields[3]);
		} else {
			cout << "Warning: Skipping invalid line in file.\n";
		}
	}

	file.close();
	cout << "Items loaded successfully from " << filePath << endl;
}


// Main function
int main() {
	vector<Item> items;
	items.emplace_back("Laptop", "A high-performance laptop.", 5, "images/laptop.jpg");

	const string saveFilePath = "save/inventory.csv";

	while (true) {
		cout << "What would you like to do? (1: Read items, 2: Add an item, 3: Save items, 4: Load items, 0: Exit): ";
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
		} else if (choice == 3) {
			saveItemsToFile(items, saveFilePath);
		} else if (choice == 4) {
			loadItemsFromFile(items, saveFilePath);
		} else if (choice == 0) {
			cout << "Exiting program. Goodbye!\n";
			break;
		} else {
			cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}

