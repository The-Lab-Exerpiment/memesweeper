#include "Minefield.h"

Minefield::Minefield(const int _mines) :
	rng(std::random_device()()),
	fieldRange(0, width* height - 1) {
	//do smth
}

void Minefield::SpawnMine() {
	int bombTile;
	do {
		bombTile = fieldRange(rng);
	} while (!tiles[bombTile].IsBomb());
	tiles[bombTile].SetBomb();

}

void Minefield::Tile::SetBomb() {
	isBomb = true;
}

bool Minefield::Tile::IsBomb() const {
	return isBomb;
}