#include "bracket.h"
using namespace std;

int main()
{
   // int size;
    bool continue_ = true;

    /*
    // Get input for bracket size
    cout << "How large would you like your bracket: ";
    cin  >> size;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> size;
    }
    */
    bracket soccer_bracket;         // OSAA 6A Girls Soccer Playoff bracket
  //  bracket custom_bracket(size);   // Custom Bracket

    // Clear screen
    for (int i = 0; i < 30; ++i)
        printf("\n");
    
    // Draw brackets
    soccer_bracket.init_bracket("girls_6A_soccer.txt");
    while (continue_)
    {
        soccer_bracket.draw();
        soccer_bracket.decide_winner();
        cout << "Would you like to continue (0 or 1): ";
        cin  >> continue_;
    }

    //custom_bracket.draw();

    cout << endl;
    return 0;
}