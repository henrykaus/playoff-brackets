/**
 * @file bracket_driver.h
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds definition for the bracket_driver class as derived from bracket 
 *        class. bracket_driver is the interface to interact with brackets, by
 *        creating, editing, and deleting. To use this class, make an object of
 *        the class and call the start() method.
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef BRACKET_DRIVER
#define BRACKET_DRIVER

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "bracket.h"

/**
 * @brief Holds methods for the user interface to interact with brackets by
 *        creating, editing, and deleting. To use this class, make an object of
 *        the class and call the start() method.
 */
class bracket_driver : public bracket
{
    public:
        bracket_driver();   // Default constructor

        // Ask for new (resources/new) or existing file (resources/saved),
        // displays current options, saves to an array, fills bracket based on 
        // input, & saves to appropriate file (" "_saved.txt in resources/saved)
        void start();
        
    private:
        int  read_menu_option();
        void get_files(std::vector<std::string> & files, const std::string & path);
        void modify_bracket(const std::vector<std::string> & _file_options, bool _editing_existing);
        bool read_bracket_choice(const std::vector<std::string> & files_options);
        void fill_bracket(bool _editing_existing);
        void view_edit_bracket();
        void save(bool _editing_existing);
        void read_output_file(std::string & output_file);
        bool check_file_exists(const std::string & _output_file);
        void delete_bracket(const std::vector<std::string> & _file_options);

    protected:
        std::string input_file; // File that the bracket was read from 
                                // (file_name.txt)
};

#endif