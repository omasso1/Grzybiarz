#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include "Collider.h"

class Room;

class Entity {
protected:
	sf::Vector2f m_position;
	sf::Texture m_texutre;
	sf::RectangleShape m_hitbox;
	sf::RectangleShape m_texturebox;
	Collider m_collider;

public:
	Entity() = delete;
	Entity(sf::RectangleShape hitbox, sf::Vector2f position = { 20,20 });
	Entity(const Entity& src) = default;
	Entity(Entity&& src) = default;
	Entity& operator=(const Entity& other) = default;
	Entity& operator=(Entity&& other) = default;
	virtual ~Entity() = default;

	virtual void setPosition(float x, float y);
	virtual void setPosition(sf::Vector2f position);
	virtual void move(sf::Time& deltaTime) { ; }
	virtual void update(sf::Time& deltaTime, Room& world) { ; }
	virtual void draw() = 0;
	inline Collider& getCollider() { return m_collider; }
	inline sf::Vector2f getSize() const { return m_hitbox.getSize(); }
	inline sf::Vector2f getPosition() const { return m_position; }
	virtual void move(float x, float y);
};

