# Inventory Manager

A **C++ Inventory Management Program** designed to handle a collection of items with various attributes. This application will include item tracking, inventory persistence, and a graphical user interface (GUI) for ease of use.

---

## Features

### 1. Item Management
- Store multiple items with the following properties:
  - **Name**: Item name (case-insensitive, stored in lowercase).
  - **Description**: A string describing the item.
  - **Image**: An optional photo for the item.
  - **Count**: An integer representing the item's quantity.
- Each item is represented as an **instance of an object**:
  ```cpp
  struct Item {
      std::string name;
      std::string description;
      int count;
      // Image type can be implemented based on your GUI framework
  };
  ```

### 2. Item Quantity Adjustments
- **Increase** or **decrease** item quantities using `++` or `--`.
- Ability to **delete items** from the inventory.

### 3. Inventory Persistence
- Save the current inventory to a file.
- Load inventory data from a file.
- Start with a **default inventory sample** when no save data is available.
- Option to **switch between different save files**.

### 4. Graphical User Interface (GUI)
- **Scrollable item list**: Browse through items in the inventory.
- **Tabs** for:
  - Saving inventories.
  - Loading inventories.
  - Creating new inventories.
- **Detailed view**: Selecting an item displays its details.
- **Help tab**: Provides links to documentation and resources (e.g., a PDF manual and GitHub repository).

---

## Planned Structure

### Item Object
Each item will be stored as an object with attributes such as name, description, count, and image.

### Functions
- **Add Item**: Add a new item to the inventory.
- **Remove Item**: Delete an item from the inventory.
- **Adjust Quantity**: Increase or decrease the count of a specific item.
- **Save/Load Inventory**: Save the current state of the inventory to a file or load a previously saved inventory.

### GUI Implementation
The GUI will feature:
- A main screen with a scrollable list of items.
- Tabs for file operations (save/load), new inventory creation, and help.
- A detailed view of individual items with options to edit or delete.

---

## Getting Started

### Prerequisites
- A C++ compiler (e.g., GCC, Clang, or MSVC).
- A GUI framework (e.g., Qt, wxWidgets, or SFML) for implementing the graphical interface.

### Building the Project
1. Clone this repository:
   ```bash
   git clone https://github.com/username/inventory-manager.git
   ```
2. Build the project using your preferred build system (e.g., CMake):
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

---

## Future Enhancements
- Add image support for items.
- Implement advanced search and filtering options.
- Support for exporting inventory data to other formats (e.g., CSV, JSON).

---

## Help and Documentation
For detailed guidance, check out the [PDF Manual](link-to-pdf) or visit the [GitHub Repository](https://github.com/username/inventory-manager).

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
