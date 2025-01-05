# Inventory Manager

A robust C++ inventory management system that allows users to create, modify, and track inventory items with detailed information and persistent storage capabilities.

## Features

- **Item Management**
  - Create new inventory items with name, description, quantity, and image path
  - Modify existing items (name, description, quantity, image path)
  - Increment/decrement item quantities
  - Delete items
  - Case-insensitive item search

- **Data Persistence**
  - Save inventory to CSV files
  - Load inventory from saved files
  - Export inventory with custom separators
  - Automatic settings management

- **User Interface**
  - Interactive command-line interface
  - Clear menu-driven operation
  - Input validation and error handling

## Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/Inventory-Manager.git
```
2. Navigate to the project directory:
```bash
cd Inventory-Manager
```
3. Compile the program:
```bash
g++ inventory_manager.cpp src/item_class.cpp src/save_load.cpp -o inventory_manager
```

## Usage

1. Run the compiled program:
```bash
./inventory_manager
```
2. Main Menu Options:
   - Create new inventory
   - Load existing inventory
   - Modify settings
   - Manage items
   - Save/Export inventory
   - File Structure

## File Structure
```bash
.
├── inventory_manager.cpp    # Main program file
├── src/
│   ├── item_class.h        # Item class declaration
│   ├── item_class.cpp      # Item class implementation
│   ├── save_load.h         # File operations declaration
│   └── save_load.cpp       # File operations implementation
└── save/
    ├── inventory.csv       # Default inventory storage
    └── settings.cfg        # Program settings
```

## Data Storage

- Inventory data is stored in CSV format
- Default save location: `save/inventory.csv`
- Custom export options available with configurable separators
- Settings stored in `save/settings.cfg`

## Configuration

- CSV separator character can be customized through settings
- Default separator: comma (,)
- Settings are persistent between sessions

## Contributing

- Fork the repository
- Create your feature branch (`git checkout -b feature/AmazingFeature`)
- Commit your changes (`git commit -m 'Add some AmazingFeature'`)
- Push to the branch (`git push origin feature/AmazingFeature`)
- Open a Pull Request

## License

This project is licensed under the terms of the included LICENSE file.

## Technical Details

- Written in C++
- Uses standard library containers (vector, list)
- Implements file I/O operations
- Supports CSV parsing and generation
- Error handling for file operations and user input

