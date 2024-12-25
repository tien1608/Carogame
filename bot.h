#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

#include <utility>
#include "board.h"


class Bot {
protected:
    const int atk[7] = { 0, 2, 64, 4096, 262144, 16777216, 1073741824 };
    const int def[7] = { 0, 1, 8, 512, 32768, 2097152, 134217728 };
public:
    virtual ~Bot();
    long Row_Atk_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy);

    long Col_Atk_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy);

    long Main_Diagonal_Atk_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy);

    long Second_Diagonal_Atk_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy);

    long Row_Def_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy);

    long Col_Def_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy);

    long Main_Diagonal_Def_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy);

    long Second_Diagonal_Def_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy);

    virtual long evaluateMove(Board &board, int x, int y, const char ally, const char enemy) = 0;

    virtual std::pair <int,int> getBestMove(Board &board,const char ally, const char enemy) = 0;
};

class normalBot : public Bot{
public:
    ~normalBot() override;
    long evaluateMove(Board &board, int x, int y, const char ally, const char enemy) override;
    std::pair <int,int> getBestMove(Board &board, const char ally, const char enemy) override;
};

class easyBot: public Bot{
public:
    ~easyBot() override;
    long evaluateMove(Board &board, int x, int y, const char ally, const char enemy) override;
    std::pair <int,int> getBestMove(Board &board, const char ally, const char enemy) override;
};

class hardBot: public Bot{
public:
    ~hardBot() override;
    long evaluateMove(Board &board, int x, int y, const char ally, const char enemy) override;
    std::pair <int,int> getBestMove(Board &board, const char ally, const char enemy) override;
};

#endif // BOT_H_INCLUDED


