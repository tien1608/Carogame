#include "player.h"

// Constructor: Khởi tạo người chơi
Player::Player(const std::string& playerName, char playerSymbol)
    : name(playerName), symbol(playerSymbol) {}
Player::Player(){
    totalMatches = 0;
    NumofDraws = 0;
    NumOfLosses = 0;
    NumOfWins = 0;
}

// Lấy tên người chơi
std::string Player::getName() const {
    return name;
}

// Lấy ký hiệu của người chơi
char Player::getSymbol() const {
    return symbol;
}

// Cập nhật tên người chơi
void Player::setName(const std::string& playerName) {
    name = playerName;
}

// Cập nhật ký hiệu của người chơi
void Player::setSymbol(char playerSymbol) {
    symbol = playerSymbol;
}

void Player::setNumofWins(int x){
    NumOfWins = x;
}
void Player::setNumofLosses(int x){
    NumOfLosses = x;
}
void Player::setNumofDraws(int x){
    NumofDraws = x;
}
void Player::setTotalmatches(int x){
    totalMatches = x;
}

int Player::getTotalMatches() const {
    return totalMatches;
}
int Player::getNumOfWins() const {
    return NumOfWins;
}
int Player::getNumofLosses() const {
    return NumOfLosses;
}
int Player::getNumofDraws() const {
    return NumofDraws;
}
