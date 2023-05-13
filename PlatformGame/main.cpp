#include "Game.h"


using namespace sf;

int main()
{
    //Initialize srand
    std::srand(static_cast<unsigned>(time(NULL)));

    //Init Game engine
    Game game;

    //Game loop
    while (game.getWindowIsOpen())
    {

        //Update
        game.update();

        //Render
        game.render();
    }

    //End of application
    return 0;
}