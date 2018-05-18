#include "tetris.h"
#include <thread>
#include <vector>

int main(){	
	//stworzenie okna
	initscr();
	int delay,maxwidth,maxheight;
	nodelay(stdscr,true); // getch nie czeka na nacisniecie przycisku
	keypad(stdscr,true);
	noecho();
	curs_set(0);
	getmaxyx(stdscr,maxheight,maxwidth);
	
	delay=110000;
	bool get=false;
	srand(time(0));
	//podzial terminala na 4 czesci
	//linie przez srodek
	for(int i=0;i<maxwidth-1;i++){
		move(i,maxwidth/2);
		addch('X');
	}
	
	for(int i=0;i<maxwidth-1;i++){
		
		move(maxheight/2,i);
		addch('X');
	}
	
	
	//linie brzegowe

	for(int i=0; i<maxheight-1;i++){
		move(i,0);
		addch('X');
	}
	for(int i=0; i<maxwidth-1;i++){
		move(0,i);
		addch('X');
	}

	for(int i=0; i<maxwidth; i++){
		move(maxheight-1,i);
		addch('X');
	}
	for(int i=0;i<maxheight;i++){
		move(i,maxwidth-1);
		addch('X');
	}
	refresh();
		
	tetrisClass tet1,tet2,tet3,tet4;
	std::vector<std::thread> threads;

	threads.push_back(std::thread (&tetrisClass::createTerminal,&tet3,0,maxheight/2,maxwidth/2,maxheight));
	threads.push_back(std::thread (&tetrisClass::createTerminal,&tet2,maxwidth/2,0,maxwidth,maxheight/2));
	threads.push_back(std::thread (&tetrisClass::createTerminal,&tet4,maxwidth/2,maxheight/2,maxwidth,maxheight));
	threads.push_back(std::thread (&tetrisClass::firstWindow,&tet1,0,0,maxwidth/2,maxheight/2));
	for(auto& thread : threads){
		thread.join();
	}	
	

	
	nodelay(stdscr,false);
	getch();
	endwin();
	return 0;

}
