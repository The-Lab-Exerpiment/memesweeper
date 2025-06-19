#pragma once
#include <random>
#include "Vei2.h"
#include "SpriteCodex.h"
#include "Graphics.h"
#include "RectI.h"

class Minefield {
public:
	Minefield(const int _mines, Graphics& _gfx);
	void SpawnMine();

	void Draw();

	void RevealOnClick(Vei2& _position);
	void FlagOnClick(Vei2& _position);

	bool BoundaryCheck(Vei2& _positon);

private:
	class Tile {
	public:
		enum class State {
			Hidden,
			Flagged,
			Revealed
		};

		int GetAdjacent() const;
		void AddAdjacent();

		bool IsMine() const;
		void SetMine();

		State GetState() const;
		void SetState(State& _state);

		bool IsRevealed() const;
		void Reveal();

		bool IsFlagged() const;
		void Flag();

	private:
		State state = State::Hidden;
		bool isMine = false;
		int adjacent = 0;
	};

	std::mt19937 rng;
	std::uniform_int_distribution<int> fieldRange;

	Graphics& gfx;

	static constexpr int width = 15;
	static constexpr int height = 10;
	Tile tiles[width * height];

	Vei2 GridPos(const Vei2& _position) const;
	int Linear(Vei2& _position) const;
	void SetAllAdjacent();
};