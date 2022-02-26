
#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <string>

class chessBoard{
    private:

    public:
        int board[9][9];
        int whiteHome;
        int whiteMoveDirection;

        chessBoard(int whiteHomeParameter = 0);
        int initBoardFromFile(std::string fileName);
};

#endif // CHESSBOARD_H
