/**
 * @file utils.cpp
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds method definitions for the utils class. Should be used as a base
 *        class for any and all derived classes.
 * 
 * @copyright Copyright (c) 2022
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
 * @brief Gets error checking input for an integer
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
 * NOTE: Does not clear stream of excess characters
 * @param in is the input stream
 * @return char: is the uppercase character
 */
char utils::capital_char_input(std::istream & in) const
{
    char option;
    in >> option;
    return toupper(option);
}


/**
 * @brief Asks user for confirmation and returns if they said Y or N
 * 
 * @param in is the input stream
 * @param _msg is the confirmation message to display (default: Are you sure 
 *             (Y/N)?)
 * @return true: user entered y or Y
 * @return false: user entered n or N
 */
bool utils::are_you_sure(std::istream & in, const char * _msg, bool print_newline) const
{
    char option;

    // Print confirmation message
    if (_msg) cout << _msg << " (Y/N)?" << endl;
    else      cout << "Are you sure (Y/N)?" << endl;
    
    do {
        cout << "-> ";
        option = capital_char_input(cin);
        cin.ignore(10000, '\n');
    } while (option != 'Y' && option != 'N');
    if (print_newline) cout << endl;
    
    return option == 'Y';
}


/**
 * @brief Asks user for 'Y' or 'N' input, takes in the input with input checking
 *        and returns the character given as a capital. Allows the following
 *        input: 'y', 'Y', 'n', 'N'
 * 
 * @param in is the input stream
 * @param _msg is the message to be displayed before " (Y/N): "
 * @return char of either 'Y' or 'N'
 */
char utils::y_n_input(std::istream & in, const char * _msg) const
{
    char option;

    // Print confirmation message
    if (_msg) cout << _msg << " (Y/N): ";
    else      cout << "Yes or no (Y/N): ";
    
    do {
        option = capital_char_input(cin);
        cin.ignore(10000, '\n');
    } while (option != 'Y' && option != 'N');
    
    return option;
}


/**
 * @brief Reads in name of file to save bracket as with error checking
 * 
 * @param _output_file is the file name to save into (is updated in method)
 */
void utils::read_output_file(string & _output_file) const
{
    cout << "What would you like to save the file as? " << endl
         << "-> ";
    getline(cin, _output_file);

    // Disallow forbidden characters in file name
    while (_output_file.find('\\') != string::npos || _output_file.find('/') != string::npos)
    {
        _output_file.clear();
        cout << "Do not use \\ or / in your name..." << endl
             << "-> ";
        getline(cin, _output_file);
    }

    _output_file.append(".txt");
}


/**
 * @brief Fills a vector of strings with all entries in a directory
 * 
 * @param _files is a std::vector<std::string> to fill with directory entries 
 *               (must be empty)
 * @param _path is a string path to directory to get entries of
 */
void utils::get_files(vector<string> & _files, const string & _path) const
{
    if (_files.size() > 0)
        throw invalid_argument("Vector argument is non-empty");
    // Get all files in directory
    for (const auto & entry : filesystem::directory_iterator(_path))
        _files.push_back(entry.path().filename().string());
    
    // Throw error if empty directory
    if (_files.size() < 1)
        throw invalid_argument("No files in the selection, please try adding one to resources\\new.");
}


/**
 * @brief Checks if file name exists in the 'saved' directory
 * 
 * @param _output_file is the file name to check for
 * @param _path is the path to read files from
 * @return true if file exists in 'saved' directory
 * @return false if file doesn't exist in 'saved' directory
 */
bool utils::check_file_exists(const string & _output_file, const char * _path) const
{
    vector<string> reserved_files;  // Files in resources/saved

    if (!_path)
        throw invalid_argument("Path must be non-null");
    // resources/saved can be a size of 0, so ignore the throw
    try {
        this->get_files(reserved_files, _path);
    } catch (...) {}

    // If the file name exists, return that it exists
    for (int i = 0; i < (int)reserved_files.size(); ++i)
    {
        if (reserved_files[i] == _output_file)
            return true;
    }
    return false;
}