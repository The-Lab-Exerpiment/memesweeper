#pragma once
#include <random>

class Minefield {
public:
	Minefield(const int _mines);
	void SpawnMine();

private:
	class Tile {
	public:
		enum class State {
			Hidden,
			Flagged,
			Revealed
		};
		bool IsBomb() const;
		void SetBomb();

	private:
		State state = State::Hidden;
		bool isBomb = false;
	};

	std::mt19937 rng;
	std::uniform_int_distribution<int> fieldRange;

	static constexpr int width = 15;
	static constexpr int height = 10;
	Tile tiles[width * height];
};