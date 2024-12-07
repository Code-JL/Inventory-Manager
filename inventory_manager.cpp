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
		cout << "Name: " << name
		     << ", Description: " << description
		     << ", Amount: " << amount
		     << ", Image: " << imagePath << "\n";
	}

	//increase item quantity
	void increment() {
		++amount;
	}

	// Decrease item quantity
    void decrement() {
        if (amount > 0) {
            --amount;
        } else {
            cout << "Warning: Cannot decrement. Item count is already 0.\n";
        }
	}

	bool operator==(const Item& other) const {
        return name == other.name && 
               description == other.description && 
               amount == other.amount && 
               imagePath == other.imagePath;
    }

	/**
	 * Deletes an item from the inventory.
	 *
	 * @param items The vector to delete the item from.
	 * @param itemName The name of the item to delete.
	 */
	void deleteItem(vector<Item>& items, const string& itemName) {
		auto it = find_if(items.begin(), items.end(), [&itemName](const Item& item) {
			// Find the item in the vector based on its name
			return item.getName() == itemName;
		});

		if (it != items.end()) {
			// Remove the item from the vector
			items.erase(it);
			cout << "Item deleted successfully!\n";
		} else {
			cout << "Error: Item not found.\n";
		}
	}
};

/**
 * Saves items to a CSV file at the specified file path.
 * 
 * @param items The vector of items to be saved.
 * @param filePath The path to the CSV file where items will be saved.
 */
void saveItemsToFile(const vector<Item> &items, const string &filePath) {
	// Ensure the "save" directory exists
	filesystem::create_directory("save");

	// Open the file for writing
	ofstream file(filePath);
	if (!file.is_open()) {
		// If the file cannot be opened, print an error message and return
		cout << "Error: Could not open file for saving.\n";
		return;
	}

	// Write each item to the file in CSV format
	for (const auto &item : items) {
		file << item.getName() << "," 
		     << item.getDescription() << "," 
		     << item.getAmount() << "," 
		     << item.getImage() << "\n";
	}

	// Close the file after writing
	file.close();
	cout << "Items saved successfully to " << filePath << endl;
}

// Function to load items from a CSV file
/**
 * Loads items from a CSV file and stores them in the provided vector.
 *
 * @param items The vector to store the loaded items in.
 * @param filePath The path to the CSV file to load from.
 */
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
			// Create a new item and add it to the vector
			items.emplace_back(fields[0], fields[1], stoi(fields[2]), fields[3]);
		} else {
			cout << "Warning: Skipping invalid line in file.\n";
		}
	}

	file.close();
	cout << "Items loaded successfully from " << filePath << endl;
}

//This function will get an item from an inventory, by being given the name of the item. it will then return the item
const Item* GetItemByName(const vector<Item>& items, const string& name) {
	auto it = lower_bound(items.begin(), items.end(), name, [](const Item& item, const string& other) {
		return item.getName() < other;
	});

	if (it != items.end() && it->getName() == name) {
		return &*it;
	}

	return nullptr;
}

vector<Item> LoadScreen(vector<Item> items, string saveFilePath) {

	int choice;
	while (choice != 0) {
		cout << "1. New Inventory\n";
		cout << "2. Load Inventory\n";
		cout << "0. Exit\n";

		cin >> choice;

		switch (choice)
		{
		case 0:
			cout << "Exiting.";
			return {};

		case 1:
			items.emplace_back("Sample Sign", "A sample sign, simple but effective", 1, "images/sample.jpg");
			break;

		case 2:
			loadItemsFromFile(items, saveFilePath);
			break;

		default:
			cout << "Invalid choice. Try again.\n";
			break;
		}
	}
	return items;
}
// Main function
int main() {

	// Save file path
	const string saveFilePath = "save/inventory.csv";

	vector<Item> items;
	items = LoadScreen(items, saveFilePath);

	while (true) {
		// Displays item list
		if (items.empty()) {
				cout << "No items to display.\n";
			} else {
				for (const auto &item : items) {
					item.display();
				}
			}

		cout << "1. Interact with an item\n";
		cout << "2. Add an item\n";
		cout << "3. Save items\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		
		int choice;
		cin >> choice;

		if (choice == 1)
		{
			string item_name;
			Item* current_item;

			cout << "Name of item: ";
			cin >> item_name;

			auto it = find_if(items.begin(), items.end(), [&item_name](const Item& item) {
				return item.getName() == item_name;
			});
			if (it != items.end()) {
				current_item = &*it;
				current_item->display();

				while (true) {
					cout << "What would you like to do with the item?\n";
					cout << "1. Change name\n";
					cout << "2. Change description\n";
					cout << "3. Change image path\n";
					cout << "4. Increment item count\n";
					cout << "5. Decrement item count\n";
					cout << "6. Delete item\n";
					cout << "0. Exit\n";

					int subchoice;
					cin >> subchoice;

					string input;

					if (subchoice == 1) {
						cout << "Enter new name: ";
						cin.ignore();
						getline(cin, input);
						current_item->setName(input);
					} else if (subchoice == 2) {
						cout << "Enter new description: ";
						getline(cin, input);
						current_item->setDescription(input);
					} else if (subchoice == 3) {
						cout << "Enter new image path: ";
						getline(cin, input);
						current_item->setImage(input);
					} else if (subchoice == 4) {
						current_item->increment();
					} else if (subchoice == 5) {
						current_item->decrement();
					} else if (subchoice == 6) {
						auto it = find(items.begin(), items.end(), *current_item);
						if (it != items.end()) {
							items.erase(it);
							cout << "Item deleted successfully!\n";
						} else {
							cout << "Error: Item not found.\n";
						}
					} else if (subchoice == 0) {
						cout << "Exiting.\n";
						return 0;
					} else {
						cout << "Invalid choice. Please try again.\n";
					}
				}

			}
			else {
				cout << "Item not found.\n";
			}
			
		}
		
		// Adds an item
		else if (choice == 2) {
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
		}
		// Saves the items to file
		else if (choice == 3) {
			saveItemsToFile(items, saveFilePath);
		}

		// Exits the program
		else if (choice == 0) {
			cout << "Exiting program. Goodbye!\n";
			return 0;
		}
		// Invalid choice
		else {
			cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}




