#pragma once
#include "../Character.h"

class Enemy : public Character {
protected:
	sf::Vector2f m_attackRange;
	sf::Vector2f m_attackSize;
	sf::Vector2f m_hitboxOffset;
	sf::Vector2f m_hitboxSize;
	sf::Vector2i m_textureOffset;
	float m_attackCooldown; 
	float m_getHitTime;
	float m_attackTime;
	sf::Clock m_Clock;
	bool m_faceRight;


public:
	Enemy() = delete;
	Enemy(sf::Vector2f position, float speed, sf::Vector2f hitboxSize);
	Enemy(const Enemy& src) = default;
	Enemy(Enemy&& src) = default;
	Enemy& operator=(const Enemy& other) = default;
	Enemy& operator=(Enemy&& other) = default;
	virtual ~Enemy() = default;
	virtual void update(sf::Time& deltaTime, Room& room, std::unique_ptr<Character>& player) = 0;


};