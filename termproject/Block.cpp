#include "Block.h"
#include "myio.h"
#include "GameLogic.h"
#include <stdlib.h>
#include <time.h>

#define Z COLOR_RED	
#define S COLOR_GREEN	
#define O COLOR_BROWN
#define J COLOR_BLUE	

const int Block::RIGHT=WIDTH-1;
const int Block::LEFT=0;
const int Block::BOTTOM=HEIGHT+1;
const int Block::TOP=0;
int Block::colors[5] = {0,0,0,0,0};


const char * Block::BLOCK = "[]";
const char * Block::CLEAR = "  ";

const Point Block::block_shape[][4][5] = {
{
                { { 0, 1 }, { 1, 1 }, {1,1  }, {1,1 }, { 1, 2 } },
                { { 1, 2 }, { 1, 1 }, {1,1  }, {1,1 }, { 2, 1 } },
                { { 2, 1 }, { 1, 1 }, {1,1  }, {1,1 }, { 1, 0 } },
                { { 1, 0 }, { 1, 1 }, {1,1  }, {1,1 }, { 0, 1 } } //fold
},{
                { { 0, 1 }, { 1, 1 }, {1,1  }, {1,1 }, { 1, 2 } },
                { { 1, 2 }, { 1, 1 }, {1,1  }, {1,1 }, { 2, 1 } },
                { { 2, 1 }, { 1, 1 }, {1,1  }, {1,1 }, { 1, 0 } },
                { { 1, 0 }, { 1, 1 }, {1,1  }, {1,1 }, { 0, 1 } } //fold
},{
                { { 0, 1 }, { 1, 1 }, { 1, 1 }, { 1 , 1 }, { 2, 1 } },
                { { 1, 2 }, { 1, 1 }, { 1, 1 }, { 1 , 1 }, { 1, 0 } },
                { { 2, 1 }, { 1, 1 }, { 1, 1 }, { 1 , 1 }, { 0, 1 } },
                { { 1, 0 }, { 1, 1 }, { 1, 1 }, { 1 , 1 }, { 1, 2 } } //tree
}, {
                { { 0, 1 }, { 1, 2 }, { 1, 1 }, { 1 , 0 } ,{ 2, 1 } },
                { { 1, 2 }, { 2, 1 }, { 1, 1 }, { 0 , 1 } ,{ 1, 0 } },
                { { 2, 1 }, { 1, 0 }, { 1, 1 }, { 1 , 2 } ,{ 0, 1 } },
                { { 1, 0 }, { 0, 1 }, { 1, 1 }, { 2 , 1 } ,{ 1, 2 } }// cross
} };
 

Block::Block() {
	int k=0;
	srand((unsigned int)time(0));
	for(int i = 0 ; i < 5; i++){
		k = rand()%4;
		colors[i] = k;
	}
	init(k);
}

Point Block::zero = Point();

Block::Block(int type) {
	init(type%4);
}

Block::~Block() {

}
void Block::init(int type) {
	stat = 0;

	shape[0] = Block::block_shape[colors[0]][stat][0];
        shape[1] = Block::block_shape[colors[1]][stat][1];
        shape[2] = Block::block_shape[colors[2]][stat][2];
        shape[3] = Block::block_shape[colors[3]][stat][3];
        shape[4] = Block::block_shape[colors[4]][stat][4];
	color += 41;

	for(int i =0; i<5; i++){
                colors[i] += 41;
        }


	current.x = LEFT + 2;
	current.y = TOP;
	prev = current;
	checkBound();
}

void Block::transpose() {
	int s = color -41;
	
	 for(int i =0; i<5; i++){
               colors[i] -= 41;
        }

	
	stat = (stat + 1) % 4;
	shape[0] = Block::block_shape[colors[0]][stat][0];
        shape[1] = Block::block_shape[colors[1]][stat][1];
        shape[2] = Block::block_shape[colors[2]][stat][2];
        shape[3] = Block::block_shape[colors[3]][stat][3];
        shape[4] = Block::block_shape[colors[4]][stat][4];
	

	checkBound();
	for(int i =0; i<5; i++){
                colors[i] += 41;
        }

}
void Block::reversTranspose() {

	int s = color -= 41;

	for(int i =0; i<5; i++){
               colors[i] -= 41;
        }

	stat = (stat + 3) % 4;
	shape[0] = Block::block_shape[colors[0]][stat][0];
        shape[1] = Block::block_shape[colors[1]][stat][1];
        shape[2] = Block::block_shape[colors[2]][stat][2];
        shape[3] = Block::block_shape[colors[3]][stat][3];
        shape[4] = Block::block_shape[colors[4]][stat][4];
	

	checkBound();
	for(int i =0; i<5; i++){
                colors[i] += 41;
        }

}

void Block::moveUp() {

	if (current.y > TOP)
		current.y--;
}

void Block::moveDown() {

	if (current.y + bottom < BOTTOM)
		current.y++;

}
void Block::moveRight() {
	if (current.x + right < RIGHT)
		current.x++;
}
void Block::moveLeft() {
	if (current.x + left > LEFT)
		current.x--;

}
void Block::print() {
	for (int i = 0; i < 5; i++) {
		printColorString(shape[i].x * 2 + current.x * 2 + zero.x, shape[i].y + current.y + zero.y, colors[i], BLOCK);
	}
	prev = current;
}
void Block::clear() {
	for (int i = 0; i < 5; i++) {
		printColorString(shape[i].x * 2 + prev.x * 2 + zero.x, shape[i].y + prev.y + zero.y, COLOR_DEFAULT, CLEAR);
	}
}

void Block::refresh() { // 삭제 출력 이전걸현재로 바꿈

	clear();
	print();
	prev = current;
}

void Block::print(int x, int y) {
	for (int i = 0; i < 5; i++) {
		printColorString(shape[i].x * 2  + x , shape[i].y  + y , colors[i], BLOCK);
	}
}

void Block::clear(int x, int y) {
	for (int i = 0; i < 5; i++) {
		printColorString(shape[i].x * 2 + x , shape[i].y  + y , COLOR_DEFAULT, CLEAR);
	}
}

void Block::checkBound() {
	int maxX = -10, minX = 10, maxY = -10;

	for (int i = 0; i < 5; i++) {
		if (shape[i].x > maxX) {
			maxX = shape[i].x;
		}
		if (shape[i].x < minX) {
			minX = shape[i].x;
		}
		if (shape[i].y > maxY) {
			maxY = shape[i].y;
		}
	}
	left = minX;
	right = maxX;
	bottom = maxY;
}
