#include "node.h"
using namespace std;

node::node() : left(nullptr), right(nullptr)
{
    spot.first = spot.second = nullptr;
}

node::node(const node & _source) : left(nullptr), right(nullptr)
{
    copy_node(_source);
}

void node::copy_node(const node & _source)
{
    if (_source.spot.first) spot.first = new team(*_source.spot.first);
    else                    spot.first = nullptr;

    if (_source.spot.second) spot.second = new team(*_source.spot.second);
    else                     spot.second = nullptr;
}

node::node(pair<team *, team *> _spot) : left(nullptr), right(nullptr)
{
    spot.first = _spot.first;
    spot.second = _spot.second;
}

node::~node()
{
    if (spot.first)
        delete spot.first;
    if (spot.second)
        delete spot.second;
}

node & node::operator = (const node & _source)
{
    if (this != &_source)
        copy_node(_source);
    return *this;
}

const pair<team *, team *> & node::get_pair() const { return spot; }
void node::set_pair(team * _first, team * _second)
{
    spot.first  = _first;
    spot.second = _second;
}

void node::set_left(node * _left)   { left  = _left; }
void node::set_right(node * _right) { right = _right; }

node *& node::get_left()  { return left; }
node *& node::get_right() { return right; }