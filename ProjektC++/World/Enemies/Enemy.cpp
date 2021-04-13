#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position, float speed, sf::Vector2f hitboxSize)
	:Character(sf::RectangleShape(hitboxSize), position, speed), m_hitboxSize(hitboxSize), m_faceRight(true), m_attackCooldown(0.33),
	m_getHitTime(0),m_attackTime(0)
{
	m_hitbox.setPosition(m_position);
	m_hitbox.setSize(m_hitboxSize);
}



