#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <filesystem>
#include <list>

using namespace std; // Using the standard namespace


// Helper function to convert string to lowercase
string toLowerCase(const string& str) {
	string lowerStr = str;
	transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
	return lowerStr;
}

// Class representing an item
class Item {
private:
	// Member variables
	string name;                      // Item name (stored in lowercase)
	string description;               // Item description
	string imagePath;       // Path to a photo
	int amount;                       // Item quantity

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
		     << " | Description: " << description
		     << " | Amount: " << amount
		     << " | Image: " << imagePath << "\n";
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
 * Escapes a field for CSV by doubling quotes and wrapping it in quotes.
 *
 * @param field The string to escape.
 * @return The escaped string.
 */
string escapeForCSV(const string &field) {
    string escapedField = "\"";
    for (char c : field) {
        if (c == '"') {
            escapedField += "\"\""; // Escape quotes
        } else {
            escapedField += c;
        }
    }
    escapedField += "\"";
    return escapedField;
}

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
        cout << "Error: Could not open file for saving.\n";
        return;
    }

    // Write each item to the file in CSV format
    for (const auto &item : items) {
        file << escapeForCSV(item.getName()) << "," // Accessing name using getName()
             << escapeForCSV(item.getDescription()) << ","
             << item.getAmount() << "," // Accessing amount using getAmount()
             << escapeForCSV(item.getImage()) << "\n";
    }

    // Close the file after writing
    file.close();
    cout << "Items saved successfully to " << filePath << endl;
}



/**
 * Splits a CSV line into fields, respecting quotes.
 *
 * @param line The line to split.
 * @return A vector of strings representing the fields.
 */
vector<string> parseCSVLine(const string &line) {
    vector<string> fields;
    string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (c == '"') {
            inQuotes = !inQuotes; // Toggle quote state
        } else if (c == ',' && !inQuotes) {
            // End of field
            fields.push_back(field);
            field.clear();
        } else {
            // Add to the current field
            field += c;
        }
    }
    fields.push_back(field); // Add the last field
    return fields;
}


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
        vector<string> fields = parseCSVLine(line);

        // Ensure the line has the correct number of fields
        if (fields.size() == 4) {
            try {
                // Create a new item and add it to the vector
                items.emplace_back(fields[0], fields[1], stoi(fields[2]), fields[3]);
            } catch (const invalid_argument &e) {
                cout << "Warning: Invalid number format in line. Skipping.\n";
            }
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


/**
 * Saves the given settings to the "save/settings.cfg" file.
 *
 * @param settings A list of strings representing the settings to save.
 */
void SaveSettings(const list<string>& settings) {
    ofstream file("save/settings.cfg");
    if (!file.is_open()) {
        cout << "Error: Could not open settings file for saving.\n";
        return;
    }

    // Write each setting to the file
    for (const auto& setting : settings) {
        file << setting << endl;
    }

    file.close();
    cout << "Settings saved successfully.\n";
}


bool fileDoesNotExist(const std::string& filePath) {
	std::ifstream file(filePath);
	return !file.is_open();  // Returns true if file does not exist
}
/**
 * Loads the settings from the "save/settings.cfg" file.
 *
 * @return A list of strings representing the settings.
 */
list<string> loadSettings() {

    list<string> settings;
    if (fileDoesNotExist("save/settings.cfg")) {
		cout << "Could not find settings file.\n";

        // Create a new settings file with default settings
        SaveSettings(list<string>{","});
        cout << "Created new settings file.\n";
	}

	ifstream file("save/settings.cfg");

    string line;
    // Read each line from the file and add it to the settings list
    while (getline(file, line)) {
        settings.push_back(line);
    }

    // Close the file after reading
    file.close();
    cout << "Settings loaded successfully.\n";
    return settings;
}

vector<Item> LoadScreen(vector<Item> items, string saveFilePath) {

	int choice = -1;
	char seperator = loadSettings().front()[0];

	while (choice != 0) {
		cout << "--------------------------------------\n";
		cout << "What would you like to do?\n";
		cout << "--------------------------------------\n";
		cout << "1. New Inventory\n";
		cout << "2. Load Inventory\n";
		cout << "3. Settings\n";
		cout << "0. Exit\n";

		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (choice) {
		case 0:
			cout << "Exiting.\n";
			return items;

		case 1:
			items.emplace_back("Sample Sign", "A sample sign, simple but effective", 1, "images/sample.jpg");
			return items;

		case 2:
			loadItemsFromFile(items, saveFilePath);
			return items;
		
		case 3:

			int subchoice;

			while (true) {
				cout << "--------------------------------------\n";
				cout << "Setting: What would you like to change?\n";
				cout << "--------------------------------------\n";
				cout << "1. CSV seperator\n";
				cout << "\t- Default = (,)\n";
				cout << "0. Back\n";

				cin >> subchoice;

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				string newseperator;

				if (subchoice == 1) {
					cout << "Current seperator = " << seperator << "\n";
					cout << "New seperator: ";

					cin >> newseperator;

					cin.ignore(numeric_limits<streamsize>::max(), '\n');

					if (newseperator == "\"" || newseperator == "\'") {
						cout << "Invalid seperator. Try again.\n";
					}
					else {
						seperator = newseperator[0];
						SaveSettings(list<string>{newseperator});
						break;
					}
				}
				else if (subchoice == 0) {
					cout << "Going back.\n";
					break;
				}
				else {
					cout << "Invalid choice. Please try again.\n";
				}

			}
			break;

		default:
			cout << "Invalid choice. Try again.\n";
			break;
		}
	}

	//This return should never be used, just here to prevent warnings
	return items;
}


// Main function
int main() {

	// Save file path
	const string saveFilePath = "save/inventory.csv";

	vector<Item> items;
	items = LoadScreen(items, saveFilePath);

	if (items.empty()) {
    	return 0;
	}

	while (true) {
		// Displays item list
		if (items.empty()) {
				cout << "No items to display.\n";
			} else {
				for (const auto &item : items) {
					item.display();
				}
			}

		cout << "--------------------------------------\n";
		cout << "What would you like to do?\n";
		cout << "--------------------------------------\n";
		cout << "1. Interact with an item\n";
		cout << "2. Add an item\n";
		cout << "3. Save items\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		
		int choice;
		cin >> choice;

		//handle invalid input
		if (cin.fail()){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, please enter a number.\n";
			continue;
		}

		if (choice == 1)
		{
			string item_name;
			Item* current_item;

			cout << "Name of item: ";

			cin.ignore(); // Clear leftover newline
        	getline(cin, item_name); // Safely read the entire line
			item_name = toLowerCase(item_name);

			auto it = find_if(items.begin(), items.end(), [&item_name](const Item& item) {
				return item.getName() == item_name;
			});
			if (it != items.end()) {
				current_item = &*it;

				while (true) {

					cout << "--------------------------------------\n";
					current_item->display();
					cout << "What would you like to do with this item?\n";
					cout << "--------------------------------------\n";
					cout << "1. Change name\n";
					cout << "2. Change description\n";
					cout << "3. Change image path\n";
					cout << "4. Increment item count\n";
					cout << "5. Decrement item count\n";
					cout << "6. Delete item\n";
					cout << "0. Back\n";

					int subchoice;
					cin >> subchoice;

					string input;

					if (subchoice == 1) {
						cout << "Current name: " << current_item->getName() << endl;
						cout << "New name: ";
						cin.ignore();
						getline(cin, input);
						current_item->setName(input);
					} else if (subchoice == 2) {
						cout << "Current description: " << current_item->getDescription() << endl;
						cout << "New description: ";
						cin.ignore();
						getline(cin, input);
						current_item->setDescription(input);
					} else if (subchoice == 3) {
						cout << "Current image path: " << current_item->getImage() << endl;
						cout << "New image path: ";
						cin.ignore();
						getline(cin, input);
						current_item->setImage(input);
					} else if (subchoice == 4) {
						cout << "Current count: " << current_item->getAmount() << endl;
						current_item->increment();
					} else if (subchoice == 5) {
						cout << "Current count: " << current_item->getAmount() << endl;
						current_item->decrement();
					} else if (subchoice == 6) {
						auto it = find(items.begin(), items.end(), *current_item);
						items.erase(it);
						cout << "Item deleted.\n";
						break;
					} else if (subchoice == 0) {
						cout << "Going back.\n";
						break;
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
			break;
		}
		// Invalid choice
		else {
			cout << "Invalid choice. Please try again.\n";
		}
	}

	return 0;
}




