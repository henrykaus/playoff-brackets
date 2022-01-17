/**
 * @file team.cpp
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds method definitions for the team class.
 */
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


/**
 * @brief Setter for all elements of team.
 * 
 * @param _school_name  Name of school
 * @param _wins         Number of team wins
 * @param _losses       Number of team losses
 * @param _ties         Number of team ties
 * @param _seed         Team's seed in playoffs
 */
void team::set_team(string _school_name, int _wins, int _losses, int _ties, int _seed)
{
    school_name = _school_name;
    wins        = _wins;
    losses      = _losses;
    ties        = _ties;
    seed        = _seed;
}


/**
 * @brief Displays team in listed format, shown below.
 * ==EXAMPLE==
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


/**
 * @brief Displays team in one line, condensed format, shown below...
 * ==EXAMPLE==
 * ## CENTRAL CA
 */
void team::display_in_bracket() const
{
    cout << " " << setw(2) << setfill(' ') << left << seed << " ";
    // Display full name or condescensed with filler if less than 10 chars
    if (school_name.size() > 10)
        cout << school_name.substr(0, 10);
    else
        cout << setw(10) << setfill(' ') << left << school_name;
    cout << " ";
}


/**
 * @brief Checks if team seed is invalid.
 * 
 * @param _max_seed is the max seed for the playoffs (ex. seed 32)
 * @return true if the seed if greater than _max_seed or is negative.
 * @return false if a valid seed.
 */
bool team::invalid_rank(int _max_seed) const
{
    return seed > _max_seed || seed < 1;
}


/**
 * @brief Returns the seed.
 * 
 * @return int: the team seed
 */
int team::get_seed() const
{
    return seed;
}


/**
 * @brief Checks if arg seed is the same as the team seed.
 * 
 * @param _rank is the seed to test
 * @return true if _rank matches the team seed.
 * @return false if _rank doesn't match the team seed.
 */
bool team::same_seed(int _rank) const
{
    return seed == _rank;
}


/**
 * @brief Uses std::string's == to determine if arg name matches team name.
 * 
 * @param _school_name is the name to test
 * @return true if names match
 * @return false if names differ
 */
bool team::same_name(const string & _school_name) const
{
    return school_name == _school_name;
}


/**
 * @brief Prints team for file output that can be read by team::read_team(). The
 *        format is below...
 * FORMAT: SCHOOL_NAME;WINS;LOSSES;TIES;SEED
 * @param outFile is the output stream (or ofstream)
 */
void team::print_for_file(std::ostream & outFile) const
{
    outFile << school_name << ';' << wins << ';' << losses << ';' << ties << ';' << seed;
}


/**
 * @brief Reads team from a file to fill in team attributes. Format is below...
 * FORMAT: SCHOOL_NAME;WINS;LOSSES;TIES;SEED
 * @param inFile is the input stream (or ifstream)
 */
void team::read_team(std::istream & inFile)
{
    getline(inFile, school_name, ';');
    inFile >> wins;
    inFile.ignore();
    inFile >> losses;
    inFile.ignore();
    inFile >> ties;
    inFile.ignore();
    inFile >> seed;
}