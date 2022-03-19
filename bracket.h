/**
 * @file bracket.h
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds definition for the bracket -- a full and complete binary search
 *        tree.
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef BRACKET
#define BRACKET

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>
#include <fstream>
#include <stack>
#include "node.h"
#include "team.h"
#include "utils.h"

static const int SIZE_PAIR_PADDING = 18;    // Size of matchup pair in print

/**
 * @brief A binary search tree for a 2^n number of seeded teams. Has methods to
 *        initialize an empty bracket and a bracket that has been modified, to 
 *        save the bracket, print the bracket, and have the user modify the
 *        bracket by advancing winners through. A bracket that has been saved
 *        must be initialized through fill_bracket(), NOT init_bracket(). init
 *        is solely for a list of teams with seeds, not matchups (see file in
 *        resources/new and resources/saved).
 */
class bracket : public utils
{
    public:
        bracket();                  // Default constructor
        bracket(const bracket &);   // Copy constructor
        bracket(int);               // Param. constructor
        ~bracket();                 // Destructor

        bracket & operator = (const bracket &); // Copy assignment operator

        // Initialize bracket with a file with teams with seeds
        void init_bracket(const std::string & _file_name);
        // Initialize bracket with a previously modified bracket file
        void fill_bracket(const std::string & _file_name);
        // Save bracket to the file system
        void save_bracket(const std::string & _file_name) const;
        // Print bracket to screen
        void draw() const;
        // Have user pick a team to advance
        void user_advance_winner();
    
    protected:
        node * root;            // Root of bracket tree
        int    bracket_spots;   // How many elements in tree
        int    bracket_gap;     // Padding between outermost bracket spots

    private:
        // Various helper functions for the public methods
        void copy_bracket(const bracket &);
        void copy_bracket(node *&, node *);
        void init(int);
        void create_tree();
        void create_tree(node *, int, int);
        team ** order_comp_bracket(team **, int);
        void fill_bracket(team **, int);
        void fill_bracket(node *, team **, int &);
        void draw(node * _left_root, node * _right_root, int _curr_depth,
            int & _max_depth) const;
        void draw_pairs(const std::pair<team, team> &,
            const std::pair<team, team> &, int _left_padding = 0) const;
        void draw_pair(const std::pair<team, team> &, int) const;
        void erase();
        void erase(node *);
        bool search_and_decide(int);
        bool search_and_decide(node *, node *, char, int);
        void advance_winner(const team &, node *, char);
        void save_bracket(std::ofstream &, node *) const;
        void fill_bracket(std::ifstream & inFile, node *& _root);
};

#endif