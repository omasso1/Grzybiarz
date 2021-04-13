#pragma once
#include "BaseTile.h"

namespace Tile {
	class Obstacle : public BaseTile {
	public:
		Obstacle(sf::Vector2f position, sf::Texture& texture);
		Obstacle() = delete;
		virtual ~Obstacle();
	};
}