/**
 * @file utils.h
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds the definition of the utils class that holds miscellaneous
 *        methods that other classes can be derived from.
 */
#ifndef UTILS
#define UTILS

#include <iostream>

/**
 * @brief Holds utility methods for testing if an int is a power of two, getting
 *        error-checked integer input from the user and getting capital letter
 *        input from the user.
 */
class utils
{
    public:
        bool is_pow_two(int _num) const;    // Checks if integer is power of two
        // Gets error checked input for an integer
        int  integer_input(std::istream & in, const char * _err_msg = nullptr, int _min = INT_MIN, int _max = INT_MAX) const;
        // Gets error checked input for a capital character
        char capital_char_input(std::istream & in) const;
        bool are_you_sure(std::istream & in, const char * _msg = nullptr) const;
};

#endif