#include "DoorTile.h"

namespace Tile {
	Door::Door(sf::Vector2f position, sf::Texture& doorTexture, sf::Texture& floorTexture)
		:BaseTile(position, doorTexture, true), m_FloorTexture(floorTexture)
	{
	}

	Door::~Door() {

	}

	void Door::endOfRoom() {
		bindTexture(m_FloorTexture);
		m_isObstacle = false;
	}
}