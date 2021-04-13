#pragma once

#include "Entity.h"
#include "Attacks/Attack.h"

class Character : public Entity{
protected:
	float m_health;
	float m_maxHealth;
	float m_speed;
	float m_maxSpeed;
	std::vector<std::unique_ptr<Attack>> m_p_receivedAtacks;

public:
	Character() = delete;
	Character(sf::RectangleShape hitbox, sf::Vector2f position = { 500,500 },  float speed = 400, float maxSpeed = 400, float health = 100, float maxHealth = 100);
	Character(const Character& src) = default;
	Character(Character&& src) = default;
	Character& operator=(const Character& other) = default;
	Character& operator=(Character&& other) = default;
	virtual ~Character() = default;

	virtual inline void addReceivedAttack(std::unique_ptr<Attack> attack) { m_p_receivedAtacks.emplace_back(std::move(attack)); }
	inline float getHealth() const { return m_health; }
	inline float getMaxHealth() const { return m_maxHealth; }
	inline void changeHealth(float value) { m_health += value; }
	inline void changeMaxHealth(float value) { m_maxHealth += value; }
	inline void changeSpeed(float value) { m_speed += value; }
	inline void changeMaxSpeed(float value) { m_maxSpeed += value; }
	virtual bool checkReceivedAttacks();

};