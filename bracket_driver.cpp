#include "bracket_driver.h"
using namespace std;

bracket_driver::bracket_driver() : input_file("NONE"), file_not_existing(false) {}

void bracket_driver::start()
{
    vector<string> file_options;
    char file_type = read_file_type();


    switch (file_type)
    {
        case 'N':
            get_files(file_options, "resources\\new");
            break;
        case 'E':
            try {
                get_files(file_options, "resources\\saved");
                file_not_existing = true;
            }
            catch(invalid_argument const&) {
                cout << "No existing files. Please select a new file." << endl;
                get_files(file_options, "resources\\new");
            }
            break;
        default:
            break;
    }

    cout << endl;
    read_file(file_options);
    cout << endl;
    fill_bracket();
    mod_view_bracket();
    save();
}

char bracket_driver::read_file_type()
{
    char option;

    cout << "Would you like to create a \'N\'ew bracket or select an \'E\'xisting? ";
    option = capital_char_input(cin);
    while (option != 'N' && option != 'E')
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "-> ";
        option = capital_char_input(cin);
    }

    return option;
}

void bracket_driver::get_files(vector<string> & files, const string & path)
{
    for (const auto & entry : filesystem::directory_iterator(path))
        files.push_back(entry.path().filename().string());
    
    if (files.size() < 1)
        throw invalid_argument("No files in the selection, please try adding one.");
}

void bracket_driver::read_file(const vector<string> & file_options)
{
    int option;

    cout << "Which file would you like to open?" << endl;
    for (int i = 0; i < (int)file_options.size(); ++i)
        cout << "  [" << i+1 << "] " << file_options[i] << endl;
    
    cout << "-> ";
    option = integer_input(cin, "-> ");
    while (option <= 0 || option > (int)file_options.size())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "-> ";
        option = integer_input(cin, "-> ");
    }

    input_file = file_options[option - 1];
}

void bracket_driver::fill_bracket()
{
    if (file_not_existing)
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

void bracket_driver::save()
{
    string output_file;
    char   option = 'N';

    if (!file_not_existing)
    {
        while (option != 'Y' && !read_output_file(output_file))
        {
            cout << "This file name already exists, would you still like to save to this file (Y/N)?" << endl
                << "-> ";
            option = capital_char_input(cin);
            cin.ignore(10000, '\n');
        }
    }
    else
        output_file = input_file;

    cout << "Saving progress..." << endl;
    bracket::save_bracket("resources\\saved\\" + output_file);
}

bool bracket_driver::read_output_file(string & output_file)
{
    vector<string> reserved_files;

    cout << "What would you like to save the file as? " << endl
        << "-> ";
    getline(cin, output_file);
    output_file.append(".txt");

    try {
        get_files(reserved_files, "resources\\saved");
    } catch (...) {}

    for (int i = 0; i < (int)reserved_files.size(); ++i)
    {
        if (reserved_files[i] == output_file)
            return false;
    }
    return true;
}