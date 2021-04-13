#include "Collider.h"
#include "Entity.h"
#include <iostream>
#include "../Display.h"
Collider::Collider(Entity* body)
	:m_p_body(body)
{
}

void Collider::move(float x, float y)
{
	m_p_body->move(x, y);
}

sf::Vector2f Collider::getHalfSize()
{
	return m_p_body->getSize()/2.f;
}

sf::Vector2f Collider::getPosition()
{
	return m_p_body->getPosition();
}

bool Collider::checkCollisionAndPush(Collider& other, float push)
{
	sf::Vector2f otherHalfSize = other.getHalfSize();
	sf::Vector2f otherPosition = other.getPosition();

	sf::Vector2f thisHalfSize = getHalfSize();
	sf::Vector2f thisPosition = getPosition();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.f && intersectY < 0.f) {
		if (intersectX > intersectY) {
			if (deltaX > 0.f) {
				move(intersectX * (1.f - push), 0.f);
				other.move(-intersectX* push, 0.f);
			}
			else {
				move(-intersectX * (1.f - push), 0.f);
				other.move(intersectX * push, 0.f);
			}
		}
		else {
			if (deltaY > 0.f) {
				move(0.f, intersectY * (1.f - push));
				other.move(0.f, -intersectY * push);
			}
			else {
				move(0.f, -intersectY * (1.f - push));
				other.move(0.f, intersectY * push);
			}
		}
		return true;
	}
	return false;
}


bool Collider::checkCollision(Collider& other)
{
	sf::Vector2f otherHalfSize = other.getHalfSize();
	sf::Vector2f otherPosition = other.getPosition();

	sf::Vector2f thisHalfSize = getHalfSize();
	sf::Vector2f thisPosition = getPosition();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.f && intersectY < 0.f) {
		return true;
	}
	return false;
}
