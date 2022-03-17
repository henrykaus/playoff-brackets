#include "bracket.h"
using namespace std;

// Default Constructor
bracket::bracket() : root(nullptr)
{
    init(32);
}

// Copy Constructor
bracket::bracket(const bracket & _source) : root(nullptr)
{
    copy_bracket(_source);
}

void bracket::copy_bracket(const bracket & _source)
{
    bracket_spots = _source.bracket_spots;
    bracket_gap   = _source.bracket_gap;

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

// Parameterized Constructor
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

// Destructor
bracket::~bracket()
{
    erase();
}

void bracket::erase()
{
    erase(root);
    root          = nullptr;
    bracket_spots = 0;
    bracket_gap   = 0;
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

void bracket::fill_bracket(const string & _file_name)
{
    ifstream        inFile;             // Input stream

    // Open file
    inFile.open(_file_name);
    if (!inFile.is_open())
        throw invalid_argument("ERROR: file does not exist");

    erase();
    fill_bracket(inFile, root);
    bracket_gap = (2*(int)log2((bracket_spots+1)/2-1)+1) * SIZE_PAIR_PADDING; 

    inFile.close();
}

void bracket::fill_bracket(ifstream & inFile, node *& _root)
{
    inFile.peek();
    if (!inFile.eof())
    {
        pair<team, team> spot;
        bool             has_children;

        spot.first.read_team(inFile);
        inFile.ignore();
        spot.second.read_team(inFile);
        inFile.ignore();
        inFile >> has_children;
        inFile.ignore();

        _root = new node(spot);

        ++bracket_spots;

        if (has_children)
        {
            fill_bracket(inFile, _root->get_left());
            fill_bracket(inFile, _root->get_right());
        }
    }
}

// Initializes bracket from data file using fstream
void bracket::init_bracket(const string & _file_name)
{
    ifstream      inFile;             // Input stream
    stack<team>   unordered_teams;    // Teams from file
    team**        ordered_teams;      // Teams from file in seed order
    int           num_teams = 0;      // Number of teams from file
    team          temp_team;

    // Open file
    inFile.open(_file_name);
    if (!inFile.is_open())
        throw invalid_argument("File name doesn't exist");

    // Read data into a stack
    inFile.peek();
    while (!inFile.eof() && !inFile.fail())
    {
        temp_team.read_team(inFile);
        inFile.ignore();
        unordered_teams.push(temp_team);
        ++num_teams;
    }

    // Error check bad input
    if (!inFile.eof())
    {
        inFile.close();
        throw invalid_argument("File formatted incorrectly (ensure no empty lines)");
    }
    inFile.close();

    // Check if valid number of teams (2^x)
    if (!is_pow_two(num_teams))
        throw invalid_argument("Number of teams isn't power of two.");

    // Initialize array of ordered teams
    int array_size = num_teams * 2; // order_comp_teams() requires double size array
    ordered_teams  = new team*[array_size];
    for (int i = 0; i < array_size; ++i)
        ordered_teams[i] = nullptr;

    // Pop from stack into array based on seed number
    for (int i = 0; i < num_teams; ++i)
    {
        team * curr_team = new team(unordered_teams.top());
        // Check if negative, or too large of a seed, or if a double up on a seed
        if (curr_team->invalid_rank(num_teams) ||
            ordered_teams[curr_team->get_seed() - 1])
        {
            // Clean up added teams before throw
            for (int i = 0; i < num_teams; ++i)
                if (ordered_teams[i])
                    delete ordered_teams[i];
            delete ordered_teams;
            throw invalid_argument("Invalid seed in file.");
        }
        // Place team in array, remove from stack
        ordered_teams[curr_team->get_seed() - 1] = curr_team;
        unordered_teams.pop();
    }

    // Order teams based on seeded matchups (1v32, 2v31, ...) and place into tree
    ordered_teams = order_comp_bracket(ordered_teams, num_teams);
    fill_bracket(ordered_teams, num_teams);

    // Delete all elements from array
    for (int i = 0; i < num_teams; ++i)
        if (ordered_teams[i])
            delete ordered_teams[i];
    delete [] ordered_teams;
}

team ** bracket::order_comp_bracket(team ** _ordered_teams, int _size)
{
    int group_size = 1;    // How many teams are shifting
    int i, target_index;   // Iterators
    while (group_size < _size / 2)
    {
        // Space groups apart
        target_index = _size*2 - 1 - group_size; // End of expanded array
        i = _size - 1;                           // End of normal array
        while (i > group_size - 1)
        {
            for (int j = 0; j < group_size; ++j) // Moving each group
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
            for (int j = 0; j < group_size; ++j) // Moving each group
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

void bracket::fill_bracket(team ** _comp_ordered_teams, int _num_teams)
{
    int curr_index = 0;     // Requires referenced int

    // Reset bracket
    erase();
    init(_num_teams);

    // Fill bracket from array
    fill_bracket(root, _comp_ordered_teams, curr_index);
}

void bracket::fill_bracket(node * _root, team ** _comp_ordered_teams,
    int & _curr_index)
{
    // Adds teams from array if at child
    if (!_root->get_left() && !_root->get_right())
    {
        _root->set_pair(*_comp_ordered_teams[_curr_index], *_comp_ordered_teams[_curr_index + 1]);
        _curr_index += 2;
    }
    else
    {
        fill_bracket(_root->get_left(), _comp_ordered_teams, _curr_index);
        fill_bracket(_root->get_right(), _comp_ordered_teams, _curr_index);
    }
}

void bracket::save_bracket(const string & _file_name) const
{
    ofstream outFile;   // File ostream

    outFile.open(_file_name, std::ofstream::out | std::ofstream::trunc);
    save_bracket(outFile, root);
    outFile.close();
}

void bracket::save_bracket(ofstream & outFile, node * _root) const
{
    if (_root)
    {
        if (_root != this->root)
            outFile << '\n';
        _root->get_pair().first.print_for_file(outFile);
        outFile << ';';
        _root->get_pair().second.print_for_file(outFile);
        outFile << ';';

        if (_root->get_left())
        {
            outFile << "1";
            save_bracket(outFile, _root->get_left());
            save_bracket(outFile, _root->get_right());
        }
        else
            outFile << "0";
    }
}

void bracket::draw() const
{
    int max_depth = log2(bracket_spots + 1) - 1;    // Max depth of tree
    int num_columns = max_depth*2 + 1;              // Number of columns for bracket
    int center_column = num_columns / 2;            // Position of center column

    // Draw header for bracket
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

    // Draw full bracket and finals spot
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

// Draws two mirrored playoff spots
void bracket::draw_pairs(const pair<team, team> & _left_spot, 
                         const pair<team, team> & _right_spot, 
                         int _left_padding) const
{
    int right_padding = bracket_gap - (2*_left_padding);    // Padding between current spots
    
    // First team in matchup on left
    for (int i = 0; i < _left_padding; ++i)
        cout << ' ';
    cout << "|";
    if (!_left_spot.first.same_name("NONE"))
        _left_spot.first.display_in_bracket();
    else
        cout << "---------------";
    cout << "|";
    for (int i = 0; i < right_padding; ++i)
        cout << ' ';
    // First team in matchup on right
    cout << "|";
    if (!_right_spot.first.same_name("NONE"))
        _right_spot.first.display_in_bracket();
    else
        cout << "---------------";
    cout << "|\n";

    // Second team in matchup on left
    for (int i = 0; i < _left_padding; ++i)
        cout << ' ';
    cout << "|";
    if (!_left_spot.second.same_name("NONE"))
        _left_spot.second.display_in_bracket();
    else
        cout << "---------------";
    cout << "|";
    for (int i = 0; i < right_padding; ++i)
        cout << ' ';
    // Second team in matchup on right
    cout << "|";
    if (!_right_spot.second.same_name("NONE"))
        _right_spot.second.display_in_bracket();
    else
        cout << "---------------";
    cout << "|\n";
}

// Draws one bracket spot
void bracket::draw_pair(const pair<team, team> & _spot, 
                        int _left_padding) const
{
    // First team in matchup
    for (int i = 0; i < _left_padding; ++i)
        cout << ' ';
    cout << "|";
    if (!_spot.first.same_name("NONE"))
        _spot.first.display_in_bracket();
    else
        cout << "---------------";
    cout << "|\n";

    // Second team in matchup
    for (int i = 0; i < _left_padding; ++i)
        cout << ' ';
    cout << "|";
    if (!_spot.second.same_name("NONE"))
        _spot.second.display_in_bracket();
    else
        cout << "---------------";
    cout << "|" << endl;
}

void bracket::decide_winner()
{
    int  team_rank;
    bool found;

    cout << "Which team would you like to advance (team seed)? ";
    team_rank = integer_input(std::cin, "Please enter a valid seed: ", 1);
    cout << endl;

    found = search_and_decide(team_rank);
    if (!found)
        cout << "Team is out of the playoffs or doesn't exist." << endl;
    else
        cout << "Changes made if necessary." << endl;
}

bool bracket::search_and_decide(int _rank)
{
    return search_and_decide(root, nullptr, 'X', _rank);
}

bool bracket::search_and_decide(node * _root, node * _parent, char _dir, int _rank)
{
    if (_root)
    {
        bool found_left    = false;
        bool found_right   = false;
        team first         = _root->get_pair().first;
        team second        = _root->get_pair().second;
        bool first_exists  = !first.same_name("NONE");
        bool second_exists = !second.same_name("NONE");

        // Check if playoff spot has at least 1 team in it
        if (first_exists || second_exists)
        {
            // Determine if/where the found team is
            if (first_exists && first.same_seed(_rank))
                found_left = true;
            else if (second_exists && second.same_seed(_rank))
                found_right = true;

            // Determine where to continue search/decide winner
            if (first_exists && second_exists)
            {
                if (found_left)
                   advance_winner(first, _parent, _dir);
                else if (found_right)
                   advance_winner(second, _parent, _dir);
            }
            else if (first_exists && !found_left)
                found_right = search_and_decide(_root->get_right(), _root, 'R', _rank);
            else if (second_exists && !found_right)
                found_left  = search_and_decide(_root->get_left(), _root, 'L', _rank);
        }
        // Empty spot, continue left and right
        else
        {
            found_left  = search_and_decide(_root->get_left(), _root, 'L', _rank);
            if (!found_left)
                found_right = search_and_decide(_root->get_right(), _root, 'R', _rank);
        }
        return found_left || found_right;
    }
    else
        return false;
}

void bracket::advance_winner(const team & _winner, node * _parent, char _dir)
{
    // Case for if the final game
    if (!_parent)
        return;

    if (_dir == 'L')
        _parent->set_pair_first(_winner);
    else
        _parent->set_pair_second(_winner);
}