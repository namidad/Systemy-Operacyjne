#include "tetris.h"
#include <unistd.h>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <thread>

std::mutex mx;
std::mutex mxd;
std::condition_variable cv;

std::vector<char> tetrisGlobalny;
tetrisPart::tetrisPart(int col,int row){
	x=col;
	y=row;
	
}

tetrisClass::tetrisClass(){


}

void tetrisClass::printBlock(){


	int randX,randY;
	int roznica1=maxw-minw-5;
	int roznica2=maxh-minh-5;
	randX = (rand() % roznica1) + minw;
	randY = (rand() % roznica2) + minh;
	if(randX>=minw) randX+=1;
	if(randX>=maxw) randX-=2;
	if(randY>=minh) randY+=1;
	if(randY>=maxh) randY-=2;
	
		for(int i=0;i<tetrisGlobalny.size();i++){
			
			switch(tetrisGlobalny[i]){
				case 'g':
				randY--;
				if(randY>minh){
				tetris.push_back(tetrisPart(randX,randY));
				move(tetris[tetris.size()-1].y, tetris[tetris.size()-1].x);
				printw("#");
				
				}else goto wyjscie;
				break;
				case 'p':
				randX++;
				if(randX<=maxw+2){
				tetris.push_back(tetrisPart(randX,randY));
				move(tetris[tetris.size()-1].y, tetris[tetris.size()-1].x);
				printw("#");
				
				} else goto wyjscie;
				break;
				case 'd':
				randY++;
				if(randY<=maxh+2){
				tetris.push_back(tetrisPart(randX,randY));
				move(tetris[tetris.size()-1].y, tetris[tetris.size()-1].x);
				printw("#");
				
				} else goto wyjscie;
				break;
				case 'l':
				randX--;
				if(randX>minw){
				tetris.push_back(tetrisPart(randX,randY));
				move(tetris[tetris.size()-1].y, tetris[tetris.size()-1].x);
				printw("#");
				
				} else goto wyjscie;
				break;
			}
		

	}

	wyjscie:
	refresh();
	while(tetrisGlobalny.size()>0){
	tetrisGlobalny.erase(tetrisGlobalny.begin());
	}
	
}
void tetrisClass::createTerminal(int minw2, int minh2, int maxw2, int maxh2){
	mxd.lock();
	minw=minw2;
	maxw=maxw2;
	minh=minh2;
	maxh=maxh2;
	mxd.unlock();
	while(true){
	std::unique_lock<std::mutex> lock(mx);
	cv.wait(lock);
	tetrisClass::printBlock();
	}

	

}

bool tetrisClass::collision(){
	
	int tetrisX;
	int tetrisY;
	bool cos=false;
	int a,b,c,de;
	a=minw+2;
	b=maxw;
	c=minh;
	de=maxh;
	for(int i=0;i<5;i++){
	tetrisX=tetris[i].x;
	tetrisY=tetris[i].y+1;
	if(tetrisX==a || tetrisX==b || tetrisY==c || tetrisY==de){
		cos=true;
	}
	}
	return cos;

}


void tetrisClass::moveBlock(){
	//std::lock_guard<std::mutex> lock(mxd);
	bool czy=true;
	while(czy){
	if(collision()){
	for(int i=4;i>=0;i--){
	move(tetris[i].y, tetris[i].x);
	printw(" ");//X->" "
	tetris.pop_back();
	}
	refresh();
	czy=false;
	}else {
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	
	for(int i=0;i<5;i++){
	move(tetris[i].y, tetris[i].x);
	tetris[i].y=tetris[i].y+1;
	printw(" ");//X->" "
	}
	for(int i=0;i<5;i++){
	move(tetris[i].y, tetris[i].x);
	addch('X');
	}
	refresh();
	}	
	}

}




void tetrisClass::firstWindow(int minw2, int minh2, int maxw2, int maxh2){
	mxd.lock();
	minw=minw2;
	maxw=maxw2;
	minh=minh2;
	maxh=maxh2;
	mxd.unlock();
	do{
	tetrisClass::randomBlock();
	tetrisClass::moveBlock();
	std::unique_lock<std::mutex> lock(mx);
	cv.notify_one();
	}while(getch()!=27);


}


void tetrisClass::randomBlock(){
	std::lock_guard<std::mutex> lock(mxd);
	int xx=(maxw-minw)/2;
	int yy=5;
	int wybor= ( std::rand() %4 ) + 1;

	switch(wybor){
		case 1:
		tetrisGlobalny.push_back('p');
		tetrisGlobalny.push_back('p');
		tetrisGlobalny.push_back('p');
		tetrisGlobalny.push_back('d');
		tetrisGlobalny.push_back('d');
		tetris.push_back(tetrisPart(xx,yy));
		tetris.push_back(tetrisPart(++xx,yy));
		tetris.push_back(tetrisPart(++xx,yy));
		tetris.push_back(tetrisPart(xx,++yy));
		tetris.push_back(tetrisPart(xx,++yy));
		for(int i=0;i<5;i++){
		move(tetris[i].y,tetris[i].x);
		addch('X');
		}
		refresh();
		break;
		case 2:
		tetrisGlobalny.push_back('l');
		tetrisGlobalny.push_back('l');
		tetrisGlobalny.push_back('l');
		tetrisGlobalny.push_back('d');
		tetrisGlobalny.push_back('d');
		tetris.push_back(tetrisPart(xx,yy));
		tetris.push_back(tetrisPart(--xx,yy));
		tetris.push_back(tetrisPart(--xx,yy));
		tetris.push_back(tetrisPart(xx,++yy));
		tetris.push_back(tetrisPart(xx,++yy));
		for(int i=0;i<5;i++){
		move(tetris[i].y,tetris[i].x);
		addch('X');
		}
		refresh();
		break;
		case 3:
		tetrisGlobalny.push_back('d');
		tetrisGlobalny.push_back('d');
		tetrisGlobalny.push_back('d');
		tetrisGlobalny.push_back('p');
		tetrisGlobalny.push_back('p');
		tetris.push_back(tetrisPart(xx,yy));
		tetris.push_back(tetrisPart(xx,++yy));
		tetris.push_back(tetrisPart(xx,++yy));
		tetris.push_back(tetrisPart(++xx,yy));
		tetris.push_back(tetrisPart(++xx,yy));
		for(int i=0;i<5;i++){
		move(tetris[i].y,tetris[i].x);
		addch('X');
		}
		refresh();
		break;
		case 4:
		tetrisGlobalny.push_back('d');
		tetrisGlobalny.push_back('d');
		tetrisGlobalny.push_back('d');
		tetrisGlobalny.push_back('l');
		tetrisGlobalny.push_back('l');
		tetris.push_back(tetrisPart(xx,yy));
		tetris.push_back(tetrisPart(xx,++yy));
		tetris.push_back(tetrisPart(xx,++yy));
		tetris.push_back(tetrisPart(--xx,yy));
		tetris.push_back(tetrisPart(--xx,yy));
		for(int i=0;i<5;i++){
		move(tetris[i].y,tetris[i].x);
		addch('X');
		}
		refresh();
		break;
	}
		
	
	
}


tetrisClass::~tetrisClass(){

}
