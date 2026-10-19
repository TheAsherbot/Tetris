#include <iostream>

#include "Source/Tetris.h"
#include "Source/RNG.h"


int main() {

	RNG::Setup();

	Tetris* tetris = new Tetris();;

	tetris->Start();

	delete tetris;

	return 0;
}