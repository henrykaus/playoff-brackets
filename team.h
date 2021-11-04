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

        void display()              const;
        void display_in_bracket()   const;
        bool invalid_rank(int)      const;
        int  get_seed()             const;
        bool same_seed(int)         const;

    private:
        std::string school_name;    // Name of school
        int         wins;           // Wins for season
        int         losses;         // Losses for season
        int         ties;           // Ties for season
        int         seed;           // Seed in division
};

#endif