#pragma once

#include <Windows.h>

class Renderer
{
public:
	enum Key : short
	{
		Z = 1,
		X = 2,
		Up = 4,
		Down = 8,
		Left = 16,
		Right = 32,
		Q = 128,
	};

	Renderer(short width, short height, short fontWidth, short fontHeight);
	~Renderer();
	
	/// <summary>
	/// Renders a single character to the screen
	/// </summary>
	/// <param name="x">0-width. 0 left, width right</param>
	/// <param name="y">=-height. 0 bottom, height top</param>
	/// <param name="character">Character to draw onto the screen</param>
	void WriteToScreen(short x, short y, wchar_t character);

	/// <summary>
	/// Renders a single character to the screen
	/// </summary>
	/// <param name="x">0-width. 0 left, width right</param>
	/// <param name="y">y-height. 0 top, height bottom</param>
	/// <param name="character">String to draw onto the screen</param>
	void WriteToScreen(short x, short y, wchar_t* character);
	
	void Render();

	bool IsKeyPressed(Key key);
	bool IsKeyHeld(Key key);
	bool IsKeyReleased(Key key);

	void Update();

private:

	void HandleInput();

	short width = 0;
	short height = 0;

	HANDLE consoleHandle;
	HANDLE consolInputHandle;
	wchar_t* screenBuffer;
	DWORD numberOfCharactersWritten = 0;

	Key heldKeys;
	Key pressedKeys;
	Key releasedKeys;
};
