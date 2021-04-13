#include "Entity.h"
#include <SFML/Graphics/RectangleShape.hpp>

Entity::Entity(sf::RectangleShape hitbox, sf::Vector2f position)
	:m_collider(this),m_hitbox(hitbox),m_position(position)
{
	m_hitbox.setOrigin(m_hitbox.getSize() / 2.f);
	m_texturebox.setOrigin(m_hitbox.getSize() / 2.f);
	m_hitbox.setPosition(position);
	m_texturebox.setPosition(position);
}

void Entity::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
	m_hitbox.setPosition(m_position);
	m_texturebox.setPosition(m_position);
}

void Entity::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_hitbox.setPosition(m_position);
	m_texturebox.setPosition(m_position );
}

void Entity::move(float x, float y)
{
	m_position.x += x;
	m_position.y += y;
	m_hitbox.setPosition(m_position);
	m_texturebox.setPosition(m_position);
}
