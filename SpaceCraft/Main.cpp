#include "Game.h"
#include<time.h>

int main()
{
	srand(time(0));

	//Init game engine
	Game game;

	while (game.running())
	{
		game.pollEvent();
		//Update
		if (game.getHptoMain() > 0)
		{
			game.update();
		}

		//Render
		game.render();

	}



	return 0;
}