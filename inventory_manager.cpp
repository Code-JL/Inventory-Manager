#include "src/item_class.h"
#include "src/save_load.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <list>


using namespace std; // Using the standard namespace

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

	int choice = -1;

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
				cout << "1. Export CSV seperator\n";
				cout << "\t- Default = (,)\n";
				cout << "0. Back\n";

				cin >> subchoice;

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				string newseperator;

				if (subchoice == 1) {
					char seperator = loadSettings().front()[0];
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

	char seperator = loadSettings().front()[0];
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
		cout << "3. Save inventory\n";
		cout << "4. Export inventory\n";
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
					cout << "4. Increment amount\n";
					cout << "5. Decrement amount\n";
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
			cin.ignore();
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
		else if (choice == 4) {
			cout << "Name of export file: ";
			cin.ignore();
			string exportname;
			getline(cin, exportname);
			saveItemsToFile(items, "export/" + exportname + ".csv", seperator);

			cout << "Items saved successfully  exported to export/" << exportname << ".csv\n";
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




