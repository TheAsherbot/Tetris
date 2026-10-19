#pragma once

#include "TetrisPeices.h"

#include "Renderer.h"
#include "Timer.h"

class Tetris
{
public:
	Tetris();
	~Tetris();

	void Start();

private:
	bool isGameOver = false;

	Renderer renderer;

	bool board[10 * 20];

	Peice currentPiece;
	short currentPieceX = 0;
	short currentPieceY = 0;

	float tickTime = 0.75;

	Timer tickTimer;

	void Setup();
	void Spawn();

	bool IsColliding(const Peice& piece, short testX, short testY);
	bool CanRotate(bool clockwise);

	void RenderGame();

	void Place();
	bool TryLineClear();
	void GameOver();

	void TickCallback();
};
