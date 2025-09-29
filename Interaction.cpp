/**
 * @file Interaction.cpp
 * @brief Implementation of the abstract base class Interaction for insurance CRM System
 * @author Davide Cremonesi
 * @date 14/07/2025
 * @version 1.0
 */

#include "Interaction.h"

// ID counter initialization shared among all class instances
int Interaction::nextID = 1;

// PRIVATE VALIDATION METHODS

bool Interaction::isValidDate(const string& _date) {
    // Check if the date is empty
    if(_date.empty()) return false;

    // Check the length (10 characters)
    if(_date.length() != 10) return false;

    // Check if the 2 and 5 char are '/'
    if(_date[2] != '/' || _date[5] != '/') return false;

    // Extract day, month, year
    string day = _date.substr(0, 2);
    string month = _date.substr(3, 2);
    string year = _date.substr(6, 4);

    // Check that all parts contain only digits
    for (char c : day + month + year) {
        if (!isdigit(c)) return false;
    }

    // Convert to integers for range validation
    int dayInt = stoi(day);
    int monthInt = stoi(month);
    int yearInt = stoi(year);

    // Basic range validation
    if (dayInt < 1 || dayInt > 31) return false;
    if (monthInt < 1 || monthInt > 12) return false;
    if (yearInt < 1900) return false;

    // If it passes all the checks
    return true;

}

// CONSTRUCTORS

Interaction::Interaction() : date(""), description(""), internalID(nextID++) {
    // Empty constructor - uses initialization list for efficiency
}

Interaction::Interaction(const string& _date, const string& _description){
    // Validate date before assignment
    if (!isValidDate(_date)) {
        throw invalid_argument("Invalid date format. Expected DD/MM/YYYY with valid values.");
    }

    this->date = _date;
    this->description = _description;
    this->internalID = nextID;
    nextID++;

}

// GETTERS

string Interaction::getDate() const {
    return this->date;
}

string Interaction::getDescription() const {
    return this->description;
}

int Interaction::getInternalID() const {
    return this->internalID;
}

// SETTERS

void Interaction::setDate(const string& _date){
    // Validate date before assignment
    if (!isValidDate(_date)) {
        throw invalid_argument("Invalid date format. Expected DD/MM/YYYY with valid values.");
    }
    this->date = _date;
}

void Interaction::setDescription(const string& _description) {
    this->description = _description;
}