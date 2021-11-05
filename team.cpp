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

/* Ex.
 * CENTRAL CATHOLIC:
 * #-#-#
 * Seed: ##
 */
void team::display() const
{
    cout << school_name << ": " << endl
         << wins << "-" << losses;
    if (ties > 0)
        cout << '-' << ties;
    cout << endl
         << "Seed: " << seed << endl;
}

// Ex. " ## CENTRAL CA "
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
    // Checks if negative or over some max seed
    return seed > _max_seed || seed < 1;
}

int team::get_seed() const
{
    return seed;
}

bool team::same_seed(int rank) const
{
    return seed == rank;
}

bool team::same_name(const string & _school_name) const
{
    return school_name == _school_name;
}

void team::print_for_file(std::ostream & outFile) const
{
    outFile << school_name << ';' << wins << ';' << losses << ';' << ties << ';' << seed << ';';
}

void team::read_team(std::istream & inFile)
{
    getline(inFile, school_name, ';');
    inFile >> wins;
    inFile.get();
    inFile >> losses;
    inFile.get();
    inFile >> ties;
    inFile.get();
    inFile >> seed;
    inFile.get();
}