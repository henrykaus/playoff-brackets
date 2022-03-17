#include "bracket_driver.h"
using namespace std;

bracket_driver::bracket_driver() : input_file("NONE")
{}


void bracket_driver::start()
{
    vector<string> file_options;
    int            file_type;
    
    cout << endl;
    do {
        file_options.clear();
        file_type = read_file_type();
        switch (file_type)
        {
            case 1:
                get_files(file_options, "resources\\new");
                modify_file(file_options, false);
                break;
            case 2:
                bool file_exists;
                try {
                    get_files(file_options, "resources\\saved");
                    file_exists = true;
                }
                catch (const invalid_argument & err) {
                    cout << "No existing files. Please select a new file." << endl;
                    get_files(file_options, "resources\\new");
                    file_exists = false;
                }
                modify_file(file_options, file_exists);
                break;
            case 3:
                get_files(file_options, "resources\\saved");
                delete_file(file_options);
                break;
            default:
                break;
        }
    } while (file_type != 0);
}


int bracket_driver::read_file_type()
{
    int option;

    cout << "What would you like to do?" << endl
         << "  [1] Create a New Bracket" << endl
         << "  [2] Select an Existing Bracket" << endl
         << "  [3] Delete an Existing Bracket" << endl
         << "  [0] Quit the Program" << endl
         << "-> ";

    option = integer_input(cin, "-> ", 0, 3);
    cout << endl;

    return option;
}


void bracket_driver::delete_file(const vector<string> & _file_options)
{
    int option;
    string file_to_delete = ".\\resources\\saved\\";

    // Print list of existing files
    cout << "Which file would you like to delete?" << endl;
    for (int i = 0; i < (int)_file_options.size(); ++i)
        cout << "  [" << i+1 << "] " << _file_options[i] << endl;
    cout << "  [0] Do Not Delete" << endl;
    
    // Get input for file
    cout << "-> ";
    option = integer_input(cin, "-> ", 0, _file_options.size());
    cout << endl;
    
    if (option == 0) return;
    if (!are_you_sure(cin))
    {
        cout << endl;
        return;
    }
    cout << endl;

    // Delete file/throw error
    file_to_delete += _file_options[option - 1].c_str();
    
    if (remove(file_to_delete.c_str()) != 0)
    {
        cerr << "ERROR: file does not exist." << endl << endl;
        return;
    }

    cout << _file_options[option - 1].c_str() << " was removed." << endl << endl;
}


void bracket_driver::get_files(vector<string> & _files, const string & _path)
{
    for (const auto & entry : filesystem::directory_iterator(_path))
        _files.push_back(entry.path().filename().string());
    
    if (_files.size() < 1)
        throw invalid_argument("No files in the selection, please try adding one to resources\\new.");
}


void bracket_driver::modify_file(const std::vector<std::string> & _file_options, bool _file_exists)
{
    if (read_file(_file_options))
    {
        try {
            fill_bracket(_file_exists);
            mod_view_bracket();
            save(_file_exists);
        }
        catch (const invalid_argument & err) {
            cerr << err.what() << endl << endl;
        }
    }
}


bool bracket_driver::read_file(const vector<string> & _file_options)
{
    int option;

    cout << "Which file would you like to open?" << endl;
    for (int i = 0; i < (int)_file_options.size(); ++i)
        cout << "  [" << i+1 << "] " << _file_options[i] << endl;
    cout << "  [0] Go Back" << endl;
    
    cout << "-> ";
    option = integer_input(cin, "-> ", 0, _file_options.size());
    cout << endl;
    if (option == 0)
        return false;

    input_file = _file_options[option - 1];
    return true;
}


void bracket_driver::fill_bracket(bool _file_exists)
{
    if (_file_exists)
        bracket::fill_bracket("resources\\saved\\" + input_file);
    else
        bracket::init_bracket("resources\\new\\" + input_file);
}


void bracket_driver::mod_view_bracket()
{
    char option;
    bracket::draw();
    cout << endl;
    cout << "Would you like to continue (Y/N): ";
    option = capital_char_input(cin);
    cin.ignore(10000, '\n');
    // Draw brackets
    while (option == 'Y')
    {
        bracket::decide_winner();
        cout << endl;
        bracket::draw();
        cout << "Would you like to continue (Y/N): ";
        option = capital_char_input(cin);
        cin.ignore(10000, '\n');
    }
}


void bracket_driver::save(bool _file_exists)
{
    string output_file;
    char   option = 'N';

    // Check if want to save
    do {
        cout << "Would you like to save your changes (Y/N): ";
        option = capital_char_input(cin);
        cin.ignore(10000, '\n');
    } while (option != 'Y' && option != 'N');
    if (option == 'N')
    {
        cout << endl;
        return;
    }

    // Get file name to save to
    option = 'N';
    if (!_file_exists)
    {
        while (!read_output_file(output_file))
        {
            cout << endl;
            if (are_you_sure(cin, "This file name already exists, would you still like to save to this file"))
                break;
            else
                cout << endl;
        }
    }
    else
        output_file = input_file;

    cout << "Saving progress..." << endl << endl;
    bracket::save_bracket("resources\\saved\\" + output_file);
}


bool bracket_driver::read_output_file(string & _output_file)
{
    vector<string> reserved_files;

    cout << "What would you like to save the file as? " << endl
        << "-> ";
    getline(cin, _output_file);
    while (_output_file.find('\\') != string::npos || _output_file.find('/') != string::npos)
    {
        cout << "Do not use \\ or / in your name..." << endl
            << "-> ";
        _output_file.clear();
        getline(cin, _output_file);
    }
    _output_file.append(".txt");

    try {
        get_files(reserved_files, "resources\\saved");
    } catch (...) {}

    for (int i = 0; i < (int)reserved_files.size(); ++i)
    {
        if (reserved_files[i] == _output_file)
            return false;
    }
    return true;
}