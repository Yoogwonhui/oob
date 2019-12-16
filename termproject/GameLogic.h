
#include "Block.h"

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

static const int WIDTH = 5;
static const int HEIGHT = 12;

class GameLogic {
public:
	int score;
	bool isRun;
	int interval;
	int clearLines;
	/*board[y][x]*/
	char *board[HEIGHT];
	/*게임시작*/
	void start();
	/*컨트롤 하는 블럭을 이동*/
	void moveLeft();
	/*컨트롤 하는 블럭을 이동*/
	void moveRight();
	/*컨트롤 하는 블럭을 이동*/
	void moveDown();
	/*컨트롤 하는 블럭을 회전*/
	void transforse();
	/*컨트롤 하는 블럭을 가장 아래로 이동*/
	void drop();
	/*제어하는 블럭을 표시*/
	void printBlock();
	GameLogic();
	virtual ~GameLogic();

private:
	Block block;
	Block next;
	bool isNotGameOver;
	void check(Block block);
	bool isCollision();
	void refresh();
	void gameOver();
	void gameClear();
	void nextTurn();
	int level;
};

#endif /* GAMELOGIC_H_ */
