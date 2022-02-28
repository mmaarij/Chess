#ifndef CYBERPEA_H
#define CYBERPEA_H
#include "chessPlayer.h"
#include"ENUM.h"
#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define PAWN 10
#define KNIGHT 30
#define BISHOP 30
#define ROOK 50
#define QUEEN 90
#define KING 900

class Data
{
    public:
        int score;
        int index;
};

class CyberPea : public chessPlayer {

    private:

        // ********** HEATMAPS **********

        float blackPawn[8][8] =
        {
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
            {1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
            {0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
            {0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
            {0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
            {0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
        };

        float whitePawn[8][8] =
        {
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.5, 1.0, 1.0, -2.0, -2.0, 1.0, 1.0, 0.5},
            {0.5, -0.5, -1.0, 0.0, 0.0, -1.0, -0.5, 0.5},
            {0.0, 0.0, 0.0, 2.0, 2.0, 0.0, 0.0, 0.0},
            {0.5, 0.5, 1.0, 2.5, 2.5, 1.0, 0.5, 0.5},
            {1.0, 1.0, 2.0, 3.0, 3.0, 2.0, 1.0, 1.0},
            {5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0},
            {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
        };

        float Knight[8][8] =
        {
            {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
            {-4.0, -2.0, 0.0, 0.0, 0.0, 0.0, -2.0, -4.0},
            {-3.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, -3.0},
            {-3.0, 0.5, 1.5, 2.0, 2.0, 1.5, 0.5, -3.0},
            {-3.0, 0.0, 1.5, 2.0, 2.0, 1.5, 0.0, -3.0},
            {-3.0, 0.5, 1.0, 1.5, 1.5, 1.0, 0.5, -3.0},
            {-4.0, -2.0, 0.0, 0.5, 0.5, 0.0, -2.0, -4.0},
            {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
        };

        float blackBishop[8][8] =
        {
            { -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
            {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
            {-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
            {-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
            {-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
            {-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
            {-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
            {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
        };

        float whiteBishop[8][8] =
        {
            {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
            {-1.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, -1.0},
            {-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0},
            {-1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0},
            {-1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 0.5, -1.0},
            {-1.0, 0.0, 0.5, 1.0, 1.0, 0.5, 0.0, -1.0},
            {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
            { -2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
        };

        float blackRook[8][8] =
        {
            { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
            {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
            {0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0}
        };

        float whiteRook[8][8] =
        {
            {0.0, 0.0, 0.0, 0.5, 0.5, 0.0, 0.0, 0.0},
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
            {-0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.5},
            {0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5},
            { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}

        };

        float Queen[8][8] =
        {
            { -2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
            {-1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0},
            {-1.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
            {-0.5, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
            {0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 0.0, -0.5},
            {-1.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.0, -1.0},
            {-1.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, -1.0},
            {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
        };

        float blackKing[8][8] =
        {
            { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
            {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
            {2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
            {2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0}
        };

        float whiteKing[8][8] =
        {
            {2.0, 3.0, 1.0, 0.0, 0.0, 1.0, 3.0, 2.0},
            {2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 2.0, 2.0},
            {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
            {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
            { -3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0}
        };


    public:

        // Constructor
        CyberPea(Color playerColor = White):chessPlayer("Mr. Chess AI", playerColor) {}


        // Decide Move
        void decideMove(gameState* state, action* Move, int maxDepth)
        {
            int TotalMoves = state->Actions.getActionCount(); //= state->computePossibleActions();
            cout << endl << "Total Possible Moves " << TotalMoves << endl;

            if (TotalMoves == 0) {
                Move->fromRow = Move->fromCol = Move->toRow = Move->toCol = 0;
                return;
            }

            Data bestMove;
            int totalComputations = 0;

            int DEPTH = 5;
            cout << "Search Depth: " << DEPTH << endl;

            auto start = high_resolution_clock::now(); // start measuring execution time

            bestMove = minimax(state, 5, INT_MIN, INT_MAX, totalComputations); // depth = 5 | alpha = -inf | beta = +inf
            int SelectedMove = bestMove.index;

            auto stop = high_resolution_clock::now(); // stop measuring execution time

            cout << "Total Computations Taken Into Account: " << totalComputations << endl;
            auto duration = duration_cast <milliseconds> (stop - start);
            cout << "Execution Time: " << duration.count() << " milliseconds" << endl;
            
            state->Actions.getAction(SelectedMove, Move);

            int piece = state->Board.board[Move->fromRow][Move->fromCol];
            showMove(piece, Move);
            
            return;
        }


        void showMove(int piece, action * Move)
        {
            cout << "Move ";

            if (piece > 0)
                cout << "White ";
            else if (piece < 0)
                cout << "Black ";

            switch (piece)
            {
            case 4:
            case -4:
                cout << "Rook";
                break;

            case 2:
            case -2:
                cout << "Knight";
                break;

            case 3:
            case -3:
                cout << "Bishop";
                break;

            case 5:
            case -5:
                cout << "Queen";
                break;

            case 6:
            case -6:
                cout << "King";
                break;

            case 1:
            case -1:
                cout << "Pawn";
                break;

            }

            cout << " (" << Move->fromRow << ", " << Move->fromCol << ") To (" << Move->toRow << ", " << Move->toCol << ")" << endl;

        }


        // Minimax + Alpha Beta Pruning
        Data minimax (gameState* state, int depth, int alpha, int beta, int &totalComputations)
        {
            //we want to compute all possible moves here.
            int TotalMoves = state->Actions.getActionCount();
            actionList tempList;
            action tempAction;
            
            totalComputations++;

            if (depth == 0 || TotalMoves == 0) // base case
            {
                Data leaf;
                leaf.score = evaluateScore(state);
                return leaf;
            }
            else
            {
                //backup action list
                for (int i = 0; i < TotalMoves; i++)
                {
                    state->Actions.getAction(i, &tempAction);
                    tempList.addAction(tempAction);
                }
            }

            if (state->getPlayer() == White) // ******************** MAXIMIZING PLAYER ********************
            {
                Data maxEval;
                maxEval.score = INT_MIN;

                for (int i = 0; i < TotalMoves; i++)
                {
                    // backup board state
                    int backupBoard[8][8];
                    for (int r = 0; r < 8; r++)
                    {
                        for (int c = 0; c < 8; c++)
                        {
                            backupBoard[r][c] = state->Board.board[r][c];
                        }
                    }

                    //select move from list
                    state->Actions.getAction(i, &tempAction);
                    // make look-ahead move on board and change player
                    state->applyMove(tempAction);
                    
                    // ********** RECURSIVE CALL **********
                    Data eval = minimax(state, depth - 1, alpha, beta, totalComputations);

                    // undo look-ahead move on board // restore backed up board
                    for (int r = 0; r < 8; r++)
                    {
                        for (int c = 0; c < 8; c++)
                        {
                            state->Board.board[r][c] = backupBoard[r][c];
                        }
                    }
                    state->setPlayer(White);
                    state->Actions.resetActions();

                    //restore action list
                    for (int j = 0; j < TotalMoves; j++)
                    {
                        tempList.getAction(j, &tempAction);
                        state->Actions.addAction(tempAction);
                    }

                    // select max
                    if (eval.score > maxEval.score)
                    {
                        maxEval.score = eval.score;
                        maxEval.index = i;
                    }
                    
                    // alpha pruning
                    alpha = max(alpha, eval.score);
                    if (beta <= alpha)
                        break;

                }
                return maxEval;
            }

            else                             // ******************** MINIMIZING PLAYER ********************
            {
                Data minEval;
                minEval.score = INT_MAX;

                for (int i = 0; i < TotalMoves; i++)
                {
                    // backup board state
                    int backupBoard[8][8];
                    for (int r = 0; r < 8; r++)
                    {
                        for (int c = 0; c < 8; c++)
                        {
                            backupBoard[r][c] = state->Board.board[r][c];
                        }
                    }

                    //select move from list
                    state->Actions.getAction(i, &tempAction);
                    // apply selected look-ahead move on board and change player
                    state->applyMove(tempAction);

                    // ********** RECURSIVE CALL **********
                    Data eval = minimax(state, depth - 1, alpha, beta, totalComputations);

                    // undo look-ahead move on board // restore backed up board
                    for (int r = 0; r < 8; r++)
                    {
                        for (int c = 0; c < 8; c++)
                        {
                            state->Board.board[r][c] = backupBoard[r][c];
                        }
                    }
                    state->setPlayer(Black);
                    state->Actions.resetActions();

                    //restore action list
                    for (int j = 0; j < TotalMoves; j++)
                    {
                        tempList.getAction(j, &tempAction);
                        state->Actions.addAction(tempAction);
                    }

                    // select min
                    if (eval.score < minEval.score)
                    {
                        minEval.score = eval.score;
                        minEval.index = i;
                    }

                    // beta pruning
                    beta = min(beta, eval.score);
                    if (beta <= alpha)
                        break;
                }
                return minEval;
            }
            
        }


        // Evaluate Function with Piece Scoing and Positional Evaluation (Heat Maps)
        int evaluateScore(gameState* state)
        {
            int tempScore = 0;

            // evaluate move score
            for (int x = 0; x < 8; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    if (state->Board.board[x][y] == 1) // WHITE PAWN
                    {
                        tempScore += PAWN;
                        tempScore += (int)(whitePawn[x][y] * 2);
                    }

                    else if (state->Board.board[x][y] == -1) // BLACK PAWN
                    {
                        tempScore -= PAWN;
                        tempScore += (int)(blackPawn[x][y] * 2);
                    }
                        
                    else if (state->Board.board[x][y] == 4) // WHITE ROOK
                    {
                        tempScore += ROOK;
                        tempScore += (int)(whiteRook[x][y] * 2);
                    }

                    else if (state->Board.board[x][y] == -4) // BLACK ROOK
                    {
                        tempScore -= ROOK;
                        tempScore += (int)(blackRook[x][y] * 2);
                    }

                    else if (state->Board.board[x][y] == 2) // WHITE KNIGHT
                    {
                        tempScore += KNIGHT;
                        tempScore += (int)(Knight[x][y] * 2);
                    }

                    else if (state->Board.board[x][y] == -2) // BLACK KNIGHT
                    {
                        tempScore -= KNIGHT;
                        tempScore += (int)(Knight[x][y] * 2);
                    }

                    else if (state->Board.board[x][y] == 3) // WHITE BISHOP
                    {
                        tempScore += BISHOP;
                        tempScore += (int)(whiteBishop[x][y] * 2);
                    }

                    else if (state->Board.board[x][y] == -3)  // BLACK BISHOP
                    {
                        tempScore -= BISHOP;
                        tempScore += (int)(blackBishop[x][y] * 2);
                    }

                    else if (state->Board.board[x][y] == 5)  // WHITE QUEEN
                    {
                        tempScore += QUEEN;
                        tempScore += (int)(Queen[x][y] * 2);
                    }

                    else if (state->Board.board[x][y] == -5) // BLACK QUEEN
                    {
                        tempScore -= QUEEN;
                        tempScore += (int)(Queen[x][y] * 2);
                    }

                    else if (state->Board.board[x][y] == 6) // WHITE KING
                    {
                        tempScore += KING;
                        tempScore += (int)(whiteKing[x][y] * 2);
                    }

                    else if (state->Board.board[x][y] == -6) // BLACK KING
                    {
                        tempScore -= KING;
                        tempScore += (int)(blackKing[x][y] * 2);
                    }
                }
            }

            return tempScore;
        }
};


#endif // CYBERPEA_H
