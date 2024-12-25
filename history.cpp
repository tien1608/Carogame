#include "history.h"
#include <algorithm>

void History::save_game_history(const std::string& playerX_Name, const std::string& playerO_Name, const std::string& result, const std::vector<std::pair<int, int>>& moves){

    std::ifstream read_file("caro_game_history.csv");
    std::ofstream write_file("caro_game_history.csv", std::ios::app);

    // Kiểm tra nếu file mở thành công
    if (!read_file.is_open() || !write_file.is_open()) {
        std::cerr << "Cannot open file!" << std::endl;
        return;
    }

    // Nếu file trống, ghi tiêu đề vào
    read_file.seekg(0, std::ios::end);
    if (read_file.tellg() == 0) {
        write_file << "STT,Player_X Name,Player_O Name,Result,Time,InfoGame\n";
    }
    std::string movesInfo;
    for (const auto& move : moves) {
        movesInfo +=std::to_string(move.first) + " " + std::to_string(move.second) + " ";
    }

    // Đọc số dòng hiện tại để tính STT
    read_file.seekg(0, std::ios::beg);
    int stt = -1;
    std::string line;
    while (std::getline(read_file, line)) {
        ++stt;
    }

    // Lấy thời gian hiện tại
    std::time_t now = std::time(0);
    char time_str[20];
    std::strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    // Ghi thông tin ván đấu vào file CSV
    write_file << stt + 1 << ","
               << playerX_Name << ","
               << playerO_Name << ","
               << result << ","
               << time_str << ","
               << movesInfo<<"\n";
    // Đóng file
    read_file.close();
    write_file.close();
}

void History::display_game_history() {
    std::ifstream file("caro_game_history.csv");

    // Kiểm tra nếu file mở thành công
    if (!file.is_open()) {
        std::cerr << "Cannot open file!" << std::endl;
        return;
    }

    std::string line;
    if (std::getline(file, line)) {
        // Dòng đầu tiên đã được đọc nhưng không xử lý
    }

    // Đọc và hiển thị tiêu đề bảng
    std::cout << "+-----+---------------------+---------------------+--------------------+---------------------+" << std::endl;
    std::cout << "| STT | PlayerX Name        | PlayerY Name        | Result             | Time                |" << std::endl;
    std::cout << "+-----+---------------------+---------------------+--------------------+---------------------+" << std::endl;

    // Đọc và hiển thị từng dòng trong file
    while (std::getline(file, line)) {
        // Tách các trường thông tin bằng dấu ','
        std::stringstream ss(line);
        std::string stt, playerX, playerO, result, time;

        std::getline(ss, stt, ',');
        std::getline(ss, playerX, ',');
        std::getline(ss, playerO, ',');
        std::getline(ss, result, ',');
        std::getline(ss, time, ',');

        // Hiển thị thông tin trong bảng, căn chỉnh các cột cho hợp lý
        std::cout << "| "
                  << std::setw(3) << stt << " | "
                  << std::setw(19) << playerX << " | "
                  << std::setw(19) << playerO << " | "
                  << std::setw(18) << result << " | "
                  << std::setw(19) << time << " |" << std::endl;
    }

    std::cout << "+-----+---------------------+---------------------+--------------------+---------------------+" << std::endl;

    file.close();
}

void History::clear_game_history() {
    std::ofstream file("caro_game_history.csv");

    // Kiểm tra nếu file mở thành công
    if (!file.is_open()) {
        std::cerr << "Cannot open file!" << std::endl;
        return;
    }

    // Ghi tiêu đề lại vào file (xóa hết dữ liệu cũ)
    file << "STT,Player_X Name,Player_O Name,Result,Time,InfoGame\n";

    file.close();
}

void History::replay(int gameNumber) {
    std::ifstream file("caro_game_history.csv");

    if (!file.is_open()) {
        std::cerr << "Cannot open file for replaying game!" << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Bỏ qua dòng tiêu đề

    bool gameFound = false;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string stt, playerX, playerO, result, time, infoGame;

        std::getline(ss, stt, ',');
        std::getline(ss, playerX, ',');
        std::getline(ss, playerO, ',');
        std::getline(ss, result, ',');
        std::getline(ss, time, ',');
        std::getline(ss, infoGame, ',');

        if (std::stoi(stt) == gameNumber) {
            gameFound = true;
            std::cout << "Replaying game " << gameNumber << ":\n";
            std::cout << "Player X: " << playerX << "\n";
            std::cout << "Player O: " << playerO << "\n";
            std::cout << "Moves replay:\n";

            // Reset bàn cờ
            Board gameBoard;

            // Phân tích và thực hiện các nước đi
            std::stringstream moveStream(infoGame);
            int x, y;
            char currentSymbol = 'X';

            while (moveStream >> x >> y) {
                gameBoard.makeMove(x, y, currentSymbol);
                gameBoard.drawBoard();

                // Chuyển lượt
                currentSymbol = (currentSymbol == 'X') ? 'O' : 'X';
            }
            break;
        }
    }

    if (!gameFound) {
        std::cerr << "Game with number " << gameNumber << " not found!" << std::endl;
    }

    file.close();
}

void History::update_player_Info(const std::string& playerName1, const std::string& playerName2, int result) {
    std::string filename = "player_info.csv";
    std::ifstream file(filename);
    std::vector<Player> players;

    // Đọc dữ liệu hiện tại từ file vào vector
    if (file.is_open()) {
        std::string line;
        std::getline(file, line); // Bỏ qua dòng tiêu đề nếu có

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            Player player;
            std::string temp;

            std::getline(ss, temp, ','); // Tên người chơi
            player.setName(temp);

            std::getline(ss, temp, ','); // Tổng số trận
            player.setTotalmatches(std::stoi(temp));

            std::getline(ss, temp, ','); // Số trận thắng
            player.setNumofWins(std::stoi(temp));

            std::getline(ss, temp, ','); // Số trận thua
            player.setNumofLosses(std::stoi(temp));

            std::getline(ss, temp, ','); // Số trận hòa
            player.setNumofDraws(std::stoi(temp));

            players.push_back(player);
        }

        file.close();
    }

    auto updateOrAddPlayer = [&](const std::string& playerName, int matchResult) {
        auto it = std::find_if(players.begin(), players.end(), [&](const Player& p) {
            return p.getName() == playerName;
        });

        if (it != players.end()) {
            // Cập nhật người chơi nếu đã tồn tại
            it->setTotalmatches(it->getTotalMatches() + 1);
            if (matchResult == 1) {
                it->setNumofWins(it->getNumOfWins() + 1);
            } else if (matchResult == -1) {
                it->setNumofLosses(it->getNumofLosses() + 1);
            } else if (matchResult == 0) {
                it->setNumofDraws(it->getNumofDraws() + 1);
            }
        } else {
            // Thêm mới người chơi nếu chưa tồn tại
            Player newPlayer;
            newPlayer.setName(playerName);
            newPlayer.setTotalmatches(1);
            if (matchResult == 1) {
                newPlayer.setNumofWins(1);
            } else if (matchResult == -1) {
                newPlayer.setNumofLosses(1);
            } else if (matchResult == 0) {
                newPlayer.setNumofDraws(1);
            }
            players.push_back(newPlayer);
        }
    };

    // Cập nhật hoặc thêm mới hai người chơi
    updateOrAddPlayer(playerName1, result == 1 ? 1 : (result == -1 ? -1 : 0));
    updateOrAddPlayer(playerName2, result == -1 ? 1 : (result == 1 ? -1 : 0));

    // Ghi dữ liệu đã cập nhật vào file
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Cannot open file to save player info!" << std::endl;
        return;
    }

    outFile << "Player Name,Total Matches,Num of Wins,Num of Losses,Num of Draws,Win Rate\n";
    for (const auto& player : players) {
        double winRate = player.getTotalMatches() > 0
                         ? static_cast<double>(player.getNumOfWins()) / player.getTotalMatches() * 100
                         : 0.0;
        outFile << player.getName() << ","
                << player.getTotalMatches() << ","
                << player.getNumOfWins() << ","
                << player.getNumofLosses() << ","
                << player.getNumofDraws() << ","
                << std::fixed << std::setprecision(2) << winRate << "%\n";
    }

    outFile.close();
}

void History::PrintPlayerInfo() {
    std::string filename = "player_info.csv";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);// bỏ qua tiêu đề
    std::cout << std::string(90, '-') << std::endl;

    std::cout << std::setw(20) << std::left << "Player Name"
              << std::setw(15) << "Total Matches"
              << std::setw(15) << "Num of Wins"
              << std::setw(15) << "Num of Losses"
              << std::setw(15) << "Num of Draws"
              << "Win Rate" << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    while (std::getline(file, line)) {

        std::stringstream ss(line);
        std::string playerName, totalMatches, numWins, numLosses, numDraws, winRate;

        std::getline(ss, playerName, ',');
        std::getline(ss, totalMatches, ',');
        std::getline(ss, numWins, ',');
        std::getline(ss, numLosses, ',');
        std::getline(ss, numDraws, ',');
        std::getline(ss, winRate, ',');

        std::cout << std::setw(20) << std::left << playerName
                  << std::setw(15) << totalMatches
                  << std::setw(15) << numWins
                  << std::setw(15) << numLosses
                  << std::setw(15) << numDraws
                  << winRate << std::endl;
        std::cout << std::string(90, '-') << std::endl;
    }

    file.close();
}

void History::searchPlayerByName(const std::string& Name){
    std::string filename = "player_info.csv";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);// bỏ qua tiêu đề

    bool playerFound = false;
    while (std::getline(file, line)) {

        std::stringstream ss(line);
        std::string playerName, totalMatches, numWins, numLosses, numDraws, winRateStr;

        std::getline(ss, playerName, ',');
        std::getline(ss, totalMatches, ',');
        std::getline(ss, numWins, ',');
        std::getline(ss, numLosses, ',');
        std::getline(ss, numDraws, ',');
        std::getline(ss, winRateStr, ',');

        if (playerName == Name) {
            std::cout << std::string(90, '-') << std::endl;
            // In thông tin người chơi
            std::cout << std::setw(20) << std::left << "Player Name"
                      << std::setw(15) << "Total Matches"
                      << std::setw(15) << "Num of Wins"
                      << std::setw(15) << "Num of Losses"
                      << std::setw(15) << "Num of Draws"
                      << "Win Rate" << std::endl;
            std::cout << std::string(90, '-') << std::endl;

            std::cout << std::setw(20) << std::left << playerName
                      << std::setw(15) << totalMatches
                      << std::setw(15) << numWins
                      << std::setw(15) << numLosses
                      << std::setw(15) << numDraws
                      << winRateStr << std::endl;
            std::cout << std::string(90, '-') << std::endl;

            double winRate = std::stod(winRateStr.substr(0, winRateStr.find('%')));
            std::cout<<"players of the same level:\n";
            searchPlayersByWinRate(winRate);

            playerFound = true;
            break;
        }
    }

    if (!playerFound) {
        std::cout << "Player with name \"" << Name << "\" not found in the database." << std::endl;
    }

    file.close();
}
void History::searchPlayersByWinRate(double winrate){
    std::string filename = "player_info.csv";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);// bỏ qua tiêu đề

    std::vector<std::string> matchingPlayers;

    double lowerBound = winrate - 10;
    double upperBound = winrate + 10;

    while (std::getline(file, line)) {

        std::stringstream ss(line);
        std::string playerName, totalMatches, numWins, numLosses, numDraws, winRateStr;

        std::getline(ss, playerName, ',');
        std::getline(ss, totalMatches, ',');
        std::getline(ss, numWins, ',');
        std::getline(ss, numLosses, ',');
        std::getline(ss, numDraws, ',');
        std::getline(ss, winRateStr, ',');

        // Loại bỏ ký tự '%' từ chuỗi tỷ lệ thắng và chuyển thành số
        double winRate = std::stod(winRateStr.substr(0, winRateStr.find('%')));

        // Kiểm tra tỷ lệ thắng có nằm trong khoảng không
        if (winRate >= lowerBound && winRate <= upperBound) {
            matchingPlayers.push_back(line);
        }
    }

    file.close();

    if (matchingPlayers.empty()) {
        std::cout << "No players found with win rate in the range ["
                  << lowerBound << ", " << upperBound << "]." << std::endl;
        return;
    }

    // In tiêu đề
    std::cout << std::string(90, '-') << std::endl;
    std::cout << std::setw(20) << std::left << "Player Name"
              << std::setw(15) << "Total Matches"
              << std::setw(15) << "Num of Wins"
              << std::setw(15) << "Num of Losses"
              << std::setw(15) << "Num of Draws"
              << "Win Rate" << std::endl;
    std::cout << std::string(90, '-') << std::endl;

    // In thông tin người chơi
    for (const auto& player : matchingPlayers) {
        std::stringstream ss(player);
        std::string playerName, totalMatches, numWins, numLosses, numDraws, winRate;

        std::getline(ss, playerName, ',');
        std::getline(ss, totalMatches, ',');
        std::getline(ss, numWins, ',');
        std::getline(ss, numLosses, ',');
        std::getline(ss, numDraws, ',');
        std::getline(ss, winRate, ',');

        std::cout << std::setw(20) << std::left << playerName
                  << std::setw(15) << totalMatches
                  << std::setw(15) << numWins
                  << std::setw(15) << numLosses
                  << std::setw(15) << numDraws
                  << winRate << std::endl;
        std::cout << std::string(90, '-') << std::endl;
    }
}
