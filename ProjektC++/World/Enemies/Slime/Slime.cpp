#include "Slime.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include "../../functions.h"
#include "../../DebugDefines.h"
#include "../../Room.h"


Slime::Slime(sf::Vector2f position, float speed, sf::Vector2f hitboxSize)
	:Enemy(position,speed,hitboxSize),m_basicAttack(this, sf::RectangleShape({ 10,m_hitbox.getSize().y, }), sf::Vector2f(m_hitbox.getSize().x / 2.f + 10 / 2.f, 0), 0.10f, 0.10f,
		[](Character& target) {target.changeHealth(-10.f); })
{
	m_state = SlimeState::IDLE;
	m_newState = SlimeState::IDLE;
	m_animations.addAnimation("./World/enemies/Slime/Textures/", "slimeIdle", (int32_t)SlimeState::IDLE, m_texturebox, m_faceRight);
	m_animations.addAnimation("./World/enemies/Slime/Textures/", "slimeMove", (int32_t)SlimeState::MOVING, m_texturebox, m_faceRight);
	m_animations.addAnimation("./World/enemies/Slime/Textures/", "slimeAttack", (int32_t)SlimeState::ATTACKING, m_texturebox, m_faceRight);
	m_animations.addAnimation("./World/enemies/Slime/Textures/", "slimeHurt", (int32_t)SlimeState::GET_HIT, m_texturebox, m_faceRight);
	m_animations.addAnimation("./World/enemies/Slime/Textures/", "slimeDie", (int32_t)SlimeState::DIE, m_texturebox, m_faceRight);
	m_attackTime = m_animations.getAnimation((int32_t)SlimeState::ATTACKING)->getAnimationDuration();
	m_attackCooldown = m_attackTime * 2;
	m_getHitTime = m_animations.getAnimation((int32_t)SlimeState::GET_HIT)->getAnimationDuration();

	m_animations.startAnimation((int32_t)m_state, m_position);
	DEBUG_FUNC(m_texturebox.setOutlineColor(sf::Color(0, 0, 0)));
	DEBUG_FUNC(m_texturebox.setOutlineThickness(3));
	DEBUG_FUNC(m_hitbox.setOutlineColor(sf::Color(255, 0, 0)));
	DEBUG_FUNC(m_hitbox.setOutlineThickness(1));
	DEBUG_FUNC(m_hitbox.setFillColor(sf::Color(0, 0, 0, 0)));
}

void Slime::draw()
{
	m_animations.draw();
	DEBUG_FUNC(Display::draw(m_hitbox));

}

void Slime::move(sf::Time& deltaTime, std::unique_ptr<Character>& player)
{
	sf::Vector2f v = player->getPosition() - m_position;
	if (v.x > 0) {
		m_faceRight = true;
	}
	else if (v.x < 0) {
		m_faceRight = false;
	}
	if (v.x || v.y) m_newState = SlimeState::MOVING;
	v = normalizeVector(v) * m_speed * deltaTime.asSeconds();
	m_position += v;
	m_hitbox.move(v);
	m_texturebox.move(v);
}

void Slime::attack(Room& room) {
	if (m_faceRight) {
		m_basicAttack.setPosition({ m_position + m_basicAttack.getAttackOffset() });
	}
	else {
		m_basicAttack.setPosition({ m_position - m_basicAttack.getAttackOffset() });
	}
	room.addAttack(m_basicAttack.clone());
}

bool Slime::inRange(std::unique_ptr<Character>& character)
{
	if (m_faceRight) {
		m_basicAttack.setPosition({ m_position + m_basicAttack.getAttackOffset() });
	}
	else {
		m_basicAttack.setPosition({ m_position - m_basicAttack.getAttackOffset() });
	}
	return character->getCollider().checkCollision(m_basicAttack.getCollider());

}



bool Slime::checkIfNewState() {
	
	if (m_newState != m_state) {
		m_state = m_newState;
		return true;
	}
	return false;
}

void Slime::input(sf::Event& e)
{
}

void Slime::update(sf::Time& deltaTime, Room& room, std::unique_ptr<Character>& player) {
	//reset czasu od dostania uderzenia i ataku
	if (m_state == SlimeState::GET_HIT || m_state == SlimeState::ATTACKING) {
		if (m_Clock.getElapsedTime().asSeconds() > m_attackTime && m_state == SlimeState::ATTACKING) {
			m_newState = SlimeState::IDLE;
		}
		else if (m_Clock.getElapsedTime().asSeconds() > m_getHitTime && m_state == SlimeState::GET_HIT) {
			m_newState = SlimeState::IDLE;
		}
	}
	//otrzymanie uderzenia
	else if (checkReceivedAttacks()) {
		m_newState = SlimeState::GET_HIT;
		m_Clock.restart();
	}
	else if (m_Clock.getElapsedTime().asSeconds() > m_attackCooldown && inRange(player))
	{
		attack(room);
		m_newState = SlimeState::ATTACKING;
		m_Clock.restart();
	}
	else if(m_state==SlimeState::IDLE || m_state == SlimeState::MOVING){
		move(deltaTime, player);
	}

	if (checkIfNewState()) {
		m_animations.startAnimation((int32_t)m_state, m_position);
	}
	m_animations.update(deltaTime);
}

void Slime::move(sf::Time& deltaTime) {
	
}


void Slime::move(float x, float y)
{
	m_position.x += x;
	m_position.y += y;
	m_hitbox.move({ x,y });
	m_texturebox.move({ x,y });
}
