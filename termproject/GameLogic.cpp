#include "GameLogic.h"
#include <stdio.h>
#include "myio.h"
#include "Block.h"
#include <time.h>
int z =0;

GameLogic::GameLogic() {
	for (int i = 0; i < HEIGHT + 1; i++) {
		board[i] = new char[WIDTH];
		for (int j = 0; j < WIDTH; j++) {
			board[i][j] = 0;
		}
	}
	for (int j = 0; j < WIDTH; j++) {
		board[HEIGHT][j] = 1;
	}

	isRun = true;
	Block::zero.x = 6;
	Block::zero.y = 2;
}

GameLogic::~GameLogic() {
	
	for (int i = 0; i < HEIGHT + 1; i++) {
		delete board[i];
	}
}

void GameLogic::start() {
	isNotGameOver=true;
	block = Block();
	next = Block();
	score = 0;
	interval = 105000;
	level = 1;
	refresh();
	int n;
	unsigned char key;
	clock_t refresh1 = clock();
	clock_t current = refresh1;
	clock_t blockDown = refresh1;


	while (isNotGameOver) {
		

		current = clock();
		if (current - refresh1 > 16000) {
			refresh1 = current;
			printBlock();
			
			
		}
		n = getchar();
		if(z==0){
			transforse();
			z++;
		}
		if (n != EOF) {
			

			key = n;
			
			switch (key) {
			case 'q':
				isNotGameOver=false;
				this->isRun = false;
				break;
			case 'e':
				transforse();
				break;
			case 's':
				moveDown();
				break;
			case 'd':
				moveRight();
				break;
			case 'a':
				moveLeft();
				break;
			case 'x':
				drop();
				
				break;
			default:
				break;
			}
			
		}
		gotoxy(80, 24);
		
	}
}

void GameLogic::printBlock() {
	block.refresh();
}

void GameLogic::moveDown() {
	block.moveDown();
	if (isCollision()) {
		block.moveUp();
		//보드에 저장
		for (int i = 0; i < 5; i++) {
			board[block.current.y + block.shape[i].y][block.current.x + block.shape[i].x] = block.colors[i];
		}
		nextTurn();
	}

}
void GameLogic::moveLeft() {
	block.moveLeft();
	if (isCollision())
		block.moveRight();
}

void GameLogic::moveRight() {
	block.moveRight();
	if (isCollision())
		block.moveLeft();
}

void GameLogic::transforse() {
	Block temp = block;
	block.transpose();
	if (isCollision()) {
		block.reversTranspose();
	} else {
		temp.clear();
		block.print();
	}
}

void GameLogic::drop() {

//	for (int x = 0; x < WIDTH; x++) {
 //               for (int y = 0; y < HEIGHT; y++) {
//                        board[y][x] = 0;
//	if(board[HEIGHT-1][0] == 0 && board[HEIGHT-2][0] != 0 ){
//		board[HEIGHT-2][0] = 0;
		
//		board[HEIGHT-1][0] = block.colors[1];
//		printColorString(HEIGHT-8, WIDTH-2, 42,"[]");
//	}
		
	
	while (!isCollision()){
		block.moveDown();
			
	}
	block.moveUp();
	z--;
	nextTurn();
}

bool GameLogic::isCollision() {
	int x, y;
	for (int i = 0; i < 5; i++) {
		x = block.current.x + block.shape[i].x;
		y = block.current.y + block.shape[i].y;

		if (x >= WIDTH || y > HEIGHT || x < 0) {
			return true;
		}

		if (board[y][x]) {
			return true;
		}
	}
	return false;
}

void GameLogic::gameOver() {
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			board[y][x] = 0;
		}
	}
	refresh();
	
	printColorString(Block::zero.x, Block::zero.y + 10, COLOR_BLACK, "gameover");
	isNotGameOver=false;

}
void GameLogic::gameClear() {

}
void GameLogic::nextTurn() {
	//보드에 저장
	for (int i = 0; i < 5; i++) {
		board[block.current.y + block.shape[i].y][block.current.x + block.shape[i].x] = block.colors[i];
	}
	block.refresh();
	check(block);
	//새블럭 생성
	block = next;
	next = Block();

	if (isCollision()) {
		gameOver();
	}
}

void GameLogic::check(Block block) {

	bool needClear = false;
	bool removeable;
	int lineCount = 0;
	int y = block.current.y + block.bottom;

	for (int i = 0; i < 5; i++) {
		removeable = true;
		for (int x = 0; x < WIDTH; x++) {
			if (!board[y][x]) {
				removeable = false;
				break;
			}
		}
		if (removeable) {
			needClear = true;
			lineCount++;
		} else {
			y--;
		}
	}
	switch (lineCount) {
	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	case 4:
		score += 800;
		break;
	default:
		break;
	}
	clearLines += lineCount;
	char l[4];
	sprintf(l, "%d", clearLines);
	printColorString(40, 15, 0, l);
//	if (clearLines >= 20) {
//		nextLevel();

//	}
	if (needClear)
		refresh();

}

void GameLogic::refresh() {

	for (int i = 0; i < HEIGHT; i++) {
		gotoxy(Block::zero.x - 2, Block::zero.y + i);
		putchar('*');

		for (int x = 0; x < WIDTH; x++) {
			if (board[i][x]) {
				printColorString(x * 2 + Block::zero.x, Block::zero.y + i, board[i][x], Block::BLOCK);
			} else {
				printColorString(x * 2 + Block::zero.x, Block::zero.y + i, board[i][x], Block::CLEAR);
			}
		}
		gotoxy(Block::zero.x + WIDTH * 2, Block::zero.y + i);
		putchar('*');
	}
	gotoxy(Block::zero.x - 2, Block::zero.y + HEIGHT);
	printf("*************");

}



