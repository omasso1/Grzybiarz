#pragma once
#include "BaseTile.h"
namespace Tile {
	class Floor : public BaseTile {
	public:
		Floor(sf::Vector2f position, sf::Texture& texture);
		Floor() = delete;
		virtual ~Floor();
	};
}