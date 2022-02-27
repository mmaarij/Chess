#ifndef CYBERPEA_H
#define CYBERPEA_H
#include "chessPlayer.h"
#include"ENUM.h"
#include <iostream>
#include <time.h>

using namespace std;

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
            bestMove = minimax(state, 1);
            int SelectedMove = bestMove.index;
            if (bestMove.score == 0)
            {
                srand(time(0));
                SelectedMove = rand() % TotalMoves;
            }
            

            state->Actions.getAction(SelectedMove, Move);

            return;
        }

        // Calculate Score 
        int evalScoreFirstLvl(gameState* state, int TotalMoves)
        {
            int maxIndex = 0;
            int maxScore = INT_MIN;

            for (int i = 0; i < TotalMoves; i++)
            {
                int tempScore = 0;
                action tempAction;
                state->Actions.getAction(i, &tempAction);

                // make move on board
                state->Board.board[tempAction.toRow][tempAction.toCol] = state->Board.board[tempAction.fromRow][tempAction.fromCol];
                state->Board.board[tempAction.fromRow][tempAction.fromCol] = 0;

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

                // if move better than any prev then store new move
                if (tempScore > maxScore)
                {
                    maxScore = tempScore;
                    maxIndex = i;
                }

                // undo move on board
                state->Board.board[tempAction.fromRow][tempAction.fromCol] = state->Board.board[tempAction.toRow][tempAction.toCol];
                state->Board.board[tempAction.toRow][tempAction.toCol] = 0;

            }

            if (maxScore == 0)
            {
                srand(time(0));
                maxIndex = rand() % TotalMoves;
            }
            return maxIndex;
        }


        Data minimax(gameState* state, int depth)
        {
            //we want to compute all possible moves here.
            int TotalMoves = state->Actions.getActionCount(); // this == computepossibleactions
            actionList tempList;
            action tempAction;
            
            


            if (depth == 0 || TotalMoves == 0) // base case
            {
                Data leaf;
                leaf.score = calcScore(state);
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

            if (state->getPlayer() == White)
            {
                Data maxEval;
                maxEval.score = INT_MIN;

                for (int i = 0; i < TotalMoves; i++)
                {
                    state->Actions.getAction(i, &tempAction);

                    // make look-ahead move on board and change player
                    state->applyMove(tempAction);

                    Data eval = minimax(state, depth - 1);

                    // undo look-ahead move on board
                    state->Board.board[tempAction.fromRow][tempAction.fromCol] = state->Board.board[tempAction.toRow][tempAction.toCol];
                    state->Board.board[tempAction.toRow][tempAction.toCol] = 0;
                    state->setPlayer(White);
                    state->Actions.resetActions();
                    for (int j = 0; j < TotalMoves; j++)
                    {
                        tempList.getAction(j, &tempAction);
                        state->Actions.addAction(tempAction);
                    }

                    if (eval.score > maxEval.score)
                    {
                        maxEval.score = eval.score;
                        maxEval.index = i;
                    }
                }
                return maxEval;
            }

            else
            {
                Data minEval;
                minEval.score = INT_MAX;

                for (int i = 0; i < TotalMoves; i++)
                {
                    state->Actions.getAction(i, &tempAction);

                    // make look-ahead move on board and change player
                    state->applyMove(tempAction);

                    Data eval = minimax(state, depth - 1);

                    // undo look-ahead move on board
                    state->Board.board[tempAction.fromRow][tempAction.fromCol] = state->Board.board[tempAction.toRow][tempAction.toCol];
                    state->Board.board[tempAction.toRow][tempAction.toCol] = 0;
                    state->setPlayer(Black);
                    state->Actions.resetActions();
                    for (int j = 0; j < TotalMoves; j++)
                    {
                        tempList.getAction(j, &tempAction);
                        state->Actions.addAction(tempAction);
                    }

                    if (eval.score < minEval.score)
                    {
                        minEval.score = eval.score;
                        minEval.index = i;
                    }
                }
                return minEval;
            }
            
        }


        int calcScore(gameState* state)
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
