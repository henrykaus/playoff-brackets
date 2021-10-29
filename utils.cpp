#include "utils.h"
using namespace std;

bool utils::is_pow_two(int _num)
{
    return _num <= 0 || !(_num & (_num - 1));
}