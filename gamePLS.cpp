//        to-do list:
//-redo the entire goddamn bullet thing goddamnit
/*
				 /\
                 |
                 |
                 |

*/
//-make gameplay
//-make multiplayer mode

//FIX ISSUES
//-bullets flash (cuz idk, 2+ bullets do weird printworld thing)
//-proram crashes after too many bullets
//-player cant move after firing a bullet
//-

//std::this_thread::sleep_for(std::chrono::milliseconds(10))

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <thread>
#include <vector>
#include <ctime>
#include "curses.h"
#undef getch
#include <conio.h>

using namespace std;

#define WORLD_X 119
#define WORLD_Y 26
#define TITLENAME "INSERT GAME NAME HERE"
#define SUBTITLENAME "A game made by the Burnaby South Programming and Robotics club"


struct player {
	int health;
	int x;
	int y;
	char direction;
};

player p1;//player 1

struct mob {
	int x;
	int y;
};

struct bullet {
	int duration;
	int x;
	int prevX = 0;
	int y;
	int prevY = 0;
	char direction;
	int vx;
	int vy;
	int damage;
	bool cont = false;
};

vector<bullet> bullets;

bool gameOver = false;
bool beginning = true;
bool title = true;
bool leaveGame = false;

bool goForIt = true;

bool AyFamDidjaPrintABullet = false;
int numberInVector = 0;
bool bulletOrNaw = true;

char enteredKey;

char world[WORLD_Y][WORLD_X];

void initWorld()
{
	for (int i = 0; i < WORLD_Y; ++i)
	{
		for (int x = 0; x < WORLD_X; ++x)
		{
			world[i][x] = ' ';
		}
	}
}

void printWorld()
{
	while (gameOver == false) 
	{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	if (goForIt == true)
	{
		clear();
		goForIt = false;
		for (int i = 0; i < WORLD_Y; ++i)
		{
			for (int x = 0; x < WORLD_X; ++x)
			{

				if (i == p1.y && x == p1.x)
				{
					printw("%c", '@');
				}
				else
				{
					printw("%c", world[i][x]);
				}
			}
			printw("\n");
		}
		printw("Health: %d", p1.health);
		if (beginning == true) { beginning = false; }
		goForIt = true;
	}
		refresh();
	}
}

void frick_A_Bullet()
{
	bullet b;
	b.cont = true;
	
	b.prevX = p1.x;
	b.prevY = p1.y;
	b.x = p1.x;
	b.y = p1.y;
	b.direction = p1.direction;
	
	while (b.cont == true)
	{
		switch (b.direction)
		{
		case 'w':
			if (b.y != 1)
			{
				b.y--;
				world[b.y][b.x] = '+';
				//printWorld();
				world[b.y][b.x] = ' ';
			}
			else
			{
				b.cont = false;
				b.y--;
				world[b.y][b.x] = '+';
				//printWorld();
				world[b.y][b.x] = ' ';
			}
			break;
		case 'a':
			if (b.x != 1)
			{
				b.x--;
				world[b.y][b.x] = '+';
				//printWorld();
				world[b.y][b.x] = ' ';
			}
			else
			{
				b.cont = false;
				b.x--;
				world[b.y][b.x] = '+';
				//printWorld();
				world[b.y][b.x] = ' ';
			}
			break;
		case 's':
			if (b.y != WORLD_Y - 1)
			{
				b.y++;
				world[b.y][b.x] = '+';
				//printWorld();
				world[b.y][b.x] = ' ';
			}
			else
			{
				b.cont = false;
				b.y++;
				world[b.y][b.x] = '+';
				//printWorld();
				world[b.y][b.x] = ' ';
			}
			break;
		case 'd':
			if (b.x != WORLD_X - 1)
			{
				b.x++;
				world[b.y][b.x] = '+';
				//printWorld();
				world[b.y][b.x] = ' ';
			}
			else
			{
				b.cont = false;
				b.x++;
				world[b.y][b.x] = '+';
				//printWorld();
				world[b.y][b.x] = ' ';
			}
			break;
		}
	}
	//printWorld();
}


void singleMode()
{	
	thread E(printWorld);
	E.detach();
	while (gameOver == false)
	{
		if (beginning == true) { printWorld(); }

		enteredKey = _getch();

		switch (enteredKey)
		{
		case 'w':
			if (p1.y >= 1) { p1.y--; }
			break;

		case 's':
			if (p1.y != WORLD_Y - 1) { p1.y++; }
			break;

		case 'a':
			if (p1.x >= 1) { p1.x--; }
			break;

		case 'd':
			if (p1.x != WORLD_X - 1) { p1.x++; }
			break;

		case ' ':
			frick_A_Bullet();
			break;
		}
		if (enteredKey != ' ')
		{
			p1.direction = enteredKey;
			//printWorld();
		}
	}
}


void multiMode()
{
	while (gameOver == false)
	{

	}
}


int main()
{
	initWorld();
	initscr();

	string lel;
	int optionPicked = 1;
	bool enter = false;
	char input;

	while (leaveGame == false)
	{
		clear();
		lel = TITLENAME;
		int gosh = WORLD_X - lel.size();
		gosh = gosh / 2;
		if (gosh % 2 != 0)
		{
			gosh = gosh - 1;
		}
		for (int i = 0; i < gosh; i++)
		{
			lel = " " + lel;
		}
		printw("%s \n\n", lel.c_str());
		
		

		lel = SUBTITLENAME;
		gosh = WORLD_X - lel.size();
		gosh = gosh / 2;
		if (gosh % 2 != 0)
		{
			gosh = gosh - 1;
		}
		for (int i = 0; i < gosh; i++)
		{
			lel = " " + lel;
		}
		printw("%s \n\n", lel.c_str());
		
		

		string lol = "Singleplayer";
		gosh = WORLD_X - lol.size();
		gosh = gosh / 2;
		if (gosh % 2 != 0)
		{
			gosh = gosh - 1;
		}
		if (optionPicked == 1) { gosh--; lol = ">" + lol; }
		for (int i = 0; i < gosh; i++)
		{
			lol = " " + lol;
		}
		printw("%s \n\n", lol.c_str());
		
		

		lol = "Multi-player";
		gosh = WORLD_X - lol.size();
		gosh = gosh / 2;
		if (gosh % 2 != 0)
		{
			gosh = gosh - 1;
		}
		if (optionPicked == 2) { gosh--; lol = ">" + lol; }
		for (int i = 0; i < gosh; i++)
		{
			lol = " " + lol;
		}
		printw("%s \n\n", lol.c_str());
		refresh();

		input = _getch();
		if (input == 's') {optionPicked = 2;}
		if (input == 'w') {optionPicked = 1;}
		if (input == ' ' && optionPicked == 1) { singleMode(); }
		if (input == ' ' && optionPicked == 2) { multiMode(); }
	}
}
