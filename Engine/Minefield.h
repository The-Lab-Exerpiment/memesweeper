#pragma once
#include <random>
#include "Graphics.h"

class Minefield {
public:
	Minefield(const int _mines, Graphics& _gfx);
	void SpawnMine();
	void Draw();

private:
	class Tile {
	public:
		enum class State {
			Hidden,
			Flagged,
			Revealed
		};
		bool IsMine() const;
		void SetMine();

	private:
		State state = State::Hidden;
		bool isMine = false;
	};

	std::mt19937 rng;
	std::uniform_int_distribution<int> fieldRange;

	Graphics& gfx;

	static constexpr int size = 10;

	static constexpr int width = 15;
	static constexpr int height = 10;
	Tile tiles[width * height];
};