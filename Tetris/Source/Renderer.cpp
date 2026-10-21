#include "Renderer.h"

#include "RNG.h"

Renderer::Renderer(short width, short height, short fontWidth, short fontHeight)
{
	this->width = width;
	this->height = height;

	pressedKeys = (Key)0;
	heldKeys = (Key)0;
	releasedKeys = (Key)0;

	consoleHandle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	screenBuffer = new wchar_t[width * height];
	consolInputHandle = GetStdHandle(STD_INPUT_HANDLE);

	for (short i = 0; i < width * height; i++)
	{
		screenBuffer[i] = L' ';
	}

	SMALL_RECT windowRect = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(consoleHandle, TRUE, &windowRect);

	CONSOLE_FONT_INFOEX consoleFontInfo;
	consoleFontInfo.cbSize = sizeof(consoleFontInfo);
	consoleFontInfo.nFont = 1;
	consoleFontInfo.dwFontSize.X = fontWidth;
	consoleFontInfo.dwFontSize.Y = fontHeight;
	consoleFontInfo.FontFamily = FF_DONTCARE;
	consoleFontInfo.FontWeight = FW_NORMAL;
	wcscpy_s(consoleFontInfo.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleHandle, false, &consoleFontInfo);


	COORD bufferSize = { (short)width, (short)height };
	SetConsoleScreenBufferSize(consoleHandle, bufferSize);

	windowRect = { 0, 0, (short)(width - 1), (short)(height - 1) };
	SetConsoleWindowInfo(consoleHandle, TRUE, &windowRect);

	SetConsoleActiveScreenBuffer(consoleHandle);

	SetConsoleMode(consolInputHandle, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT);
}

Renderer::~Renderer()
{
	delete[] screenBuffer;
}

void Renderer::WriteToScreen(short x, short y, wchar_t character)
{
	screenBuffer[y * width + x] = character;
}

void Renderer::WriteToScreen(short x, short y, wchar_t* character)
{
	int i = 0;
	while (character[i] != L'\0')
	{
		WriteToScreen(x + i, y, character[i]);
		i++;
	}
}

void Renderer::Render()
{
	WriteConsoleOutputCharacterW(consoleHandle, screenBuffer, width * height, { 0, 0 }, &numberOfCharactersWritten);
}

void Renderer::Update()
{
	// Clear single-frame states from the previous frame
	pressedKeys = (Key)0;
	releasedKeys = (Key)0;

	HandleInput();
}

void Renderer::HandleInput()
{
	INPUT_RECORD inputBuffer[128];
	DWORD eventsRead = 0;

	// CHeck for input events
	DWORD evenetsAvailable = 0;
	GetNumberOfConsoleInputEvents(consolInputHandle, &evenetsAvailable);

	if (evenetsAvailable > 0)
	{
		if (ReadConsoleInputW(consolInputHandle, inputBuffer, 128, &eventsRead))
		{
			RNG::Waste();

			for (DWORD i = 0; i < eventsRead; i++)
			{
				if (inputBuffer[i].EventType == KEY_EVENT)
				{
					bool isKeyDown = inputBuffer[i].Event.KeyEvent.bKeyDown;
					WORD keyCode = inputBuffer[i].Event.KeyEvent.wVirtualKeyCode;
					wchar_t unicodeChar = inputBuffer[i].Event.KeyEvent.uChar.UnicodeChar;

					Key mappedKey = (Key)0;

					if (keyCode == VK_UP)               mappedKey = Key::Up;
					else if (keyCode == VK_DOWN)         mappedKey = Key::Down;
					else if (keyCode == VK_LEFT)         mappedKey = Key::Left;
					else if (keyCode == VK_RIGHT)        mappedKey = Key::Right;
					else if (unicodeChar == L'q' || unicodeChar == L'Q' || keyCode == 'Q') mappedKey = Key::Q;
					else if (unicodeChar == L'z' || unicodeChar == L'Z' || keyCode == 'Z') mappedKey = Key::Z;
					else if (unicodeChar == L'x' || unicodeChar == L'X' || keyCode == 'X') mappedKey = Key::X;

					if (mappedKey != 0)
					{
						if (isKeyDown)
						{
							// Only flag as 'pressed' if it wasn't already held down (prevents key-repeat spam)
							if (!(heldKeys & mappedKey))
							{
								pressedKeys = (Key)(pressedKeys | mappedKey);
							}
							heldKeys = (Key)(heldKeys | mappedKey);
						}
						else
						{
							// Key was released
							heldKeys = (Key)(heldKeys & ~mappedKey);
							releasedKeys = (Key)(releasedKeys | mappedKey);
						}
					}
				}
			}
		}
	}
}

bool Renderer::IsKeyPressed(Key key)
{
	return pressedKeys & key;
}