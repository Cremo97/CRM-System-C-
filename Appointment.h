/**
 * @file Appointment.h
 * @brief Definition of the Appointment class for insurance CRM System
 * @author Davide Cremonesi
 * @date 15/07/2025
 * @version 1.0
 */

#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "Interaction.h"

/**
 * @class Appointment
 * @brief Represents a scheduled Appointment for a customer in the insurance CRM
 * 
 * This class inherits from Interaction and handles Appointment-specific data such as 
 * Appointment type (Offering, Consultation, Follow-up) and current status (Scheduled, Completed, Cancelled).
 * Appointments represent meetings with customers before the actual contracts are signed.
 */
class Appointment: public Interaction{
    private:
        string appointmentType;             /// Type of Appointment: "Offering", "Consultation", "Follow-up"
        string status;                      /// Status of the Appointment: "Scheduled", "Completed", "Cancelled"

    public:
        // VALIDATION

        /**
         * @brief Validates Appointment type
         * 
         * @param _appointmentType The Appointment type to validate
         * @return true if valid, false otherwise
         */
        static bool isValidAppointmentType(const string& _appointmentType);

        /**
         * @brief Validates Appointment status
         * 
         * @param _status The status to validate
         * @return true if valid, false otherwise
         */
        static bool isValidStatus(const string& _status);

        // CONSTRUCTORS

        /**
         * @brief Default constructor
         * 
         * Creates an Appointment with empty fields and default values.
         * Automatically assigns a unique ID through the base class.
         */
        Appointment();

        /**
         * @brief Parameterized constructor
         * 
         * @param _date The date of the Appointment (DD/MM/YYYY format)
         * @param _description Description of the Appointment
         * @param _appointmentType Type of Appointment ("Offering", "Consultation", "Follow-up")
         * @param _status Current status ("Scheduled", "Completed", "Cancelled")
         * @throws invalid_argument if date format is invalid or Appointment type/status are invalid
         * 
         * Creates an Appointment with specified details. Validates input parameters before assignment to ensure data integrity.
         */
        Appointment(const string& _date, const string& _description, const string& _appointmentType, const string& _status);

        // INTERACTION PURE VIRTUAL METHOD DEFINITIONS

        /**
         * @brief Get the type of Interaction
         * 
         * @return Always returns "Appointment"
         * 
         * Override the pure virtual method from base class Interaction.
         */
        string getType() const override;

        /**
         * @brief Print detailed Appointment information
         * 
         * Override the pure virtual method from base class Interaction.
         * Displays all Appointment details including inherited fields (date, description, ID) and Appointment-specific fields (appointmentType, status).
         */
        void printDetails() const override;

        // GETTERS

        /**
         * @brief Get the Appointment type
         * 
         * @return The type of Appointment as a string
         */
        string getAppointmentType() const;

        /**
         * @brief Get the Appointment status
         * 
         * @return The current status as a string
         */
        string getStatus() const;

        // SETTERS

        /**
         * @brief Set the Appointment type
         * 
         * @param _appointmentType New Appointment type (String)
         * @throws invalid_argument if Appointment type is invalid
         * 
         * Updates the Appointment type after validation.
         * Valid types: "Offering", "Consultation", "Follow-up"
         */
        void setAppointmentType(const string& _appointmentType);

        /**
         * @brief Set the Appointment status
         * 
         * @param _status New status for the Appointment (String)
         * @throws invalid_argument if status is invalid
         * 
         * Updates the Appointment status after validation.
         * Valid statuses: "Scheduled", "Completed", "Cancelled"
         */
        void setStatus(const string& _status);

};

#endif