/**
 * @file CRM.h
 * @brief Definition of the CRM class - Simple menu interface for insurance CRM System
 * @author Davide Cremonesi
 * @date 13/08/2025
 * @version 1.0
 */

#ifndef CRM_H
#define CRM_H

#include "CustomerHandler.h"
#include "FileHandler.h"

/**
 * @class CRM
 * @brief The class that orchestrates all other. This is the one that must be executed.
 * 
 * This class provides a clean command-line interface for the insurance CRM system.
 * All business logic is delegated to the other classes.
 */
class CRM {
    private:
        CustomerHandler customerHandler;    /// Manages all customer data and operations
        // No FileHandler instance needed

        // USER INTERFACE METHODS
        
        /**
         * @brief Display the main menu with current system status
         * 
         * Shows all available options and current database size.
         * Clears screen for better user experience.
         */
        void displayMainMenu() const;
        
        // INPUT VALIDATION UTILITIES
        
        /**
         * @brief Get validated user menu choice
         * @param min Minimum valid choice value (int)
         * @param max Maximum valid choice value (int)
         * @return Valid user choice within specified range
         * 
         * Continuously prompts until valid input is received.
         * Handles invalid input with error messages.
         */
        int getUserChoice(int min, int max) const;
        
        /**
         * @brief Get string input from user with prompt
         * @param prompt Message to display to user (string)
         * @return User input as string
         * 
         * Handles full line input including spaces.
         */
        string getUserInput(const string& prompt) const;
        
        /**
         * @brief Get validated integer input from user
         * @param prompt Message to display to user (string)
         * @return Valid integer input
         * 
         * Continuously prompts until valid integer is received.
         * Used primarily for customer ID searches.
         * Automatically clears input buffer after each attempt.
         */
        int getUserInt(const string& prompt) const;
        
        /**
         * @brief Get validated positive float input from user
         * @param prompt Message to display to user (string)
         * @return Valid positive float input
         * 
         * Ensures input is both a valid float and positive value.
         * Used primarily for monetary amounts (Annual premiums).
         */
        float getUserFloat(const string& prompt) const;
        
        /**
         * @brief Clear input buffer after invalid input
         * 
         * Prevents input stream issues when user enters invalid data.
         * Essential for robust input handling in menu systems.
         */
        void clearInputBuffer() const;
        
        /**
         * @brief Pause execution until user presses Enter
         * 
         * Used to prevent menu from immediately refreshing after displaying information or completing operations.
         */
        void waitForEnter() const;

        /**
         * @brief Check if a date is grater than another 
         * @param date1 the greater date
         * @param date2 the lower date
         * @return true if date1 > date2, false otherwise
         * 
         * Used in the contract to check if the Expired date is greater than the Date
         */
        bool isDateGreater(const string& date1, const string& date2) const;

    public:
        // CONSTRUCTOR
        
        /**
         * @brief Default constructor
         * 
         * Initializes CRM system with empty CustomerHandler.
         * No automatic data loading - system starts clean.
         */
        CRM();
        
        // MAIN SYSTEM CONTROL
        
        /**
         * @brief Start the CRM system from clean state
         * 
         * Displays welcome message and enters main menu loop.
         * Always starts with empty database - no automatic loading.
         * User must explicitly load data if needed.
         */
        void start();
        
        /**
         * @brief Run the main menu interaction loop
         * 
         * Continuously displays menu and processes user choices:
         * - Customer management (add, view, search)
         * - Interaction management (appointments, contracts)
         * - File operations (save, load in TXT/CSV formats)
         * - System statistics and reporting
         * 
         * Delegates all business operations to CustomerHandler and FileHandler.
         * Exits when user selects exit option.
         */
        void runMainMenu();
};




#endif