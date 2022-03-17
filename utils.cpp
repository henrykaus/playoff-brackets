/**
 * @file utils.cpp
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds method definitions for the utils class. Should be used as a base
 *        class for any and all derived classes.
 */
#include "utils.h"
using namespace std;


/**
 * @brief Uses binary representations to determine if num is power of two.
 * 
 * @param _num is the number to test
 * @return true if _num is a power of two.
 * @return false if _num is not a power of two.
 */
bool utils::is_pow_two(int _num) const
{
    return _num <= 0 || !(_num & (_num - 1));
}


/**
 * @brief 
 * 
 * @param in is the input stream
 * @param _err_msg is the error message to display (default: nullptr)
 * @param _min is the minimum integer the number can be (default: INT_MIN)
 * @param _max is the maximum integer the number can be (default: INT_MAX)
 * @return int of the number the user input
 */
int utils::integer_input(std::istream & in, const char * _err_msg, int _min, int _max) const
{
    int number;     // Temp number for user to enter into

    // Gets number from user as long as valid and between _min and _max (inclusive)
    in >> number;
    while (in.fail() || number < _min || number > _max)
    {
        in.clear();
        in.ignore(10000, '\n');
        if (_err_msg)
            cout << _err_msg;
        in >> number;
    }

    return number;
}


/**
 * @brief Gets a character from user and return the uppercase variant.
 * NOTE: Any other characters still exist in stream
 * @param in is the input stream
 * @return char: is the uppercase character
 */
char utils::capital_char_input(std::istream & in) const
{
    char option;
    in >> option;
    return toupper(option);
}

bool utils::are_you_sure(std::istream & in, const char * _msg) const
{
    char option;

    if (_msg)
        cout << _msg << endl;
    else
        cout << "Are you sure (Y/N)?" << endl;
    
    do {
        cout << "-> ";
        option = capital_char_input(cin);
        cin.ignore(10000, '\n');
    } while (option != 'Y' && option != 'N');
    
    if (option == 'Y')
        return true;
    else   
        return false;
}