#include "utils.h"
using namespace std;

bool utils::is_pow_two(int _num) const
{
    // Uses binary representations to determine if power of two
    return _num <= 0 || !(_num & (_num - 1));
}

int utils::integer_input(std::istream & in, const char * err_msg) const
{
    int number;
    in >> number;
    while (in.fail())
    {
        in.clear();
        in.ignore(10000, '\n');
        if (err_msg)
            cout << err_msg;
        in >> number;
    }
    return number;
}