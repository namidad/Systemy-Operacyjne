#include "snake.h"
#include <unistd.h>
#include <mutex>
#include <chrono>

std::mutex mx;

snakePart::snakePart(int col,int row){
	x=col;
	y=row;
	
}
snakeClass::snakeClass(){
}

void snakeClass::start2(int minw2, int minh2, int maxw2, int maxh2){
	mx.lock();
	srand(time(NULL));
	bool tru=true;
	minw=minw2;
	maxw=maxw2;
	minh=minh2;
	maxh=maxh2;
	direction='s';
	//na koniec wektora snake dodaje kolejny element, ktory jest struktura
	for(int i=0;i<7;i++){
	snake.push_back(snakePart((maxw-20)-i,(maxh/2)+5));	
	}

	for(int i=0;i<7;i++){
	//przenies kursor na wspolrzedne X Y danego elementu w strukturze
	move(snake[i].y,snake[i].x);

	//wstaw znak X, z ktorego waz jest poczatkowo zbudowany
	addch('x');	
	}
	//odswiez okno aby zobaczyc zmiany
	refresh();
	mx.unlock();	
	while(true){
	moveSnake();	
}


	
}
bool snakeClass::collision(int d){
	
	int snakeX=snake[0].x;
	int snakeY=snake[0].y;
	int a,b,c,de;
	a=minw+1;
	b=maxw-1;
	c=minh+1;
	de=maxh-1;
	//zalezy od potencjalnego kierunku
	if(d==0){
		snakeY--;
	}else if(d==1){
		snakeX++;
	}else if(d==2){
		snakeY++;
	}else if(d==3){
		snakeX--;
	}
	//jezeli ktoras wspolrzedna dotknie brzegu zwroc true
	if(snakeX==a || snakeX==b || snakeY==c || snakeY==de){
		return true;
	} 
	
	//jezeli poprzednie warunki nie zostaly spelnione, zwroc false i przypisz kierunek, ktory wywolal funkcje
	return false;
}

bool snakeClass::collision2(int d){
	
	int snakeX=snake[0].x;
	int snakeY=snake[0].y;
	//zalezy od potencjalnego kierunku
	if(d==0){
		snakeY--;
	}else if(d==1){
		snakeX++;
	}else if(d==2){
		snakeY++;
	}else if(d==3){
		snakeX--;
	}

	//jezeli waz wejdzie w siebie samego zwroc true | sprawdzamy od 3 elementu
	for(int i=2;i<snake.size();i++){
		if(snakeX==snake[i].x && snakeY==snake[i].y){
		return true;
		}
	}
	return false;

}

void snakeClass::moveSnake(){
	usleep(10000);
	std::unique_lock<std::mutex>lock(mx);
	int usleep(useconds_t useconds);

	
	losuj:
	kierunek = rand() % 4; // wylosuj kierunek od 0 - 3 
	//0-north 1-east 2-south 3-west

	//sprawdzamy czy wejdzie w samego siebie
	if(collision2(kierunek)){
	goto losuj;
	}

	//sprawdzamy wszystkie mozliwosci uderzenia w sciany 
	if((kierunek==0) && (direction!='s')){
		if(collision(kierunek)){
			if(collision(1)){
				direction='w';
			}else direction='e';
		}else direction='n';
	}else if((kierunek == 1) && (direction!='w')){
		if(collision(kierunek)){
			if(collision(0)){
				direction='s';
			}else direction='n';
		}else direction='e';
	}else if((kierunek == 2) && (direction !='n')){
		if(collision(kierunek)){
			if(collision(1)){
				direction='w';
			}else direction='e';
		}else direction='s';
	}else if((kierunek == 3) && (direction !='e')){
		if(collision(kierunek)){
			if(collision(0)){
				direction='s';
			}else direction='n';
		}else direction='w';
		
	}else goto losuj;
	//aby widziec efekty poruszania sie
	
	//przenosimy kursor na ostatni element weza
	move(snake[snake.size()-1].y, snake[snake.size()-1].x);
	//zamiast znaku wypelniamy terminal pustym polem
	printw(" ");//X->" "
	//odswiezamy
	refresh();
	//usuwamy ostatni element w wektorze
	snake.pop_back();

	//w zaleznosci od koncowego kierunku dodajemy nowy element w wektorze na poczatek - głowa
	//n-north-0 e-east-1 s-south-2 w-west-3
	switch(direction){
	case 'n':	
		snake.insert(snake.begin(), snakePart(snake[0].x,snake[0].y-1));
		break;
	case 'e':
		snake.insert(snake.begin(), snakePart(snake[0].x+1,snake[0].y));
		break;
	case 's':
		snake.insert(snake.begin(), snakePart(snake[0].x,snake[0].y+1));
		break;
	case 'w':
		snake.insert(snake.begin(), snakePart(snake[0].x-1,snake[0].y));
		break;
	default:
		break;
	}
	//losujemy nowy znak
	znak=(rand() % 92)+33;
	//ustaw kursor na wspolrzedne nowego elementu w wektorze
	move(snake[0].y,snake[0].x);
	//dodaj znak
	addch(znak); 
	refresh();

}




snakeClass::~snakeClass(){

}












