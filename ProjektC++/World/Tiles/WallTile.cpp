#include "WallTile.h"
#include <SFML/Graphics/Texture.hpp>
namespace Tile {
	Wall::Wall(sf::Vector2f position, sf::Texture& texture)
		:BaseTile(position,texture,true)
	{
	
	}
	Wall::~Wall() {

	}
}