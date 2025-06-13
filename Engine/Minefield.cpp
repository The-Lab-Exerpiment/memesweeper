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
	for (int tile = 0;tile < width * height;tile++) {
		if (tiles[tile].IsMine()) {
			for (int x = 0;x < size;x++) {
				for (int y = 0;y < size;y++) {
					gfx.PutPixel(tile % width * size + x, tile / width * size + y, Color(255, 0, 0));
				}
			}
		}
	}
}

void Minefield::SpawnMine() {
	int mineTile;
	do {
		mineTile = fieldRange(rng);
	} while (!tiles[mineTile].IsMine());
	tiles[mineTile].SetMine();

}

void Minefield::Tile::SetMine() {
	isMine = true;
}

bool Minefield::Tile::IsMine() const {
	return isMine;
}