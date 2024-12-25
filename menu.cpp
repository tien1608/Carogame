#include "menu.h"
#include "board.h"
#include "player.h"
#include "bot.h"
#include "history.h"
#include <iostream>
#include <limits>

void verifyInput(int *p){
    while (true) {
            std::cin >> *(p);

            // Nếu nhập sai (chuỗi, ký tự, hoặc số không hợp lệ)
            if (std::cin.fail()) {
                std::cin.clear(); // Xóa cờ lỗi
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Bỏ qua đầu vào không hợp lệ
                std::cout<<"Invalid choice. Try again!\n";
            } else {
                break; // Nhập hợp lệ
            }
        }
}

void Menu::showMainMenu() {
    std::cout << "\n//-------- MAIN MENU --------//\n";
    std::cout << "1. Play with Other Player\n";
    std::cout << "2. Play with BOT\n";
    std::cout << "3. Replay\n";
    std::cout << "4. Player's Information\n";
    std::cout << "5. Exit\n";
    std::cout << "Press number to choose: ";
}

void Menu::playingGame(){
    int choice;

    while (true) {
        showMainMenu();
        verifyInput(&choice);

        switch (choice) {
            case 1: playWithPlayer(); break;
            case 2: playWithBot(); break;
            case 3: replayGame(); break;
            case 4: showPlayerInfo(); break;
            case 5: std::cout << "Exiting...\n"; return;
            default: std::cout << "Invalid choice. Try again!\n";
        }
    }
}

void Menu::playWithPlayer(){
    History histoty;
    std::vector<std::pair<int,int>> moves;
    std::cout << "Starting game with another player...\n";
    Board gameBoard;
    std::string player1Name, player2Name;
    // Nhập tên 2 người chơi
    std::cout << "Enter Player 1's name: ";
    std::cin >> player1Name;
    std::cout << "Enter Player 2's name: ";
    std::cin >> player2Name;

    Player player1(player1Name, 'X');
    Player player2(player2Name, 'O');
    Player* currentPlayer = &player1;
    int x,y;
    while(true){
        gameBoard.drawBoard();
        std::cout << currentPlayer->getName() << "'s turn " << currentPlayer->getSymbol() << " (row column): ";
        verifyInput(&x);
        verifyInput(&y);
        //check nuoc di hop le
        if(gameBoard.checkMove(x,y)){
                gameBoard.makeMove(x,y,currentPlayer->getSymbol());
                moves.push_back({x,y});
                //checkwin
            if(gameBoard.checkWin(x,y,currentPlayer->getSymbol())){
                gameBoard.drawBoard();
                std::cout << currentPlayer->getName() << " wins!\n";
                delete currentPlayer;
                histoty.save_game_history(player1.getName(),player2.getName(),currentPlayer->getName() + " Wins!", moves);
                if(currentPlayer->getName() == player1.getName()){
                    histoty.update_player_Info(player1.getName(),player2.getName(),1);
                }
                else {
                    histoty.update_player_Info(player1.getName(),player2.getName(),-1);
                }
                break;
            }
            //check ban co full
            if(gameBoard.checkFull()){
            std::cout << "It's a draw!\n";
            delete currentPlayer;
            histoty.save_game_history(player1.getName(),player2.getName(),"Draw!",moves);
            histoty.update_player_Info(player1.getName(),player2.getName(),0);
            break;
        }
        //chuyen luot
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
        }
        else {
            std::cout << "Invalid move! Try again.\n";
        }
    }

}


void Menu::replayGame(){
    History history;
    std::cout<<"Replay games...\n";
    history.display_game_history();
    std::cout<<"Select game to replay: ";
    int choice;
    verifyInput(&choice);
    history.replay(choice);
}
void Menu::showPlayerInfo(){
    std::cout<<"Players Infomation: \n";
    std::cout<<"\n";
    History history;
    history.PrintPlayerInfo();
    int choice;

    while (true) {
        std::cout<<"\n";
        std::cout<<"1. Search player by name.\n";
        std::cout<<"2. Search player by winrate.\n";
        std::cout<<"3. Return main\n";
        std::cout << "Press number to choose: ";
        verifyInput(&choice);

        switch (choice) {
            case 1:
                {
                    std::string name;
                    std::cout<<"Enter player name: ";
                    std::cin>> name;
                    std::cout<<std::endl;
                    std::cout<<"Infomation of player: "<<name<<std::endl;
                    history.searchPlayerByName(name);
                    break;
                }
            case 2:
                {
                    double winrate;
                    std::cout<<"Enter winrate: ";
                    std::cin>>winrate;
                    std::cout<<std::endl;
                    std::cout<<"Players with a win rate close to "<<winrate<<"% are: "<<std::endl;
                    history.searchPlayersByWinRate(winrate);
                    break;
                }

            case 3: return;
            default: std::cout << "Invalid choice. Try again!\n";
        }
    }

}

void Menu::playWithBot() {
    int choice;
    Bot *bot;
    while (true) {
        std::cout << "\n//-------- Play with BOT --------//\n";
        std::cout << "1. Easy Mode\n";
        std::cout << "2. Normal Mode\n";
        std::cout << "3. Hard Mode\n";
        std::cout << "4. Back to MAIN MENU\n";
        std::cout << "Press number to choose: ";
        verifyInput(&choice);

        if(choice >4|| choice <1){
            std::cout<<"Invalid choice. Try again!\n";
            continue;
        }
        else if (choice == 4){
            return;
        }
        else if(choice == 1){
            bot = new easyBot();
            break;
        }
        else if(choice == 2){
            bot = new normalBot();
            break;
        }
        else if(choice == 3){
            bot = new hardBot();
            break;
        }
    }
    char botsymbol, playersymbol;
    while(true){
        std::cout<<"1. player goes first (X)\n";
        std::cout<<"2. Bot goes first (X)\n";
        std::cout << "Press number to choose: ";
        verifyInput(&choice);
        if(choice == 1){
            botsymbol = 'O';
            playersymbol = 'X';
            break;
        }
        else if(choice == 2){
            botsymbol = 'X';
            playersymbol = 'O';
            break;
        }
        else{
            std::cout<<"Invalid choice. Try again!\n";
            continue;
        }
    }
    Board gameBoard;
    Player player("Player", playersymbol);
    Player* currentPlayer = &player;
    int x, y;
    int _count = 0;
    while (true) {
    gameBoard.drawBoard();
        if(_count == 0&&botsymbol=='X'){
                gameBoard.makeMove(5,5,botsymbol);
                gameBoard.drawBoard();
                _count++;
                std::cout << "Bot played at: " << 5 << " " << 5 << "\n";
            }
        if (currentPlayer == &player) {
            std::cout << player.getName() << "'s turn " << player.getSymbol() << " (row column): ";
            verifyInput(&x);
            verifyInput(&y);

            if (gameBoard.checkMove(x, y)) {
                    gameBoard.makeMove(x,y,player.getSymbol());
                if (gameBoard.checkWin(x, y, player.getSymbol())) {
                    gameBoard.drawBoard();
                    std::cout << player.getName() << " wins!\n";
                    delete bot;
                    delete currentPlayer;
                    break;
                }

                if (gameBoard.checkFull()) {
                    std::cout << "It's a draw!\n";
                    delete bot;
                    delete currentPlayer;
                    break;
                }

                currentPlayer = nullptr; // Đổi lượt sang bot
            } else {
                std::cout << "Invalid move! Try again.\n";
            }
        } else {
            std::pair<int, int> bestMove = bot->getBestMove(gameBoard,botsymbol,playersymbol);
            gameBoard.drawBoard();
            gameBoard.makeMove(bestMove.first, bestMove.second, botsymbol);
            std::cout << "Bot played at: " << bestMove.first << " " << bestMove.second << "\n";

            if (gameBoard.checkWin(bestMove.first, bestMove.second, botsymbol)) {
                gameBoard.drawBoard();
                std::cout << "Bot wins!\n";
                delete bot;
                delete currentPlayer;
                break;
            }

            if (gameBoard.checkFull()) {
                std::cout << "It's a draw!\n";
                delete bot;
                delete currentPlayer;
                break;
            }
            currentPlayer = &player; // Đổi lượt sang người chơi
        }
    }
}



