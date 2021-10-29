#ifndef TEAM
#define TEAM

#include <iostream>
#include <string>
#include <iomanip>

class team
{
    public:
        team();
        team(std::string, int, int, int, int);

        void display() const;
        void display_in_bracket() const;
        bool invalid_rank(int) const;
        int  get_seed() const;

    private:
        std::string school_name;
        int wins;
        int losses;
        int ties;
        int seed;
};

#endif