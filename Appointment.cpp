/**
 * @file Appointment.cpp
 * @brief Implementation of the Appointment class for insurance CRM System
 * @author Davide Cremonesi
 * @date 15/07/2025
 * @version 1.0
 */

#include "Appointment.h"

// PRIVATE VALIDATION METHODS

bool Appointment::isValidAppointmentType(const string& _appointmentType) {
    // return the condition's result directly
    return (_appointmentType == "Offering" || _appointmentType == "Consultation" || _appointmentType == "Follow-up");
}

bool Appointment::isValidStatus(const string& _status) {
    // return the condition's result directly
    return (_status == "Scheduled" || _status == "Completed" || _status == "Cancelled");
}

// CONSTRUCTORS

Appointment::Appointment() : Interaction(), appointmentType(""), status(""){}

Appointment::Appointment(const string& _date, const string& _description, const string& _appointmentType, const string& _status) : Interaction(_date, _description){ // Initialization list for using the base constructor and check the date validity

    // Validate appointment type
    if(!isValidAppointmentType(_appointmentType)){
        throw invalid_argument("Invalid appointment type. Valid types: Offering, Consultation, Follow-up");
    }

    // Validate status
    if (!isValidStatus(_status)) {
        throw invalid_argument("Invalid status. Valid statuses: Scheduled, Completed, Cancelled");
    }

    this->appointmentType = _appointmentType;
    this->status = _status;
}

// [INTERACTION] PURE VIRTUAL METHOD IMPLEMENTATIONS

string Appointment::getType() const {
    return "Appointment";
}

void Appointment::printDetails() const{
    cout << "===== APPOINTMENT DETAILS =====" << endl;
    cout << "ID:\t\t\t" << getInternalID() << endl;
    cout << "Type:\t\t\t" << getType() << endl;
    cout << "Date:\t\t\t" << getDate() << endl;
    cout << "Description:\t\t" << getDescription() << endl;
    cout << "Appointment Type:\t" << this->appointmentType << endl;
    cout << "Appointment Status:\t" << this->status << endl;
    cout << "===============================" << endl;
}

// GETTERS

string Appointment::getAppointmentType() const{
    return this->appointmentType;
}

string Appointment::getStatus() const {
    return this->status;
}

// SETTERS

void Appointment::setAppointmentType(const string& _appointmentType){
    if(!isValidAppointmentType(_appointmentType)){
        throw invalid_argument("Invalid appointment type. Valid types: Offering, Consultation, Follow-up");
    }

    this->appointmentType = _appointmentType;
}

void Appointment::setStatus(const string& _status){
    if (!isValidStatus(_status)) {
        throw invalid_argument("Invalid status. Valid statuses: Scheduled, Completed, Cancelled");
    }

    this->status = _status;
}