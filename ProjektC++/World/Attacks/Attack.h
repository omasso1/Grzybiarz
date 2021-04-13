#pragma once

#include "../Entity.h"
#include <SFML/System/Clock.hpp>

class Character;

class Attack : public Entity {
protected:
	float m_lifetime;
	float m_castTime;
	Character* m_p_source;
	std::vector<Character*> m_p_alreadyHit;
	void (*m_p_f_effectFunc)(Character& target);
	sf::Vector2f m_attackOffset;

public:
	Attack(Character* source,const sf::RectangleShape& hitbox,const sf::Vector2f& attackOffset, float lifetime, float castTime, void (*effectFunc)(Character& target));
	Attack() = delete;
	Attack(const Attack& src) = default;
	Attack(Attack&& src) = default;
	Attack& operator=(const Attack& other) = default;
	Attack& operator=(Attack&& other) = default;
	virtual ~Attack() = default;

	virtual void draw() = 0;
	virtual void update(sf::Time& deltaTime) = 0;
	virtual inline std::unique_ptr<Attack> clone() = 0;
	virtual void hit(std::unique_ptr<Character>& target);
	virtual sf::Vector2f& getAttackOffset() { return m_attackOffset; }
	inline void setEffectFunc(void (*effectFunc)(Character& target)) { this->m_p_f_effectFunc = effectFunc; }
	inline bool isCasted() { return m_castTime <= 0; }
	inline bool isNotLive() { return m_lifetime <= 0; }
	inline Character* getSource() { return m_p_source; }
	bool didntHitBefore(Character* character);
	inline auto getEffectFunc() { return m_p_f_effectFunc; }
};