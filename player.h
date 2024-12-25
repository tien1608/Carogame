#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <string>
#include <vector>

class Player {
private:
    std::string name; // Tên người chơi
    char symbol; // Ký hiệu của người chơi (X hoặc O)
    int totalMatches;    //tổng số trận
    int NumOfWins; // số trận thắng
    int NumOfLosses;
    int NumofDraws;
public:
    // Constructor
    Player(const std::string& playerName, char playerSymbol);

    Player();

    // Getter: Lấy tên người chơi
    std::string getName() const;

    // Getter: Lấy ký hiệu của người chơi
    char getSymbol() const;

    // Setter: Cập nhật tên người chơi
    void setName(const std::string& playerName);

    // Setter: Cập nhật ký hiệu của người chơi
    void setSymbol(char playerSymbol);

    void setNumofWins(int x);

    void setNumofLosses(int x);

    void setNumofDraws(int x);

    void setTotalmatches(int x);

    int getTotalMatches() const;

    int getNumOfWins() const;

    int getNumofLosses() const;

    int getNumofDraws() const;
};

#endif // PLAYER_H_INCLUDED
