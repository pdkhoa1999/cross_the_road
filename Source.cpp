#include"Header.h"
char moving=' ',temp;
cGame game;
void subThread()
{
	while (true) {
		game.updatePosVehicle();
		game.updatePosAnimal();
		
		game.updatePosPeople(moving);
		moving = ' ';
		
		game.drawGame();
		Sleep(40);
	}
}

int main()
{
	game.drawBox();
	thread t(subThread);
	while (true)
	{
			temp = toupper(_getch());
		if (temp == 'A' || temp == 'D' || temp == 'S' || temp == 'W')
			moving = temp;
		if (temp == 27)
			return 0;
	}
	


	cin.get();
	return 0;
}