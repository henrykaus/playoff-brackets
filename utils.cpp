#include "utils.h"
using namespace std;

bool utils::is_pow_two(int _num) const
{
    // Uses binary representations to determine if power of two
    return _num <= 0 || !(_num & (_num - 1));
}

int utils::integer_input(std::istream & in, const char * _err_msg, int _min, int _max) const
{
    int number;

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

char utils::capital_char_input(std::istream & in) const
{
    char option;
    in >> option;
    return toupper(option);
}