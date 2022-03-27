/**
 * @file utils.h
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds the definition of the utils class that holds miscellaneous
 *        methods that other classes can be derived from.
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef UTILS
#define UTILS

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

/**
 * @brief Holds utility methods for testing if an int is a power of two, getting
 *        error-checked integer input from the user, getting capital letter
 *        input from the user, asking for confirmation, and getting Y/N input.
 */
class utils
{
    public:
        bool is_pow_two(int _num) const;    // Checks if integer is power of two
        // Gets error checked input for an integer
        int  integer_input(std::istream & in, const char * _err_msg = nullptr, int _min = INT_MIN, int _max = INT_MAX) const;
        // Gets error checked input for a capital character
        char capital_char_input(std::istream & in) const;
        // Checks if user wants to continue
        bool are_you_sure(std::istream & in, const char * _msg = nullptr, bool print_newline = false) const;
        // Gets Y or N input
        char y_n_input(std::istream & in, const char * _msg = nullptr) const;
        void read_output_file(std::string &) const;
        void get_files(std::vector<std::string> &, const std::string &) const;
        bool check_file_exists(const std::string &, const char *) const;
};

#endif