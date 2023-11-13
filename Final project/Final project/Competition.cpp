
#include <iostream>
#include "Team.hpp"
#include <vector>
#include "map"
#include <fstream>
#include <algorithm>

class Competition {
private:
    std::vector<Team> teams;
    std::map<std::string, Team> teamMap; // represents the collection of teams in the competition. These teams are stored in this vector.

public:
    const std::vector<Team>& getTeams() const {
        return teams;
    }

    void addTeam(const Team& team) {
        teams.push_back(team);
    }
    void removeTeamByName(const std::string& teamName) {
        teams.erase(std::remove_if(teams.begin(), teams.end(),
        [teamName](const Team& team) { return team.getTeamName() == teamName; }),
            teams.end());

            // remove team from the map
            teamMap.erase(teamName);
        }

        // function to get a Team by name from the map
        const Team* getTeamByName(const std::string& teamName) const {
            auto it = teamMap.find(teamName);
            return (it != teamMap.end()) ? &it->second : nullptr;
        }

    std::vector<Team> predictQuarterFinalists() const {
        std::vector<Team> quarterFinalists = teams;

        std::sort(quarterFinalists.begin(), quarterFinalists.end(), [](const Team& a, const Team& b) {
            return a.getScore() > b.getScore();
        });

       
        quarterFinalists.resize(std::min(4, static_cast<int>(quarterFinalists.size())));

        return quarterFinalists;
    }

    std::vector<Team> predictSemiFinalists(const std::vector<Team>& quarterFinalists) const {
        std::vector<Team> semiFinalists = quarterFinalists;

        std::sort(semiFinalists.begin(), semiFinalists.end(), [](const Team& a, const Team& b) {
            return a.getScore() > b.getScore();
        });

        semiFinalists.resize(std::min(2, static_cast<int>(semiFinalists.size())));

        return semiFinalists;
    }

    std::string predictWinner(const std::vector<Team>& semiFinalists) const {
        const Team* winner = &semiFinalists[0];

        for (size_t i = 1; i < semiFinalists.size(); ++i) {
            const Team& currentTeam = semiFinalists[i];

            if (currentTeam.getScore() > winner->getScore()) {
                winner = &currentTeam;
            }
        }

        return winner->getTeamName();
    }
    
    bool removeTeamFromFile(const std::string& filename, const std::string& teamNameToRemove) {
            std::ifstream inFile(filename);
            std::ofstream outFile("temp.txt"); // Create a temporary file

            if (!inFile.is_open() || !outFile.is_open()) {
                return false; // Error opening files
            }

            std::string line;
            bool teamRemoved = false;

            while (std::getline(inFile, line)) {
                if (line != teamNameToRemove) {
                    outFile << line << "\n";
                } else {
                    teamRemoved = true;
                }
            }

            inFile.close();
            outFile.close();

            if (teamRemoved) {
                std::remove(filename.c_str());       // Delete the original file
                std::rename("temp.txt", filename.c_str()); // Rename the temporary file
            } else {
                std::remove("temp.txt"); // Remove the temporary file
            }

            return teamRemoved;
        }
};

