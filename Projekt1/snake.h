#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
//struktura zawierajaca pojedyncza czesc weza
struct snakePart{
	int x,y;
	snakePart(int col,int row);

};

class snakeClass{
	//rozmiary okna, w ktorym waz sie porusza || potencjalny kierunek weza
	int minw,minh, maxw, maxh,kierunek;
	//kierunek w ktorym obecnie porusza sie waz N/E/S/W oraz znak na nowa czesc
	char direction,znak;
	//wektor, w ktorym znajduja sie kolejne czesci weza
	std::vector<snakePart> snake;
	//sprawdza czy w nastepnym ruchu wystapi kolizja
	bool collision(int d);
	bool collision2(int d);
public:

	snakeClass();
	//funkcja, ktora rozpoczyna dzialanie programu
	void start2(int minw2, int minh2, int maxw2, int maxh2);
	~snakeClass();
	//porusz wezem
	void moveSnake();
};


