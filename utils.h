#ifndef UTILS
#define UTILS

#include <iostream>

class utils
{
    public:
        bool is_pow_two(int) const;
        int  integer_input(std::istream & in, const char * err_msg = nullptr) const;
        char capital_char_input(std::istream & in) const;
};

#endif