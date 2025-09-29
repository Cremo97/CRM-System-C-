# Master AI Engineering - C++ Project - InsuraPro CRM System

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue)
![Version](https://img.shields.io/badge/Version-1.0-green)
![Author](https://img.shields.io/badge/Author-Davide%20Cremonesi-orange)


## 📋 Overview
InsuraPro is a comprehensive Customer Relationship Management (CRM) system specifically designed for insurance companies. Built with modern C++ principles, it provides a robust solution for managing customer data, scheduling appointments, and tracking insurance contracts.

The system offers an intuitive command-line interface that allows insurance agents to efficiently handle customer information, maintain detailed interaction histories, and generate comprehensive reports. With support for both TXT and CSV file formats, InsuraPro seamlessly integrates with existing workflows and external analysis tools.

## 🚀 How to Run the Project


### 🔧 Compilation

#### Option 1: Direct Compilation
```bash
# Compile with g++
g++ -o main.exe main.cpp Appointment.cpp Interaction.cpp Contract.cpp Customer.cpp CustomerHandler.cpp FileHandler.cpp CRM.cpp
```


#### Option 2: IDE 
1. Open all `.cpp` and `.h` files in your IDE
2. Set `main.cpp` as the main file
3. Compile and run the project

### 📁 Project Structure

```
insurapro-crm/
├── main.cpp                                  # Program entry point
├── CRM.h / CRM.cpp                           # User interface and main control
├── Customer.h / Customer.cpp                 # Customer data management
├── CustomerHandler.h / CustomerHandler.cpp   # Customer collection management
├── Interaction.h / Interaction.cpp           # Abstract base class
├── Appointment.h / Appointment.cpp           # Appointment management
├── Contract.h / Contract.cpp                 # Contract management
├── FileHandler.h / FileHandler.cpp           # File I/O (TXT/CSV)
├── README.md                                 # This file
.
.
└── html/index.html                           # HTML documentation home automatically generated with Doxygen

```

## 📖 Quick User Guide

### Main Menu
After startup, the system presents a menu with 10 options:

1. **Add Customer**: Insert new customer
2. **View All Customers**: Display all customers
3. **Search Customer**: Search by ID, name or email
4. **Add Appointment**: Add appointment to a customer
5. **Add Contract**: Add contract to a customer
6. **Edit Interaction**: Modify existing appointments or contracts
7. **Save Data**: Save in TXT or CSV format
8. **Load Data**: Load data from existing file
9. **View Statistics**: System statistics
0. **Exit**: Exit (with save option)   (option 0)


### Data Files
The system supports two formats:
- **TXT**: Human-readable format for backup and review
- **CSV**: Spreadsheet format for external analysis

## 📚 Technical Documentation

The project includes complete documentation generated with Doxygen available in web page format under the *html/index.html* folder:

### Regenerate Documentation
```bash
# Make sure Doxygen is installed
doxygen Doxyfile

# Open documentation
# Windows
start html/index.html

# macOS
open html/index.html

# Linux
xdg-open html/index.html
```

### Documentation Content
- **API Reference**: Complete documentation of all classes and methods
- **Class Diagrams**: UML diagrams of class relationships
- **File Dependencies**: Graphs of file dependencies
- **Source Code**: Annotated and navigable source code

The documentation integrates this README as the main page for smooth navigation between user guide and technical reference.

## 🧪 Testing

### Basic Functionality Test
1. Start the program
2. Add a test customer
3. Create an appointment for the customer
4. Create a contract for the customer
5. Save data in CSV or TXT format
6. Restart the program and load data (you can also use the *test_data.csv* or *test_data.txt* files)
7. Verify that all data is present

## 💡 Technical Notes

### Design Patterns Used
- **Polymorphism**: Appointment and Contract classes derive from Interaction
- **RAII**: Automatic memory management with smart pointers
- **Single Responsibility**: Each class has a specific responsibility
- **Static Factory Methods**: Centralized validation

### Modern C++ Features
- Smart pointers (`unique_ptr`) for automatic memory management
- Range-based for loops
- Exception handling with `invalid_argument`
- Const correctness
- Initialization lists in constructors

## 📝 File Formats

### CSV Format
Header: `CustomerID,FirstName,LastName,Email,PhoneNumber,InteractionType,InteractionID,Date,Description,AppointmentType,AppointmentStatus,ContractNumber,PolicyType,AnnualPremium,ExpirationDate`

### TXT Format
Structured human-readable format with dedicated sections for each customer and their interactions.


## 👨‍💻 Author

**Davide Cremonesi**
- Project developed for **High Performance Programming with C++** module
- Date: August 2025
- Version: 1.0


---

💼 **InsuraPro Solutions** - *Improving efficiency and customer service quality for insurance companies*
