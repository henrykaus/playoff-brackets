#include <cstring>
#include "bracket_driver.h"
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
    
    return 0;
}