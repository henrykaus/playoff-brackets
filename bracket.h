#ifndef BRACKET
#define BRACKET

#include <iostream>
#include <iomanip>
#include <stdexcept>
//#include <utility>
#include <cmath>
#include <fstream>
#include <stack>
#include "team.h"
#include "utils.h"

static const int SIZE_PAIR_PADDING = 18;

class node
{
    public:
        node();
        node(const node &);
        node(std::pair<team *, team *>);
        ~node();

        node & operator = (const node &);

        void set_left(node *);
        void set_right(node *);
        void set_pair(team *, team *);

        node *& get_left();
        node *& get_right();
        const std::pair<team *, team *> & get_pair() const;

    private:
        std::pair<team *, team *> spot;
        node * left;
        node * right;

        void copy_node(const node &);
};

class bracket : public utils
{
    public:
        bracket();
        bracket(const bracket &);
        bracket(int);
        ~bracket();

        bracket & operator = (const bracket &);

        void init_bracket(std::string file_name);
        void draw() const;
    
    private:
        node * root;
        int bracket_spots;
        int bracket_gap;

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
};

#endif