/**
 * @file CustomerHandler.cpp
 * @brief Implementation of the CustomerHandler class for insurance CRM System
 * @author Davide Cremonesi
 * @date 08/08/2025
 * @version 1.0
 */

 #include "CustomerHandler.h"

// CONSTRUCTORS

CustomerHandler::CustomerHandler() {
    // Empty constructor - vector is automatically initialized
}

// CUSTOMER MANAGEMENT

void CustomerHandler::addCustomer(unique_ptr<Customer> _newCustomer) {
    if(_newCustomer != nullptr){
        this->customers.push_back(move(_newCustomer));
    }

}

bool CustomerHandler::removeCustomer(int _customerID){
    // Iterate through all customers using iterator
    for(auto i = this->customers.begin(); i != this->customers.end(); i++ ){
        // (*i) dereferences the iterator to get unique_ptr<Customer>&
        if((*i)->getCustomerID() == _customerID){
            this->customers.erase(i); // Iterator i needed for the erase

            return true;
        }
    }

    return false;
}

int CustomerHandler::getCustomerCount() const{
    return this->customers.size(); 

}

bool CustomerHandler::isEmpty() const{
    return this->customers.empty();     // Native vector function: true if the container size is 0, false otherwise.
}

void CustomerHandler::clearAllCustomers(){
    this->customers.clear();            // Native vector function: Removes all elements from the vector (which are destroyed)
    Customer::resetIDCounter(1);        // Reset ID counter for fresh start
}

// SEARCH AND RETRIEVAL

Customer* CustomerHandler::findCustomerByID(int _customerID) const{
    // Range-based for loop
    for(const auto& customer : this->customers){
        // customer is already unique_ptr<Customer>&
        if(customer->getCustomerID() == _customerID) {
            return customer.get();  // Extract raw pointer from unique_ptr
        }
    }
    return nullptr;             // Customer not found
}

vector<Customer*> CustomerHandler::searchCustomersByFullName(const string& _fullName) const{
    vector<Customer*> results;

    // Convert _fullName to lowercase for case-insensitive search
    string lowerFullName_toSearch = _fullName;
    for (char& c : lowerFullName_toSearch) {
        c = tolower(c);
    }
    
    for(const auto& customer : this->customers){
        string lowerFullName = customer->getFullName();
        for (char& c : lowerFullName) {
            c = tolower(c);
        }

        if(lowerFullName.find(lowerFullName_toSearch) != string::npos){
            results.push_back(customer.get());
        }
    }

    return results;             
}

vector<Customer*> CustomerHandler::searchCustomersByEmail(const string& _email) const{
    vector<Customer*> results;

    // Convert _email to lowercase for case-insensitive search
    string lowerEmail_toSearch = _email;
    for (char& c : lowerEmail_toSearch) {
        c = tolower(c);
    }
    
    for(const auto& customer : this->customers){
        string lowerEmail = customer->getEmail();
        for (char& c : lowerEmail) {
            c = tolower(c);
        }

        if(lowerEmail.find(lowerEmail_toSearch) != string::npos){
            results.push_back(customer.get());
        }
    }

    return results; 
}

const vector<unique_ptr<Customer>>& CustomerHandler::getAllCustomers() const{
    return customers;
}

// DISPLAY AND REPORTING

void CustomerHandler::printAllCustomersSummary() const{
    if (this->customers.empty()) {
        cout << "No customers in the CRM system." << endl;
        cout << "====================================" << endl;
        return;
    }
    
    cout << "======== CUSTOMERS SUMMARY ========" << endl;
    cout << "Total Customers: " << customers.size() << endl;
    cout << "====================================" << endl;

    for(const auto& customer : this->customers){
        customer->printCustomerInfo(); 
        cout << endl;  // Add spacing between customers    
    }

    cout << "\n===========================================" << endl;
}

void CustomerHandler::printAllCustomersDetailed() const{
    if (this->customers.empty()) {
        cout << "No customers in the CRM system." << endl;
        return;
    }    

    cout << "======== DETAILED CUSTOMERS REPORT ========" << endl;
    cout << "Total Customers: " << customers.size() << endl;
    cout << "===========================================" << endl;

    for(const auto& customer : this->customers){
        cout << "\n--- Customer " << customer->getCustomerID() << " ---" << endl;
        customer->printCustomerInfo(); 
        cout << endl;  // Add spacing between customers    
    }

    cout << "\n===========================================" << endl;
}

void CustomerHandler::printCRMStatistics() const{
    cout << "========== CRM STATISTICS ==========" << endl;
    cout << "Total Customers: " << customers.size() << endl;

    if (customers.empty()) {
        cout << "No data to display." << endl;
        cout << "====================================" << endl;
        return;
    }

    // Calculate total interactions
    int totalInteractions = 0;
    int totalAppointments = 0;
    int totalContracts = 0;

    for(const auto& customer : this->customers){
       totalInteractions += customer->getInteractionCount();

       for(const auto& interaction : customer->getInteractions()){
        if(interaction->getType() == "Appointment"){
            totalAppointments++;
        } else{
            totalContracts++;
        }
       }
    }

    cout << "Total Interactions: " << totalInteractions << endl;
    cout << "  - Appointments: " << totalAppointments << endl;
    cout << "  - Contracts: " << totalContracts << endl;


}