#include "board.h"

// Constructor để khởi tạo bàn cờ
// Hàm khởi tạo bàn cờ
Board::Board() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = ' '; // Gán ô trống ban đầu
        }
    }
}

// Hàm vẽ và hiển thị bàn cờ
void Board::drawBoard() {
    std::cout << "   ";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << i << " "; // In chỉ số cột
    }
    std::cout << "\n";

    for (int i = 0; i < SIZE; ++i) {
        std::cout << i << " "; // In chỉ số hàng
        for (int j = 0; j < SIZE; ++j) {
            std::cout << "|";
            std::cout << board[i][j];
        }
        std::cout << "|\n";

        // In đường kẻ ngang giữa các hàng
        std::cout << "  ";
        for (int j = 0; j < SIZE; ++j) {
            std::cout << "--";
        }
        std::cout << "-\n";
    }
}

// Hàm kiểm tra vị trí có hợp lệ không
bool Board::checkMove(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        return false; // Vị trí ngoài bàn cờ
    }
    if (board[x][y] != ' ') {
        return false; // Vị trí đã có quân cờ
    }
    return true;
}

// Hàm thực hiện di chuyển
bool Board::makeMove(int x, int y, char player) {
    if (checkMove(x, y)) {
        board[x][y] = player;
        return true;
    }
    return false;
}

// Hàm kiểm tra người chơi có thắng không
bool Board::checkWin(int x, int y, char player) {
    // Kiểm tra theo hướng ngang
    int count = 0;
    for (int i = y - 4; i <= y + 4; i++) {
        if (i >= 0 && i < SIZE && board[x][i] == player) {
            count++;
            if (count == 5) return true;
        } else {
            count = 0;
        }
    }

    // Kiểm tra theo hướng dọc
    count = 0;
    for (int i = x - 4; i <= x + 4; i++) {
        if (i >= 0 && i < SIZE && board[i][y] == player) {
            count++;
            if (count == 5) return true;
        } else {
            count = 0;
        }
    }

    // Kiểm tra theo hướng chéo (xuôi)
    count = 0;
    for (int i = -4; i <= 4; i++) {
        int nx = x + i;
        int ny = y + i;
        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == player) {
            count++;
            if (count == 5) return true;
        } else {
            count = 0;
        }
    }

    // Kiểm tra theo hướng chéo (ngược)
    count = 0;
    for (int i = -4; i <= 4; i++) {
        int nx = x + i;
        int ny = y - i;
        if (nx >= 0 && nx < SIZE && ny >= 0 && ny < SIZE && board[nx][ny] == player) {
            count++;
            if (count == 5) return true;
        } else {
            count = 0;
        }
    }

    return false;
}

// Hàm kiểm tra bàn cờ có đầy không
bool Board::checkFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return false; // Vẫn còn ô trống
            }
        }
    }
    return true; // Bàn cờ đầy
}
char Board::getValue(int x, int y){
    return board[x][y];
}
