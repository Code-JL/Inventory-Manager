#include "save_load.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>


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
void saveItemsToFile(const vector<Item> &items, const string &filePath, char seperator) {
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
        file << escapeForCSV(item.getName()) << seperator // Accessing name using getName()
             << escapeForCSV(item.getDescription()) << seperator
             << item.getAmount() << seperator // Accessing amount using getAmount()
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

bool fileDoesNotExist(const std::string& filePath) {
	std::ifstream file(filePath);
	return !file.is_open();  // Returns true if file does not exist
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
    return settings;
}