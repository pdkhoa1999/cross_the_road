#include"Header.h"


void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void fixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX)&~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}


//people//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void cPeople::erase()
{
	gotoXY(mX, mY);
	cout << " ";
	for (int i = -1; i < 2; i++)
	{
		gotoXY(mX + i, mY + 1);
		cout << " ";
	}

	gotoXY(mX - 1, mY +2);
	cout << " ";
	gotoXY(mX + 1, mY + 2);
	cout << " ";
}
void cPeople::down()
{
	erase();
	if (mY + 5 > maxHeight)
		return;
	mY += 5;

}
void cPeople::draw()
{
	gotoXY(mX, mY);
	cout << (char)254u;
	for (int i = -1; i < 2; i++)
	{
		gotoXY(mX+i, mY + 1);
		cout << (char)254u;
	}
	gotoXY(mX - 1, mY +2);
	cout << (char)254u;
	gotoXY(mX + 1, mY + 2);
	cout << (char)254u;
}
void cPeople::up()
{
	erase();
	if (mY < 3)
		return;
	mY -= 5;
}
void cPeople::right()
{
	erase();
	if (mX + 6 > maxWidth)
		return;
	mX += 5;
}
void cPeople::left()
{
	erase();
	if (mX < 6)
		return;
	mX -= 5;
}
//game//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void cGame::drawGame()
{
	man.draw();
	for (int i = 0; i < v.size(); i++)
	{
		v[i]->draw();
	}
	for (int i = 0; i < a.size(); i++)
	{
		a[i]->draw();
	}
}
cPeople cGame::getPeople()
{
	return this->man;
}
void cGame::updatePosPeople(char a)
{
	if (a == 'W') man.up();
	else if (a == 'D') man.right();
	else if (a == 'S') man.down();
	else if (a == 'A')man.left();
	else return;
}
void cGame::drawBox()
{
	for (int i = 0; i < maxHeight;i++)
	{
		for (int j = 0; j < maxWidth; j++)
		{
			if (j == maxWidth-1 || j == 0)
			{
				gotoXY(j, i);
				cout << "|";
			}
			else if (i == maxHeight-1 || i%5==0)
			{
				gotoXY(j, i);
				cout << "-";
			}
		}
	}
}
void cGame::updatePosVehicle()
{
	srand(time(NULL));
	cVehicle *supe;
	int a = rand()%8;
	if (a ==0||a==1||a==2||a==3)
	{
		if (v.empty()||v.back()->getX()>12) {
			supe = new cTruck(1, l4);
			v.push_back(supe);
		}
	}
	else  if(a==4||a==5||a==6||a==7) {
		if (v.empty() || v.back()->getX() < maxWidth-12) {
			supe = new cCar(maxWidth-5, l3);
			v.push_back(supe);
		}
	}
	for (int i = 0; i < v.size(); i++)
	{
		int a = v[i]->Move(1);
		if (a == -1)
		{
			v[i]->eraseWhole();
			v.erase(v.begin() + i);
		}
	}
	
}
void cGame::updatePosAnimal()
{
	srand(time(NULL));
	cAnimal *supe;
	int b = rand() % 8;
	if (b ==0||b==1||b==2||b==3)
	{
		if (a.empty() || a.back()->getX() < maxWidth - 12) {
			supe = new cBird(maxWidth - 5, l1);
			a.push_back(supe);
		}
	}
	else if(b==4||b==5||b==6||b==7) {
		if (a.empty() || a.back()->getX() >12 ) {
			supe = new cDinosaur(2, l2);
			a.push_back(supe);
		}
	}
	for (int i = 0; i < a.size(); i++)
	{
		int c = a[i]->Move(1);
		if (c == -1)
		{
			a[i]->eraseWhole();
			a.erase(a.begin() + i);
		}
	}

}

//vehicle//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int cTruck::Move(int a)
{
	if (getX() > maxWidth-10)
		return -1;
	cVehicle::Move(a);
	return 0;
}
void cTruck::draw()
{
	gotoXY(getX()-1, getY());
	cout << " ";
	gotoXY(getX() - 1, getY()+1);
	cout << " ";
	gotoXY(getX() - 1, getY()+2);
	cout << " ";
	for (int i = 0; i < 6; i++)
	{
		if (i != 4) {
			gotoXY(getX() + i, getY());
			cout << (char)254u;
		}
		else
		{
			gotoXY(getX() + i, getY());
			cout <<" ";
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (i != 4) {
			gotoXY(getX() + i, getY() + 1);
			cout << (char)254u;
		}
		else
		{
			gotoXY(getX() + i, getY() + 1);
			cout << " ";
		}
	}
	for (int i = 0; i < 8; i++)
	{
		gotoXY(getX() + i, getY() + 2);
		cout << (char)254u;
	}
}
void cTruck::eraseWhole(){
	for (int i = 0; i < 6; i++)
	{
		if (i != 4) {
			gotoXY(getX() + i, getY());
			cout << " ";
		}
	}
	for (int i = 0; i < 8; i++)
	{
		if (i != 4) {
			gotoXY(getX() + i, getY() + 1);
			cout << " ";
		}
	}
	for (int i = 0; i < 8; i++)
	{
		gotoXY(getX() + i, getY() + 2);
		cout << " ";
	}
}
void cCar::draw()
{
	gotoXY(getX()+2, getY());
	cout << " ";
	gotoXY(getX() + 4, getY() + 1);
	cout << " ";
	gotoXY(getX() + 4, getY() + 2);
	cout << " ";
	gotoXY(getX()-1, getY() + 2);
	cout << " ";
	for (int i = 0; i < 2; i++)
	{
		gotoXY(getX() + i, getY() );
		cout << (char)254u;
	}
	for (int i = -2; i < 4; i++)
	{
		gotoXY(getX() + i, getY() + 1);
		cout << (char)254u;
	}
	gotoXY(getX() - 2, getY() + 2);
	cout << (char)254u;
	gotoXY(getX()+ 3 , getY() +2);
	cout << (char)254u;
}
int cCar::Move(int a)
{
	if (getX()<10)
		return -1;
	cVehicle::Move(-a);
	return 0;
}
void cCar::eraseWhole()
{
	for (int i = 0; i < 2; i++)
	{
		gotoXY(getX() + i, getY());
		cout << " ";
	}
	for (int i = -2; i < 4; i++)
	{
		gotoXY(getX() + i, getY() + 1);
		cout << " ";
	}
	gotoXY(getX() - 2, getY() + 2);
	cout << " ";
	gotoXY(getX() + 3, getY() + 2);
	cout << " ";
}

//animal//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void cBird::draw()
{
	gotoXY(getX()-2, getY()+1);
	cout << (char)254u << " " << (char)254u << " " << (char)254u<<" ";
	gotoXY(getX() - 1, getY());
	cout << (char)254u << " " << (char)254u<<" ";
}
int cBird::Move(int a)
{
	if (getX() <4)
		return -1;
	cAnimal::Move(-a);
	return 0;
}
void cBird::eraseWhole()
{
	gotoXY(getX() - 2, getY() + 1);
	cout << " " << " " << " " << " " << " ";
	gotoXY(getX() - 1, getY());
	cout << " " << " " << " ";
}
void cDinosaur::draw()
{

	gotoXY(getX()-1, getY());
	cout <<" "<< (char)254u << (char)254u;
	gotoXY(getX()-1, getY()+1);
	cout <<" "<< (char)254u << (char)254u<<(char)254u;
	gotoXY(getX()-1, getY()+2);
	cout <<" "<< (char)254u << (char)254u;
	gotoXY(getX() - 2, getY() + 3);
	cout <<" "<< (char)254u << (char)254u << (char)254u;

}

void cDinosaur::eraseWhole()
{
	gotoXY(getX(), getY());
	cout << " " <<" " ;
	gotoXY(getX(), getY() + 1);
	cout <<" " <<" " <<" ";
	gotoXY(getX(), getY() + 2);
	cout <<" " <<" ";
	gotoXY(getX() - 1, getY() + 3);
	cout <<" " <<" " <<" ";
}

int cDinosaur::Move(int a)
{
	
	if (getX() > maxWidth - 10)
		return -1;
	cAnimal::Move(a);
	return 0;
}