/*
 queue that keesp track coordinates of all the body segments and the head 
 we constantly update the "path" so theres a distance between 
 the tail and the head, for each time the head moves
 the tail moves, keeping a constant distance (body)
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

#define W 20
#define H 10

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define FOOD 'O'
#define BORDER '*'
#define BG ' '
#define BODY_SEGMENT '#'
#define TAIL 't'
#define EXIT 'q'

typedef enum bool {
	true = 1, false = 0
} bool;
 
struct {
	bool has_body;
	bool has_tail;
	char head_state;
	int head_x;
	int head_y;
	int tail_x;
	int tail_y;
} Snake = {false, false, '>', 1, 1, 0, 0};

char key;
char map[H][W];
int count = 0;
int status = 0;
Queue path = {NULL, NULL};
 
void move();
void getKey();
void setup();
void printMap();
int getRand(int start, int end);
void spawnFood();
   
int main() {
	setup();
	while(status != 1) {
		system("cls");
		printMap(); // print map 
		getKey();
		move();     // updates, which reflects inmeadetly on the next interation
	}
	printf("Game over...\n");
	return 0; 
}


void move() {
	int pre_x = Snake.head_x;
	int pre_y = Snake.head_y;
	switch(key) {
		case UP:{
			Snake.head_y--;
			Snake.head_state = '^';
			break;
		}
		case DOWN:{
			Snake.head_y++;
			Snake.head_state = 'v';
			break;
		}
		case LEFT:{
			Snake.head_x--;
			Snake.head_state = '<';
			break;
		}
		case RIGHT:{
			Snake.head_x++;
			Snake.head_state = '>';
			break;
		}
		default:
			return;
	}
	if(map[Snake.head_y][Snake.head_x] == BORDER || map[Snake.head_y][Snake.head_x] == BODY_SEGMENT) {
		status = 1;
		return;
	}
	
	// we construct the distance or path between the head and the tail and define its structure trough coordinates
	// the tail needs to be in each part of the body eventually, this is achived by saving coordinates
	
	if(map[Snake.head_y][Snake.head_x] == FOOD) {  // grows 
		if(Snake.has_tail){       // growing with a tail ensures adding at least +1 body segment
			map[pre_y][pre_x] = BODY_SEGMENT;
			Snake.has_body = true;
		} else {
			map[pre_y][pre_x] = TAIL;
			Snake.tail_x = pre_x; // first pos of the tail; before the head eats the first food 
			Snake.tail_y = pre_y;
			Snake.has_tail = true;
		}
		enq(&path, Snake.head_x, Snake.head_y);
		count++;
		spawnFood();
	} else { // moves
		// request the queue the next step for the tail
		if(Snake.has_tail) {   
			map[Snake.tail_y][Snake.tail_x] = BG; // current pos of the tail 
			Snake.tail_x = path.front->coord[0];
			Snake.tail_y = path.front->coord[1];
			map[Snake.tail_y][Snake.tail_x] = TAIL; // next pos of the tail , for next movement
			deq(&path);
			enq(&path, Snake.head_x, Snake.head_y); 

			if(Snake.has_body) 
				map[pre_y][pre_x] = BODY_SEGMENT;
		} else
			map[pre_y][pre_x] = BG;
	}
	map[Snake.head_y][Snake.head_x] = Snake.head_state;
} 

void getKey() {
	scanf("%c", &key);
	int c;
	while((c=getchar()) != '\n'); // cleans the input buffer 
	if(key == EXIT)
		status = 1;
}

void setup() {
	srand(time(NULL));
	for(int i = 0; i < H; i++) {
		for(int j = 0; j < W; j++) {
			if(i == 0 || i == H-1) 
				map[i][j] = BORDER;
			else if (j == 0 || j == W-1)
				map[i][j] = BORDER;
			else 
				map[i][j] = BG;
		}
	}
	map[Snake.head_y][Snake.head_x] = Snake.head_state;
	spawnFood();
}

void printMap() {
	for(int i = 0; i < H; i++) {
		for(int j = 0; j < W; j++) {
			if(map[i][j] == TAIL){
				printf("%c ", BODY_SEGMENT);
			} else {
				printf("%c ", map[i][j]);
			}
		}
		putchar('\n');
	}
	printf(">> Points: %d\n", count);
	printf(">> Exit: q\n", count);
}

int getRand(int start, int end) {
	return rand() % (end-start) + start;
}

void spawnFood() {
	int rand_x = getRand(1, W-1);
	int rand_y = getRand(1, H-1);
	map[rand_y][rand_x] = FOOD; 
}
