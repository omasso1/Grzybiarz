#include "FloorTile.h"

namespace Tile {
	Floor::Floor(sf::Vector2f position, sf::Texture& texture)
		:BaseTile(position,texture,false)
	{
	}

	Floor::~Floor() {

	}
}