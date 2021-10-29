#include "team.h"
using namespace std;

// Default Constructor
team::team() : school_name("NONE"), wins(0), losses(0), ties(0), seed(0)
{}

// Param. Constructor
team::team(string _school_name, int _wins, int _losses, int _ties, int _seed)
    : school_name(_school_name), wins(_wins), losses(_losses), ties(_ties),
      seed(_seed)
{}

void team::display() const
{
    cout << school_name << ": " << endl
         << wins << "-" << losses;
    if (ties > 0)
        cout << '-' << ties;
    cout << endl
         << "Seed: " << seed << endl;
}

void team::display_in_bracket() const
{
    cout << " " << setw(2) << setfill(' ') << left << seed << " ";
    if (school_name.size() > 10)
        cout << school_name.substr(0, 10);
    else
        cout << setw(10) << setfill(' ') << left << school_name;
    cout << " ";
}

bool team::invalid_rank(int _max_seed) const
{
    return seed > _max_seed || seed < 1;
}

int team::get_seed() const
{
    return seed;
}