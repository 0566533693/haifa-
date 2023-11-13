//
//  Competition.hpp
//  Final project
//
//  Created by Apple on 05/11/2023.
//



#include <stdio.h>
// Competition.hpp
#ifndef Competition_hpp
#define Competition_hpp

#include <iostream>
#include <vector>
#include "Team.hpp"

class Competition {
private:
    std::vector<Team> teams;

public:
    const std::vector<Team>& getTeams() const;
    void addTeam(const Team& team);
    std::vector<Team> predictQuarterFinalists() const;
    std::vector<Team> predictSemiFinalists(const std::vector<Team>& quarterFinalists) const;
    std::string predictWinner(const std::vector<Team>& semiFinalists) const;
};

bool isAdminLoggedIn();
void displayUserMenu();
void displayAdminMenu();
void addTeam(Competition& competition);

#endif /* Competition_hpp */


