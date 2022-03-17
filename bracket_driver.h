#ifndef BRACKET_DRIVER
#define BRACKET_DRIVER

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include "bracket.h"

class bracket_driver : public bracket
{
    public:
        bracket_driver();

        void start();       // Ask for new (resources/new) or existing file (resources/saved), read_file_type()
                            // displays current options, saves to an array, read_file()
                            // fills bracket base on input,                 view_edit_bracket()
                            // saves to appropriate file (" "_saved.txt in resources/saved) save()
        
    private:
        int  read_menu_option();
        void get_files(std::vector<std::string> & files, const std::string & path);
        void modify_bracket(const std::vector<std::string> & _file_options, bool _editing_existing);
        bool read_bracket_choice(const std::vector<std::string> & files_options);
        void fill_bracket(bool _editing_existing);
        void view_edit_bracket();
        void save(bool _editing_existing);
        void read_output_file(std::string & output_file);
        bool check_file_exists(const std::string & _output_file);
        void delete_bracket(const std::vector<std::string> & _file_options);

    protected:
        std::string input_file;
};

#endif