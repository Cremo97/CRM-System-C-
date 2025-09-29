/**
 * @file Interaction.h
 * @brief Definition of the abstract base class Interaction for insurance CRM System
 * @author Davide Cremonesi
 * @date 14/07/2025
 * @version 1.0
 */

#ifndef INTERACTION_H
#define INTERACTION_H

#include <bits/stdc++.h>
using namespace std;

/**
 * @class Interaction
 * @brief Abstract base class representing a customer Interaction in the insurance CRM
 * 
 * This class is the foundation for different types of customer interactions such as Appointment and Contract. 
 * It provides common functionality including automatic ID generation, date validation, and basic data management.
 * 
 * The class uses automatic ID generation to ensure each Interaction has a unique identifier.
 * All dates must follow DD/MM/YYYY format with valid ranges (day: 1-31, month: 1-12, year: >1900).
 * 
 * @note This is an abstract class and cannot be instantiated directly
 */


class Interaction{
    private:
        int internalID;                         /// Unique ID for Interaction
        static int nextID;                      /// Static counter for generating the unique IDs across all instances
    
        protected:                                  // Only the derived classes can use it
        string date;                            /// Date of the Interaction (format: DD/MM/YYYY)
        string description;                     /// Description of the Interaction

        
    public:
        // VALIDATION

        /**
         * @brief Validates the date format and values
         * 
         * @param _date The date string to validate (String)
         * @return true if valid (DD/MM/YYYY format with valid ranges), false otherwise
         */
        static bool isValidDate(const string& _date);

        // CONSTRUCTORS

        /**
         * @brief Default Constructor (uses initialization list for efficiency).
         * 
         * Creates an Interaction with empty date and description.
         * Automatically assign the Unique ID using the static counter.
         */
        Interaction();

        /**
         * @brief Parameterized constructor
         * 
         * @param _date The date of the Interaction [DD/MM/YYYY format] (String)
         * @param _description The description of the Interaction (String)
         * @throws invalid_argument if date format is invalid.
         * 
         * Creates an Interaction with specified date and description.
         * Validates the date format before assignment.
        */
        Interaction(const string& _date, const string& _description);     // String passed by reference for optimization, const prevents modification

        // DESTRUCTOR

        /**
         * @brief Virtual destructor
         * 
         * Ensures proper cleanup when deleting objects.
         */
        virtual ~Interaction() = default;

        // PURE VIRTUAL METHODS

        /**
         * @brief Get the type of the Interaction
         * 
         * @return String representing the specific  type of Interaction.
         * @note Pure virtual method - must be implemented by derived classes.
         */
        virtual string getType() const = 0;     // Const used to prevent malevolous alteration

        /**
         * @brief Print detailed information about the Interaction
         * 
         * Displays all relevant details specific to the Interaction type.
         * @note Pure virtual method - must be implemented by derived classes
         */
        virtual void printDetails() const = 0;

        // GETTERS

        /**
         * @brief Get the Interaction date
         * 
         * @return The date as a string in DD/MM/YYYY format
         */
        string getDate() const;

        /**
         * @brief Get the Interaction description
         * 
         * @return The description as a string
         */
        string getDescription() const;

        /**
         * @brief Get the unique internal ID
         * 
         * @return The unique identifier assigned during creation
         */
        int getInternalID() const;

        // SETTERS

        /**
         * @brief Set the Interaction date
         * 
         * @param _date The new date for the Interaction [DD/MM/YYYY format] (String)
         * @throws invalid_argument if date format is invalid
         * Updates the date field after validation. Ensures data integrity.
         */
        void setDate(const string& _date);

        /**
         * @brief Set the description of the Interaction
         * 
         * @param _description The new description for the Interaction (String)
         */
        void setDescription(const string& _description);

};




#endif