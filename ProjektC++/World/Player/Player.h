#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "../../Display.h"
#include "../Character.h"
#include "../../Animation.h"
#include "../Attacks/MeleAttack.h"


enum class PlayerState : int32_t {
	IDLE = 0,
	MOVING = 1,
	ATTACKING = 2
};

class Player : public Character{
private:
	sf::Vector2f m_hitboxSize;
	Animations m_p_animations;
	PlayerState m_state;
	PlayerState m_newState;
	float m_attackCooldown;
	sf::Clock m_attackClock;
	bool m_faceRight;
	MeleAttack m_basicAttack;

public:
	Player(sf::Vector2f position = { DEF_WIDTH / 2, DEF_HEIGHT / 2 }, float speed = 650, sf::Vector2f hitboxSize = { 58,66 });
	void move(sf::Time& deltaTime) override;
	void update(sf::Time& deltaTime, Room& world) override;
	void draw() override;
	void move(float x, float y) override;
	void checkPressedKeys(sf::Time& deltaTime,Room& room);
	bool checkIfNewState();
	void input(sf::Event& e);
	void attack(Room& room);
	bool checkAttackKey();
	bool checkMoveKeys();
	virtual void setPosition(sf::Vector2f position) override;
	virtual void setPosition(float x, float y) override;
};