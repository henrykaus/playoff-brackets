#include <cstring>
#include "../bracket/bracket_driver.h"
using namespace std;

int main()
{
    bracket_driver user_bracket;

    try {
        user_bracket.start();
    }  
    catch (const invalid_argument & err)
    {
        cout << err.what() << endl;
    }

    // remove(".\\resources\\saved\\remove_me.txt") == 0)
    
    return 0;
}