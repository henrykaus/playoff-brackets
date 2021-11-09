#ifndef UTILS
#define UTILS

#include <iostream>

class utils
{
    public:
        bool is_pow_two(int _num) const;
        int  integer_input(std::istream & in, const char * _err_msg = nullptr, int _min = INT_MIN, int _max = INT_MAX) const;
        char capital_char_input(std::istream & in) const;
};

#endif