# PharmaSystem - Pharmacy Management System

A comprehensive pharmacy management system built with Qt Framework, designed to help pharmacies manage their inventory, sales, and suppliers efficiently.

## Features

- **User Authentication**: Secure login system for staff members
- **Inventory Management**: Track and manage pharmaceutical products
- **Sales Management**: Process and record sales transactions
- **Supplier Management**: Manage supplier information and orders
- **PDF Generation**: Generate reports and invoices in PDF format
- **Database Integration**: SQLite database for data persistence

## Technology Stack

- **Framework**: Qt 5
- **Language**: C++
- **Database**: SQLite
- **Build System**: qmake
- **UI Design**: Qt Designer

## Project Structure

```
PharmaSystem/
├── controllers/      # Business logic controllers
├── models/          # Data models
├── views/           # UI views
├── utils/           # Utility functions
├── database/        # Database related files
├── assets/         # Resource files
└── config/         # Configuration files
```

## Prerequisites

- Qt 5.x or higher
- C++ compiler (GCC/Clang)
- SQLite3
- Make

## Building from Source

1. Clone the repository:
```bash
git clone https://github.com/Itz-SuleX5/PharmaSystem.git
```

2. Navigate to the project directory:
```bash
cd PharmaSystem
```

3. Generate Makefile:
```bash
qmake PharmaSystemQT.pro
```

4. Build the project:
```bash
make
```

## Running the Application

After building, run the application:
```bash
./PharmaSystemQT
```

## Features in Detail

### Inventory Management
- Add/Edit/Delete products
- Track stock levels
- Set reorder points
- Product categorization

### Sales Management
- Process sales transactions
- Generate invoices
- View sales history
- Daily/Monthly reports

### Supplier Management
- Manage supplier information
- Track orders
- Supplier contact details

## Database Schema

The system uses SQLite for data storage, with tables for:
- Users
- Products
- Sales
- Suppliers
- Inventory

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details. 