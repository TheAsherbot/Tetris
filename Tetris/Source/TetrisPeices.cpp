#include "TetrisPeices.h"

#include "RNG.h"


namespace Peices
{
	Peice GetRandomPeice()
	{
		int randomIndex = RNG::GetRandomNumber(7);
		switch (randomIndex)
		{
		case 0:
			return LPeiceData;
		case 1:
			return JPeiceData;
		case 2:
			return IPeiceData;
		case 3:
			return OPeiceData;
		case 4:
			return TPeiceData;
		case 5:
			return ZPeiceData;
		case 6:
			return SPeiceData;
		default:
			return LPeiceData; // Default case, should not happen
		}
	}

	Peice RotateClockwise(const Peice& peice)
	{
		Peice newPeice = peice;

		if (peice.type == Peice::O)
		{
			return newPeice; // O peice doesn't rotate
		}
		else if (peice.type != Peice::I) // need to rotate it in a 3x3
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (x < 3 && y < 3)
					{
						short sourceX = y;
						short sourceY = 2 - x;
						newPeice.pattern[y * 4 + x] = peice.pattern[sourceY * 4 + sourceX];
					}
					else
					{
						newPeice.pattern[y * 4 + x] = false;
					}
				}
			}
		}
		else
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					short sourceX = y;
					short sourceY = 3 - x;
					newPeice.pattern[y * 4 + x] = peice.pattern[sourceY * 4 + sourceX];
				}
			}
		}

		return newPeice;
	}

	Peice RotateCounterClockwise(const Peice& peice)
	{
		Peice newPeice = peice;
		if (peice.type == Peice::O)
		{
			return newPeice; // O peice doesn't rotate
		}
		else if (peice.type != Peice::I) // need to rotate it in a 3x3
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					if (x < 3 && y < 3)
					{
						short sourceX = 2 - y;
						short sourceY = x;
						newPeice.pattern[y * 4 + x] = peice.pattern[sourceY * 4 + sourceX];
					}
					else
					{
						newPeice.pattern[y * 4 + x] = false;
					}
				}
			}
		}
		else
		{
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					short sourceX = 3 - y;
					short sourceY = x;
					newPeice.pattern[y * 4 + x] = peice.pattern[sourceY * 4 + sourceX];
				}
			}
		}

		return newPeice;
	}

	short LowestPointFromTop(const Peice& peice)
	{
		for (short y = 3; y >= 0; y--)
		{
			for (short x = 0; x < 4; x++)
			{
				if (peice.pattern[y * 4 + x])
				{
					return y;
				}
			}
		}
		return 0;
	}
}