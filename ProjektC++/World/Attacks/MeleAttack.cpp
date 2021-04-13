#include "MeleAttack.h"
#include "../../DebugDefines.h"
#include "../../Display.h"
#include <iostream>
MeleAttack::MeleAttack(Character* source, const sf::RectangleShape& hitbox, const sf::Vector2f& attackOffset, float lifetime, float castTime, void(*effectFunc)(Character& target))
	:Attack(source, hitbox, attackOffset,lifetime,castTime,effectFunc)
{
	DEBUG_FUNC(m_hitbox.setOutlineColor(sf::Color(255, 0, 0)));
	DEBUG_FUNC(m_hitbox.setOutlineThickness(1));
	DEBUG_FUNC(m_hitbox.setFillColor(sf::Color(0, 0, 0, 0)));
}


void MeleAttack::draw() {
	DEBUG_FUNC(Display::draw(m_hitbox));
}

void MeleAttack::update(sf::Time& deltaTime)
{
	if(m_castTime > 0)
		m_castTime -= deltaTime.asSeconds();
	else {
		m_lifetime -= deltaTime.asSeconds();
	}
}

