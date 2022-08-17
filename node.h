/**
 * @file node.h
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds definition for a node class that holds two competing teams in a
 *        playoff bracket tree.
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef BRACKET_NODE
#define BRACKET_NODE

#include "team.h"

/**
 * @brief The node class is a node in a complete balanced BST for a tournament
 *        bracket. You can set left and right pointers as well as the data in 
 *        the pair of team, as well as get all of the data. (A glorified struct)
 */
class node
{
    public:
        node();                                 // Default constructor
        node(const node &);                     // Copy constructor
        node(const std::pair<team, team> &);    // Param. constructor

        node & operator = (const node &);       // Copy assignment operator

        void set_left(node *);                  // Set left pointer
        void set_right(node *);                 // Set right pointer
        void set_pair(const team &, const team &);  // Set both teams
        void set_pair_first(const team &);      // Set first team
        void set_pair_second(const team &);     // Set second team

        node *& get_left();                     // Get left pointer
        node *& get_right();                    // Get right pointer
        const std::pair<team, team> & get_pair() const; // Get both teams

    private:
        std::pair<team, team> spot;     // Playoff round contenders
        node *                left;     // Left child
        node *                right;    // Right child

        void copy_node(const node &);           // Copy helper
};

#endif