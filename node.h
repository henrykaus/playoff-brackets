#ifndef BRACKET_NODE
#define BRACKET_NODE

#include "team.h"

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
        void set_pair_first(team *);
        void set_pair_second(team *);

        node *& get_left();
        node *& get_right();
        const std::pair<team *, team *> & get_pair() const;

    private:
        std::pair<team *, team *> spot;     // Playoff round contenders
        node *                    left;     // Left child
        node *                    right;    // Right child

        void copy_node(const node &);
};

#endif