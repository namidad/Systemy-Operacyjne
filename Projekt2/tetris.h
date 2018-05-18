#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
//struktura zawierajaca pojedyncza czesc weza

struct tetrisPart{
	int x,y;
	tetrisPart(int col,int row);

};

extern std::vector<char> tetrisGlobalny;

class tetrisClass{
	//rozmiary okna, w ktorym klocki sie znajduja || potencjalny kierunek weza
	int minw,minh, maxw, maxh,rozmiar;
	//wektor, w ktorym znajduja sie kolejne czesci weza
	std::vector<tetrisPart> tetris;
	//sprawdza czy w nastepnym ruchu wystapi kolizja
public:
	tetrisClass();
	//funkcja, ktora rozpoczyna dzialanie programu
	void start2(int, int, int , int);
	~tetrisClass();
	//porusz klockiem
	void createTerminal(int, int, int , int);
	//stworz okienko
	void printBlock();
	void moveBlock();
	// kolizja
	void randomBlock();
	void firstWindow(int, int, int , int);
	bool collision();
};


