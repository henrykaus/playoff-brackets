#include "bracket.h"
using namespace std;

int main()
{
    int size;
    cout << "How large would you like your bracket: ";
    cin  >> size;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> size;
    }
    bracket my_bracket;
    bracket another_bracket(size);

    for (int i = 0; i < 30; ++i)
        printf("\n");
    my_bracket.init_bracket("girls_6A_soccer.txt");
    //another_bracket.draw();
    my_bracket.draw();
    cout << endl;

    return 0;
}