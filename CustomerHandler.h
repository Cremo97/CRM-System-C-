/**
 * @file CustomerHandler.h
 * @brief Definition of the CustomerHandler class for insurance CRM System
 * @author Davide Cremonesi
 * @date 07/08/2025
 * @version 1.0
 */

#ifndef CUSTOMERHANDLER_H
#define CUSTOMERHANDLER_H

#include "Customer.h"


/**
 * @class CustomerHandler
 * @brief Manages multiple Customers in the insurance CRM system
 * 
 * This class provides functionality to manage a collection of Customers, including adding, removing, searching, and displaying Customers.
 * 
 * DESIGN CHOICES:
 * - Uses vector<unique_ptr<Customer>> for automatic memory management
 * - Provides multiple search methods for flexible Customers lookup
 * - Returns raw pointers for read operations to avoid ownership transfer
 * - Maintains statistics and provides reporting functionality
 */
class CustomerHandler{
    private:
        vector<unique_ptr<Customer>> customers;    /// Collection of all customers

    public:
        // CONSTRUCTORS

        /**
         * @brief Default constructor
         * 
         * Creates an empty CustomerHandler ready to manage customers.
         */
        CustomerHandler();

        // DESTRUCTOR

        /**
         * @brief Destructor
         * 
         * Automatically cleans up all customers due to unique_ptr.
         */
        ~CustomerHandler() = default;

        // CUSTOMER MANAGEMENT

        /**
         * @brief Add a new customer to the system
         * 
         * @param newCustomer Unique pointer to a Customer object
         */
        void addCustomer(unique_ptr<Customer> _newCustomer);

         /**
         * @brief Remove a customer by ID
         * 
         * @param customerID The ID of the customer to remove
         * @return true if customer was found and removed, false otherwise
         */
        bool removeCustomer(int _customerID);

        /**
         * @brief Get total number of customers
         * 
         * @return The total count of customers in the system
         */
        int getCustomerCount() const;

        /**
         * @brief Check if there are any customers
         * 
         * @return true if no customers exist, false otherwise
         */
        bool isEmpty() const;

        /**
         * @brief Clear all customers from the instance
         * 
         * Removes all customers and their associated data.
         */
        void clearAllCustomers();

        // SEARCH AND RETRIEVAL

        /**
         * @brief Find customer by ID
         * 
         * @param customerID The ID to search for (int)
         * @return Pointer to the customer if found, nullptr otherwise
         */
        Customer* findCustomerByID(int _customerID) const;

        /**
         * @brief Search customers by full name
         * 
         * @param fullName The full name to search for (case-insensitive)
         * @return Vector of pointers to matching customers
         */
        vector<Customer*> searchCustomersByFullName(const string& _fullName) const;

        /**
         * @brief Search customers by email
         * 
         * @param email The email to search for (case-insensitive)
         * @return Vector of pointers to matching customers
         */
        vector<Customer*> searchCustomersByEmail(const string& _email) const;

        /**
         * @brief Get all customers with READ-ONLY access
         * 
         * @return Const reference to the vector of customers
         * The returned reference allows iteration, counting, and element access but prevents modification of the customer collection.
         * 
         * Example:
         * @code
         * CustomerHandler c_handler;
         * for(const auto& customer: c_handler.getAllCustomers()){
         *      foo(customer); 
         * }
         * @endcode
         */
        const vector<unique_ptr<Customer>>& getAllCustomers() const;

        // DISPLAY AND REPORTING

        /**
         * @brief Print summary of all customers
         * 
         * Displays basic information for all customers.
         */
        void printAllCustomersSummary() const;

        /**
         * @brief Print detailed information for all customers
         * 
         * Displays complete profiles for all customers including interactions.
         */
        void printAllCustomersDetailed() const;

        /**
         * @brief Print CRM system statistics
         * 
         * Displays overall system statistics and metrics.
         */
        void printCRMStatistics() const;

};


#endif