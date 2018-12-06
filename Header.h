#pragma once
#ifndef _header_h_
#define _header_h_
#include<iostream>
using namespace std;
#include<Windows.h>
#include<thread>
#include<conio.h>
#include<time.h>
#include<vector>
const int maxWidth = 100;
const int maxHeight = 31;
const int l1 = 21, l2 = 6, l3 = 11, l4 = 16, l5 = 1;//toa do cac lane


class cVehicle {
	int mX, mY;
public:
	cVehicle(int x, int y):mX(x),mY(y){}
	virtual int Move(int a) { mX += a; return 0; } // di chuyen a don vi
	virtual void draw()=0;// ve xe
	int getX() { return mX; }
	int getY() { return mY; };
	virtual void eraseWhole()=0;//xoa khi toi dich
};
class cAnimal {
	int mX, mY;
public:
	cAnimal(int x, int y) :mX(x), mY(y) {}
	virtual int Move(int a) { mX += a; return 0; };
//	virtual void tell() = 0;
	virtual void draw() = 0;
	int getX() { return mX; }
	int getY() { return mY; };
	virtual void eraseWhole() = 0;
};
class cTruck : public cVehicle {
public:
	cTruck(int x, int y) : cVehicle(x, y) {}
	void draw();
	int Move(int a);
	void eraseWhole();
};
class cCar: public cVehicle {
public:
	cCar(int x, int y) : cVehicle(x, y) {};
	void draw();
	int Move(int a);
	void eraseWhole();
};
class cBird : public cAnimal {
public:
	cBird(int x, int y) :cAnimal(x, y) {};
	void draw();
	int Move(int a);
	void eraseWhole();
};
class cDinosaur : public cAnimal {
public:
	cDinosaur(int x, int y) : cAnimal(x, y) {};
	void draw();
	int Move(int a);
	void eraseWhole();
};
class cPeople {
	int mX, mY;
	bool mState; 
public:
	cPeople():mX(maxWidth/2),mY(maxHeight-4){ }
	void up();
	void left();
	void right();
	void down();
//	bool isImpact(const cVehicle*&);
//	bool isImpact(const cAnimal*&);
//	bool isFinish();
//	bool isDead();
	void draw();
	void erase();

};
class cGame {
	vector<cVehicle*> v;
	vector<cAnimal*>a;
	cPeople man;
	int level;
public:
	void drawGame(); //ve nguoi, xe, thu
	void drawBox();//ve outline
//	~cGame();
	cPeople getPeople() ;//lay thang nguoi
	vector<cVehicle*> getVehicle() { return v; }//lay vector xe
	vector<cAnimal*>  getAnimal() { return a; }//lay vector thu
//	void resetGame();
//	void exitGame(HANDLE a);
//	void startGame();
//	void loadGame(istream a);
//	void saveGame(istream a);
//	void pauseGame(HANDLE a);
//	void resumeGame(HANDLE a);
	void updatePosVehicle();//cap nhat vi tri xe va tao xe moi
	void updatePosPeople(char a);//dieu khien nguoi choi
	void updatePosAnimal();// cap nhat vi tri thu va tao thu moi

};
void gotoXY(int x, int y);
void fixConsoleWindow();





#endif // !_header_h_
