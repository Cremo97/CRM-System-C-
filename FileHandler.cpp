/**
 * @file FileHandler.cpp
 * @brief Implementation of the FileHandler class for insurance CRM System
 * @author Davide Cremonesi
 * @date 11/08/2025
 * @version 1.0
 */

#include "FileHandler.h"

// PUBLIC METHODS

bool FileHandler::saveData(const CustomerHandler& _customerHandler, const string& _exportFileName){
    string extension = getFileExtension(_exportFileName);

    if(extension == "csv"){
        return saveToCSV(_customerHandler, _exportFileName);
    } else { 
        return saveToTXT(_customerHandler, _exportFileName);
    }
} 


bool FileHandler::loadData(CustomerHandler& _customerHandler, const string& _importFileName) {
    string extension = getFileExtension(_importFileName);
    
    if (extension == "csv") {
        return loadFromCSV(_customerHandler, _importFileName);
    } else {
        return loadFromTXT(_customerHandler, _importFileName);
    }
}

// PRIVATE METHODS

string FileHandler::getFileExtension(const string& _fileName){
    size_t extDot = _fileName.find_last_of('.');

    if(extDot == string::npos){
        return ""; // No extension found
    }

    string extension = _fileName.substr(extDot + 1);
    // Convert to lowercase for case-insensitive comparison
    for (char& c : extension) {
            c = tolower(c);
        }

    return extension;
}

// CSV IMPLEMENTATION

bool FileHandler::saveToCSV(const CustomerHandler& _customerHandler, const string& _exportFileName){
    // Create a matrix 
    vector<vector<string>> csvMatrix;

    // Add the header
    csvMatrix.push_back({
        "CustomerID", "FirstName", "LastName", "Email", "PhoneNumber",          // Customer Info
        "InteractionType", "InteractionID", "Date", "Description",              // Interaction Info
        "AppointmentType", "AppointmentStatus",                                 // Appointment Info
        "ContractNumber","PolicyType", "AnnualPremium", "ExpirationDate"        // Contract Info
    });

    // Populate with CRM system data
    for(const auto& customer : _customerHandler.getAllCustomers()){             // Iterate for all the Customers
        const auto& interactions = customer->getInteractions();                  // Get all the Interactions of this Customer

        if(interactions.empty()){
            
            // Customer without Interactions
            csvMatrix.push_back({
                to_string(customer->getCustomerID()),
                customer->getFirstName(),
                customer->getLastName(),
                customer->getEmail(),
                customer->getPhoneNumber(),
                "", "", "", "", "", "", "", "", "", ""
            });
        } else{
            // Customer with interactions
            for(const auto& interaction : interactions){
                
                // Starting with generic Interaction Info
                vector<string> row = {
                    to_string(customer->getCustomerID()),
                    customer->getFirstName(),
                    customer->getLastName(),
                    customer->getEmail(),
                    customer->getPhoneNumber(),
                    interaction->getType(),
                    to_string(interaction->getInternalID()),
                    interaction->getDate(),
                    interaction->getDescription()
                };

                // Checking wich Interaction it is, in order to add the correct field.
                if(interaction->getType() == "Appointment"){
                    
                    // Appointment
                    Appointment* a = dynamic_cast<Appointment*> (interaction.get());   //Cast safely to Appointment to access specific methods
                    if(a != nullptr){
                        row.insert(row.end(),{a->getAppointmentType(), a->getStatus(), "", "", "", ""});
                    }
                } else if (interaction->getType() == "Contract"){

                    // Contract
                    Contract* c = dynamic_cast<Contract*> (interaction.get());
                    if(c != nullptr){
                        row.insert(row.end(), {"", "", c->getContractNumber(), c->getPolicyType(), to_string(c->getAnnualPremium()), c->getExpirationDate()});
                    }
                    
                }
                csvMatrix.push_back(row);
            }   // end Interaction for
        }   // end Interaction if
    }   // end Customers for

    // Write Matrix to file
    ofstream f(_exportFileName);                 // Open file for writing -> Output file stream
    if (!f.is_open()) {
        return false;
    }
    
    // Write each row of the matrix to file
    for(const auto& row : csvMatrix){
        for(size_t i = 0; i < row.size(); i++){
            f << row[i];                         // Write field value
            if (i < row.size() - 1) {
                f << ",";                        // Add comma separator (except for last field)
            }
        }
        f << endl;                               // End row with newline
    }

    f.close();                                   // Close file (automatic with ofstream destructor)
    return true;                                 // Return success

}

bool FileHandler::loadFromCSV(CustomerHandler& _customerHandler, const string& _importFileName) {
    
    ifstream f(_importFileName);                                                // Open CSV file for reading -> Input File stream
    if (!f.is_open()) {
        return false;                                                            
    }
    
    // Clear existing data in CustomerHandler
    _customerHandler.clearAllCustomers();                                       
    
    string line;
    bool isHeader = true;                                                       // Flag to skip header row
    
    // Read file line by line
    while (getline(f, line)) {
        if (isHeader) {
            isHeader = false;
            continue;                                                           // Skip header line
        }
        
        if (line.empty()) continue;                                             // Skip empty lines
        
        // Parse CSV line into fields
        vector<string> fields; 
        stringstream csvLineParser(line);                                       // Create string parser for this CSV line
        string field;
        
        while (getline(csvLineParser, field, ',')) {                            // Read until next comma (CSV delimiter)
            fields.push_back(field);                                            // Add extracted field to vector
        }                                                                       // Example: "1,Mario,Rossi,email,phone" becomes ["1","Mario","Rossi","email","phone"]
        
        
        if (fields.size() < 5) continue;                                        // Invalid line - need at least customer fields
        
        // Extract customer data from fields
        int customerID = stoi(fields[0]);                                       // CustomerID
        string firstName = fields[1];                                           // FirstName  
        string lastName = fields[2];                                            // LastName
        string email = fields[3];                                               // Email
        string phone = fields[4];                                               // PhoneNumber
        
        // Check if customer already exists in handler
        Customer* existingCustomer = _customerHandler.findCustomerByID(customerID);
        
        if (!existingCustomer) {
            // Customer doesn't exist - create new customer
            auto newCustomer = make_unique<Customer>(firstName, lastName, email, phone);
            
            // Add interaction if present in this row
            if (fields.size() > 5 && !fields[5].empty()) {                     // Check if interaction data exists
                string interactionType = fields[5];                            // InteractionType
                
                if (interactionType == "Appointment" && fields.size() >= 11) {
                    // Create Appointment from CSV fields
                    string date = fields[7];                                   // Date
                    string description = fields[8];                            // Description
                    string appointmentType = fields[9];                        // AppointmentType
                    string status = fields[10];                                // AppointmentStatus
                    
                    auto appointment = make_unique<Appointment>(date, description, appointmentType, status);
                    newCustomer->addInteraction(move(appointment));
                }
                else if (interactionType == "Contract" && fields.size() >= 15) {
                    // Create Contract from CSV fields
                    string date = fields[7];                                   // Date
                    string description = fields[8];                            // Description
                    string contractNumber = fields[11];                        // ContractNumber
                    string policyType = fields[12];                            // PolicyType
                    float premium = stof(fields[13]);                          // AnnualPremium
                    string expirationDate = fields[14];                        // ExpirationDate
                    
                    auto contract = make_unique<Contract>(date, description, policyType, premium, expirationDate);
                    newCustomer->addInteraction(move(contract));
                }
            }
            
            // Add customer to handler
            _customerHandler.addCustomer(move(newCustomer));
        } 
        else {
            // Customer already exists - just add interaction if present
            if (fields.size() > 5 && !fields[5].empty()) {                     // Check if interaction data exists
                string interactionType = fields[5];                            // InteractionType
                
                if (interactionType == "Appointment" && fields.size() >= 11) {
                    // Add Appointment to existing customer
                    string date = fields[7];                                   // Date
                    string description = fields[8];                            // Description
                    string appointmentType = fields[9];                        // AppointmentType
                    string status = fields[10];                                // AppointmentStatus
                    
                    auto appointment = make_unique<Appointment>(date, description, appointmentType, status);
                    existingCustomer->addInteraction(move(appointment));
                }
                else if (interactionType == "Contract" && fields.size() >= 15) {
                    // Add Contract to existing customer
                    string date = fields[7];                                   // Date
                    string description = fields[8];                            // Description
                    string contractNumber = fields[11];                        // ContractNumber
                    string policyType = fields[12];                            // PolicyType
                    float premium = stof(fields[13]);                          // AnnualPremium
                    string expirationDate = fields[14];                        // ExpirationDate
                    
                    auto contract = make_unique<Contract>(date, description, policyType, premium, expirationDate);
                    existingCustomer->addInteraction(move(contract));
                }
            }
        }
    }   // end while reading lines
    
    f.close();                                                                
    return true;                                                                 
}

// TXT IMPLEMENTATION

bool FileHandler::saveToTXT(const CustomerHandler& _customerHandler, const string& _exportFileName){

    ofstream f(_exportFileName);                                                                // Open file for writing -> Output file stream
    if (!f.is_open()) {         
        return false;                                                                           // Return false if file cannot be opened
    }           

    // Write file header with system overview           
    f << "====== CRM SYSTEM DATA ======" << endl;           
    f << "Total Customers: " << _customerHandler.getCustomerCount() << endl;                    // Display total number of customers
    f << "=============================" << endl << endl;

    
    int customerNumber = 1;                                                                     // Counter for customer numbering in output
    for(const auto& customer : _customerHandler.getAllCustomers()) {                        

        // Write customer header with sequential number         
        f << "=== CUSTOMER " << customerNumber << " ===" << endl;           

        // Write basic customer information with tab formatting         
        f << "Customer ID:\t" << customer->getCustomerID() << endl;                             // Display unique customer ID
        f << "Name:\t\t" << customer->getFullName() << endl;                                    // Display full name (firstname + lastname)
        f << "Email:\t\t" << customer->getEmail() << endl;                                      // Display email address
        f << "Phone:\t\t" << customer->getPhoneNumber() << endl;                                // Display phone number
        f << "Interactions:\t" << customer->getInteractionCount() << endl;                      // Display total interaction count

        // Write customer interactions if any exist         
        const auto& interactions = customer->getInteractions();                                 // Get all interactions for this customer
        if (!interactions.empty()) {            
            f << endl << "--- INTERACTIONS ---" << endl;                                        // Section header for interactions

            int interactionNumber = 1;                                                          // Counter for interaction numbering
            for(const auto& interaction : interactions) {                       
                
                // Write interaction header with sequential number
                f << "Interaction " << interactionNumber << ":" << endl;
                
                // Write basic interaction information
                f << "  Type:\t\t" << interaction->getType() << endl;                           // Display interaction type (Appointment/Contract)
                f << "  ID:\t\t" << interaction->getInternalID() << endl;                       // Display unique interaction ID
                f << "  Date:\t\t" << interaction->getDate() << endl;                           // Display interaction date
                f << "  Description:\t" << interaction->getDescription() << endl;               // Display interaction description
                
                // Add specific details based on interaction type
                if (interaction->getType() == "Appointment") {
                    // Cast safely to Appointment to access appointment specific methods
                    Appointment* apt = dynamic_cast<Appointment*>(interaction.get());
                    if (apt != nullptr) {
                        f << "  App. Type:\t" << apt->getAppointmentType() << endl;             // Display appointment type (Offering/Consultation/Follow-up)
                        f << "  Status:\t" << apt->getStatus() << endl;                         // Display appointment status (Scheduled/Completed/Cancelled)
                    }
                } else if (interaction->getType() == "Contract") {
                    // Cast safely to Contract to access contract-specific methods
                    Contract* contract = dynamic_cast<Contract*>(interaction.get());
                    if (contract != nullptr) {
                        f << "  Contract #:\t" << contract->getContractNumber() << endl;       // Display auto-generated contract number
                        f << "  Policy Type:\t" << contract->getPolicyType() << endl;          // Display policy type (Auto/Home/Life/Health)
                        f << "  Annual Premium:\tEUR " << contract->getAnnualPremium() << endl;// Display annual premium amount
                        f << "  Expires:\t" << contract->getExpirationDate() << endl;          // Display contract expiration date
                    }
                }
                
                f << endl;                                                                     // Add blank line after each interaction for readability
                interactionNumber++;                                                            
            }   // end interactions for
        }   // end interactions if
        
        f << "========================" << endl << endl;                        
        customerNumber++;                                                       
    }   // end customers for
    
    // Close file and return success
    f.close();                                                                   
    return true;
}

bool FileHandler::loadFromTXT(CustomerHandler& _customerHandler, const string& _importFileName) {
    // Open TXT file for reading
    ifstream f(_importFileName);                                                 // Open file for reading -> Input file stream
    if (!f.is_open()) {
        return false;                                                            // Return false if file cannot be opened
    }
    
    // Clear existing data in CustomerHandler
    _customerHandler.clearAllCustomers();                                       // Start with clean slate
    
    string line;
    
    // Read file line by line looking for customer sections
    while (getline(f, line)) {
        // Look for customer section markers "=== CUSTOMER X ==="
        if (line.find("=== CUSTOMER") != string::npos) {
            
            
            string customerName, customerEmail, customerPhone;
            int customerID = 0;
            
            // Parse customer information section
            // This loop reads customer basic info until it finds either:
            //      - "--- INTERACTIONS ---" (customer HAS interactions)
            //      - "========================" (customer has NO interactions)
            while (getline(f, line) && line.find("--- INTERACTIONS ---") == string::npos && line.find("========================") == string::npos) {
                
                // Parse Customer ID line
                if (line.find("Customer ID:") != string::npos) {
                    size_t tabPos = line.find('\t');                            // Find tab separator
                    if (tabPos != string::npos) {
                        string idStr = line.substr(tabPos + 1);                 // Extract ID string after tab
                        customerID = stoi(idStr);                               // Convert string to integer
                    }
                }
                // Parse Name line  
                else if (line.find("Name:") != string::npos) {
                    size_t tabPos = line.find('\t');                            // Find tab separator
                    if (tabPos != string::npos) {
                        customerName = line.substr(tabPos + 1);                 // Extract full name after tab
                    }
                }
                // Parse Email line
                else if (line.find("Email:") != string::npos) {
                    size_t tabPos = line.find('\t');                            // Find tab separator
                    if (tabPos != string::npos) {
                        customerEmail = line.substr(tabPos + 1);                // Extract email after tab
                    }
                }
                // Parse Phone line
                else if (line.find("Phone:") != string::npos) {
                    size_t tabPos = line.find('\t');                            // Find tab separator
                    if (tabPos != string::npos) {
                        string rawPhone = line.substr(tabPos + 1);              // Auxillary raw phone for validation
                        customerPhone = "";
                        for (char c : rawPhone) {
                            if (isdigit(c)) {
                                customerPhone += c;
                            }
                        }
                    }
                }
            }   // end customer basic info parsing
            
            // Create customer if we have valid basic data
            unique_ptr<Customer> newCustomer = nullptr;
            if (!customerName.empty() && !customerEmail.empty() && !customerPhone.empty()) {
                
                // Split full name into first and last name
                size_t spacePos = customerName.find(' ');                       // Find space separator in full name
                string firstName = customerName.substr(0, spacePos);            // Extract first name (before space)
                string lastName = "";
                if (spacePos != string::npos) {
                    lastName = customerName.substr(spacePos + 1);               // Extract last name (after space)
                }
                
                // Create new customer with parsed data
                newCustomer = make_unique<Customer>(firstName, lastName, customerEmail, customerPhone);
            }
            
            // Parse interactions section if present
            if (line.find("--- INTERACTIONS ---") != string::npos) {
                
                // Parse individual interactions
                while (getline(f, line) && line.find("========================") == string::npos) {
                    
                    // Look for interaction markers "Interaction X:"
                    if (line.find("Interaction ") != string::npos && line.find(":") != string::npos) {
                        
                        // Initialize interaction variables
                        string interactionType, interactionDate, interactionDescription;
                        string appointmentType, appointmentStatus;
                        string contractNumber, policyType, expirationDate;
                        float annualPremium = 0.0;
                        
                        // Parse interaction details
                        while (getline(f, line) && !line.empty() && line.find("Interaction ") == string::npos && line.find("========================") == string::npos) {
                            
                            // Parse Type line
                            if (line.find("  Type:") != string::npos) {
                                size_t tabPos = line.find('\t');
                                if (tabPos != string::npos) {
                                    interactionType = line.substr(tabPos + 1);     // Extract interaction type
                                }
                            }
                            // Parse Date line
                            else if (line.find("  Date:") != string::npos) {
                                size_t tabPos = line.find('\t');
                                if (tabPos != string::npos) {
                                    interactionDate = line.substr(tabPos + 1);     // Extract date
                                }
                            }
                            // Parse Description line
                            else if (line.find("  Description:") != string::npos) {
                                size_t tabPos = line.find('\t');
                                if (tabPos != string::npos) {
                                    interactionDescription = line.substr(tabPos + 1); // Extract description
                                }
                            }
                            // Parse Appointment specific fields
                            else if (line.find("  App. Type:") != string::npos) {
                                size_t tabPos = line.find('\t');
                                if (tabPos != string::npos) {
                                    appointmentType = line.substr(tabPos + 1);     // Extract appointment type
                                }
                            }
                            else if (line.find("  Status:") != string::npos) {
                                size_t tabPos = line.find('\t');
                                if (tabPos != string::npos) {
                                    appointmentStatus = line.substr(tabPos + 1);   // Extract appointment status
                                }
                            }
                            // Parse Contract specific fields
                            else if (line.find("  Contract #:") != string::npos) {
                                size_t tabPos = line.find('\t');
                                if (tabPos != string::npos) {
                                    contractNumber = line.substr(tabPos + 1);      // Extract contract number
                                }
                            }
                            else if (line.find("  Policy Type:") != string::npos) {
                                size_t tabPos = line.find('\t');
                                if (tabPos != string::npos) {
                                    policyType = line.substr(tabPos + 1);          // Extract policy type
                                }
                            }
                            else if (line.find("  Annual Premium:") != string::npos) {
                                size_t eurPos = line.find("EUR ");
                                if (eurPos != string::npos) {
                                    string premiumStr = line.substr(eurPos + 4);   // Extract premium after "EUR "
                                    annualPremium = stof(premiumStr);              // Convert to float
                                }
                            }
                            else if (line.find("  Expires:") != string::npos) {
                                size_t tabPos = line.find('\t');
                                if (tabPos != string::npos) {
                                    expirationDate = line.substr(tabPos + 1);      // Extract expiration date
                                }
                            }
                        }   // end interaction details parsing
                        
                        // Create interaction based on parsed data
                        if (newCustomer != nullptr && !interactionType.empty() && !interactionDate.empty()) {
                            
                            if (interactionType == "Appointment" && !appointmentType.empty() && !appointmentStatus.empty()) {
                                // Create Appointment interaction
                                auto appointment = make_unique<Appointment>(interactionDate, interactionDescription, appointmentType, appointmentStatus);
                                newCustomer->addInteraction(move(appointment));
                            }
                            else if (interactionType == "Contract" && !policyType.empty() && annualPremium > 0 && !expirationDate.empty()) {
                                // Create Contract interaction
                                auto contract = make_unique<Contract>(interactionDate, interactionDescription, policyType, annualPremium, expirationDate);
                                newCustomer->addInteraction(move(contract));
                            }
                        }
                        
                        // If inner loop found another interaction line, we need to process it in the outer loop
                        // continue prevents calling getline() again, so 'line' keeps the "Interaction X:" value
                        if (line.find("Interaction ") != string::npos) {
                            continue;       // Reprocess current line in outer loop without losing it
                        }
                        
                    }   // end interaction processing
                }       // end interactions section parsing
            }           // end interactions section check
            
            // Add completed customer to handler
            if (newCustomer != nullptr) {
                _customerHandler.addCustomer(move(newCustomer));                
            }
            
        }   // end customer section processing
    }   // end file reading while
    
    f.close();
    return true;
}