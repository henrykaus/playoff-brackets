/**
 * @file main.cpp
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief A bracket generator program. This program allows the user to select
 *        from a batch of seeded brackets and fill in their own predictions. The
 *        user to modify their bracket to any extent, save their progress and
 *        return even after the program's close. The user can also delete old
 *        saved brackets.
 * @version 0.5
 * @date 2022-03-19
 * 
 * @copyright Copyright (c) 2022
 */
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