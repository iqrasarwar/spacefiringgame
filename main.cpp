//BSEF19M012
//IQRA SARWAR
//DO RUN THIS FILE ON FULL SCREEN OTHERWISE IT WILL GENRETE AMBIGOUS BEHAVOIUR.


#include <iostream>
#include<iomanip>
#include<conio.h>
#include<windows.h>		//Library to handle sleep fun and cursor pos
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// this class obj array is contained in rocket and spaceship classes as per instruction.
//further ins were not stated so i ahve implemented it as following:
//spaceship and rocket classes contains array of fireballs when they fire size is decremented by 1.
//for rocket class if size reaches means that player run short of fire objs and game ends.
//i have given enough fireballs to spaceships so as an enemy they are not supposed to run short of fires.i have not displayed any count
//on screen as it was not strictly instructed to do so.
//i have treated fire as an object of faireball class.
class fireBalls
{
public:
	fireBalls();
	~fireBalls();
	void draw(int, int);
	void move(int);
	void clear(int, int);
	int getx();
	int gety();
	void set_xy(int, int);

private:
	int xloc;
	int yloc;
};
//constructor
fireBalls::fireBalls()
{
	xloc = 0;
	yloc = 0;
}
//destructor-nothing to destroy
fireBalls::~fireBalls()
{
}
//draw fire obj on screen
void fireBalls::draw(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "_*_";
}
//move fire object on screen x times on screen if x is 1 move 1 position down if -1 move 1 pos up.
void fireBalls::move(int x)
{
	clear(this->getx(), this->gety());
	this->yloc += x;
	draw(this->getx(), this->gety());
	set_xy(this->getx(), this->gety());
}
//clear a fire obj from screen i.e when it moves 1 pos up this func clear the previosly drawn
void fireBalls::clear(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "   ";
}
//return x cor of fireball
int fireBalls::getx()
{
	return this->xloc;
}
//return y coor of fireball
int fireBalls::gety()
{
	return this->yloc;
}
//set x y coor of fireball
void fireBalls::set_xy(int xloc, int yloc)
{
	this->xloc = xloc;
	this->yloc = yloc;
}

class Spaceship;
//this class deals with player obj rocket
class  Rocket
{
public:
	Rocket();
	void draw(int, int);
	void move(int);
	void fire(Spaceship** s);
	void set_array(int);
	int get_size();
	void clear(int, int);
	int getx();
	int gety();
	void set_xy(int, int);
	void set_hits(int);
	int get_hits();
	int get_lifes();
	void set_lifes(int);
private:
	int lives;
	int xloc;
	int yloc;
	fireBalls* array;
	int size;
	int hits;
};
Rocket::Rocket()
{
	lives = 3;
	hits = 0;
	size = 100;
	array = new fireBalls[size];
}
//draw rocket
void Rocket::draw(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	for (int i = 0; i < 3; i++)
	{
		CursorPosition.Y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << " .. .. .." << endl;
	}
	for (int i = 0; i < 4; i++) {
		CursorPosition.Y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << "**********" << endl;
	}
}
//move rocket by clearing it first then setting new coor and redrawing it.
void Rocket::move(int x)
{
	clear(this->xloc, this->yloc);
	switch (x)
	{
	case 2:
		this->yloc += 3;
		break;
	case 1:
		this->yloc -= 3;
		break;
	case 3:
		this->xloc -= 3;
		break;
	case 4:
		this->xloc += 3;
		break;
	}
	draw(this->xloc, this->yloc);
	set_xy(this->xloc, this->yloc);
}
//clear used to clear previously drawn rocket when it moves
void Rocket::clear(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	for (int i = 0; i < 3; i++)
	{
		CursorPosition.Y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << "         " << endl;
	}
	for (int i = 0; i < 4; i++) {
		CursorPosition.Y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << "          " << endl;
	}
}
//return x cor
int Rocket::getx()
{
	return this->xloc;
}
//ret y cor
int Rocket::gety()
{
	return this->yloc;
}
//set x y coor
void Rocket::set_xy(int xloc, int yloc)
{
	this->xloc = xloc;
	this->yloc = yloc;
}
//set hits - track of num of hits is essentiasl to handle lifes of player
void Rocket::set_hits(int x)
{
	this->hits = x;
}
//get hits
int Rocket::get_hits()
{
	return this->hits;
}
//lifes setter
int Rocket::get_lifes()
{
	return this->lives;
}
//lifes getter
void Rocket::set_lifes(int x)
{
	this->lives = x;
}
//set array of obj of fireballs
void Rocket::set_array(int x)
{
	size--;
	array = new fireBalls[size];
}
//return curren size of fireballs obj array
int Rocket::get_size()
{
	return this->size;
}

//class to handle welcome screen wining losing result showing and score lifes showing 
class welcomeScreen
{
public:
	void drawRocket();
	void start();
	void win();
	void board(int x);
private:
};
//draw rocket on display screen
void welcomeScreen::drawRocket()
{
	cout << "\n\n \t\t\t-: SPACE FIRING GAME :- \n\n\n";
	for (int i = 0; i <= 5; i++)
	{
		cout << std::setw(30);
		for (int j = (5 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= 2 * i; k++)
			cout << "*";
		cout << endl;
	}
	for (int i = 0; i <= 3; i++)
	{
		cout << std::setw(30);
		cout << " ";
		for (int i = 0; i <= 10; i++)
		{
			cout << "*";
		}
		cout << endl;
	}
	for (int i = 0; i <= 3; i++)
	{
		cout << std::setw(30);
		cout << " ";
		for (int i = 0; i <= 10; i++)
		{
			cout << "*";
		}
		cout << endl;
	}
	for (int i = 6; i <= 10; i++)
	{
		cout << std::setw(25);
		for (int j = (10 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= 2 * i; k++)
			cout << "*";
		cout << endl;
	}
	for (int i = 0; i <= 2; i++)
	{
		cout << std::setw(32);
		cout << " ";
		for (int i = 0; i < 2; i++)
		{
			cout << "*";
		}
		cout << std::setw(2);
		for (int i = 0; i < 2; i++)
		{
			cout << "*";
		}
		cout << std::setw(2);
		for (int i = 0; i < 2; i++)
		{
			cout << "*";
		}
		cout << endl;
	}
}
//take s input and start game
void welcomeScreen::start()
{
	cout << std::setw(33);
	cout << endl << endl;
	cout << "| ";
	cout << " START ";
	cout << " |";
	cout << endl << endl;
	cout << std::setw(50);
	cout << "Press S to start the game.";
	cout << endl << endl;
	char ch;
	ch = _getch();
	int ascii = ch;
	if (ascii == 115 || ascii ==83) {
		system("cls");
	}
}
//show winnig screen
void welcomeScreen::win()
{
	system("cls");
	cout << "YOU WINN!" << endl;
	cout << "score:: 60" << endl;
	exit(0);
}

//major spaceship abstract class
class  Spaceship
{
public:
	Spaceship();
	virtual void draw(int, int) = 0;
	virtual void fire(Rocket *);
	virtual void move(int);
	int getx();
	int gety();
	void set_xy(int, int);
	virtual void set_hits(int);
	virtual int gethits();
	virtual void clear(int, int);
	void dec_size();
	void set_array(int x);
	int get_size();
	int get_score();
	void set_score(int);
	bool get_cleared();
	void set_cleared(bool);
	void destroyed(int, int);
private:
	fireBalls* array;
	bool cleared;
	int size;
	int xloc;
	int yloc;
	int hits;
	static int score;
};
Spaceship::Spaceship()
{
	cleared = false; //tell weather spaceship is clered from screen or not
	xloc = 0;
	yloc = 0;
	hits = 0;
	size = 150;
}
//fire at rocket
void Spaceship::fire(Rocket* r)
{
	fireBalls f;
	f.draw(this->getx() + 2, this->gety() + 11);
	f.set_xy(this->getx() + 2, this->gety() + 11);
	bool clash_rocket = false;

	while (clash_rocket == false)
	{
		if (f.gety() < r->gety())
		{
			f.move(1);
			Sleep(20);
		}
		else if (f.gety() == r->gety())
		{
			if (f.getx() >= r->getx() - 1 && f.getx() <= r->getx() + 9)
			{
				if (r->get_hits() < 3)
				{
					r->set_hits(r->get_hits() + 1);
					f.clear(f.getx(), f.gety());
					f.set_xy(this->getx() + 2, this->gety() + 11);
				}
				else if (r->get_hits() == 3)
				{
					clash_rocket = true;
					r->set_hits(r->get_hits() + 1);
					f.clear(f.getx(), f.gety());
					r->set_lifes(r->get_lifes() - 1);
					f.set_xy(this->getx() + 4, this->gety() + 11);
					break;
				}
				else if (r->get_hits() > 3)
					break;
			}
			else if (f.getx() < r->getx() || f.getx() > r->getx() + 9)
			{
				f.clear(f.getx(), f.gety());
				f.set_xy(this->getx() + 2, this->gety() + 11);
				r->set_hits(r->get_hits() - r->get_hits());
				break;
			}

		}
		else if (f.gety() > r->gety())
		{
			f.clear(f.getx(), f.gety());
			f.set_xy(this->getx() + 2, this->gety() + 11);
			r->set_hits(r->get_hits() - r->get_hits());
		}
	}

	r->set_hits(r->get_hits() - r->get_hits());
	clash_rocket = false;
}
//move spaceships overrided function
void Spaceship::move(int y)

{
	clear(this->getx(), this->gety());
	this->set_xy(this->getx(), this->gety() + y);
	this->draw(this->getx(), this->gety());
}
//return x cor
int Spaceship::getx()
{
	return this->xloc;
}
//return y coor
int Spaceship::gety()
{
	return this->yloc;
}
//set x y coor
void Spaceship::set_xy(int xloc, int yloc)
{
	this->xloc = xloc;
	this->yloc = yloc;
}
//set hits
void Spaceship::set_hits(int x)
{
	this->hits = x;
}
//set y coor
int Spaceship::gethits()
{
	return this->hits;
}
//clear spaceships
void Spaceship::clear(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	for (int i = 0; i < 3; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(3);
		for (int j = (3 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= 2 * i; k++)
			cout << " ";
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(4);
		cout << " ";
		for (int i = 0; i <= 4; i++)
		{
			cout << " ";
		}
		cout << endl;
	}
	for (int i = 2; i <= 5; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(0);
		for (int j = (5 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= (2 * i); k++)
			cout << " ";
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(9);
		cout << "     ";
		cout << endl;
	}
}
//dec size of array of objs
void Spaceship::dec_size()
{
	this->size--;
}
//set array of objs
void Spaceship::set_array(int x)
{
	size--;
	array = new fireBalls[size];
}
//retuen size of array of objs
int Spaceship::get_size()
{
	return this->size;
}
//return score 
int Spaceship::get_score()
{
	return score;
}
//set score
void Spaceship::set_score(int x)
{
	this->score = x;
}
//tell if spaceship is present on screen or cleared
bool Spaceship::get_cleared()
{
	return cleared;
}
//set clearing status
void Spaceship::set_cleared(bool x)
{
	this->cleared = x;
}
//used to destroy rocket when it get hited by consective hits
void Spaceship::destroyed(int x, int y)
{
	this->set_cleared(true);
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	for (int i = 0; i < 3; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(3);
		for (int j = (3 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= 2 * i; k++)
			cout << " ";
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(4);
		cout << " ";
		for (int i = 0; i <= 4; i++)
		{
			cout << " ";
		}
		cout << endl;
	}
	for (int i = 2; i <= 5; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(0);
		for (int j = (5 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= (2 * i); k++)
			cout << " ";
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(9);
		cout << "     ";
		cout << endl;
	}
	this->set_xy(-100, -100);
}
int Spaceship::score = 0;


class  MartianShip : public Spaceship
{
public:
	MartianShip();
	void draw(int, int);
	void move(int y);
	void clear(int, int);
	void set_hits(int x);
	int gethits();
	void fire(Rocket *);
private:
	int hits;
};
//constructor
MartianShip::MartianShip()
{
	hits = 0;
}
//draw martianship
void MartianShip::draw(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	for (int i = 0; i < 3; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(3);
		for (int j = (3 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= 2 * i; k++)
			cout << "%";
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(4);
		cout << " ";
		for (int i = 0; i <= 4; i++)
		{
			cout << "%";
		}
		cout << endl;
	}
	for (int i = 2; i <= 5; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(0);
		for (int j = (5 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= (2 * i); k++)
			cout << "%";
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(9);
		cout << " : : ";
		cout << endl;
	}
}
//move martianship
void MartianShip::move(int y)
{
	clear(this->getx(), this->gety());
	this->set_xy(this->getx(), this->gety() + y);
	this->draw(this->getx(), this->gety());
}
//clear martian ship
void MartianShip::clear(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	for (int i = 0; i < 3; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(3);
		for (int j = (3 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= 2 * i; k++)
			cout << " ";
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(4);
		cout << " ";
		for (int i = 0; i <= 4; i++)
		{
			cout << " ";
		}
		cout << endl;
	}
	for (int i = 2; i <= 5; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(0);
		for (int j = (5 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= (2 * i); k++)
			cout << " ";
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(9);
		cout << "     ";
		cout << endl;
	}
}
//set hits of marship
void MartianShip::set_hits(int x)
{
	this->hits = x;
}
//get hits
int MartianShip::gethits()
{
	return this->hits;
}
//fire marianship at rocket
void MartianShip::fire(Rocket* r)
{
	fireBalls f;
	f.draw(this->getx() + 2, this->gety() + 11);
	f.set_xy(this->getx() + 2, this->gety() + 11);
	bool clash_rocket = false;

	while (clash_rocket == false)
	{
		if (f.gety() < r->gety())
		{
			f.move(1);
			Sleep(20);
		}
		else if (f.gety() == r->gety())
		{
			if (f.getx() >= r->getx()-1 && f.getx() <= r->getx() + 9)
			{
				if (r->get_hits() < 3)
				{
					this->set_array(get_size() - 1);
					r->set_hits(r->get_hits() + 1);
					f.clear(f.getx(), f.gety());
					f.set_xy(this->getx() + 2, this->gety() + 11);
				}
				else if (r->get_hits() == 3)
				{
					this->set_array(get_size() - 1);
					clash_rocket = true;
					r->set_hits(r->get_hits() + 1);
					f.clear(f.getx(), f.gety());
					r->set_lifes(r->get_lifes() - 1);
					f.set_xy(this->getx() + 4, this->gety() + 11);
					break;
				}
				else if (r->get_hits() > 3)
					break;
			}
			else if (f.getx() < r->getx() || f.getx() > r->getx() + 9)
			{
				this->set_array(get_size() - 1);
				f.clear(f.getx(), f.gety());
				f.set_xy(this->getx() + 2, this->gety() + 11);
				r->set_hits(r->get_hits() - r->get_hits());
				break;
			}

		}
		else if (f.gety() > r->gety())
		{
			this->set_array(get_size() - 1);
			f.clear(f.getx(), f.gety());
			f.set_xy(this->getx() + 2, this->gety() + 11);
			r->set_hits(r->get_hits() - r->get_hits());
		}
	}

	r->set_hits(r->get_hits() - r->get_hits());
	clash_rocket = false;
}

//small ship
class  StarShip : public Spaceship
{
public:
	StarShip();
	void draw(int x, int y);
	void clear(int, int);
	void fire(Rocket *);
	void move(int);
	void set_hits(int x);
	int gethits();
private:
	int hits;
};
//constructor
StarShip::StarShip()
{
	hits = 0;
}
//draw starship
void StarShip::draw(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "    " << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "    ^   " << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "   /*\\  " << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "  /***\\ " << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << " /*****\\" << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "*********" << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "\\*******/" << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << " \\*****/     " << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "  \\***/       " << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "   ====      " << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "   ::::     " << endl;
	CursorPosition.Y = y++;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "   ::::  " << endl;
}
//clear it
void StarShip::clear(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
	for (int i = 0; i < 3; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(3);
		for (int j = (3 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= 2 * i; k++)
			cout << " ";
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(4);
		cout << " ";
		for (int i = 0; i <= 4; i++)
		{
			cout << " ";
		}
		cout << endl;
	}
	for (int i = 2; i <= 5; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(0);
		for (int j = (5 - i); j >= 0; j--)
			cout << " ";
		for (int k = 0; k <= (2 * i); k++)
			cout << " ";
		cout << endl;
	}
	for (int i = 0; i < 2; i++)
	{
		CursorPosition.Y = y++;
		SetConsoleCursorPosition(console, CursorPosition);
		cout << std::setw(9);
		cout << "     ";
		cout << endl;
	}
}
//fire starship at rocket
void StarShip::fire(Rocket* r)
{
	fireBalls f;
	f.draw(this->getx() + 2, this->gety() + 11);
	f.set_xy(this->getx() + 2, this->gety() + 11);
	bool clash_rocket = false;

	while (clash_rocket == false)
	{
		if (f.gety() < r->gety())
		{
			f.move(1);
			Sleep(20);
		}
		else if (f.gety() == r->gety())
		{
			if (f.getx() >= r->getx()-1 && f.getx() <= r->getx() + 9)
			{
				if (r->get_hits() < 3)
				{
					this->set_array(get_size() - 1);
					r->set_hits(r->get_hits() + 1);
					f.clear(f.getx(), f.gety());
					f.set_xy(this->getx() + 2, this->gety() + 11);
				}
				else if (r->get_hits() == 3)
				{
					this->set_array(get_size() - 1);
					clash_rocket = true;
					r->set_hits(r->get_hits() + 1);
					f.clear(f.getx(), f.gety());
					r->set_lifes(r->get_lifes() - 1);
					f.set_xy(this->getx() + 4, this->gety() + 11);
					break;
				}
				else if (r->get_hits() > 3)
					break;
			}
			else if (f.getx() <  r->getx() || f.getx() > r->getx() + 9)
			{
				this->set_array(get_size() - 1);
				f.clear(f.getx(), f.gety());
				f.set_xy(this->getx() + 2, this->gety() + 11);
				r->set_hits(r->get_hits() - r->get_hits());
				break;
			}

		}
		else if (f.gety() > r->gety())
		{
			this->set_array(get_size() - 1);
			f.clear(f.getx(), f.gety());
			f.set_xy(this->getx() + 2, this->gety() + 11);
			r->set_hits(r->get_hits() - r->get_hits());
		}
	}
	
	r->set_hits(r->get_hits() - r->get_hits());
	clash_rocket = false;
}
//move starship
void StarShip::move(int y)
{
	clear(this->getx(), this->gety());
	this->set_xy(this->getx(), this->gety() + y);
	this->draw(this->getx(), this->gety());
}
//set hits
void StarShip::set_hits(int x)
{
	this->hits = x;
}
//get hits
int StarShip::gethits()
{
	return this->hits;
}
//fire by rocket at mship and sship
void Rocket::fire(Spaceship** s)
{
	welcomeScreen w;
	fireBalls f;
	StarShip ss;
	Spaceship* st;
	st = &ss;
	f.draw(this->getx() + 2, this->gety());
	f.set_xy(this->getx() + 2, this->gety());
	bool clash_ship = false;
	while (clash_ship == false)
	{
		if (f.gety() <= 1)
		{
			this->set_array(get_size() - 1);
			f.clear(f.getx(), f.gety());
			f.set_xy(this->getx() + 2, this->gety());
			break;
		}
		else f.move(-1);
		Sleep(20);
		for (int i = 0; i < 8; i++)
		{
			if (f.getx() <= s[i]->getx() + 11 && f.getx() >= s[i]->getx())
			{
				if (f.gety() <= s[i]->gety() + 11)
				{
					if (i % 2 == 0) {
						if (s[i]->gethits() + 1 < 5)
						{
							this->set_array(get_size() - 1);
							clash_ship = true;
							s[i]->set_hits(s[i]->gethits() + 1);
							f.clear(f.getx(), f.gety());
							f.set_xy(this->getx() + 2, this->gety());
						}
						else if (s[i]->gethits() + 1 == 5)
						{
							this->set_array(get_size() - 1);
							clash_ship = true;
							f.clear(f.getx(), f.gety());
							f.set_xy(this->getx() + 2, this->gety());
							st->set_score(st->get_score() + 10);
							if (st->get_score() >= 60)
								w.win();
							s[i]->destroyed(s[i]->getx(), s[i]->gety());
							break;
						}
						else break;
					}
					else if (i % 2 != 0) {
						if (s[i]->gethits() + 1 < 3)
						{
							this->set_array(get_size() - 1);
							clash_ship = true;
							s[i]->set_hits(s[i]->gethits() + 1);
							f.clear(f.getx(), f.gety());
							f.set_xy(this->getx() + 2, this->gety());
						}
						else if (s[i]->gethits() + 1 == 3) {
							this->set_array(get_size() - 1);
							clash_ship = true;
							f.clear(f.getx(), f.gety());
							f.set_xy(this->getx() + 2, this->gety());
							st->set_score(st->get_score() + 5);
							if (st->get_score() >= 60)
								w.win();
							s[i]->destroyed(s[i]->getx(), s[i]->gety());
							break;
						}

					}
				}
			}
			else
				s[i]->set_hits(s[i]->gethits() - s[i]->gethits());

		}
	}
	clash_ship = false;

}
//func of welcome class to show score and lives.
void welcomeScreen::board(int x)
{
	CursorPosition.X = 145;
	CursorPosition.Y = 2;
	StarShip ss;
	Spaceship* s = &ss;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "=============" << endl;
	CursorPosition.Y = 3;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << " lifes:" << x << endl;
	CursorPosition.Y = 4;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << " score: " <<s->get_score()  << endl;
	CursorPosition.Y = 5;
	SetConsoleCursorPosition(console, CursorPosition);
	cout << "=============" << endl;
}

int main()
{
	Rocket r;
	do{
		MartianShip m[4];
		StarShip s[4];
		Spaceship* ss[8] = { &m[0],&s[0],&m[1],&s[1],&m[2],&s[2],&m[3],&s[3] };
		const int KEY_ARROW_CHAR1 = 224;
		const int KEY_ARROW_UP = 72;
		const int KEY_ARROW_DOWN = 80;
		const int KEY_ARROW_LEFT = 75;
		const int KEY_ARROW_RIGHT = 77;
		int asci;
		welcomeScreen w;
		w.drawRocket();
		w.start();
		cout << endl << endl;
		int x = 0; int j = 0;
		//draw spaceships on screen move them slightly
		for (int b = 0; b < 3; b++)
		{
			for (int i = 0; i < 8; i++) {
				ss[i]->draw(0 + x, j);
				ss[i]->set_xy(x, j);
				x += 15;
			}
			j += 1;
			x = 0;
			Sleep(300);
			if (b != 2)system("cls");
		}
		int xcor[8];
		for (int i = 0; i < 8; i++)
		{
			if (i % 2 == 0) xcor[i] = m[i].getx() + 11;
			if (i % 2 != 0) xcor[i] = m[i].getx() + 8;

		}
		srand(time(0));
		r.draw(40, 30);
		r.set_xy(40, 30);
		w.board(r.get_lifes());
		fireBalls f;
		f.set_xy(r.getx() + 2, r.gety());
		//testing move functions
		//move function is defined for both classes and move it by indicated number along y axis.as it was not required to move them
		//continously so if you wnnna test them do move any spaceship as:: obj.move(int)  obj is any obj int is number to move up or down.
		s[0].move(2);
		Sleep(1000);
		m[3].move(3);
		Sleep(1000);
		while (1)
		{
			unsigned char ch1 = _getch();
			asci = ch1;
			if (ch1 == KEY_ARROW_CHAR1)
			{
				unsigned char ch2 = _getch();
				switch (ch2)
				{
				case KEY_ARROW_UP:
					if (r.gety() - 3 < 0) {
						//1
					}
					else {
						r.move(1);
						f.set_xy(r.getx() + 2, r.gety());
					}
					break;
				case KEY_ARROW_DOWN:
					r.move(2);
					f.set_xy(r.getx() + 2, r.gety());
					break;
				case KEY_ARROW_LEFT:
					if (r.getx() - 3 < 0) {
						//1
					}
					else {
						r.move(3);
						f.set_xy(r.getx() + 2, r.gety());
					}
					break;
				case KEY_ARROW_RIGHT:
					if (r.getx() + 3 > 159) {
						//1
					}
					else {
						r.move(4);
						f.set_xy(r.getx() + 2, r.gety());
					}
					break;
				}

			}

			if (asci == 102 ||asci==70)
			{
				//if size of firebalss obj array is greater tahn zero do fire else end game.
				if (r.get_size() > 0) {
					r.fire(ss);
				}
				else {
					system("cls");
					cout << "fireballs ended";
					exit(0);
				}
			}
			//display lifes and score
			w.board(r.get_lifes());
			int store;
			//if lifes have not ended do fire if lifes are zero end game
			//when a life is ended do restart by printing restart etc
			if ((rand() % 10) % 7 == 0)
			{
				 store = r.get_lifes();
				   if (r.get_lifes() > 0)
					{
					   for (int i = 0; i < 8; i++) {
						   ss[i]->set_hits(0);
					   }
					   for (int i = 0; i < 4; i++)
					   {
						   if (s[i].getx() != -100) 
						   {
							  // if (s[i].get_cleared() == false)
							   s[i].fire(&r);
						   }
					   }
				   } 
				   if (r.get_lifes() < store)
				   {
					   if (r.get_lifes() != 0)
					   {
						   system("cls");
						   cout << "restarting" << endl;
						   break;
					   }
				   }
				   if (r.get_lifes() == 0) {
					   system("cls");
					   cout << "you losed all lifes!";
					   exit(0);
				   }

					
			}
			if ((rand() % 10) % 6 == 0)
					{
						store = r.get_lifes();
						for (int i = 0; i < 8; i++) {
							ss[i]->set_hits(0);
						}

						if (r.get_lifes() > 0)
						{
							for (int i = 0; i < 4; i++)
							{
								if (m[i].getx() != -100)
								{
									//if (m[i].get_cleared() == false)
									m[i].fire(&r);
								}
							}
						}
						if (r.get_lifes() < store)
						{
							if (r.get_lifes() != 0)
							{
								system("cls");
								cout << "restarting" << endl;
								break;
							}
						}
						if (r.get_lifes() == 0) {
							system("cls");
							cout << "you losed all lifes!";
							exit(0);
						}

					}
			//display board
			w.board(r.get_lifes());
			cout << endl;
			cout << endl;
		}
	}
	while (r.get_lifes() != 0);
	return 0;
}
// i have assumed some generall thing which were not restricted
//1. score presists among lifes of user i e when it restarts score from previous life is not lost 
//2.you can cont after 100 fireballs from rocket gam ends with respective msg .
//3.for quick check got to class constructor set size to any smaller value i e 5 asnd game will end after 5 fireballs from user 
//4. i have not restricted the fireballs of spaceships just decremented their size.score 60 to win the game
//kindly do not change the sequence of functions and classes as they are interdependent so it will disturb flow of execution
//mam allowed to do single file programing.
//Due to use of random functions winnig this game is quite bit difficult :)
//play with patience and press keys garadully otherwise overlapping pattrens and strange behaviour is shown so plzzzzz use it with patience
//pressing multiple f keys and any other results in lose of lifes not destruction of ships.
