#include <cstring>
#include "bracket_driver.h"
using namespace std;

int main()
{
    bracket_driver my_bracket;
    my_bracket.start();
    /*
   // int size;
    int  continue_ = 1;
    char option;
    bracket soccer_bracket;         // OSAA 6A Girls Soccer Playoff bracket
    
    // Clear screen
    for (int i = 0; i < 75; ++i)
        printf("\n");
    
    cout << "Would you like to work on an \'E\'xisting file or \'S\'tart over? ";
    cin  >> option;
    option = toupper(option);
    while (option != 'E' && option != 'S')
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "-> ";
        cin >> option;
        option = toupper(option);
    }
    cout << endl;

    if (option == 'E')
        soccer_bracket.fill_bracket("resources/saved/6A_football_saved copy.txt");
    else
        soccer_bracket.init_bracket("resources/new/6A_football.txt");

    soccer_bracket.draw();
    cout << endl;
    cout << "Would you like to continue (0 or 1): ";
    cin  >> continue_;
    // Draw brackets
    while (continue_)
    {
        soccer_bracket.decide_winner();
        cout << endl;
        soccer_bracket.draw();
        cout << "Would you like to continue (0 or 1): ";
        cin  >> continue_;
    }

    cout << "Saving progress..." << endl;
    soccer_bracket.save_bracket("resources/saved/6A_football_saved copy.txt");
    */

    return 0;
}