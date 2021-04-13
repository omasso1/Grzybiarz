#pragma once
#include "BaseTile.h"

namespace Tile {
	class Wall : public BaseTile {
	public:
		Wall(sf::Vector2f position, sf::Texture& texture);
		Wall() = delete;
		virtual ~Wall();
	};
}