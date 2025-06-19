#include "Minefield.h"

Minefield::Minefield(const int _mines, Graphics& _gfx) :
	rng(std::random_device()()),
	fieldRange(0, width* height - 1),
	gfx(_gfx) {
	for (int mine = 0;mine < _mines;mine++) {
		SpawnMine();
	}
	SetAllAdjacent();
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
					switch (tiles[x + y * width].GetAdjacent()) {
					case 0:
						SpriteCodex::DrawTile0(location, gfx);
						break;
					case 1:
						SpriteCodex::DrawTile1(location, gfx);
						break;
					case 2:
						SpriteCodex::DrawTile2(location, gfx);
						break;
					case 3:
						SpriteCodex::DrawTile3(location, gfx);
						break;
					case 4:
						SpriteCodex::DrawTile4(location, gfx);
						break;
					case 5:
						SpriteCodex::DrawTile5(location, gfx);
						break;
					case 6:
						SpriteCodex::DrawTile6(location, gfx);
						break;
					case 7:
						SpriteCodex::DrawTile7(location, gfx);
						break;
					case 8:
						SpriteCodex::DrawTile8(location, gfx);
						break;
					}
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
	if (state != State::Revealed) {
		state = State::Revealed;
	}
}

void Minefield::RevealAll(Vei2& _position) {
	if (tiles[Linear(_position)].IsBlank()) {
		for (int dx = -1;dx <= 1;dx++) {
			for (int dy = -1;dy <= 1;dy++) {
				Vei2 newPos = _position + Vei2(dx, dy);

				if(GridBoundaryCheck(newPos)&&!tiles[Linear(newPos)].IsRevealed()) {
					tiles[Linear(newPos)].Reveal();
					RevealAll(newPos);
				}
			}
		}
	}
}

void Minefield::Tile::PureReveal() {
	state = State::Revealed;
}

bool Minefield::Tile::IsFlagged() const {
	return state == State::Flagged;
}

void Minefield::Tile::Flag() {
	if (!(state == State::Flagged)) {
		state = State::Flagged;
	}
	else {
		state = State::Hidden;
	}
}

void Minefield::RevealOnClick(Vei2& _position) {
	Vei2 gridCoords = GridPos(_position);
	if (BoundaryCheck(_position) && !tiles[Linear(gridCoords)].IsFlagged()) {

		if (tiles[Linear(gridCoords)].IsMine()) {
			SetGameOver();
		}
		else {
			RevealAll(gridCoords);
		}
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

bool Minefield::GridBoundaryCheck(Vei2& _position) const {
	return _position.x >= 0 && _position.y >= 0 &&
		_position.x < width && _position.y < height;
}

int Minefield::Linear(Vei2& _position) const {
	return _position.x + _position.y * width;
}

int Minefield::Tile::GetAdjacent() const {
	return adjacent;
}

void Minefield::Tile::AddAdjacent() {
	adjacent += 1;
}

void Minefield::SetAllAdjacent() {
	for (int tile = 0;tile < width * height;tile++) {

		for (int x = -1;x <= 1;x++) {
			for (int y = -1; y <= 1; y++) {
				if (tile + x + y * width >= 0 && tile + x + y * width < width * height) {
					if (tiles[tile + x + y * width].IsMine()) {
						tiles[tile].AddAdjacent();
					}
				}
			}
		}
	}
}

bool Minefield::IsGameOver() const {
	return gameOver;
}

void Minefield::SetGameOver() {
	gameOver = true;

	for (int tile = 0;tile < width * height;tile++) {
		if (tiles[tile].IsMine()) {
			tiles[tile].PureReveal();
		}
	}
}

bool Minefield::Tile::IsBlank() const {
	return adjacent == 0;
}