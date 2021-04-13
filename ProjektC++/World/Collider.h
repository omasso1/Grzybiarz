#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include <memory>

class Entity;

class Collider {
private:
	Entity* m_p_body;
public:
	Collider(Entity* body);
	Collider() = delete;
	Collider(const Collider& src) = default;
	Collider(Collider&& src) = default;
	Collider& operator=(const Collider& src) = default;
	Collider& operator=(Collider&& src) = default;
	~Collider() = default;

	void move(float x, float y);
	sf::Vector2f getHalfSize();
	sf::Vector2f getPosition();
	bool checkCollisionAndPush(Collider& other, float push);
	bool checkCollision(Collider& other);
	


};