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
    public:

        // Constructor
        CyberPea(Color playerColor = White) {}


        // Decide Move
        void decideMove(gameState* state, action* Move, int maxDepth)
        {
            int TotalMoves = state->Actions.getActionCount(); //= state->computePossibleActions();
            cout << endl << "Total Possible Moves " << TotalMoves;

            if (TotalMoves == 0) {
                Move->fromRow = Move->fromCol = Move->toRow = Move->toCol = 0;
                return;
            }

            Data bestMove;
            int totalComputations = 0;

            auto start = high_resolution_clock::now(); // start measuring execution time

            bestMove = minimax(state, 5, INT_MIN, INT_MAX, totalComputations); // depth = 12 | alpha = -inf | beta = +inf
            int SelectedMove = bestMove.index;

            auto stop = high_resolution_clock::now(); // stop measuring execution time

            if (bestMove.score == 0) // random moves initially until a piece is able to get captured
            {
                srand(time(0));
                SelectedMove = rand() % TotalMoves;
            }

            cout << endl << "Total Computations Taken Into Account: " << totalComputations << endl;
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Execution Time: " << duration.count()/1000000 << " seconds" << endl;
            
            state->Actions.getAction(SelectedMove, Move);

            return;
        }


        // Minimax
        Data minimax (gameState* state, int depth, int alpha, int beta, int &totalComputations)
        {
            //we want to compute all possible moves here.
            int TotalMoves = state->Actions.getActionCount(); // this == computepossibleactions
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


        // Evaluate Function
        int evaluateScore(gameState* state)
        {
            int tempScore = 0;

            // evaluate move score
            for (int x = 0; x < 8; x++)
            {
                for (int y = 0; y < 8; y++)
                {
                    if (state->Board.board[x][y] == 1)
                        tempScore += PAWN;
                    else if (state->Board.board[x][y] == -1)
                        tempScore -= PAWN;

                    else if (state->Board.board[x][y] == 4)
                        tempScore += ROOK;
                    else if (state->Board.board[x][y] == -4)
                        tempScore -= ROOK;

                    else if (state->Board.board[x][y] == 2)
                        tempScore += KNIGHT;
                    else if (state->Board.board[x][y] == -2)
                        tempScore -= KNIGHT;

                    else if (state->Board.board[x][y] == 3)
                        tempScore += BISHOP;
                    else if (state->Board.board[x][y] == -3)
                        tempScore -= BISHOP;

                    else if (state->Board.board[x][y] == 5)
                        tempScore += QUEEN;
                    else if (state->Board.board[x][y] == -5)
                        tempScore -= QUEEN;

                    else if (state->Board.board[x][y] == 6)
                        tempScore += KING;
                    else if (state->Board.board[x][y] == -6)
                        tempScore -= KING;
                }
            }

            return tempScore;
        }
};


#endif // CYBERPEA_H
