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
                            // fills bracket base on input,                 mod_view_bracket()
                            // saves to appropriate file (" "_saved.txt in resources/saved) save()
        
    private:
        char read_file_type();
        void get_files(std::vector<std::string> & files, const std::string & path);
        void read_file(const std::vector<std::string> & files_options);
        void fill_bracket();
        void mod_view_bracket();
        void save();
        bool read_output_file(std::string & output_file);

    protected:
        std::string input_file;
        bool        file_exists;
};

#endif