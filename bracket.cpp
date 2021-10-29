#include "bracket.h"
using namespace std;

/* *********************** BRACKET CLASS ************************ */
bracket::bracket() : root(nullptr)
{
    init(32);
}

bracket::bracket(const bracket & _source) : root(nullptr)
{
    copy_bracket(_source);
}

void bracket::copy_bracket(const bracket & _source)
{
    bracket_gap   = _source.bracket_gap;
    bracket_spots = _source.bracket_spots;

    if (_source.root)
        copy_bracket(root, _source.root);
}

void bracket::copy_bracket(node *& _dest_root, node * _source_root)
{
    if (_source_root)
    {
        _dest_root = new node(*_source_root);
        copy_bracket(_dest_root->get_left(), _source_root->get_left());
        copy_bracket(_dest_root->get_right(), _source_root->get_right());
    }
    else
        _dest_root = nullptr;
}

bracket::bracket(int _bracket_teams) : root(nullptr)
{
    init(_bracket_teams);
}

bracket & bracket::operator = (const bracket & _source)
{
    if (this != &_source)
        copy_bracket(_source);
    return *this;
}

void bracket::init(int _bracket_teams)
{
    bracket_spots = 0;
    if (_bracket_teams == 1 || !is_pow_two(_bracket_teams))
        throw invalid_argument("Number of teams isn't power of two.");
    
    for (int temp_bracket_size = _bracket_teams / 2; temp_bracket_size > 1; temp_bracket_size /= 2)
        bracket_spots += temp_bracket_size;
    ++bracket_spots;

    bracket_gap = (2*(int)log2((bracket_spots+1)/2-1)+1) * SIZE_PAIR_PADDING;

    create_tree();
}

void bracket::create_tree()
{
    root = new node();
    create_tree(root, 0, log2(bracket_spots+1) - 1);
}

void bracket::create_tree(node * _curr_root, int _curr_depth, int _max_depth)
{
    if (_curr_depth < _max_depth)
    {
        _curr_root->set_left(new node());
        _curr_root->set_right(new node());
        create_tree(_curr_root->get_left(), _curr_depth + 1, _max_depth);
        create_tree(_curr_root->get_right(), _curr_depth + 1, _max_depth);
    }
}

bracket::~bracket()
{
    erase();
}

void bracket::erase()
{
    erase(root);
    root = nullptr;
}

void bracket::erase(node * _curr_root)
{
    if (_curr_root)
    {
        erase(_curr_root->get_left());
        erase(_curr_root->get_right());
        delete _curr_root;
    }
}

void bracket::init_bracket(string file_name)
{
    ifstream        inFile;
    stack<team *>   unordered_teams;
    team**          ordered_teams;
    int num_teams = 0;

    string          school_name;
    int wins, losses, ties, seed;

    // Open file
    inFile.open(file_name);
    if (!inFile.is_open())
        throw invalid_argument("File name doesn't exist");

    inFile.clear();
    // Read data into a stack
    while (!inFile.eof() && inFile.good())
    {
        getline(inFile, school_name, ';');
        inFile >> wins;
        inFile.get();
        inFile >> losses;
        inFile.get();
        inFile >> ties;
        inFile.get();
        inFile >> seed;
        inFile.get();

        unordered_teams.push(new team(school_name, wins, losses, ties, seed));
        ++num_teams;
    }

    // Error check bad input
    if (inFile.fail() && !inFile.eof())
    {
        inFile.close();
        for (int i = 0; i < num_teams; ++i)
        {
            delete unordered_teams.top();
            unordered_teams.pop();
        }
        throw invalid_argument("File formatted incorrectly (ensure no empty lines)");
    }

    inFile.close();

    // Check if valid number of teams (2^x)
    if (!is_pow_two(num_teams))
    {
        // Clean up before throw
        for (int i = 0; i < num_teams; ++i)
        {
            delete unordered_teams.top();
            unordered_teams.pop();
        }
        throw invalid_argument("Number of teams isn't power of two.");
    }

    // Initialize array of ordered teams
    int array_size = num_teams * 2;
    ordered_teams = new team*[array_size];
    for (int i = 0; i < array_size; ++i)
        ordered_teams[i] = nullptr;

    // Pop from stack into array based on seed number
    for (int i = 0; i < num_teams; ++i)
    {
        team * curr_team = unordered_teams.top();
        // Check if negative, or too large of a seed, or if a double up on 1 seed
        if (curr_team->invalid_rank(num_teams) ||
           (ordered_teams[curr_team->get_seed() - 1]))
        {
            // Clean up added teams before throw
            for (int i = 0; i < num_teams; ++i)
            {
                if (ordered_teams[i])
                    delete ordered_teams[i];
            }
            delete ordered_teams;
            throw invalid_argument("Invalid seed in file.");
        }
        ordered_teams[curr_team->get_seed() - 1] = curr_team;
        unordered_teams.pop();
    }

    // Get bracket ready for insertions
    ordered_teams = order_comp_bracket(ordered_teams, num_teams);
    fill_bracket(ordered_teams, num_teams);
    delete [] ordered_teams;
}

team ** bracket::order_comp_bracket(team ** _ordered_teams, int _size)
{
    int group_size = 1;
    int i, target_index;
    while (group_size < _size / 2)
    {
        // Space groups apart
        target_index = _size*2 - 1 - group_size; // End of expanded array
        i = _size - 1;                           // End of normal array
        while (i > group_size - 1)
        {
            for (int j = 0; j < group_size; ++j)    // Moving each group
            {
                _ordered_teams[target_index] = _ordered_teams[i];
                _ordered_teams[i] = nullptr;
                --target_index;
                --i;
            }
            target_index -= group_size;
        }

        // Recombine groups
        target_index = _size*2 - 1 - group_size; // End of expanded array
        i = group_size;                          // Startish of array
        while (i < _size)
        {
            for (int j = 0; j < group_size; ++j)    // Moving each group
            {
                _ordered_teams[i] = _ordered_teams[target_index];
                _ordered_teams[target_index] = nullptr;
                --target_index;
                ++i;
            }
            target_index -= group_size;
            i += group_size;
        }
        group_size *= 2;
    }
    return _ordered_teams;
}

void bracket::fill_bracket(team ** _comp_ordered_teams, int num_teams)
{
    int curr_index = 0;
    erase();
    init(num_teams);
    fill_bracket(root, _comp_ordered_teams, curr_index);
}

void bracket::fill_bracket(node * _root, team ** _comp_ordered_teams,
    int & _curr_index)
{
    if (!_root->get_left() && !_root->get_right())
    {
        _root->set_pair(_comp_ordered_teams[_curr_index],
            _comp_ordered_teams[_curr_index+1]);
        _curr_index += 2;
    }
    else
    {
        fill_bracket(_root->get_left(), _comp_ordered_teams, _curr_index);
        fill_bracket(_root->get_right(), _comp_ordered_teams, _curr_index);
    }
}

void bracket::draw() const
{
    int max_depth = log2(bracket_spots + 1) - 1;
    int num_columns = max_depth*2 + 1;
    int center_column = num_columns / 2;

    for (int i = 0; i < num_columns; ++i)
    {
        if (i == center_column - 2 || i == center_column + 2)
            cout << left << setw(18) << setfill(' ') << "QUARTERFINALS";
        else if (i == center_column - 1 || i == center_column + 1)
            cout << left << setw(18) << setfill(' ') << "SEMIFINALS";
        else if (i == center_column)
            cout << left << setw(18) << setfill(' ') << "FINAL";
        else if (i < center_column)
            cout << left << "ROUND: " << setw(11) << setfill(' ') << i + 1;
        else
            cout << left << "ROUND: " << setw(11) << setfill(' ') 
                 << num_columns - i;
    }
    cout << endl << setw(num_columns * 18 - 2) << setfill('=') << '=' << endl;

    max_depth = 0;
    draw(root->get_left(), root->get_right(), 0, max_depth);
    draw_pair(root->get_pair(), bracket_gap/2 + SIZE_PAIR_PADDING/2);
}

void bracket::draw(node * _left_root, node * _right_root, int _curr_depth,
    int & _max_depth) const
{
    if (_left_root)
    {
        if (_curr_depth > _max_depth)
            _max_depth = _curr_depth;
        draw(_left_root->get_left(), _right_root->get_left(), _curr_depth + 1,
            _max_depth);
        draw_pairs(_left_root->get_pair(), _right_root->get_pair(),
            (_max_depth-_curr_depth) * SIZE_PAIR_PADDING);
        draw(_left_root->get_right(), _right_root->get_right(), _curr_depth + 1,
            _max_depth);
    }
}

void bracket::draw_pairs(const pair<const team*, const team*> & _left_spot, 
                         const pair<const team*, const team*> & _right_spot, 
                         int _left_padding) const
{
    int right_padding = bracket_gap - (2*_left_padding); //FIXME
    // First team in matchup on left
    for (int i = 0; i < _left_padding; ++i)
        cout << ' ';
    cout << "|";
    if (_left_spot.first)
        _left_spot.first->display_in_bracket();
    else
        cout << "---------------";
    cout << "|";
    for (int i = 0; i < right_padding; ++i)
        cout << ' ';
    // First team in matchup on right
    cout << "|";
    if (_right_spot.first)
        _right_spot.first->display_in_bracket();
    else
        cout << "---------------";
    cout << "|\n";

    // Second team in matchup on left
    for (int i = 0; i < _left_padding; ++i)
        cout << ' ';
    cout << "|";
    if (_left_spot.second)
        _left_spot.second->display_in_bracket();
    else
        cout << "---------------";
    cout << "|";
    for (int i = 0; i < right_padding; ++i)
        cout << ' ';
    // Second team in matchup on right
    cout << "|";
    if (_right_spot.second)
        _right_spot.second->display_in_bracket();
    else
        cout << "---------------";
    cout << "|\n";
}

void bracket::draw_pair(const pair<const team*, const team*> & _spot, 
                        int _left_padding) const
{
    // First team in matchup
    for (int i = 0; i < _left_padding; ++i)
        cout << ' ';
    cout << "|";
    if (_spot.first)
        _spot.first->display_in_bracket();
    else
        cout << "---------------";
    cout << "|\n";

    // Second team in matchup
    for (int i = 0; i < _left_padding; ++i)
        cout << ' ';
    cout << "|";
    if (_spot.second)
        _spot.second->display_in_bracket();
    else
        cout << "---------------";
    cout << "|" << endl;
}


/* *********************** NODE CLASS ************************ */
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