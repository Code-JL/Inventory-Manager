# Inventory Manager

A **C++ Inventory Management Program** designed to handle a collection of items with various attributes. This application is a discontinued console-based program for managing inventory.

---

## Features

### 1. Item Management
- Store multiple items with the following properties:
  - **Name**: Item name (case-insensitive, stored in lowercase).
  - **Description**: A string describing the item.
  - **Count**: An integer representing the item's quantity.
  - **Image Path**: An optional path to an image associated with the item.

### 2. Inventory Management Options
- **Add Items**: Add new items with specified attributes (name, description, count, and image path).
- **Modify Items**:
  - Change item name.
  - Update description.
  - Set a new image path.
  - Increment or decrement item quantity.
- **Delete Items**: Remove items from the inventory.
- **View Items**: Display all items in the inventory.

### 3. File Operations
- **Save Inventory**: Save the current inventory to a CSV file.
- **Load Inventory**: Load items from a CSV file into the inventory.
- **Export Inventory**: Export the inventory to a user-specified file with a configurable delimiter (default is `,`).

### 4. Settings
- Configure the CSV export delimiter, ensuring compatibility with different formats.

### 5. User Interface
- Console-based menu system for easy navigation:
  - Main menu options include creating a new inventory, loading an inventory, and accessing settings.
  - Item interaction menu for modifying individual item attributes.

---

## Getting Started

### Prerequisites
- A C++ compiler (e.g., GCC, Clang, or MSVC).

### Building the Project
1. Clone this repository:
   ```bash
   git clone https://github.com/Code-JL/Inventory-Manager.git
   ```
2. Build the project using your preferred build system:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

---

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
