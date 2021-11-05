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
        bracket();
        bracket(const bracket &);
        bracket(int);
        ~bracket();

        bracket & operator = (const bracket &);

        void init_bracket(const std::string & file_name);
        void save_bracket(const std::string & file_name);
        void fill_bracket(const std::string & _file_name);
        void draw() const;
        void decide_winner();
    
    private:
        node * root;            // Root of bracket tree
        int    bracket_spots;   // How many elements in tree

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
        void draw_pairs(const std::pair<const team*, const team*> &,
            const std::pair<const team*, const team*> &, int _left_padding = 0)
            const;
        void draw_pair(const std::pair<const team*, const team*> &, int) const;
        void erase();
        void erase(node *);
        bool search_and_decide(int);
        bool search_and_decide(node *, node *, char, int);
        void user_pick_winner(node *, node *, char);
        void save_bracket(std::ofstream &, node *);
        void fill_bracket(std::ifstream & inFile, node *& _root);
};

#endif