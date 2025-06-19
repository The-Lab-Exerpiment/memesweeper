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
			Vei2 location(x * SpriteCodex::tileSize, y * SpriteCodex::tileSize);

			switch (tiles[x + y * width].GetState()) {
			case Tile::State::Flagged:
				SpriteCodex::DrawTileFlag(location, gfx);
			case Tile::State::Hidden:
				SpriteCodex::DrawTileButton(location, gfx);
				break;
			case Tile::State::Revealed:
				if (tiles[x + y * width].IsMine()) {
					SpriteCodex::DrawTileBomb(location, gfx);
				}
				else {
					SpriteCodex::DrawTile0(location, gfx);
				}
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

bool Minefield::Tile::IsRevealed() const {
	return state == State::Revealed;
}

void Minefield::Tile::Reveal() {
	if (!(state == State::Revealed)) {
		state = State::Revealed;
	}
}

bool Minefield::Tile::IsFlagged() const {
	return state == State::Flagged;
}

void Minefield::Tile::Flag() {
	if (!(state == State::Flagged)) {
		state = State::Flagged;
	}
}

void Minefield::RevealOnClick(Vei2& _position) {
	Vei2 gridCoords = GridPos(_position);
	if (BoundaryCheck(_position) && !tiles[Linear(gridCoords)].IsFlagged()) {
		tiles[Linear(gridCoords)].Reveal();
	}
}

void Minefield::FlagOnClick(Vei2& _position) {
	Vei2 gridCoords = GridPos(_position);
	if (BoundaryCheck(_position) && !tiles[Linear(gridCoords)].IsRevealed()) {
		tiles[Linear(gridCoords)].Flag();
	}
}

Vei2 Minefield::GridPos(const Vei2& _position) const {
	return _position / SpriteCodex::tileSize;
}

bool Minefield::BoundaryCheck(Vei2& _position) {
	return GridPos(_position).x < width && GridPos(_position).y < height;
}

int Minefield::Linear(Vei2& _position) const {
	return _position.x + _position.y * width;
}