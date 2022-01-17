/**
 * @file bracket.h
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds definiton for the bracket -- a full and complete BST.
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

static const int SIZE_PAIR_PADDING = 18;

class bracket : public utils
{
    public:
        bracket();                  // Default constructor
        bracket(const bracket &);   // Copy constructor
        bracket(int);               // Param. constructor
        ~bracket();                 // Destructor

        bracket & operator = (const bracket &); // Copy assignment operator

        void init_bracket(const std::string & _file_name);
        void fill_bracket(const std::string & _file_name);
        void save_bracket(const std::string & _file_name) const;
        void draw() const;
        void decide_winner();
    
    protected:
        node * root;            // Root of bracket tree
        int    bracket_spots;   // How many elements in tree
        int    bracket_gap;     // Padding between outermost bracket spots

    private:
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