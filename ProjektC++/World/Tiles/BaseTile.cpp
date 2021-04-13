#include "BaseTile.h"
#include "../../Display.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include "../../DebugDefines.h"

namespace Tile {

	BaseTile::BaseTile(sf::Vector2f position, sf::Texture& texture,bool isObstacle)
		:Entity(sf::RectangleShape({ TILE_WIDTH,TILE_HEIGHT }),position),m_isObstacle(isObstacle)
	{
		bindTexture(texture);
		m_texturebox.setSize({ TILE_WIDTH,TILE_HEIGHT });
		m_texturebox.setTextureRect({ 0,0, TILE_WIDTH,TILE_HEIGHT });
		DEBUG_FUNC(m_hitbox.setOutlineColor(sf::Color(0,0,0)));
		DEBUG_FUNC(m_hitbox.setOutlineThickness(1));
		DEBUG_FUNC(m_texturebox.setOutlineColor(sf::Color(0, 0, 0)));
		DEBUG_FUNC(m_texturebox.setOutlineThickness(1));
		DEBUG_FUNC(m_hitbox.setFillColor(sf::Color(0, 0, 0, 0)));
	}

	void BaseTile::bindTexture(sf::Texture& texture){
		m_texturebox.setTexture(&texture);
	}

	void BaseTile::draw()
	{
		//std::cout << m_p_position.x << " " << m_p_position.y << std::endl;
		//DEBUG_FUNC(Display::draw(m_p_hitbox));
		Display::draw(m_texturebox);

	}

}