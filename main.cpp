/**
 * TicTacToe
 * Antoine Leresche
 * 04.10.2022
*/

#include <iostream>
#include <array>
#include <string>
#include <exception>


// Enumeration of all the players
enum class Player {CROSS, CIRCLE, NONE};

// Size and map type
const int SIZE = 3;
using game_map = std::array<std::array<Player, SIZE>, SIZE>;

/**
 * Switch between user CROSS and CIRCLE
 * @param user user to change
*/
Player switchUser(Player user) {
    if(user == Player::CIRCLE){
        return Player::CROSS;
    }
    return Player::CIRCLE;
}

/**
 * Check if a user has won but only in vertical or horizontal
 * @param hOrV true the check is horizontal, false for vertical
 * @return true if the choosed user has won
*/
bool checkHV(const game_map& map,Player user,bool hOrV) {
 
    for(int y=0; y < SIZE; y++) {
        int check = 0;
        for(int x=0; x < SIZE; x++) {
            // Get current value according to vertical or horizontal
            Player player = hOrV ? map[x][y] : map[y][x];
        
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
 * Check if a user won
 * @param player to be checked
 * @return the player 
*/
bool hasWon(const game_map& map, Player user) {
    int check = 0;
    // First diagonal
    for(int i=0; i < SIZE; i++) {
        if(user == map[i][i]) {
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
        if(user == map[SIZE-1-i][i]) {
            check++;
        }
    }

    if(check == SIZE) {
        return true;
    }

    return  checkHV(map,user,true) || checkHV(map,user,false);
}

/**
 * Get a string from a user
 * @param player 
*/
std::string_view fromPlayer(Player player) {
    switch (player) {
        case Player::CIRCLE : return "O";
        case Player::CROSS: return "X";
        case Player::NONE: return "-";
        default: return "-";
    }
}

/**
 * Dislay array 
 * @param Game array to display
*/
void displayArray(const game_map& array) {
    //iterate on each case of the array
    for (int y = 0; y < array.size(); y++) {
        for (int x = 0; x < array[0].size(); x++) {
            std::cout << " " << fromPlayer(array[y][x]) << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * This method ask the user to check a case and then save it on the array
 * @param user the current user
 * @param isComputer if true the case is asked by the computer
 * @return true if the choice is wrong
 */
bool wrongChoice(game_map& map, Player user) {
    std::cout << "User " << fromPlayer(user) << " give some coordinate (format:x,y):" << std::endl;
    
    // Ask user the coordinate of the case to check
    std::string caseToAdd;
    std::cin >> caseToAdd;

    // Get single coordinate x or y
    std::string xString = caseToAdd.substr(0, caseToAdd.find(','));
    std::string yString = caseToAdd.substr(caseToAdd.find(',') + 1);


    // Convert the coordinate to map
    try{
        Player& askedCase  = map.at(std::stoi(yString)).at(std::stoi(xString));
        // Check if a player is already on this case
        if (askedCase == Player::NONE) {
            askedCase = user;
            return false;
        }
    } catch(std::exception &ex) {
        std::cout << "Array out of bound" << std::endl;
    }

    return true;
}

int main() {

    game_map map = {{{Player::NONE, Player::NONE, Player::NONE},   
                    {Player::NONE, Player::NONE, Player::NONE},
                    {Player::NONE, Player::NONE, Player::NONE}}};

    
    Player currentUser = Player::CIRCLE;
    do{
        currentUser = switchUser(currentUser);
        while (wrongChoice(map, currentUser)) {
          std::cout << "Wrong entry - try again" << std::endl;
        }
        displayArray(map);
    }while(!hasWon(map, currentUser));

    std::cout << "Player " << fromPlayer(currentUser) << " has won" << std::endl;

}