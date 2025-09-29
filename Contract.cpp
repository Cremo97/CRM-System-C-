/**
 * @file Contract.cpp
 * @brief Implementation of the Contract class for insurance CRM System
 * @author Davide Cremonesi
 * @date 25/07/2025
 * @version 1.0
 */

#include "Contract.h"


// PRIVATE VALIDATION METHODS

bool Contract::isValidPolicyType(const string& _policyType){
    return _policyType == "Auto" || _policyType == "Home" || _policyType == "Life" || _policyType == "Health";
}

bool Contract::isValidPremium(float _premium){
    return _premium > 0.0;
}

// PRIVATE AUTOGENERATION METHOD

string Contract::generateContractNumber(){
    // Get policy type code (first 4 chars, uppercase)
    string typeCode = policyType.substr(0, 4);
    for (int i = 0; i < typeCode.length(); i++) {
        typeCode[i] = toupper(typeCode[i]);
    }
    
    // Get date without slashes (DDMMYYYY)
    string dateCode = getDate();
    string cleanDate = "";
    for (int i = 0; i < dateCode.length(); i++) {
        if (dateCode[i] != '/') {
            cleanDate += dateCode[i];
        }
    }
    
    // Get ID and parse to string
    string idStr = to_string(getInternalID());
    if (idStr.length() == 1) {
        idStr = "00" + idStr;
    } else if (idStr.length() == 2) {
        idStr = "0" + idStr;
    }
    
    return typeCode + "-" + cleanDate + "-" + idStr;
}

// CONSTRUCTORS

Contract::Contract() : Interaction(), contractNumber(""), policyType(""), annualPremium(0.0), expirationDate("") {
    // Default constructor with initialization list
}

Contract::Contract(const string& _date, const string& _description, const string& _policyType, float _annualPremium, const string& _expirationDate) : Interaction(_date, _description) {
    
    // Validate policy type
    if (!isValidPolicyType(_policyType)) {
        throw invalid_argument("Invalid policy type. Valid types: Auto, Home, Life, Health");
    }
    
    // Validate annual premium
    if (!isValidPremium(_annualPremium)) {
        throw invalid_argument("Invalid annual premium amount. it must be positive.");
    }
    
    // Validate expiration date format (reuse base class validation)
    if (!isValidDate(_expirationDate)) {
        throw invalid_argument("Invalid expiration date format. Expected DD/MM/YYYY with valid values.");
    }

    // Assign validated values

    this->policyType = _policyType;
    this->annualPremium = _annualPremium;
    this->expirationDate = _expirationDate;

    // Generate contract number after all data is set
    this->contractNumber = generateContractNumber();
}

// INTERACTION PURE VIRTUAL METHOD IMPLEMENTATIONS

string Contract::getType() const {
    return "Contract";
}

void Contract::printDetails() const {
    cout << "====== CONTRACT DETAILS ======" << endl;
    cout << "ID:\t\t\t" << getInternalID() << endl;
    cout << "Type:\t\t\t" << getType() << endl;
    cout << "Contract Number:\t" << contractNumber << endl;
    cout << "Signing Date:\t\t" << getDate() << endl;
    cout << "Description:\t\t" << getDescription() << endl;
    cout << "Policy Type:\t\t" << policyType << endl;
    cout << "Annual Premium:\t\tEUR " << annualPremium << endl;
    cout << "Expiration Date:\t" << expirationDate << endl;
    cout << "===============================" << endl;
}

// GETTERS

string Contract::getContractNumber() const {
    return contractNumber;
}

string Contract::getPolicyType() const {
    return policyType;
}

float Contract::getAnnualPremium() const {
    return annualPremium;
}

string Contract::getExpirationDate() const {
    return expirationDate;
}

// SETTERS

void Contract::setPolicyType(const string& _policyType) {
    if (!isValidPolicyType(_policyType)) {
        throw invalid_argument("Invalid policy type. Valid types: Auto, Home, Life, Health");
    }
    
    this->policyType = _policyType;
    
    // Regenerate contract number with new policy type
    this->contractNumber = generateContractNumber();
}

void Contract::setAnnualPremium(float _annualPremium) {
    if (!isValidPremium(_annualPremium)) {
        throw invalid_argument("Invalid premium amount. Premium must be positive.");
    }
    
    this->annualPremium = _annualPremium;
}

void Contract::setExpirationDate(const string& _expirationDate) {
    if (!isValidDate(_expirationDate)) {
        throw invalid_argument("Invalid expiration date format. Expected DD/MM/YYYY with valid values.");
    }
    
    this->expirationDate = _expirationDate;
}