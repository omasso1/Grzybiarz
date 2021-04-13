#include "ObstacleTile.h"

namespace Tile {
	Obstacle::Obstacle(sf::Vector2f position, sf::Texture& texture)
		:BaseTile(position, texture,true)
	{
	}
	Obstacle::~Obstacle() {

	}
}