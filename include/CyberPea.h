#ifndef CYBERPEA_H
#define CYBERPEA_H
#include "chessPlayer.h"
#include"ENUM.h"

class CyberPea : public chessPlayer {
    public:
        CyberPea(Color playerColor=White);
        void decideMove(gameState* state, action* Move, int maxDepth);
};


#endif // CYBERPEA_H
