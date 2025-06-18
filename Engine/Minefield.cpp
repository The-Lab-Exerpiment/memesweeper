#include "Minefield.h"

Minefield::Minefield(const int _mines, Graphics& _gfx) :
	rng(std::random_device()()),
	fieldRange(0, width* height - 1),
	gfx(_gfx) {
	for (int mine = 0;mine < _mines;mine++) {
		SpawnMine();
	}
}

void Minefield::Draw() {
	gfx.DrawRect(0, 0, width * SpriteCodex::tileSize, height * SpriteCodex::tileSize, SpriteCodex::baseColor);

	for (int x = 0;x < width;x++) {
		for (int y = 0;y < height;y++) {

			switch (tiles[x + y * width].GetState()) {

			case Tile::State::Flagged:
				SpriteCodex::DrawTileFlag(Vei2(x * SpriteCodex::tileSize, y * SpriteCodex::tileSize), gfx);
			case Tile::State::Hidden:
				SpriteCodex::DrawTileButton(Vei2(x * SpriteCodex::tileSize, y * SpriteCodex::tileSize), gfx);
				break;
			}
		}
	}
}

void Minefield::SpawnMine() {
	int mineTile;
	do {
		mineTile = fieldRange(rng);
	} while (tiles[mineTile].IsMine());
	tiles[mineTile].SetMine();

}

void Minefield::Tile::SetMine() {
	isMine = true;
}

bool Minefield::Tile::IsMine() const {
	return isMine;
}

Minefield::Tile::State Minefield::Tile::GetState() const {
	return state;
}

void Minefield::Tile::SetState(State& _state) {
	state = _state;
}