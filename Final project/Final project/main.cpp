#include <iostream>
#include <fstream>
#include "Team.hpp"
#include "Competition.hpp"
#include <string>
bool loadTeamsFromFile;
int main() {
    Competition competition;  // Create a competition instance.
    std::ifstream inputFile("teams.txt");
        if (!inputFile) {
            std::cout << "Failed to open teams.txt" << std::endl;
            return 1;
        }

        std::string teamName;
        while (std::getline(inputFile, teamName)) {
            // Create a team and add it to the competition
            Team team(teamName);
            competition.addTeam(team);
//        }    if (!loadTeamsFromFile(competition)) {
//        return 1;
//    }

    // Check if an admin is logged in. You can add more logic for user vs. admin roles.
    bool isAdmin = isAdminLoggedIn();

    while (true) {
        try {
            if (isAdmin) {
                displayAdminMenu();  // Display the admin menu.
                int choice;
                std::cin >> choice;

                switch (choice) {
                    case 1:
                        // Display list of teams
                        std::cout << "List of teams in the competition:\n";
       for (const auto& team : competition.getTeams()) {
                  std::cout << team.getTeamName() << "\n";
                        }
                        break;
                    case 2:
                        addTeam(competition);
                        break;
                    case 3:
                    {
                        std::string teamNameToRemove;
                        std::cout << "Enter the name of the team to remove: ";
                        std::cin >> teamNameToRemove;
                        
             if (removeTeamFromFile("teams.txt", teamNameToRemove)) {
                            // Team successfully removed from the file
                            std::cout << "Team removed successfully.\n";
        competition.removeTeamByName(teamNameToRemove); // Remove the team from the competition instance
                        } else {
                            std::cout << "Error removing team. Team not found or file operation failed.\n";
                        }
                        break;
                    }
                    case 4:
                        // Other admin actions
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } else {
                displayUserMenu();  // Display the user menu.
                int choice;
                std::cin >> choice;

                switch (choice) {
                    case 1:  // Predict quarter-finalists.
                        std::vector<Team> quarterFinalists = competition.predictQuarterFinalists();
                        // Display or work with the quarter-finalists.
                        break;
                    case 2:  // Predict semi-finalists.
              std::vector<Team> quarterFinalists = competition.predictQuarterFinalists();
                        std::vector<Team> semiFinalists = competition.predictSemiFinalists(quarterFinalists);
                        // Display or work with the semi-finalists.
                        break;
                case 3:  // Predict the final winner.
                std::vector<Team> quarterFinalists = competition.predictQuarterFinalists();
    std::vector<Team> semiFinalists = competition.predictSemiFinalists(quarterFinalists);
                        std::string winner = competition.predictWinner(semiFinalists);
                        // Display or work with the winner.
                        break;
                    case 4:  // Exit.
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
