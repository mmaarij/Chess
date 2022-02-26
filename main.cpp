#include "include\\actionList.h"
#include <iostream>
#include <iomanip>
#include "include\\chess.h"
#include "include\\autoPlayer.h"
#include "include\\humanPlayer.h"
#include "include\\CyberPea.h"

using namespace std;

int main(){
    chess Game;
    Game.Players[0] = new humanPlayer("CyberPea", Black);
    Game.Players[1] = new CyberPea();
    Game.playGame();
    return 0;
}