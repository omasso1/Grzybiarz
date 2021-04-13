#pragma once
#include "BaseTile.h"
namespace Tile {
	class Door : public BaseTile {
		sf::Texture& m_FloorTexture;
	public:
		Door(sf::Vector2f position, sf::Texture& doorTexture, sf::Texture& floorTexture);
		Door() = delete;
		virtual ~Door();

		void endOfRoom() override;
	};
}