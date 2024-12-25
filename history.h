#ifndef HISTORY_H_INCLUDED
#define HISTORY_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include <utility>
#include "player.h"
#include "board.h"

class History{
    public:
    void save_game_history(const std::string& playerX_Name, const std::string& playerO_Name, const std::string& result, const std::vector<std::pair<int, int>>& moves);
    void display_game_history();
    void clear_game_history();
    void replay(int gameNumber);
    void update_player_Info(const std::string& playerName1, const std::string& playerName2, int result);
    void PrintPlayerInfo();
    void searchPlayerByName(const std::string& Name);
    void searchPlayersByWinRate(double winrate);
};

#endif // HISTORY_H_INCLUDED
