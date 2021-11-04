#ifndef UTILS
#define UTILS

#include <iostream>

class utils
{
    public:
        bool is_pow_two(int) const;
        int  integer_input(std::istream & in = std::cin, const char * err_msg = nullptr) const;
};

#endif