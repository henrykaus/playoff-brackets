/**
 * @file main.cpp
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief 
 * @version 0.5
 * @date 2022-03-17
 * 
 * @copyright Copyright (c) 2022
 */
#include <cstring>
#include "bracket_driver.h"
using namespace std;

// MAIN
int main()
{
    bracket_driver user_bracket;

    try {
        user_bracket.start();
    }  
    catch (const invalid_argument & err) {
        cerr << err.what() << endl;
    }

    return 0;
}