#include "..\\include\\CyberPea.h"
#include<iostream>
#include "..\\include\\ENUM.h"
#include<cstdlib>
#include <time.h>
using namespace std;

CyberPea::CyberPea(Color playerColor):chessPlayer("Mr. Chess AI", playerColor){


}

void CyberPea::decideMove(gameState* state, action* Move, int maxDepth ){

    int TotalMoves = state->Actions.getActionCount(); //= state->computePossibleActions();
    cout<<endl<<"Total Possible Moves "<<TotalMoves;
    if(TotalMoves == 0){
        Move->fromRow = Move->fromCol= Move->toRow = Move->toCol = 0;
        return;
    }

    srand(time(0));
    int RandomlySelectedMove = rand()%TotalMoves;

    state->Actions.getAction(RandomlySelectedMove,Move);

    return;
}
