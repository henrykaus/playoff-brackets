/**
 * @file bracket_driver.cpp
 * @author Henry Kaus (https://github.com/henrykaus)
 * @brief Holds method definitions for the bracket_driver class which controls
 *        the user interface.
 * 
 * @copyright Copyright (c) 2022
 */
#include "bracket_driver.h"
using namespace std;

// Default constructor
bracket_driver::bracket_driver() : input_file("NONE")
{}


/**
 * @brief Starts and runs the overall bracket generator program by taking input
 *        and choosing methods to run from therein.
 * NOTE: To use the program, create a bracket_driver object, and call start()
 */
void bracket_driver::start()
{
    vector<string> file_options;    // File names in directory
    int            menu_option;     // Menu choice
    
    cout << endl;
    do {
        file_options.clear();

        switch (menu_option = read_main_menu_option())
        {
            case 0:         // Quit program
                break;
            case 1:         // Edit new file
                get_files(file_options, "resources\\new");
                modify_bracket(file_options, false);
                break;
            case 2:         // View existing file
                bool file_exists;
                try {
                    get_files(file_options, "resources\\saved");
                    file_exists = true;
                }
                // No files exist in resources/saved
                catch (const invalid_argument & err) {
                    get_files(file_options, "resources\\new");
                    file_exists = false;
                    cout << "No existing files. Please select a new file."
                        << endl;
                }
                modify_bracket(file_options, file_exists);
                break;
            case 3:         // Delete existing file
                get_files(file_options, "resources\\saved");
                delete_bracket(file_options);
                break;
            case 4:         // Create a new starter bracket
                create_a_bracket();
                break;
            default:
                break;
        }
    } while (menu_option != 0);
}


/**
 * @brief Prints main menu and takes input from user via stdin
 * 
 * @return int: option to run (1: new bracket, 2: existing bracket, 3: delete
 *              bracket, 4: new starter bracket, 0: quit program)
 */
int bracket_driver::read_main_menu_option()
{
    int option;

    cout << "What would you like to do?" << endl
         << "  [1] Create a New Bracket" << endl
         << "  [2] Select an Existing Bracket" << endl
         << "  [3] Delete an Existing Bracket" << endl
         << "  [4] Create a New Starter Bracket" << endl
         << "  [0] Quit the Program" << endl
         << "-> ";

    option = integer_input(cin, "-> ", 0, 4);
    cout << endl;

    return option;
}


/**
 * @brief Lets user pick a bracket to view, fills bracket, allows for
 *        modification, and saves the bracket.
 * 
 * @param _file_options is a std::vector<std::string> of possible brackets to 
 *                      view 
 * @param _editing_existing is if user has previously selected to edit existing 
 *                          bracket
 */
void bracket_driver::modify_bracket(const std::vector<std::string> & _file_options, bool _editing_existing)
{
    // Get menu choice
    if (read_bracket_choice(_file_options))
    {
        // Fill bracket, allow for edits, allow for saves
        try {
            fill_bracket(_editing_existing);
            view_edit_bracket();
            save(_editing_existing);
        }
        catch (const invalid_argument & err) {
            cerr << err.what() << endl << endl;
        }
    }
}


/**
 * @brief Reads should via stdin on user's choice of bracket to open
 * 
 * @param _file_options is std::vector<std::string> of possible files to open 
 * @return true if user selected a file to open
 * @return false if user selected to go back a menu
 */
bool bracket_driver::read_bracket_choice(const vector<string> & _file_options)
{
    int option;     // Menu choice
    
    // Print menu
    cout << "Which file would you like to open?" << endl;
    for (int i = 0; i < (int)_file_options.size(); ++i)
        cout << "  [" << i+1 << "] " << _file_options[i] << endl;
    cout << "  [0] Go Back" << endl;
    
    // Get input on choice of bracket
    cout << "-> ";
    option = integer_input(cin, "-> ", 0, _file_options.size());
    cout << endl;
    if (option == 0)
        return false;

    // Set input_file
    input_file = _file_options[option - 1];
    return true;
}


/**
 * @brief Calls bracket::fill_bracket() with path to file
 * 
 * @param _editing_existing is if user is editing an existing bracket
 */
void bracket_driver::fill_bracket(bool _editing_existing)
{
    if (_editing_existing)
        bracket::fill_bracket("resources\\saved\\" + input_file);
    else
        bracket::init_bracket("resources\\new\\" + input_file);
}


/**
 * @brief Has user view and edit bracket until they decide to quit
 */
void bracket_driver::view_edit_bracket()
{
    char option;

    // Initial bracket view
    bracket::draw();
    cout << endl;
    option = y_n_input(cin, "Would you like to continue editing");

    // Draw/edit bracket
    while (option == 'Y')
    {
        bracket::user_advance_winner();
        cout << endl;
        bracket::draw();
        cout << endl;
        option = y_n_input(cin, "Would you like to continue editing");
    }
}


/**
 * @brief Saves a file to filesystem by asking user to save changes and for a 
 *        file name if appropriate.
 * 
 * @param _editing_existing is if the user is editing an existing file
 */
void bracket_driver::save(bool _editing_existing)
{
    string output_file; // File to save to
    char   option;

    // Check if want to save
    option = y_n_input(cin, "Would you like to save your changes");
    if (option == 'N') {
        cout << endl;
        return;
    }

    // Assign file name to output file
    if (!_editing_existing)
    {
        // Get file name from user for new file
        read_output_file(output_file);
        // If exists, ask for confirmation
        while (check_file_exists(output_file, "resources\\saved"))
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
    }
    else
        output_file = input_file;

    cout << "Saving progress..." << endl << endl;
    bracket::save_bracket("resources\\saved\\" + output_file);
}


/**
 * @brief Deletes bracket from 'saved' directory by choosing an option and
 *        asking for confirmation
 * 
 * @param _file_options are the possible files to delete from directory
 */
void bracket_driver::delete_bracket(const vector<string> & _file_options)
{
    int    option;                                      // Menu choice
    string file_to_delete = ".\\resources\\saved\\";    // File to delete
    string are_you_sure_msg = "Are you sure you want to delete ";

    // Print list of existing files
    cout << "Which file would you like to delete?" << endl;
    for (int i = 0; i < (int)_file_options.size(); ++i)
        cout << "  [" << i+1 << "] " << _file_options[i] << endl;
    cout << "  [0] Do Not Delete" << endl;
    
    // Get input for file
    cout << "-> ";
    option = integer_input(cin, "-> ", 0, _file_options.size());
    cout << endl;
    
    // Allow abortion of deletion
    if (option == 0) return;
    are_you_sure_msg += _file_options[option - 1];
    if (!are_you_sure(cin, are_you_sure_msg.c_str(), true)) return;

    // Delete file/throw error
    file_to_delete += _file_options[option - 1].c_str();
    if (remove(file_to_delete.c_str()) != 0)
    {
        cerr << "ERROR: file does not exist." << endl << endl;
        return;
    }

    cout << _file_options[option - 1].c_str() << " was removed." << endl << endl;
}


/**
 * @brief Menu system and functionality for creating a starter bracket.
 */
void bracket_driver::create_a_bracket()
{
    int    menu_option;     // Menu choice
    string team_to_remove;
    
    do {
        switch (menu_option = read_creator_menu_option())
        {
            case 0:         // Discard and go back
                creator.clear();
                break;
            case 1:         // Add teams
                creator.input_teams();
                cout << endl;
                break;
            case 2:         // Remove teams
                cout << "Which team would you like to remove:" << endl << " -> ";
                getline(cin, team_to_remove);
                if (creator.remove_team(team_to_remove))
                    cout << team_to_remove << " removed." << endl << endl;
                else
                    cout << team_to_remove << " does not exist." << endl << endl;
                break;
            case 3:         // Edit teams
                creator.edit_specific();
                cout << endl;
                break;
            case 4:         // Print bracket
                creator.print();
                cout << endl;
                break;
            case 5:         // Save
                if (!creator.save())
                {
                    cout << "Saving failed, please ensure you have 2^n teams"
                         << " and valid seeds for each team." << endl << endl;
                    menu_option = -1;
                }
                break;
            default:
                break;
        }
    } while (menu_option != 0 && menu_option != 5);
}


/**
 * @brief Prints creator menu and takes input from user via stdin
 * 
 * @return int: option to run (1: add teams, 2: remove teams, 3: edit teams,
 *              4: save, 5: print bracket, 0: discard and go back)
 */
int bracket_driver::read_creator_menu_option()
{
    int option;

    cout << "What would you like to do?" << endl
         << "  [1] Add Teams" << endl
         << "  [2] Remove Teams" << endl
         << "  [3] Edit Teams" << endl
         << "  [4] Print Bracket" << endl
         << "  [5] Save and Go Back" << endl
         << "  [0] Discard Changes and Go Back" << endl
         << "-> ";

    option = integer_input(cin, "-> ", 0, 5);
    cin.ignore(10000, '\n');
    cout << endl;

    return option;
}