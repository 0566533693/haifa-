
#ifndef Team_hpp
#define Team_hpp

#include <iostream>
#include <string>

class Team {
public:
    Team(const std::string& name);  // Constructor

    std::string getTeamName() const;
    int getScore() const;
    void incrementScore();

private:
    std::string teamName;
    int score;
};

#endif /* Team_hpp */
