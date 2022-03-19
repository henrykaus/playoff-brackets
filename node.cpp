/**
 * @file node.cpp
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds method definitions for the node class as apart of a bracket 
 *        complete, balanced BST.
 * 
 * @copyright Copyright (c) 2022
 */
#include "node.h"
using namespace std;

// Default constructor
node::node() : left(nullptr), right(nullptr)
{
    spot.first.set_team("NONE", 0, 0, 0, 0);
    spot.second.set_team("NONE", 0, 0, 0, 0);
}

// Copy constructor
node::node(const node & _source) : left(nullptr), right(nullptr)
{
    copy_node(_source);
}

// Private copy helper
void node::copy_node(const node & _source)
{
    spot.first  = _source.spot.first;
    spot.second = _source.spot.second;
}

// Parameterized constructor
node::node(const pair<team, team> & _spot) : left(nullptr), right(nullptr)
{
    spot.first  = _spot.first;
    spot.second = _spot.second;
}

// Copy assignment operator
node & node::operator = (const node & _source)
{
    if (this != &_source)
        copy_node(_source);
    return *this;
}

// Setters
void node::set_pair(const team & _first, const team & _second)
{
    spot.first  = _first;
    spot.second = _second;
}
void node::set_pair_first(const team & _first)   { spot.first  = _first; }
void node::set_pair_second(const team & _second) { spot.second = _second; }
void node::set_left(node * _left)   { left  = _left; }
void node::set_right(node * _right) { right = _right; }

// Getters
const pair<team, team> & node::get_pair() const { return spot; }
node *& node::get_left()  { return left; }
node *& node::get_right() { return right; }