/**
 * @file bracket_creator.h
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds definition for the bracket_creator class as derived from utils 
 *        class. bracket_creator is the interface to create starter brackets, by
 *        adding, removing, editing, and inputing teams.
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef BRACKET_CREATOR
#define BRACKET_CREATOR

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <list>
#include "utils.h"
#include "team.h"

/**
 * @brief Holds methods for user interface to create a starter bracket that is
 *        used to create new brackets. After inputing teams, use save() method
 *        to save to a file in the local file system.
 */
class bracket_creator : protected utils
{
    public:
        bracket_creator();
        
        void clear();       // Clears list of all teams
        void print() const; // Prints every team in the list
        // Searches for first occurance of a team name
        std::list<team>::iterator search_list(const std::string &);
        // Pushes a team to the end of the bracket list
        void add_team(const team &);
        // Removes first occurence of team in the bracket list
        bool remove_team(const std::string &);
        // Takes input to add teams to the list
        void input_teams();
        // Prompts user to edit any attribute of the team
        void edit_specific();
        // Saves data to an data file with input for a unique file name
        bool save() const;
        // Checks if input teams are valid
        bool is_valid() const;

    private:
        std::list<team> bracket_teams;   // List of teams for a bracket

        // Private helper for saving the teams
        void save(const std::string &) const;
};

#endif