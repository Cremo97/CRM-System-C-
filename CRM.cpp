/**
 * @file CRM.cpp
 * @brief Implementation of the CRM class for insurance CRM System
 * @author Davide Cremonesi
 * @date 13/08/2025
 * @version 1.0
 */

#include "CRM.h"

// PRIVATE METHODS - USER INTERFACE

void CRM::displayMainMenu() const {
    system("clear || cls");  // Clear screen (works on both Unix and Windows)
    
    cout << "\n" << string(50, '=') << endl;
    cout << "         INSURAPRO CRM - MAIN MENU" << endl;
    cout << string(50, '=') << endl;
    cout << "Database: " << customerHandler.getCustomerCount() << " customers" << endl;
    cout << string(50, '-') << endl;
    cout << "1. Add Customer" << endl;
    cout << "2. View All Customers" << endl;
    cout << "3. Search Customer" << endl;
    cout << "4. Add Appointment" << endl;
    cout << "5. Add Contract" << endl;
    cout << "6. Edit Interaction" << endl;
    cout << "7. Save Data" << endl;
    cout << "8. Load Data" << endl;
    cout << "9. View Statistics" << endl;
    cout << "0. Exit" << endl;
    cout << string(50, '=') << endl;
    cout << "Choice: ";
}

// PRIVATE METHODS - INPUT VALIDATION UTILITIES

int CRM::getUserChoice(int min, int max) const {
    int choice;
    while (true) {
        if (cin >> choice && choice >= min && choice <= max) {      // If something is inserted and it is >= min and <= max
            clearInputBuffer();
            return choice;
        } else {
            cout << "Invalid! Enter " << min << "-" << max << ": ";
            clearInputBuffer();
        }
    }
}

string CRM::getUserInput(const string& prompt) const {
    string input;
    cout << prompt;
    
    // If cin is "clean", ignore the newline
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    
    getline(cin, input);
    return input;
}

int CRM::getUserInt(const string& prompt) const {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {         // Check that the input type is equals to the "value" type
            clearInputBuffer();
            return value;
        } else {
            cout << "Invalid number! Try again: ";
            clearInputBuffer();
        }
    }
}

float CRM::getUserFloat(const string& prompt) const {
    float value;
    while (true) {
        cout << prompt;
        if (cin >> value && value > 0) {
            clearInputBuffer();
            return value;
        } else {
            cout << "Invalid! Enter positive number: ";
            clearInputBuffer();
        }
    }
}

void CRM::clearInputBuffer() const {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Empty the buffer until newline
}

void CRM::waitForEnter() const {
    cout << "\nPress Enter to continue...";
    cin.get();                                            // Ready to read
}

bool CRM::isDateGreater(const string& date1, const string& date2) const {
    // Convert DD/MM/YYYY format to YYYYMMDD for checking
    
    string day1 = date1.substr(0, 2);
    string month1 = date1.substr(3, 2);
    string year1 = date1.substr(6, 4);
    
    string day2 = date2.substr(0, 2);
    string month2 = date2.substr(3, 2);
    string year2 = date2.substr(6, 4);
    
    string comparable1 = year1 + month1 + day1;
    string comparable2 = year2 + month2 + day2;
    
    return comparable1 > comparable2;
}


// CONSTRUCTOR

CRM::CRM() {
    // Empty constructor - CustomerHandler is automatically initialized
}

// PUBLIC METHODS - MAIN SYSTEM CONTROL

void CRM::start() {
    cout << "\n" << string(60, '=') << endl;
    cout << "           WELCOME TO INSURAPRO CRM SYSTEM" << endl;
    cout << "           Customer Relationship Management" << endl;
    cout << "                   Coded with <3 by" << endl;
    cout << "                   Davide Cremonesi" << endl;
    cout << string(60, '=') << endl;
    cout << "Starting with empty database." << endl;
    cout << "Use 'Load Data' option to import existing customer data." << endl;
    
    waitForEnter();
    runMainMenu();
}

void CRM::runMainMenu(){
    int choice;

    do {
        displayMainMenu();
        choice = getUserChoice(0, 9);   // Checks the input
        
        switch (choice) {
            case 1: {  // Add Customer
                cout << "\n=== ADD NEW CUSTOMER ===" << endl;
                string firstName, lastName, email, phone;
                bool success = false;
                
                // First Name
                while (true) {
                    firstName = getUserInput("First name: ");
                    if (firstName.empty()) {
                        cout << "First name cannot be empty. Please try again." << endl;
                    } else {
                        break;
                    }
                }
                
                // Last Name  
                while (true) {
                    lastName = getUserInput("Last name: ");
                    if (lastName.empty()) {
                        cout << "Last name cannot be empty. Please try again." << endl;
                    } else {
                        break;
                    }
                }
                
                // Email 
                while (true) {
                    email = getUserInput("Email: ");
                    if (email.empty()) {
                        cout << "Email cannot be empty. Please try again." << endl;
                        continue;
                    }
                    
                    // Static validation method
                    if (!Customer::isValidEmail(email)) {
                        cout << "Invalid email format. Must contain @ and not be empty." << endl;
                        continue;
                    }
                    
                    break;  // Email is valid
                }
                
                // Phone Number
                while (true) {
                    phone = getUserInput("Phone number (10 digits): ");
                    if (phone.empty()) {
                        cout << "Phone number cannot be empty. Please try again." << endl;
                        continue;
                    }
                    
                    // Static validation method 
                    if (!Customer::isValidPhoneNumber(phone)) {
                        cout << "Invalid phone number. Must be exactly 10 digits." << endl;
                        continue;
                    }
                    
                    break;  // Phone is valid
                }
                
                // Show summary and confirm
                cout << "\n--- Customer Summary ---" << endl;
                cout << "Name: " << firstName << " " << lastName << endl;
                cout << "Email: " << email << endl;
                cout << "Phone: " << phone << endl;
                
                string confirm = getUserInput("\nIs this information correct? (yes/no): ");
                if (confirm == "yes" || confirm == "y" || confirm == "YES" || confirm == "Y") {
                    try {
                        auto customer = make_unique<Customer>(firstName, lastName, email, phone);
                        cout << "Customer created with ID: " << customer->getCustomerID() << endl;
                        customerHandler.addCustomer(move(customer));
                        cout << "Customer added successfully!" << endl;
                    } catch (const exception& e) {
                        cout << "Unexpected error: " << e.what() << endl;
                    }
                } else {
                    cout << "Customer creation cancelled." << endl;
                }
                            waitForEnter();
                            break;
            }
            
            case 2: {  // View All Customers
                cout << "\n=== ALL CUSTOMERS ===" << endl;
                customerHandler.printAllCustomersSummary();
                
                waitForEnter();
                break;
            }
            
            case 3: {  // Search Customer
                cout << "\n=== SEARCH CUSTOMER ===" << endl;
                if (customerHandler.isEmpty()) {
                    cout << "No customers in the system. Add some customers first!" << endl;
                    waitForEnter();
                    break;
                }
                while(true){
                    cout << "\nSearch options:" << endl;
                    cout << "1. By ID  2. By Name  3. By Email  0. Back to Main Menu" << endl;
                    int searchChoice = getUserChoice(0, 3);
                    
                    if (searchChoice == 0) {
                        break;
                    }
                    
                    bool found = false;
                    while(!found)
                        if (searchChoice == 1) {
                            int id = getUserInt("Enter Customer ID: ");
                            Customer* customer = customerHandler.findCustomerByID(id);
                            if (customer) {
                                customer->printCompleteProfile();
                                found = true;
                            } else {
                                cout << "Customer not found." << endl;
                                break;
                            }
                        } else if (searchChoice == 2) {
                            string name = getUserInput("Enter name to search: ");
                            auto results = customerHandler.searchCustomersByFullName(name);
                            if (results.empty()) {
                                cout << "No customers found." << endl;
                                break;
                            } else {
                                cout << "Found " << results.size() << " customer(s):" << endl;
                                for (auto* customer : results) {
                                    customer->printCustomerInfo();
                                    cout << endl;
                                }
                                found = true;
                            }
                        } else if (searchChoice == 3) {
                            string email = getUserInput("Enter email to search: ");
                            auto results = customerHandler.searchCustomersByEmail(email);
                            if (results.empty()) {
                                cout << "No customers found." << endl;
                                break;
                            } else {
                                cout << "Found " << results.size() << " customer(s):" << endl;
                                for (auto* customer : results) {
                                    customer->printCustomerInfo();
                                    cout << endl;
                                }
                                found = true;
                            }
                        }
                    }
                
                waitForEnter();
                break;
            }
            
            case 4: {  // Add Appointment
                cout << "\n=== ADD APPOINTMENT ===" << endl;
                if (customerHandler.isEmpty()) {
                    cout << "No customers in system. Add customers first." << endl;
                } else {
                    int id = getUserInt("Enter Customer ID: ");
                    Customer* customer = customerHandler.findCustomerByID(id);
                    if (!customer) {
                        cout << "Customer not found." << endl;
                    } else {
                        cout << "Customer: " << customer->getFullName() << endl;
                        try {
                            // Date
                            string date;
                            while (true) {
                                date = getUserInput("Date (DD/MM/YYYY): ");
                                if (date.empty()) {
                                    cout << "Date cannot be empty. Please try again." << endl;
                                    continue;
                                }
                                
                                // Static validation method
                                if (!Interaction::isValidDate(date)) {
                                    cout << "Invalid Date format. Must be (DD/MM/YYYY) format and not be empty." << endl;
                                    continue;
                                }
                                
                                break;  // Date is valid
                            }
                            string description = getUserInput("Description: ");
                            
                            
                            // Type
                            string type;
                            while(true){
                                cout << "Types: Offering, Consultation, Follow-up" << endl;
                                type = getUserInput("Type: ");
                                if (type.empty()){
                                    cout << "Type cannot be empty. Please try again." << endl;
                                    continue;
                                }

                                // Static validation method
                                if(!Appointment::isValidAppointmentType(type)){
                                    cout << "Invalid Type format. Must be: Offering, Consultation, Follow-up and not be empty." << endl;
                                    continue;
                                }

                                break;  // Type is valid
                            }
                            
                            // Status
                            string status;
                            while(true){
                                cout << "Status: Scheduled, Completed, Cancelled" << endl; 
                                status = getUserInput("Status: ");
                                if (status.empty()){
                                    cout << "Status cannot be empty. Please try again." << endl;
                                    continue;
                                }

                                // Static validation method
                                if(!Appointment::isValidStatus(status)){
                                    cout << "Invalid Status format. Must be: Scheduled, Completed, Cancelled and not be empty." << endl;
                                    continue;
                                }

                                break;  // Status is valid
                            }
                            
                            auto appointment = make_unique<Appointment>(date, description, type, status);
                            customer->addInteraction(move(appointment));
                            cout << "Appointment added successfully!" << endl;
                        } catch (const exception& e) {
                            cout << "Error: " << e.what() << endl;
                        }
                    }
                }
                waitForEnter();
                break;
            }
            
            case 5: {  // Add Contract
                cout << "\n=== ADD CONTRACT ===" << endl;
                if (customerHandler.isEmpty()) {
                    cout << "No customers in system. Add customers first." << endl;
                } else {
                    int id = getUserInt("Enter Customer ID: ");
                    Customer* customer = customerHandler.findCustomerByID(id);
                    if (!customer) {
                        cout << "Customer not found." << endl;
                    } else {
                        cout << "Customer: " << customer->getFullName() << endl;
                        try {
                            
                            // Date
                            string date;
                            while (true) {
                                date = getUserInput("Date (DD/MM/YYYY): ");
                                if (date.empty()) {
                                    cout << "Date cannot be empty. Please try again." << endl;
                                    continue;
                                }
                                
                                // Static validation method
                                if (!Interaction::isValidDate(date)) {
                                    cout << "Invalid Date format. Must be (DD/MM/YYYY) format and not be empty." << endl;
                                    continue;
                                }
                                
                                break;  // Date is valid
                            }
                            // Description
                            string description = getUserInput("Description: ");
                           
                            // Policy Type
                            string policyType;
                            while(true){
                                cout << "Policy Types: Auto, Home, Life, Health" << endl;
                                policyType = getUserInput("Policy Type: ");
                                if (policyType.empty()){
                                    cout << "Policy Type cannot be empty. Please try again." << endl;
                                    continue;
                                }

                                // Static validation method
                                if(!Contract::isValidPolicyType(policyType)){
                                    cout << "Invalid Policy Type format. Must be: Auto, Home, Life, Health and not be empty." << endl;
                                    continue;
                                }

                                break;  // Policy Type is valid
                            }

                            // Annual premium
                            float premium;
                            while(true){
                                premium = getUserFloat("Annual premium (EUR): ");

                                // Static validation method
                                if(!Contract::isValidPremium(premium)){
                                    cout << "Invalid Annual premium. Must be greater than 0 and not be empty." << endl;
                                    continue;
                                }

                                break;  // Annual premium  is valid
                            }

                            // expirationDate
                            string expirationDate;
                            while (true) {
                                expirationDate = getUserInput("Expiration Date (DD/MM/YYYY): ");
                                if (expirationDate.empty()) {
                                    cout << "expirationDate cannot be empty. Please try again." << endl;
                                    continue;
                                }
                                
                                // Static validation method
                                if (!Interaction::isValidDate(expirationDate) || !isDateGreater(expirationDate, date)) {
                                    cout << "Invalid Expiration Date format. Must be (DD/MM/YYYY) format greater than Date and not be empty." << endl;
                                    continue;
                                }
                                
                                break;  // Expiration Date is valid
                            }

                        
                            auto contract = make_unique<Contract>(date, description, policyType, premium, expirationDate);
                            customer->addInteraction(move(contract));
                            cout << "Contract added successfully!" << endl;
                        } catch (const exception& e) {
                            cout << "Error: " << e.what() << endl;
                        }
                    }
                }
                waitForEnter();
                break;
            }
            
            case 6: {  // Edit Interaction
                cout << "\n=== EDIT INTERACTION ===" << endl;
                if (customerHandler.isEmpty()) {
                    cout << "No customers in system." << endl;
                } else {
                    int customerID = getUserInt("Enter Customer ID: ");
                    Customer* customer = customerHandler.findCustomerByID(customerID);
                    if (!customer) {
                        cout << "Customer not found." << endl;
                    } else if (customer->getInteractionCount() == 0) {
                        cout << "Customer has no interactions." << endl;
                    } else {
                        cout << "Customer: " << customer->getFullName() << endl;
                        customer->printAllInteractions();
                        
                        int interactionID = getUserInt("Enter Interaction ID to edit: ");
                        Interaction* interaction = customer->findInteractionByID(interactionID);
                        
                        if (!interaction) {
                            cout << "Interaction not found." << endl;
                        } else {
                            cout << "\nCurrent interaction details:" << endl;
                            interaction->printDetails();
                            
                            cout << "\nWhat to edit?" << endl;
                            cout << "1. Date  2. Description";
                            string newDate;
                            if (interaction->getType() == "Appointment") {
                                cout << "  3. Appointment Type  4. Status" << endl;
                                int editChoice = getUserChoice(1, 4);
                                
                                Appointment* apt = dynamic_cast<Appointment*>(interaction);
                                try {
                                    switch (editChoice) {
                                        case 1:{
                                            // Date
                                            
                                            while (true) {
                                                newDate = getUserInput("New Date (DD/MM/YYYY): ");
                                                if (newDate.empty()) {
                                                    cout << "Date cannot be empty. Please try again." << endl;
                                                    continue;
                                                }
                                                
                                                // Static validation method
                                                if (!Interaction::isValidDate(newDate)) {
                                                    cout << "Invalid Date format. Must be (DD/MM/YYYY) format and not be empty." << endl;
                                                    continue;
                                                }
                                                
                                                break;  // Date is valid
                                            }
                                            apt->setDate(newDate);
                                            break;
                                        }
                                        case 2:{
                                            apt->setDescription(getUserInput("New description: "));
                                            break;
                                        }
                                        case 3:{
                                            // Type
                                            string newType;
                                            while(true){
                                                cout << "Types: Offering, Consultation, Follow-up" << endl;
                                                newType = getUserInput("New Type: ");
                                                if (newType.empty()){
                                                    cout << "Type cannot be empty. Please try again." << endl;
                                                    continue;
                                                }

                                                // Static validation method
                                                if(!Appointment::isValidAppointmentType(newType)){
                                                    cout << "Invalid Type format. Must be: Offering, Consultation, Follow-up and not be empty." << endl;
                                                    continue;
                                                }

                                                break;  // Type is valid
                                            }
                                            apt->setAppointmentType(newType);
                                            break;
                                        }
                                        case 4:{
                                            // Status
                                            string newstatus;
                                            while(true){
                                                cout << "Status: Scheduled, Completed, Cancelled" << endl; 
                                                newstatus = getUserInput("New Status: ");
                                                if (newstatus.empty()){
                                                    cout << "Status cannot be empty. Please try again." << endl;
                                                    continue;
                                                }

                                                // Static validation method
                                                if(!Appointment::isValidStatus(newstatus)){
                                                    cout << "Invalid Status format. Must be: Scheduled, Completed, Cancelled and not be empty." << endl;
                                                    continue;
                                                }

                                                break;  // Status is valid
                                            }
                                            apt->setStatus(newstatus);
                                            break;
                                        }
                                    }
                                    cout << "Appointment updated successfully!" << endl;
                                } catch (const exception& e) {
                                    cout << "Error: " << e.what() << endl;
                                }
                                
                            } else if (interaction->getType() == "Contract") {
                                cout << "  3. Policy Type  4. Annual Premium  5. Expiration Date" << endl;
                                int editChoice = getUserChoice(1, 5);
                                
                                Contract* contract = dynamic_cast<Contract*>(interaction);
                                try {
                                    switch (editChoice) {
                                        case 1:{
                                            // Date
                                            
                                            while (true) {
                                                newDate = getUserInput("New Date (DD/MM/YYYY): ");
                                                if (newDate.empty()) {
                                                    cout << "Date cannot be empty. Please try again." << endl;
                                                    continue;
                                                }
                                                
                                                // Static validation method
                                                if (!Interaction::isValidDate(newDate)) {
                                                    cout << "Invalid Date format. Must be (DD/MM/YYYY) format and not be empty." << endl;
                                                    continue;
                                                }
                                                
                                                break;  // Date is valid
                                            }
                                            contract->setDate(newDate);
                                            break;
                                        }
                                        case 2:{
                                            contract->setDescription(getUserInput("New description: "));
                                            break;
                                        }
                                        case 3:{
                                            // Policy Type
                                            string newPolicyType;
                                            while(true){
                                                cout << "Policy Types: Auto, Home, Life, Health" << endl;
                                                newPolicyType = getUserInput("New Policy Type: ");
                                                if (newPolicyType.empty()){
                                                    cout << "Policy Type cannot be empty. Please try again." << endl;
                                                    continue;
                                                }

                                                // Static validation method
                                                if(!Contract::isValidPolicyType(newPolicyType)){
                                                    cout << "Invalid Policy Type format. Must be: Auto, Home, Life, Health and not be empty." << endl;
                                                    continue;
                                                }

                                                break;  // Policy Type is valid
                                            }
                                            contract->setPolicyType(newPolicyType);
                                            break;
                                        }
                                        case 4:{
                                            // Annual premium
                                            float newPremium;
                                            while(true){
                                                newPremium = getUserFloat("New Annual premium (EUR): ");

                                                // Static validation method
                                                if(!Contract::isValidPremium(newPremium)){
                                                    cout << "Invalid Annual premium. Must be greater than 0 and not be empty." << endl;
                                                    continue;
                                                }

                                                break;  // Annual premium  is valid
                                            }
                                            contract->setAnnualPremium(newPremium);
                                            break;
                                        }
                                        case 5:{
                                            // expirationDate
                                            string newExpirationDate;
                                            while (true) {
                                                newExpirationDate = getUserInput("New Expiration Date (DD/MM/YYYY): ");
                                                if (newExpirationDate.empty()) {
                                                    cout << "expirationDate cannot be empty. Please try again." << endl;
                                                    continue;
                                                }
                                                
                                                // Static validation method
                                                if (!Interaction::isValidDate(newExpirationDate) || !isDateGreater(newExpirationDate, contract->getDate())) {
                                                    cout << "Invalid Expiration Date format. Must be (DD/MM/YYYY) format greater than Date and not be empty." << endl;
                                                    continue;
                                                }
                                                
                                                break;  // Expiration Date is valid
                                            }
                                            contract->setExpirationDate(newExpirationDate);
                                            break;
                                        }
                                    }
                                    cout << "Contract updated successfully!" << endl;
                                } catch (const exception& e) {
                                    cout << "Error: " << e.what() << endl;
                                }
                            }
                        }
                    }
                }
                waitForEnter();
                break;
            }
            
            case 7: {  // Save Data
                cout << "\n=== SAVE DATA ===" << endl;
                if (customerHandler.isEmpty()) {
                    cout << "No data to save." << endl;
                } else {
                    cout << "1. Save as TXT  2. Save as CSV" << endl;
                    int saveChoice = getUserChoice(1, 2);
                    
                    string filename;
                    if (saveChoice == 1) {
                        filename = getUserInput("Enter filename (default: crm_data.txt): ");
                        if (filename.empty()) filename = "crm_data.txt";                        // Default if empty
                    } else {
                        filename = getUserInput("Enter filename (default: crm_data.csv): ");
                        if (filename.empty()) filename = "crm_data.csv";                        // Default if empty
                    }
                    
                    if (FileHandler::saveData(customerHandler, filename)) {
                        cout << "Data saved successfully to " << filename << endl;
                    } else {
                        cout << "Failed to save data." << endl;
                    }
                }
                waitForEnter();
                break;
            }
            
            case 8: {  // Load Data
                cout << "\n=== LOAD DATA ===" << endl;
                if (!customerHandler.isEmpty()) {                                                           // Check if the CRM is not empty and if so warn the user
                    string confirm = getUserInput("This will replace current data. Continue? (yes/no): ");
                    if (confirm != "yes") {
                        cout << "Load cancelled." << endl;
                        waitForEnter();
                        break;
                    }
                }
                
                string filename = getUserInput("Enter filename to load: ");
                if (FileHandler::loadData(customerHandler, filename)) {
                    cout << "Data loaded successfully from " << filename << endl;
                    cout << "Total customers: " << customerHandler.getCustomerCount() << endl;
                } else {
                    cout << "Failed to load data from " << filename << endl;
                }
                waitForEnter();
                break;
            }
            
            case 9: {  // Statistics
                cout << "\n=== SYSTEM STATISTICS ===" << endl;
                customerHandler.printCRMStatistics();
                waitForEnter();
                break;
            }
            
            case 0: {  // Exit
                cout << "\n=== EXIT SYSTEM ===" << endl;
                
                if (customerHandler.getCustomerCount() > 0) {
                    string save = getUserInput("Save data before exit? (Yes/No): ");
                    if (save == "Yes" || save == "Y" || save == "y") {
                        if (FileHandler::saveData(customerHandler, "crm_data.txt")) {
                            cout << "Data saved successfully!" << endl;
                        }
                    }
                }
                cout << "Thank you for using InsuraPro CRM!" << endl;
                break;
            }
        }
        
    } while (choice != 0);

}