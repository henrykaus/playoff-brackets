#include "node.h"
using namespace std;

// Default constructor
node::node() : left(nullptr), right(nullptr)
{
    spot.first = spot.second = nullptr;
}

// Copy constructor
node::node(const node & _source) : left(nullptr), right(nullptr)
{
    copy_node(_source);
}

// Private copy helper
void node::copy_node(const node & _source)
{
    if (_source.spot.first) spot.first = new team(*_source.spot.first);
    else                    spot.first = nullptr;

    if (_source.spot.second) spot.second = new team(*_source.spot.second);
    else                     spot.second = nullptr;
}

// Parameterized constructor
node::node(pair<team *, team *> _spot) : left(nullptr), right(nullptr)
{
    spot.first = _spot.first;
    spot.second = _spot.second;
}

// Destructor
node::~node()
{
    if (spot.first)
        delete spot.first;
    if (spot.second)
        delete spot.second;
}

// Copy assignment operator
node & node::operator = (const node & _source)
{
    if (this != &_source)
        copy_node(_source);
    return *this;
}

// Setters
void node::set_pair(team * _first, team * _second)
{
    spot.first  = _first;
    spot.second = _second;
}

void node::set_pair_first(team * _first)   { spot.first  = _first; }
void node::set_pair_second(team * _second) { spot.second = _second; }
void node::set_left(node * _left)   { left  = _left; }
void node::set_right(node * _right) { right = _right; }

// Getters
const pair<team *, team *> & node::get_pair() const { return spot; }
node *& node::get_left()  { return left; }
node *& node::get_right() { return right; }