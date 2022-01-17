/**
 * @file team.h
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds the definition for the team class.
 */
#ifndef TEAM
#define TEAM

#include <iostream>
#include <string>
#include <iomanip>

/**
 * @brief Holds information for a school team including name, wins, losses, ties
 *        and seed. It can be displayed in various ways, and used to compare
 *        other schools.
 */
class team
{
    public:
        team();                                 // Default constructor
        team(std::string, int, int, int, int);  // Param. constructor

        void display()              const;      // Listed display
        void display_in_bracket()   const;      // Display in # SCHOOL_NAME format
        // Check if team's seed is less than 1 or greater than arg
        bool invalid_rank(int)      const;
        int  get_seed()             const;      // Returns team seed
        bool same_seed(int)         const;      // Checks for match with arg
        bool same_name(const std::string &) const;  // Checks for match with arg
        void print_for_file(std::ostream &) const;  // Prints team in file input format
        void read_team(std::istream &);             // Reads team from file input
        void set_team(std::string, int, int, int, int); // Setter for all elements

    private:
        std::string school_name;    // Name of school
        int         wins;           // Wins for season
        int         losses;         // Losses for season
        int         ties;           // Ties for season
        int         seed;           // Seed in division
};

#endif