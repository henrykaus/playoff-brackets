/**
 * @file bracket_creator.h
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief 
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
 * @brief 
 */
class bracket_creator : protected utils
{
    public:
        bracket_creator();
        
        void clear();
        void print() const;
        std::list<team>::iterator search_list(const std::string &);
        void add_team(const team &);
        bool remove_team(const std::string &);
        void input_teams();
        void edit_specific();
        bool save() const;
        bool is_valid() const;

    private:
        std::list<team> bracket_teams;

        void save(const std::string &) const;
};

#endif