#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
#include <Windows.h>

HANDLE consoleHandle;
HANDLE consolInputHandle;
wchar_t* screenBuffer;
DWORD numberOfCharactersWritten = 0;

void SetUpCMD(int width, int height)
{
	consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	screenBuffer = new wchar_t[10 * 20];
	consolInputHandle = GetStdHandle(STD_INPUT_HANDLE);

	for (int i = 0; i < width * height; i++)
	{
		screenBuffer[i] = L' ';
	}

	SMALL_RECT windowRect = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(consoleHandle, TRUE, &windowRect);

	COORD bufferSize = { (short)width, (short)height };
	SetConsoleScreenBufferSize(consoleHandle, bufferSize);

	windowRect = { 0, 0, (short)(width - 1), (short)(height - 1) };
	SetConsoleWindowInfo(consoleHandle, TRUE, &windowRect);

	SetConsoleActiveScreenBuffer(consoleHandle);

	SetConsoleMode(consolInputHandle, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT);
}

int main() {
	int width = 10;
	int height = 20;

	SetUpCMD(10, 20);

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			screenBuffer[y * width + x] = L'#';
		}
	}
	
	WriteConsoleOutputCharacterW(consoleHandle, screenBuffer, width * height, { 0, 0 }, &numberOfCharactersWritten);

	std::cin;

	delete[] screenBuffer;

	return 0;
}