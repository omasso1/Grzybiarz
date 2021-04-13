#include "Character.h"
#include <iostream>

Character::Character(sf::RectangleShape hitbox, sf::Vector2f position, float speed, float maxSpeed, float health, float maxHealth)
	:Entity(hitbox,position), m_health(health), m_maxHealth(maxHealth), m_speed(speed), m_maxSpeed(maxSpeed)
{
}

bool Character::checkReceivedAttacks()
{
	bool r = m_p_receivedAtacks.size();
	//wywolanie funkcji ataku
	for (auto& attack : m_p_receivedAtacks) {
		attack->getEffectFunc()(*this);
	}
	m_p_receivedAtacks.erase(m_p_receivedAtacks.begin(), m_p_receivedAtacks.end());
	return r;
}



