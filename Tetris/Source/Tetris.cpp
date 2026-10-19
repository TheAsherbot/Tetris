#include "Tetris.h"

#include <iostream>

Tetris::Tetris() :
	renderer(20, 40, 10, 10), tickTimer()
{
	Setup();
}

void Tetris::Setup()
{
	isGameOver = false;

	for (int i = 0; i < 10 * 20; i++)
	{
		board[i] = false;
	}

	Spawn();
}

Tetris::~Tetris()
{
}

void Tetris::Start()
{

	bool playing = true;

	short currentPieceYPos = currentPieceY;

	tickTimer.EvokeAfter(tickTime, [this]() {
			TickCallback(); 
		});


	while (playing)
	{
		tickTimer.Update();
		renderer.Update();
		if (isGameOver)
		{
			if (renderer.IsKeyPressed(static_cast<Renderer::Key>(Renderer::Key::Z | Renderer::Key::X)))
			{
				Setup();
				isGameOver = false;
			}
			continue;
		}

		if (renderer.IsKeyPressed(Renderer::Key::Z))
		{
			if (CanRotate(false))
			{
				currentPiece = Peices::RotateCounterClockwise(currentPiece);
			}
		}
		if (renderer.IsKeyPressed(Renderer::Key::X))
		{
			if (CanRotate(true))
			{
				currentPiece = Peices::RotateClockwise(currentPiece);
			}
		}
		if (renderer.IsKeyPressed(Renderer::Key::Left))
		{
			if (!IsColliding(currentPiece, currentPieceX - 1, currentPieceY))
			{
				currentPieceX -= 1;
			}
		}
		if (renderer.IsKeyPressed(Renderer::Key::Right))
		{
			if (!IsColliding(currentPiece, currentPieceX + 1, currentPieceY))
			{
				currentPieceX += 1;
			}
		}
		if (renderer.IsKeyPressed(Renderer::Key::Down))
		{
			if (!IsColliding(currentPiece, currentPieceX, currentPieceY + 1))
			{
				currentPieceY += 1;
			}
			else
			{
				Place();
			}
		}

		RenderGame();

		Sleep(16);

		if (renderer.IsKeyPressed(Renderer::Key::Q))
		{
			// playing = false;
		}
	}

	std::cout << "end?\n";
}

bool Tetris::IsColliding(const Peice& piece, short testX, short testY)
{
	for (short px = 0; px < 4; px++)
	{
		for (short py = 0; py < 4; py++)
		{
			if (piece.pattern[py * 4 + px])
			{
				short bx = testX + px;
				short by = testY + py;

				// Wall and floor bounds check
				if (bx < 0 || bx >= 10 || by < 0 || by >= 20)
					return true;

				// Placed piece collision check
				if (board[by * 10 + bx])
					return true;
			}
		}
	}
	return false;
}


bool Tetris::CanRotate(bool clockwise)
{
	Peice rotateedPeice = (clockwise ? Peices::RotateClockwise(currentPiece) : Peices::RotateCounterClockwise(currentPiece));

	return !IsColliding(rotateedPeice, currentPieceX, currentPieceY);
}



void Tetris::RenderGame()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			renderer.WriteToScreen(x * 2, y * 2, ' ');
			renderer.WriteToScreen(x * 2 + 1, y * 2, ' ');
			renderer.WriteToScreen(x * 2 + 1, y * 2 + 1, ' ');
			renderer.WriteToScreen(x * 2, y * 2 + 1, ' ');
		}
	}

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 20; y++)
		{
			if (board[y * 10 + x])
			{
				renderer.WriteToScreen(x * 2, y * 2, '#');
				renderer.WriteToScreen(x * 2 + 1, y * 2, '#');
				renderer.WriteToScreen(x * 2 + 1, y * 2 + 1, '#');
				renderer.WriteToScreen(x * 2, y * 2 + 1, '#');
			}
			else
			{
				renderer.WriteToScreen(x * 2, y * 2, ' ');
				renderer.WriteToScreen(x * 2 + 1, y * 2, ' ');
				renderer.WriteToScreen(x * 2 + 1, y * 2 + 1, ' ');
				renderer.WriteToScreen(x * 2, y * 2 + 1, ' ');
			}
		}
	}

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (currentPiece.pattern[y * 4 + x])
			{
				renderer.WriteToScreen((currentPieceX + x) * 2, (currentPieceY + y) * 2, '#');
				renderer.WriteToScreen((currentPieceX + x) * 2 + 1, (currentPieceY + y) * 2, '#');
				renderer.WriteToScreen((currentPieceX + x) * 2 + 1, (currentPieceY + y) * 2 + 1, '#');
				renderer.WriteToScreen((currentPieceX + x) * 2, (currentPieceY + y) * 2 + 1, '#');
			}
		}
	}

	renderer.Render();
}

void Tetris::Place()
{
	for (short pieceX = 0; pieceX < 4; pieceX++)
	{
		for (short pieceY = 0; pieceY < 4; pieceY++)
		{
			if (currentPiece.pattern[pieceY * 4 + pieceX])
			{
				int boardX = currentPieceX + pieceX;
				int boardY = currentPieceY + pieceY;

				board[boardY * 10 + boardX] = true;
			}
		}
	}

	TryLineClear();

	Spawn();
}

bool Tetris::TryLineClear()
{
	for (int y = 0; y < 20; y++)
	{
		bool lineFull = true;
		for (int x = 0; x < 10; x++)
		{
			if (!board[y * 10 + x])
			{
				lineFull = false;
				break;
			}
		}
		if (lineFull)
		{
			for (int clearY = y; clearY > 0; clearY--)
			{
				for (int x = 0; x < 10; x++)
				{
					board[clearY * 10 + x] = board[(clearY - 1) * 10 + x];
				}
			}
			for (int x = 0; x < 10; x++)
			{
				board[x] = false;
			}

			TryLineClear();

			return true;
		}
	}

	return false;
}

void Tetris::Spawn()
{
	currentPiece = Peices::GetRandomPeice();
	currentPieceX = 3;
	currentPieceY = 0;

	if (IsColliding(currentPiece, currentPieceX, currentPieceY))
	{
		GameOver();
	}
}

void Tetris::GameOver()
{
	wchar_t gameOverMessage[] = L"GAME OVER";
	renderer.WriteToScreen(5, 1, gameOverMessage);

	renderer.Render();

	isGameOver = true;
}

void Tetris::TickCallback()
{
	if (!IsColliding(currentPiece, currentPieceX, currentPieceY + 1))
	{
		currentPieceY += 1;
	}
	else
	{
		Place();
	}

	tickTimer.EvokeAfter(tickTime, [this]() {
		TickCallback();
		});
}
