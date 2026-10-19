#pragma once

namespace RNG
{
	void Setup();

	void Waste();

	/// <summary>
	/// Returns a random number between 0 and max (exclusive)
	/// </summary>
	/// <param name="max">The maximum number to return</param>
	/// <returns>A random number between 0 and max (exclusive)</returns>
	int GetRandomNumber(int max);
}