#include "Attack.h"
#include "../Character.h"
Attack::Attack(Character* source,const sf::RectangleShape& hitbox,const sf::Vector2f& attackOffset, float lifetime, float castTime, void(*effectFunc)(Character& target))
	:Entity(hitbox, { 0,0 }), m_lifetime(lifetime), m_castTime(castTime), m_p_f_effectFunc(effectFunc), m_p_source(source),m_attackOffset(attackOffset)
{}

void Attack::hit(std::unique_ptr<Character>& target) { 
	target->addReceivedAttack(this->clone()); 
	m_p_alreadyHit.push_back(target.get());
}

bool Attack::didntHitBefore(Character* character)
{
	for (auto& c : m_p_alreadyHit) {
		if (c == character)
			return false;
	}
	return true;
}
