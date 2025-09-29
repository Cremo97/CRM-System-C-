/**
 * @file Contract.h
 * @brief Definition of the Contract class for insurance CRM System
 * @author Davide Cremonesi
 * @date 24/07/2025
 * @version 1.0
 */

#ifndef CONTRACT_H
#define CONTRACT_H

#include "Interaction.h"

/**
 * @class Contract
 * @brief Represents a Contract for a customer in the insurance CRM
 * 
 * This class inherits from Interaction and handles Contract-specific data such as Contract number, policy type, annual premium, and expiration date.
 * Contracts represent finalized insurance agreements after successful appointments.
 * 
 */
class Contract: public Interaction{
    private:
        string contractNumber;      /// Unique Contract identifier (format: TYPE-DDMMYYYY-XXX)
        string policyType;          /// Type of insurance policy: "Auto", "Home", "Life", "Health"
        float annualPremium;        /// Annual premium amount in euros
        string expirationDate;      /// Contract expiration date (DD/MM/YYYY format)

        

        // AUTOGENERATION
        
        /**
         * @brief Generates a unique formatted Contract number based on policy data
         * 
         * @return Formatted Contract number (e.g., "AUTO-15012025-001")
         * 
         * Combines policy type (first 4 chars), signing date (DDMMYYYY) and internalID (3 digits) to create a business-friendly identifier.
         */
        string generateContractNumber();

    public:
        // VALIDATION

        /**
         * @brief Validates policy type: "Auto", "Home", "Life", "Health"
         * 
         * @param _policyType The policy type to validate
         * @return true if valid, false otherwise
         */
        static bool isValidPolicyType(const string& _policyType);

        /**
         * @brief Validates premium amount
         * 
         * @param _premium The premium amount to validate
         * @return true if valid (positive), false otherwise
         */
        static bool isValidPremium(float _premium);
        

        // CONSTRUCTOR

        /**
         * @brief Default constructor
         * 
         * Creates a Contract with empty fields and default values.
         * Automatically assigns a unique ID through the base class.
         */
        Contract();

        /**
         * @brief Parameterized constructor
         * 
         * @param _date The date when the Contract was signed (DD/MM/YYYY format)
         * @param _description Description of the Contract
         * @param _policyType Type of insurance policy ("Auto", "Home", "Life", "Health")
         * @param _annualPremium Annual premium amount (must be positive)
         * @param _expirationDate Contract expiration date (DD/MM/YYYY format)
         * @throws invalid_argument if date format is invalid, policy type is invalid, or premium is negative
         * 
         * Creates a Contract with specified details. Contract number is auto-generated based on policy type, signing date, and internalID in format TYPE-DDMMYYYY-XXX.
         * Validates input parameters before assignment to ensure data integrity.
         */
        Contract(const string& _date, const string& _description, const string& _policyType, float _annualPremium, const string& _expirationDate);


        // INTERACTION PURE VIRTUAL METHOD DEFINITIONS

        /**
         * @brief Get the type of Interaction
         * 
         * @return Always returns "Contract"
         * 
         * Override the pure virtual method from base class Interaction.
         */
        string getType() const override;

        /**
         * @brief Print detailed Contract information
         * 
         * Override the pure virtual method from base class Interaction.
         * Displays all Contract details including inherited fields (date, description, ID) and Contract-specific fields (Contract number, policy type, premium, expiration).
         */
        void printDetails() const override;

        
        // GETTERS

        /**
         * @brief Get the Contract number
         * @return The auto-generated Contract number (format: TYPE-DDMMYYYY-XXX, e.g., "AUTO-15012025-001")
         */
        string getContractNumber() const;

        /**
         * @brief Get the policy type
         * @return The type of insurance policy as a string
         */
        string getPolicyType() const;

        /**
         * @brief Get the annual premium
         * @return The annual premium amount as a double
         */
        float getAnnualPremium() const;

        /**
         * @brief Get the expiration date
         * @return The Contract expiration date as a string
         */
        string getExpirationDate() const;

        // SETTERS

        // Note: Contract number is auto-generated and cannot be manually set

        /**
         * @brief Set the policy type
         * 
         * @param _policyType New policy type (String)
         * @throws invalid_argument if policy type is invalid
         * 
         * Updates the policy type after validation.
         * Valid types: "Auto", "Home", "Life", "Health"
         */
        void setPolicyType(const string& _policyType);

        /**
         * @brief Set the annual premium
         * 
         * @param _annualPremium New annual premium amount 
         * @throws invalid_argument if premium is negative
         * 
         * Updates the annual premium after validation.
         * Premium must be a positive value.
         */
        void setAnnualPremium(float _annualPremium);

        /**
         * @brief Set the expiration date 
         * 
         * @param _expirationDate New expiration date (DD/MM/YYYY format) (String)
         * @throws invalid_argument if date format is invalid
         * 
         * Updates the expiration date after validation using the same validation logic as the base class date validation.
         */
        void setExpirationDate(const string& _expirationDate);
};


#endif