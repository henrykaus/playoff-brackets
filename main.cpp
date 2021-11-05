#include <cstring>
#include "bracket.h"
using namespace std;

int main()
{
   // int size;
    bool continue_ = true;
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
        soccer_bracket.fill_bracket("girls_6A_soccer_saved.txt");
    else
        soccer_bracket.init_bracket("girls_6A_soccer.txt");

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
    soccer_bracket.save_bracket("girls_6A_soccer_saved.txt");

    return 0;
}