#include <iostream>
#include <array>
#include <string>


// Enumeration of all the player
enum class Player {CROSS, CIRCLE, NONE};

// Size and map of the game
const int SIZE = 3;
std::array<std::array<Player, SIZE>, SIZE> MAP = {{{Player::NONE, Player::NONE, Player::NONE},   
                                                    {Player::NONE, Player::NONE, Player::NONE},
                                                    {Player::NONE, Player::NONE, Player::NONE}}};

Player switchUser(Player user) {
    if(user == Player::CIRCLE){
        return Player::CROSS;
    }
    return Player::CIRCLE;
}

/**
 * Check the win in vertical or horizontal
 * @param hOrV true the check is horizontal, false for vertical
 * @return if the user has won
*/
bool checkHV(Player user,bool hOrV) {
 
    for(int y=0; y < SIZE; y++) {
        int check = 0;
        for(int x=0; x < SIZE; x++) {
            // Get current value according to vertical or horizontal
            Player player = hOrV ? MAP[x][y] : MAP[y][x];
        
            // If the case is check cout it
            if(player == user) {
                check++;
            } 
        }

        // After tree times we have a winner
        if(check == SIZE) {
            return true;
        }
    }
    
    return false;
}

/**
 * Check if a user win
 * @param player to be checked
 * @return the player 
*/
bool check(Player user) {
    int check = 0;
    // First diagonal
    for(int i=0; i < SIZE; i++) {
        if(user == MAP[i][i]) {
            check++;
        }
    }

    // After tree times we have a winner
    if(check == SIZE) {
        return true; 
    }

    // Second diagonal
    check = 0;
    for(int i=0; i < SIZE; i++) {
        if(user == MAP[SIZE-1-i][i]) {
            check++;
        }
    }

    if(check == SIZE) {
        return true;
    }

    return  checkHV(user,true) || checkHV(user,false);
}

std::string_view fromPlayer(Player player) {
    switch (player) {
        case Player::CIRCLE : return "O";
        case Player::CROSS: return "X";
        case Player::NONE: return "-";
        default: return "-";
    }
}

void displayArray() {
    //iterate on each case of the array
    for (int y = 0; y < MAP.size(); y++) {
        for (int x = 0; x < MAP[0].size(); x++) {
            std::cout << " " << fromPlayer(MAP[y][x]) << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * This method ask the user to check a case and then save it on the array
 * @param user the current user
 * @param isComputer if true the case is asked by the computer
 * @return false if an error occurred
 */
bool addACase(Player user) {
    std::cout << "User " << fromPlayer(user) << " give some coordinate (format:x,y):" << std::endl;
    
    // Ask user the coordinate of the case to check
    std::string caseToAdd;
    getline(std::cin, caseToAdd);

    //get single coordinate x or y
    std::string xString = caseToAdd.substr(0, caseToAdd.find(','));
    std::string yString = caseToAdd.substr(caseToAdd.find(',') + 1);

    // Convert the coordinate to map
    Player& askedCase  = MAP[std::stoi(yString)][std::stoi(xString)];
    //check if a player has halready use this position
    if (askedCase == Player::NONE) {
        askedCase = user;
        return true;
    }
    std::cout << "The case is already checked" << std::endl;
    return false;
}

int main() {

    Player currentUser = Player::CIRCLE;
    while (!(check(Player::CIRCLE) || check(Player::CROSS))) {
        bool isPassed = false;
        while (!isPassed) {
            isPassed = addACase(currentUser);
        }
        displayArray();
        currentUser = switchUser(currentUser);
    }

    if (check(Player::CIRCLE)) {
        std::cout << "Player " << fromPlayer(Player::CIRCLE) << " has won" << std::endl;
        return 0;
    }
    std::cout << "Player " << fromPlayer(Player::CROSS) << " has won" << std::endl;

}