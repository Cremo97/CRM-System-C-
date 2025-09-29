/**
 * @file Customer.cpp
 * @brief Implementation of the Customer class for insurance CRM System
 * @author Davide Cremonesi
 * @date 05/08/2025
 * @version 1.0
 */

#include "Customer.h"

// ID counter initialization shared among all class instances
int Customer::nextCustomerID = 1;

// PRIVATE VALIDATION METHODS

bool Customer::isValidEmail(const string& _email){
    // Basic email validation: must contain '@' and not be empty
    
    if (_email == ""){
        return false;
    }

    // get @ position
    int posAt = _email.find('@');

    if (posAt == 0 || posAt == _email.npos){
        return false;
    }

    return true;
}


bool Customer::isValidPhoneNumber(const string& _phoneNumber){
    // Basic phone number validation: must be 10 digits and not be empty

    if(_phoneNumber == ""){
        return false;
    }

    if(_phoneNumber.length() != 10){
        return false;
    }

    for(char c : _phoneNumber){
        if(!isdigit(c)) return false;
    }

    return true;
}

// ID COUNTER RESET

void Customer::resetIDCounter(int newValue) {
    nextCustomerID = newValue;
}

// CONSTRUCTORS

Customer::Customer(): firstName(""), lastName(""), email(""), phoneNumber(""), customerID(nextCustomerID ++){
    // Defautl constructor with initialization list
}

Customer::Customer(const string& _firstname, const string& _lastname, const string& _email, const string& _phoneNumber) : customerID(nextCustomerID ++){
    // Validate email
    if (!isValidEmail(_email)) {
        throw invalid_argument("Invalid email format. Must contain @ and not be empty.");
    }
    
    // Validate phone number
    if (!isValidPhoneNumber(_phoneNumber)) {
        throw invalid_argument("Invalid phone number. Must be exactly 10 digits.");
    }
    
    // Assign validated values
    this->firstName = _firstname;
    this->lastName = _lastname;
    this->email = _email;
    this->phoneNumber = _phoneNumber;

}


// GETTERS


string Customer::getFirstName() const {
    return firstName;
}

string Customer::getLastName() const {
    return lastName;
}

string Customer::getFullName() const {
    return firstName + " " + lastName;
}

string Customer::getEmail() const {
    return email;
}

string Customer::getPhoneNumber() const {
    return phoneNumber;
}

int Customer::getCustomerID() const {
    return customerID;
}


// SETTERS


void Customer::setFirstName(const string& _firstName) {
    this->firstName = _firstName;
}

void Customer::setLastName(const string& _lastName) {
    this->lastName = _lastName;
}

void Customer::setEmail(const string& _email){

    if (!isValidEmail(_email)) {
        throw invalid_argument("Invalid email format. Must contain @ and not be empty.");
    }

    this->email = _email;
}

void Customer::setPhoneNumber(const string& _phoneNumber) {

    if (!isValidPhoneNumber(_phoneNumber)) {
        throw invalid_argument("Invalid phone number. Must be exactly 10 digits.");
    }

    this->phoneNumber = _phoneNumber;
}


// INTERACTION MANAGEMENT


void Customer::addInteraction(unique_ptr<Interaction> _interaction){
    // Move is necessary because unique_ptr can have only one owner at a time
    // Transfer ownership of the interaction to this customer
    interactions.push_back(move(_interaction));
}

const vector<unique_ptr<Interaction>>& Customer::getInteractions() const{
    return this->interactions;
}

int Customer::getInteractionCount() const {
    return this->interactions.size();
}

// PRINT METHODS

void Customer::printAllInteractions() const{
    if(this->interactions.empty()){
        cout << "No interactions found for this customer." << endl;
        return;
    }

    cout << "=== ALL CUSTOMER INTERACTIONS ===" << endl;
    for(int i = 0; i < this->interactions.size(); i++){
        cout << "\n--- Interaction " << (i + 1) << " ---" << endl;
        interactions[i]->printDetails();    // Polymorphism !!
    }

    cout << "\nTotal interactions: " << this->interactions.size() << endl;
}

void Customer::printCustomerInfo() const {
    cout << "====== CUSTOMER INFO ======" << endl;
    cout << "Customer ID:\t\t" << this->customerID << endl;
    cout << "Full Name:\t\t" << this->getFullName() << endl;
    cout << "Email:\t\t\t" << this->email << endl;
    cout << "Phone Number:\t\t" << this->phoneNumber << endl;
    cout << "Total Interactions:\t" << this->interactions.size() << endl;
    cout << "============================" << endl;
}

void Customer::printCompleteProfile() const {
    printCustomerInfo();
    cout << endl;
    printAllInteractions();
}

// INTERACTIONS SEARCH 

Interaction* Customer::findInteractionByID(int _interactionID) const{
    for(auto& i : this->interactions){  // runtime type
        if(i->getInternalID() == _interactionID){
            return i.get();
        }
    }

    return nullptr;
}

vector<Interaction*> Customer::findInteractionsByDate(const string& _date) const {
    vector<Interaction*> result;
    
    for (const auto& i : this->interactions) { // runtime type
        if (i->getDate() == _date) {
            result.push_back(i.get());
        }
    }
    
    return result;
}

vector<Interaction*> Customer::searchInteractionsByKeyword(const string& _keyword) const {
    vector<Interaction*> result;
    
    // Convert keyword to lowercase for case-insensitive search
    string lowerKeyword = _keyword;
    for (char& c : lowerKeyword) {
        c = tolower(c);
    }
    
    for (const auto& i : this->interactions) {
        // Convert description to lowercase for comparison
        string lowerDescription = i->getDescription();
        for (char& c : lowerDescription) {
            c = tolower(c);
        }
        
        // Check if keyword is found in description
        if (lowerDescription.find(lowerKeyword) != string::npos) {      //string::npos -> constant to indicate that the research produced no result
            result.push_back(i.get());
        }
    }
    
    return result;
}