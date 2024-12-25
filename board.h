#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <iostream>

const int SIZE = 10; // Kích thước bàn cờ (15x15)

class Board {
private:
    char board[SIZE][SIZE]; // Mảng 2D lưu trữ bàn cờ

public:
    // Constructor để khởi tạo bàn cờ
    Board();

    // Hàm vẽ bàn cờ
    void drawBoard();

    // Hàm kiểm tra vị trí có hợp lệ không
    bool checkMove(int x, int y);

    // Hàm thực hiện di chuyển
    bool makeMove(int x, int y, char player);

    // Hàm kiểm tra người chơi có thắng không
    bool checkWin(int x, int y, char player);

    char getValue(int x, int y);

    // Hàm kiểm tra bàn cờ có đầy không
    bool checkFull();
};

#endif // BOARD_H_INCLUDED
