/**
 * @file Customer.h
 * @brief Definition of the Customer class for insurance CRM System
 * @author Davide Cremonesi
 * @date 29/07/2025
 * @version 1.0
 */

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Interaction.h"
#include "Appointment.h"        
#include "Contract.h"
#include <memory>               // Contains the Smart Pointer
#include <vector>               // Contains the Vector Class


/**
 * @class Customer
 * @brief Represents a Customer in the insurance CRM
 * 
 * This class manages Customer personal information and maintains a collection of all their Interactions (appointments and contracts) with the insurance company.
 * 
 * DESIGN CHOICES:
 * - Uses unique_ptr for safe memory handling, automatically deletes objects when not needed.
 * - Stores both Appointments and Contracts in the same list using polymorphism, instead of two separated list of Appointments and Contracts.
 * - Uses pointers to avoid losing data when storing the base class object (Interaction).
 * - Efficiently adding an Interaction at the Customer Interactions list.
 * 
 * REFERENCES: C++ Core Guidelines for smart pointer usage and modern C++ best practices
 */
class Customer{
    private:
        string firstName;            /// Customer's first name
        string lastName;             /// Customer's last name  
        string email;                /// Customer's email address
        string phoneNumber;          /// Customer's phone number
        int customerID;              /// Unique Customer identifier
        static int nextCustomerID;   /// Static counter for generating unique Customer IDs
        
        vector<unique_ptr<Interaction>> interactions;  /// Collection of Customer Interactions

        

    public:
        // ID COUNTER RESET

        /**
         * @brief Reset the static ID counter (for testing/loading purposes)
         *   @param newValue The new starting value for customer IDs
         */
        static void resetIDCounter(int newValue = 1);
        
        // VALIDATION

        /**
         * @brief Validates email format
         * @param _email The email to validate
         * @return true if email format is valid (contains @ and basic structure), false otherwise
         */
        static bool isValidEmail(const string& _email);

        /**
         * @brief Validates phone number format
         * @param _phoneNumber The phone number to validate
         * @return true if phone number is valid (10 digits), false otherwise
         */
        static bool isValidPhoneNumber(const string& _phoneNumber);

        // CONSTRUCTORS

        /**
         * @brief Default constructor
         * 
         * Creates a Customer with empty fields and default values.
         * Automatically assigns a unique Customer ID.
         */
        Customer();

         /**
         * @brief Parameterized constructor
         * 
         * @param _firstname Customer's first name
         * @param _lastname Customer's last name
         * @param _email Customer's email address
         * @param _phoneNumber Customer's phone number
         * @throws invalid_argument if email format is invalid or phone number is invalid
         * 
         * Creates a Customer with specified personal information.
         * Automatically assigns a unique Customer ID and validates input data.
         */
        Customer(const string& _firstname, const string& _lastname, const string& _email, const string& _phoneNumber);

        // GETTERS

        /**
         * @brief Get Customer's firstName
         * @return The Customer's first name
         */
        string getFirstName() const;

        /**
         * @brief Get Customer's lastName
         * @return The Customer's last name
         */
        string getLastName() const;

        /**
         * @brief Get Customer's full name
         * @return Formatted full name (firstName lastName)
         */
        string getFullName() const;

        /**
         * @brief Get Customer's email
         * @return The Customer's email address
         */
        string getEmail() const;

        /**
         * @brief Get Customer's phoneNumber
         * @return The Customer's phone number
         */
        string getPhoneNumber() const;

        /**
         * @brief Get Customer's ID
         * @return The unique Customer identifier
         */
        int getCustomerID() const;


        // SETTERS

        /**
         * @brief Set Customer's firstName
         * @param _firstName New first name (string)
         */
        void setFirstName(const string& _firstName);

        /**
         * @brief Set Customer's lastName
         * @param _lastName New last name (string)
         */
        void setLastName(const string& _lastName);

        /**
         * @brief Set Customer's email
         * @param _email New email address (string)
         * @throws invalid_argument if email format is invalid
         */
        void setEmail(const string& _email);

        /**
         * @brief Set Customer's phoneNumber
         * @param _phoneNumber New phone number (string)
         * @throws invalid_argument if phone number format is invalid
         */
        void setPhoneNumber(const string& _phoneNumber);



        // INTERACTION MANAGEMENT



        /**
         * @brief Add a new Interaction to the Customer
         * 
         * @param _interaction Unique pointer to an Interactions (Appointment or Contract)
         * 
         * Adds an Interactions to the Customer's list using polymorphism.
         * The unique_ptr ensures automatic memory management (automatically deleted when not useful anymore) and exclusive ownership (each Interaction can be assigned to only one Customer).
         * 
         */
        void addInteraction(unique_ptr<Interaction> _interaction);

        /**
         * @brief Get all Customer Interactions
         * @return Reference to the vector of Interactions
         * 
         * Returns a read-only reference (with &) to the internal Interactions vector for efficient access.
         * The const reference prevents copying and external modifications while allowing iteration.
         */
        const vector<unique_ptr<Interaction>>& getInteractions() const;

        /**
         * @brief Get count of Customer Interactions
         * @return Total number of Interactions
         */
        int getInteractionCount() const;

        // PRINT METHODS

        /**
         * @brief Print all Customer Interactions
         * 
         * Displays all Interactions (appointments and contracts) for this Customer
         * using polymorphic method calls to show appropriate details for each type.
         */
        void printAllInteractions() const;

        /**
         * @brief Print Customer's personal information
         * 
         * Displays Customer's personal data in a formatted layout.
         */
        void printCustomerInfo() const;

        /**
         * @brief Print complete Customer details
         * 
         * Displays both personal information and all Interactions
         * in a comprehensive Customer profile format.
         */
        void printCompleteProfile() const;

        // INTERACTIONS SEARCH 

        /**
         * @brief Find Interactions by internal ID
         * @param _interactionID The ID to search for (int)
         * @return Pointer to the Interactions if found, nullptr otherwise
         * 
         * Searches through all customer Interactions to find one with matching internal ID.
         * Useful for direct access to specific Interactions.
         */
        Interaction* findInteractionByID(int _interactionID) const;

        /**
         * @brief Find Interactions by date
         * @param _date The date to search for (string) (DD/MM/YYYY format)
         * @return Vector of pointers to Interactions on that date
         * 
         * Returns all Interactions (appointments and contracts) that occurred on the specified date.
         * Multiple Interactions can happen on the same date.
         */
        vector<Interaction*> findInteractionsByDate(const string& _date) const;

        /**
         * @brief Search interactions by description keyword
         * @param _keyword Keyword to search in descriptions (string)
         * @return Vector of pointers to matching interactions
         * 
         * Searches through all Interactions descriptions for the specified keyword.
         * Performs case-insensitive partial matching for flexible search.
         */
        vector<Interaction*> searchInteractionsByKeyword(const string& _keyword) const;
};



#endif