#include "bot.h"

Bot::~Bot(){}
easyBot::~easyBot(){}
normalBot::~normalBot(){}
hardBot::~hardBot(){}

long Bot::Row_Atk_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy){
    long RowScore = 0;
    int count_O = 0, count_X = 0, count_O2 = 0, count_X2 = 0;
    for(int i = 1; i < 6 && y +i <SIZE; i++){
        if(board.getValue(x,y+i) == ally) count_O++;
        else if(board.getValue(x,y+i) == enemy){
            count_X++;
            break;
        }
        else {
            for(int i = 2; i<7 && y+i<SIZE;i++){
                if(board.getValue(x,y+i) == ally) count_O2++;
                else if(board.getValue(x,y+i) == enemy){
                    count_X2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    for(int i = 1; i<6 && y-i>=0;i++){
        if(board.getValue(x,y-i) == ally) count_O++;
        else if(board.getValue(x,y-i) == enemy){
            count_X++;
            break;
        }
        else {
            for(int i = 2; i<7 && y-i>=0;i++){
                if(board.getValue(x,y-i) == ally) count_O2++;
                else if(board.getValue(x,y-i) == enemy){
                    count_X2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    RowScore +=(count_X == 0) ? (Bot::atk[count_O] * 2) : Bot::atk[count_O];
    RowScore += (count_X2 == 0) ? (Bot::atk[count_O2] *2) : Bot::atk[count_O2];
    RowScore +=(count_O == 0) ? (Bot::def[count_X] *2 ) : Bot::def[count_X];
    RowScore +=(count_O2 == 0) ? (Bot::def[count_X2] *2) : Bot::def[count_X2];
    if (count_O == 4) RowScore *=2;
    return RowScore;
}

long Bot::Col_Atk_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy){
    long ColScore = 0;
    int count_O = 0, count_X = 0, count_O2 = 0, count_X2 = 0;
    for(int i = 1; i < 6 && x +i <SIZE; i++){
        if(board.getValue(x+i,y) == ally) count_O++;
        else if(board.getValue(x+i,y) == enemy){
            count_X++;
            break;
        }
        else {
            for(int i = 2; i<7 && x+i<SIZE;i++){
                if(board.getValue(x+i,y) == ally) count_O2++;
                else if(board.getValue(x+i,y) == enemy){
                    count_X2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    for(int i = 1; i<6 && x-i>=0;i++){
        if(board.getValue(x-i,y) == ally) count_O++;
        else if(board.getValue(x-i,y) == enemy){
            count_X++;
            break;
        }
        else {
            for(int i = 2; i<7 && x-i>=0;i++){
                if(board.getValue(x-i,y) == ally) count_O2++;
                else if(board.getValue(x-i,y) == enemy){
                    count_X2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    ColScore +=(count_X == 0) ? (Bot::atk[count_O] * 2) : Bot::atk[count_O];
    ColScore += (count_X2 == 0) ? (Bot::atk[count_O2] *2) : Bot::atk[count_O2];
    ColScore +=(count_O == 0) ? (Bot::def[count_X] *2) : Bot::def[count_X];
    ColScore +=(count_O2 == 0) ? (Bot::def[count_X2] *2 ) : Bot::def[count_X2];
    if (count_O == 4) ColScore *=2;
    return ColScore;
}
long Bot::Main_Diagonal_Atk_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy){
    long Main_DiagonalScore = 0;
    int count_O = 0, count_X = 0, count_O2 = 0, count_X2 = 0;
    for(int i = 1; i < 6 && x +i <SIZE && y +i < SIZE; i++){
        if(board.getValue(x+i,y+i) == ally) count_O++;
        else if(board.getValue(x+i,y+i) == enemy){
            count_X++;
            break;
        }
        else {
            for(int i = 2; i<7 && x+i<SIZE && y+i < SIZE;i++){
                if(board.getValue(x+i,y+i) == ally) count_O2++;
                else if(board.getValue(x+i,y+i) == enemy){
                    count_X2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    for(int i = 1; i<6 && x-i>=0 && y-i >=0;i++){
        if(board.getValue(x-i,y-i) == ally) count_O++;
        else if(board.getValue(x-i,y-i) == enemy){
            count_X++;
            break;
        }
        else {
            for(int i = 2; i<7 && x-i>=0 && y-i >=0;i++){
                if(board.getValue(x-i,y-i) == ally) count_O2++;
                else if(board.getValue(x-i,y-i) == enemy){
                    count_X2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    Main_DiagonalScore +=(count_X == 0) ? (Bot::atk[count_O] * 2) : Bot::atk[count_O];
    Main_DiagonalScore += (count_X2 == 0) ? (Bot::atk[count_O2] *2) : Bot::atk[count_O2];
    Main_DiagonalScore +=(count_O == 0) ? (Bot::def[count_X] *2) : Bot::def[count_X];
    Main_DiagonalScore +=(count_O2 == 0) ? (Bot::def[count_X2] *2 ) : Bot::def[count_X2];
    if (count_O == 4) Main_DiagonalScore *=2;
    return Main_DiagonalScore;
}
long Bot::Second_Diagonal_Atk_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy){
    long Second_DiagonalScore = 0;
    int count_O = 0, count_X = 0, count_O2 = 0, count_X2 = 0;
    for(int i = 1; i < 6 && x +i <SIZE && y-i >=0; i++){
        if(board.getValue(x+i,y-i) == ally) count_O++;
        else if(board.getValue(x+i,y-i) == enemy){
            count_X++;
            break;
        }
        else {
            for(int i = 2; i < 7 && x +i <SIZE && y-i >=0;i++){
                if(board.getValue(x+i,y-i) == ally) count_O2++;
                else if(board.getValue(x+i,y-i) == enemy){
                    count_X2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    for(int i = 1; i<6 && x-i>=0 &&y+i<SIZE;i++){
        if(board.getValue(x-i,y+i) == ally) count_O++;
        else if(board.getValue(x-i,y+i) == enemy){
            count_X++;
            break;
        }
        else {
            for(int i = 2;i<7 && x-i>=0 &&y+i<SIZE;i++){
                if(board.getValue(x-i,y+i) == ally) count_O2++;
                else if(board.getValue(x-i,y+i) == enemy){
                    count_X2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    Second_DiagonalScore +=(count_X == 0) ? (Bot::atk[count_O] * 2) : Bot::atk[count_O];
    Second_DiagonalScore += (count_X2 == 0) ? (Bot::atk[count_O2] *2) : Bot::atk[count_O2];
    Second_DiagonalScore +=(count_O == 0) ? (Bot::def[count_X] *2) : Bot::def[count_X];
    Second_DiagonalScore +=(count_O2 == 0) ? (Bot::def[count_X2] *2) : Bot::def[count_X2];
    if (count_O == 4) Second_DiagonalScore *=2;
    return Second_DiagonalScore;
}

long Bot::Row_Def_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy){
    long score = 0;
    int count_O = 0, count_X = 0, count_O2 = 0, count_X2 = 0;
    for(int i = 1; i < 6 && y +i <SIZE; i++){
        if(board.getValue(x,y+i) == enemy) count_X++;
        else if(board.getValue(x,y+i) == ally){
            count_O++;
            break;
        }
        else {
            for(int i = 2; i<7 && y+i<SIZE;i++){
                if(board.getValue(x,y+i) == enemy) count_X2++;
                else if(board.getValue(x,y+i) == ally){
                    count_O2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    for(int i = 1; i < 6 && y -i >=0; i++){
        if(board.getValue(x,y-i) == enemy) count_X++;
        else if(board.getValue(x,y-i) == ally){
            count_O++;
            break;
        }
        else {
            for(int i = 2; i<7 && y-i>=0;i++){
                if(board.getValue(x,y-i) == enemy) count_X2++;
                else if(board.getValue(x,y-i) == ally){
                    count_O2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    score += (count_O == 0) ? (Bot::def[count_X] * 2) : Bot::def[count_X];
	score += (count_O2 == 0) ? (Bot::def[count_X2] * 2 ) : Bot::def[count_X2];
	if(count_X == 4) score *=2;
	return score;
}

long Bot::Col_Def_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy){
    long score = 0;
    int count_O = 0, count_X = 0, count_O2 = 0, count_X2 = 0;
    for(int i = 1; i < 6 && x +i <SIZE; i++){
        if(board.getValue(x+i,y) == enemy) count_X++;
        else if(board.getValue(x+i,y) == ally){
            count_O++;
            break;
        }
        else {
            for(int i = 2; i<7 && x+i<SIZE;i++){
                if(board.getValue(x+i,y) == enemy) count_X2++;
                else if(board.getValue(x+i,y) == ally){
                    count_O2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    for(int i = 1; i < 6 && x -i >=0; i++){
        if(board.getValue(x-i,y) == enemy) count_X++;
        else if(board.getValue(x-i,y) == ally){
            count_O++;
            break;
        }
        else {
            for(int i = 2; i<7 && x-i>=0;i++){
                if(board.getValue(x-i,y) == enemy) count_X2++;
                else if(board.getValue(x-i,y) == ally){
                    count_O2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    score += (count_O == 0) ? (Bot::def[count_X] * 2) : Bot::def[count_X];
	score += (count_O2 == 0) ? (Bot::def[count_X2] * 2 ) : Bot::def[count_X2];
	if(count_X == 4) score *=2;
	return score;
}
long Bot::Main_Diagonal_Def_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy){
    long score = 0;
    int count_O = 0, count_X = 0, count_O2 = 0, count_X2 = 0;
    for(int i = 1; i < 6 && x +i <SIZE&& y+i <SIZE; i++){
        if(board.getValue(x+i,y+i) == enemy) count_X++;
        else if(board.getValue(x+i,y+i) == ally){
            count_O++;
            break;
        }
        else {
            for(int i = 2; i<7 && x +i <SIZE&& y+i <SIZE;i++){
                if(board.getValue(x+i,y+i) == enemy) count_X2++;
                else if(board.getValue(x+i,y+i) == ally){
                    count_O2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    for(int i = 1; i < 6 && x -i >=0 && y-i >=0; i++){
        if(board.getValue(x-i,y-i) == enemy) count_X++;
        else if(board.getValue(x-i,y-i) == ally){
            count_O++;
            break;
        }
        else {
            for(int i = 2; i<7 && x -i >=0 && y-i >=0;i++){
                if(board.getValue(x-i,y-i) == enemy) count_X2++;
                else if(board.getValue(x-i,y-i) == ally){
                    count_O2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    score += (count_O == 0) ? (Bot::def[count_X] * 2) : Bot::def[count_X];
	score += (count_O2 == 0) ? (Bot::def[count_X2] * 2) : Bot::def[count_X2];
	if(count_X == 4) score *=2;
	return score;
}

long Bot::Second_Diagonal_Def_Point(Board &board, int x, int y, const int atk[], const int def[], const char ally, const char enemy){
    long score = 0;
    int count_O = 0, count_X = 0, count_O2 = 0, count_X2 = 0;
    for(int i = 1; i < 6 && x +i <SIZE && y-i>=0; i++){
        if(board.getValue(x+i,y-i) == enemy) count_X++;
        else if(board.getValue(x+i,y-i) == ally){
            count_O++;
            break;
        }
        else {
            for(int i = 2; i<7 && x +i <SIZE && y-i>=0;i++){
                if(board.getValue(x+i,y-i) == enemy) count_X2++;
                else if(board.getValue(x+i,y-i) == ally){
                    count_O2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    for(int i = 1; i < 6 && x -i >=0 && y+i< SIZE; i++){
        if(board.getValue(x-i,y+i) == enemy) count_X++;
        else if(board.getValue(x-i,y+i) == ally){
            count_O++;
            break;
        }
        else {
            for(int i = 2; i<7 && x -i >=0 && y+i< SIZE;i++){
                if(board.getValue(x-i,y+i) == enemy) count_X2++;
                else if(board.getValue(x-i,y+i) == ally){
                    count_O2++;
                    break;
                }
                else break;
            }
            break;
        }
    }
    score += (count_O == 0) ? (Bot::def[count_X] * 2) : Bot::def[count_X];
	score += (count_O2 == 0) ? (Bot::def[count_X2] * 2) : Bot::def[count_X2];
	if(count_X == 4) score *=2;
	return score;
}

long normalBot::evaluateMove(Board &board, int x, int y, const char ally, const char enemy){
    long atkScore = 0;
    long defScore = 0;
    long maxScore = 0;
    if(board.getValue(x,y) == ' '){
        atkScore += Row_Atk_Point(board,x,y,Bot::atk,Bot::def, ally, enemy);
        atkScore += Col_Atk_Point(board,x,y,Bot::atk,Bot::def, ally, enemy);
        defScore += Row_Def_Point(board,x,y,Bot::atk,Bot::def, ally, enemy);
        defScore += Col_Def_Point (board,x,y,Bot::atk,Bot::def, ally, enemy);
        defScore += Main_Diagonal_Def_Point(board,x,y,Bot::atk,Bot::def, ally, enemy);
        defScore += Second_Diagonal_Def_Point (board,x,y,Bot::atk,Bot::def, ally, enemy);
        maxScore = (atkScore>defScore) ? atkScore : defScore;
    }
    return maxScore;
}

std::pair <int,int> normalBot::getBestMove(Board &board, const char ally, const char enemy){
    long score = 0;
    std::pair<int,int> bestMove =  {0,0};
    for(int i = 0; i< SIZE;i++){
        for(int j = 0; j<SIZE;j++){
                if(score<normalBot::evaluateMove(board,i,j,ally,enemy)) {
                    score = normalBot::evaluateMove(board,i,j,ally,enemy);
                    bestMove.first = i;
                    bestMove.second = j;
                }
            }
        }
        return bestMove;
}

long easyBot::evaluateMove(Board &board, int x, int y, const char ally, const char enemy){
    long atkScore = 0;
    long defScore = 0;
    long maxScore = 0;
    if(board.getValue(x,y) == ' '){
        defScore += Row_Def_Point(board,x,y,Bot::atk,Bot::def, ally, enemy);
        defScore += Col_Def_Point (board,x,y,Bot::atk,Bot::def, ally, enemy);
        defScore += Main_Diagonal_Def_Point(board,x,y,Bot::atk,Bot::def, ally, enemy);
        defScore += Second_Diagonal_Def_Point (board,x,y,Bot::atk,Bot::def, ally, enemy);
        maxScore = (atkScore>defScore) ? atkScore : defScore;
    }
    return maxScore;
}

std::pair <int,int> easyBot::getBestMove(Board &board, const char ally, const char enemy){
    long score = 0;
    std::pair<int,int> bestMove =  {0,0};
    for(int i = 0; i< SIZE;i++){
        for(int j = 0; j<SIZE;j++){
                if(score<=easyBot::evaluateMove(board,i,j,ally, enemy)) {
                    score = easyBot::evaluateMove(board,i,j, ally,enemy);
                    bestMove.first = i;
                    bestMove.second = j;
                }
            }
        }
        return bestMove;
}

long hardBot::evaluateMove(Board &board, int x, int y,const char ally, const char enemy){
    long atkScore = 0;
    long defScore = 0;
    long maxScore = 0;
    if(board.getValue(x,y) == ' '){
        atkScore += Row_Atk_Point(board,x,y,Bot::atk,Bot::def,ally,enemy);
        atkScore += Col_Atk_Point(board,x,y,Bot::atk,Bot::def,ally,enemy);
        atkScore += Main_Diagonal_Atk_Point(board,x,y,Bot::atk,Bot::def,ally,enemy);
        atkScore += Second_Diagonal_Atk_Point(board,x,y,Bot::atk,Bot::def,ally,enemy);
        defScore += Row_Def_Point(board,x,y,Bot::atk,Bot::def,ally,enemy);
        defScore += Col_Def_Point (board,x,y,Bot::atk,Bot::def,ally,enemy);
        defScore += Main_Diagonal_Def_Point(board,x,y,Bot::atk,Bot::def,ally,enemy);
        defScore += Second_Diagonal_Def_Point (board,x,y,Bot::atk,Bot::def,ally,enemy);
        maxScore = (atkScore>=defScore) ? atkScore : defScore;
    }
    return maxScore;
}

std::pair <int,int> hardBot::getBestMove(Board &board,const char ally, const char enemy){
    long score = 0;
    std::pair<int,int> bestMove =  {0,0};
    for(int i = 0; i< SIZE;i++){
        for(int j = 0; j<SIZE;j++){
            //std::cout<<hardBot::evaluateMove(board,i,j,ally,enemy)<<"_";
                if(score<hardBot::evaluateMove(board,i,j, ally,enemy)) {
                    score = hardBot::evaluateMove(board,i,j,ally,enemy);
                    bestMove.first = i;
                    bestMove.second = j;
                }
            }
        }
        return bestMove;
}
