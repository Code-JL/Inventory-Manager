#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "item_class.h"
#include <string>
#include <vector>
#include <list>

using namespace std;

/**
 * Escapes a field for CSV by doubling quotes and wrapping it in quotes.
 *
 * @param field The string to escape.
 * @return The escaped string.
 */
string escapeForCSV(const string &field);

/**
 * Saves items to a CSV file at the specified file path.
 *
 * @param items The vector of items to be saved.
 * @param filePath The path to the CSV file where items will be saved.
 * @param seperator The separator character (default is comma).
 */
void saveItemsToFile(const vector<Item> &items, const string &filePath, char separator = ',');

/**
 * Splits a CSV line into fields, respecting quotes.
 *
 * @param line The line to split.
 * @return A vector of strings representing the fields.
 */
vector<string> parseCSVLine(const string &line);

/**
 * Loads items from a CSV file and stores them in the provided vector.
 *
 * @param items The vector to store the loaded items in.
 * @param filePath The path to the CSV file to load from.
 */
void loadItemsFromFile(vector<Item> &items, const string &filePath);

/**
 * Checks if a file does not exist.
 *
 * @param filePath The path to the file.
 * @return True if the file does not exist, false otherwise.
 */
bool fileDoesNotExist(const string &filePath);

/**
 * Saves the given settings to the "save/settings.cfg" file.
 *
 * @param settings A list of strings representing the settings to save.
 */
void SaveSettings(const list<string> &settings);

/**
 * Loads the settings from the "save/settings.cfg" file.
 *
 * @return A list of strings representing the settings.
 */
list<string> loadSettings();

#endif // SAVE_LOAD_H

