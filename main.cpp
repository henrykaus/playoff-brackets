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

    return 0;
}


// Create a file management class to delete, add and print files