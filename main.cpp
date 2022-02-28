#include "include\\actionList.h"
#include <iostream>
#include <iomanip>
#include "include\\chess.h"
#include "include\\autoPlayer.h"
#include "include\\humanPlayer.h"
#include "include\\CyberPea.h"


using namespace std;



int main()
{
    chess Game;
    //Game.Players[0] = new humanPlayer("Mojj & Meow", Black);
    Game.Players[0] = new CyberPea(4, Black); // depth == 3
    Game.Players[1] = new CyberPea(2); // depth == 5
    Game.playGame();

    return 0;
}