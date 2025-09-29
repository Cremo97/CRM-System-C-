/**
 * @file FileHandler.h
 * @brief Definition of the FileHandler class for insurance CRM System
 * @author Davide Cremonesi
 * @date 10/08/2025
 * @version 1.0
 */

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "CustomerHandler.h"

/**
 * @class FileHandler
 * @brief Handles essential file I/O operations for the CRM System
 * 
 * Provides save and load functionality supporting both CSV and txt formats.
 * Format is automatically detected from the file extension (.csv or .txt).
 * 
 * For the CSV file: the Header will be: Customer Info + Interaction Info + Appointment Info + Contract Info.
 * If a Customer has n Interaction, his Customer Info will be writed n times as n Interacions
 */
class FileHandler{
    private:
        /**
         * @brief Get extension from the file name inserted.
         * 
         * @param _fileName, the file name to analyze (string).
         * @return File extension in lowercase ("csv", "txt").
         */
        static string getFileExtension(const string& _fileName);

        /**
         * @brief Save data in CSV format.
         * 
         * @param _customerHandler Reference to CustomerHandler instance tha contains the CRM data (CustomerHandler)
         * @param _exportFileName file name for the CSV file (string)
         * @return true if the save was successful, false otherwise.
         */
        static bool saveToCSV(const CustomerHandler& _customerHandler, const string& _exportFileName);

        /**
         * @brief Save data in TXT format.
         * 
         * @param _customerHandler Reference to CustomerHandler instance tha contains the CRM data (CustomerHandler)
         * @param _exportFileName file name for the TXT file (string)
         * @return true if the save was successful, false otherwise.
         */
        static bool saveToTXT(const CustomerHandler& _customerHandler, const string& _exportFileName);

        /**
         * @brief Load data from CSV format.
         * 
         * @param _customerHandler Reference to CustomerHandler instance to populate with CRM data (CustomerHandler)
         * @param _importFileName file name for the CSV file (string)
         * @return true if load was successful, false otherwise.
         */
        static bool loadFromCSV(CustomerHandler& _customerHandler, const string& _importFileName);

        /**
         * @brief Load data from TXT format.
         * 
         * @param _customerHandler Reference to CustomerHandler instance to populate with CRM data (CustomerHandler)
         * @param _importFileName file name for the txt file (string)
         * @return true if load was successful, false otherwise.
         */
        static bool loadFromTXT(CustomerHandler& _customerHandler, const string& _importFileName);

    public:
        /**
         * @brief Save all Customers and their Interactions to file (CSV or TXT)
         * 
         * @param _customerHandler Reference to CustomerHandler containing the data (CustomerHandler)
         * @param _exportFileName file name with the extension (default: "crm_data.txt") (string)
         * @return true if save was successful, false otherwise
         * 
         * Automatically detects the format from the file extension:
         * - .csv -> CSV format (comma-separated values)
         * - .txt -> TXT format (human-readable text)
         * - Default format: TXT
         * 
         */
        static bool saveData(const CustomerHandler& _customerHandler, const string& _exportFileName = "crm_data.txt");

        /**
         * @brief Load Customers and their Interactions from file (CSV or TXT)
         * 
         * @param _customerHandler Reference to CustomerHandler to populate with data (CustomerHandler)
         * @param _importFileName file name with the extension (default: "crm_data.txt") (string)
         * @return true if load was successful, false otherwise
         * 
         * Automatically detects the format from the file extension:
         * - .csv -> CSV format (comma-separated values)
         * - .txt -> TXT format (human-readable text)
         * - Default format: TXT
         * 
         */
        static bool loadData(CustomerHandler& _customerHandler, const string& _importFileName = "crm_data.txt");

};

#endif