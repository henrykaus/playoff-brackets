#include "bracket_creator.h"
using namespace std;

// Default constructor
bracket_creator::bracket_creator()
{}


/**
 * @brief Clears the list of all teams.
 */
void bracket_creator::clear()
{
    bracket_teams.clear();
}


/**
 * @brief Prints every team in the list with team::display().
 */
void bracket_creator::print() const
{
    for (auto ci = bracket_teams.begin(); ci != bracket_teams.end(); ++ci)
        ci->display();
}


/**
 * @brief Searches for the first team in the list with the team name. Will
 *        return bracket_teams.end if failure to find a match.
 * 
 * @param _team_name is the team name string to search for
 * @return list<team>::iterator is the returned position
 */
list<team>::iterator bracket_creator::search_list(const string & _team_name)
{
    list<team>::iterator it;

    for (it = bracket_teams.begin(); it != bracket_teams.end(); ++it)
    {
        if (it->same_name(_team_name))
            return it;
    }
    return it;
}


/**
 * @brief Pushes a team to the end of the bracket list.
 * 
 * @param _team_to_add is the team to add to the list
 */
void bracket_creator::add_team(const team & _team_to_add)
{
    bracket_teams.push_back(_team_to_add);
}


/**
 * @brief Removes the first team in the list with a matching team name.
 * 
 * @param _team_to_remove is the team name string to remove
 * @return true if the team was removed
 * @return false if the team didn't exist
 */
bool bracket_creator::remove_team(const std::string & _team_to_remove)
{
    list<team>::iterator it = search_list(_team_to_remove);
    if (it == bracket_teams.end())
        return false;

    bracket_teams.erase(it);
    return true;
}


/**
 * @brief Takes input from user for teams to add to list until user inputs.
 *        0:0:0:0:0 to signal a stop
 * FIXME: Does not check for bad input
 */
void bracket_creator::input_teams()
{
    team team_to_add;
    bool quit = false;

    cout << "Enter a team in this format -> TEAM_NAME:WINS:LOSSES:TIES:SEED"
         << endl << "    To quit, enter -> 0:0:0:0:0" << endl;

    cout << " -> ";
    team_to_add.read_team(cin, ':');
    cin.ignore(10000, '\n');

    quit = team_to_add.same_name("0");
    while (!quit)
    {
        this->add_team(team_to_add);
        cout << " -> ";
        team_to_add.read_team(cin, ':');
        cin.ignore(10000, '\n');

        quit = team_to_add.same_name("0");
    }
}


/**
 * @brief Repeatedly prompts user to edit a team of choice and then calls
 *        team::edit_team() to edit a singular attribute for the team. Quits when
 *        user requests to stop.
 */
void bracket_creator::edit_specific()
{
    string team_to_edit;
    bool   quit = false;

    cout << "Which team would you like to edit: " << endl
         << " -> ";
    getline(cin, team_to_edit, '\n');

    list<team>::iterator it = search_list(team_to_edit);
    if (it == bracket_teams.end())
    {
        cout << endl << "That team does not exist" << endl;
        quit = true;
    }

    while (!quit)
    {
        it->edit_team();
        cout << endl;
        if (y_n_input(cin, "Would you like to continue editing") == 'N')
            quit = true;
        cout << endl;
    }
}


/**
 * @brief Will save all teams to starter bracket file in resource/new when
 *        is_valid is true and user enters and is happy with their file name.
 * 
 * @return true if saving completed
 * @return false if saving didn't complete due to user abort or invalid info in
 *         bracket
 */
bool bracket_creator::save() const
{
    string output_file;
    char   option;

    // Check validity
    if (!this->is_valid())
        return false;

    // Check if want to save
    option = y_n_input(cin, "Would you like to save your changes");
    if (option == 'N') {
        cout << endl;
        return false;
    }

    // Get file name from user for new file
    read_output_file(output_file);
    // If exists, ask for confirmation
    while (check_file_exists(output_file, "resources\\new"))
    {
        cout << endl;
        if (are_you_sure(cin, "This file name already exists, would you still like to save to this file"))
            break;
        else
        {
            cout << endl;
            read_output_file(output_file);
        }
    }

    cout << "Saving progress..." << endl << endl;
    this->save("resources\\new\\" + output_file);
    return true;
}


/**
 * @brief Private helper that opens file, saves all teams to file, and closes
 *        file.
 * 
 * @param _output_path is the file and path to save to
 */
void bracket_creator::save(const string & _output_path) const
{
    ofstream outFile;   // File ostream

    outFile.open(_output_path, std::ofstream::out | std::ofstream::trunc);
   
    for (auto ci = bracket_teams.begin(); ci != bracket_teams.end();)
    {
        ci->print_for_file(outFile);
        if (++ci != bracket_teams.end())
            outFile << "\n";
    }

    outFile.close();
}


/**
 * @brief Will check for three valid conditions listed below and return whether
 *        the bracket teams contain invalid seeds.
 * 
 * @return true if data is valid
 * @return false if data is invalid
 *          (1) Number of teams isn't power of 2
 *          (2) Duplicate seeds exist in teams
 *          (3) A seed is larger than the number of teams
 */
bool bracket_creator::is_valid() const
{
    bool * seed_array;
    int    num_seeds = bracket_teams.size();
    int    curr_seed;

    // Check for size of power of two
    if (!is_pow_two(num_seeds) || num_seeds <= 0)
        return false;

    // Initialize duplicate checking array
    seed_array = new bool[num_seeds + 1];
    for (int i = 0; i < num_seeds + 1; ++i)
        seed_array[i] = false;
    
    // Check for duplicate seeds and too large of seed
    for (auto ci = bracket_teams.begin(); ci != bracket_teams.end(); ++ci)
    {
        curr_seed = ci->get_seed();
        // Ensure curr seed is less than/equal to number of seeds
        if (curr_seed > num_seeds) {
            delete [] seed_array;
            return false;
        }
        // If seed position has already been set, a dupe exists
        if (seed_array[curr_seed]) {
            delete [] seed_array;
            return false;
        }
        else
            seed_array[curr_seed] = true;
    }

    delete [] seed_array;
    return true;
}