#include "Player.h"
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Time.hpp>
#include "../../functions.h"
#include "../../DebugDefines.h"
#include "../Room.h"

#define ATTACK_SIZE 30.f
Player::Player(sf::Vector2f position, float speed, sf::Vector2f hitboxSize)
	:Character(sf::RectangleShape(hitboxSize),position,speed),m_hitboxSize(hitboxSize), m_faceRight(true), m_attackCooldown(0.33),
	m_basicAttack(this,sf::RectangleShape({ ATTACK_SIZE,m_hitbox.getSize().y, }), sf::Vector2f(m_hitbox.getSize().x/2.f + ATTACK_SIZE/2,0), 0.20f, 0.13f,
		[](Character& target) {target.changeHealth(-10.f); })
{
	m_state = PlayerState::IDLE;
	m_newState = PlayerState::IDLE;
	m_hitbox.setPosition(m_position);
	m_hitbox.setSize(m_hitboxSize);
	m_p_animations.addAnimation("./World/Player/Textures/", "playerIdle", (int32_t)PlayerState::IDLE, m_texturebox,m_faceRight);
	m_p_animations.addAnimation("./World/Player/Textures/", "playerRun", (int32_t)PlayerState::MOVING, m_texturebox, m_faceRight);
	m_p_animations.addAnimation("./World/Player/Textures/", "playerAttack1", (int32_t)PlayerState::ATTACKING, m_texturebox, m_faceRight);

	m_p_animations.startAnimation((int32_t)m_state, m_position);
	DEBUG_FUNC(m_texturebox.setOutlineColor(sf::Color(0, 0, 0)));
	DEBUG_FUNC(m_texturebox.setOutlineThickness(3));
	DEBUG_FUNC(m_hitbox.setOutlineColor(sf::Color(255, 0, 0)));
	DEBUG_FUNC(m_hitbox.setOutlineThickness(1));
	DEBUG_FUNC(m_hitbox.setFillColor(sf::Color(0, 0, 0, 0)));
	
}

void Player::draw()
{
	m_p_animations.draw();
	DEBUG_FUNC(Display::draw(m_hitbox));

}

void Player::attack(Room& room) {	
	if (m_faceRight) {
		m_basicAttack.setPosition({ m_position + m_basicAttack.getAttackOffset() });
	}
	else {
		m_basicAttack.setPosition({ m_position - m_basicAttack.getAttackOffset() });
	}
	room.addAttack(m_basicAttack.clone());
}

typedef sf::Keyboard::Key key;
bool Player::checkAttackKey()
{
	if (sf::Keyboard::isKeyPressed(key::Space))
		return true;
	else
		return false;
}

bool Player::checkMoveKeys()
{
	if (sf::Keyboard::isKeyPressed(key::A) || sf::Keyboard::isKeyPressed(key::W) || sf::Keyboard::isKeyPressed(key::S) || sf::Keyboard::isKeyPressed(key::D))
		return true;
	else
		return false;
}

void Player::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_hitbox.setPosition(position);
	m_p_animations.recalculateTexturePosition(m_position);
}

void Player::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
	m_hitbox.setPosition(m_position);
	m_p_animations.recalculateTexturePosition(m_position);
}

void Player::checkPressedKeys(sf::Time& deltaTime, Room& room) {
	//Reset czasu odnowienia ataku
	if (m_state == PlayerState::ATTACKING) {
		if (m_attackClock.getElapsedTime().asSeconds() > m_attackCooldown) {
			m_newState = PlayerState::IDLE;
		}
	}
	//Atak
	else if (checkAttackKey() && m_attackClock.getElapsedTime().asSeconds() > m_attackCooldown) {
		move(deltaTime);
		attack(room);
		m_attackClock.restart();
		m_newState = PlayerState::ATTACKING;
	}
	//Ruch
	else if(checkMoveKeys() && m_state != PlayerState::ATTACKING){
		move(deltaTime);
		m_newState = PlayerState::MOVING;
	}
	//Zmiana stanu na nic nie robienie
	else {
		m_newState = PlayerState::IDLE;
	}
}

bool Player::checkIfNewState() {
	if (m_newState != m_state) {
		m_state = m_newState;
		return true;
	}
	return false;
}

void Player::input(sf::Event& e)
{
}


void Player::update(sf::Time& deltaTime, Room& room) {
	checkPressedKeys(deltaTime,room);
	if (checkReceivedAttacks()) {
		std::cout << m_health << std::endl;
	}

	if (checkIfNewState()) {
		m_p_animations.startAnimation((int32_t)m_state, m_position);
	}
	m_p_animations.update(deltaTime);
}


void Player::move(sf::Time& deltaTime) {
	sf::Vector2f v(0, 0);


	if (sf::Keyboard::isKeyPressed(key::A)) {
		v.x -= 1;
	}
	if (sf::Keyboard::isKeyPressed(key::D)) {
		v.x += 1;
	}
	if (sf::Keyboard::isKeyPressed(key::W)) {
		v.y -= 1;
	}
	if (sf::Keyboard::isKeyPressed(key::S)) {
		v.y += 1;
	}

	if (v.x || v.y) {
		if (v.x > 0) {
			m_faceRight = true;
		}
		else if(v.x<0){
			m_faceRight = false;
		}
		v = normalizeVector(v) * m_speed * deltaTime.asSeconds();
		m_position += v;
		m_hitbox.move(v);
		m_texturebox.move(v);
	}
}


void Player::move(float x, float y)
{
	m_position.x += x;
	m_position.y += y;
	m_hitbox.move({ x,y });
	m_texturebox.move({ x,y });
}
