#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "../../../Display.h"
#include "../Enemy.h"
#include "../../../Animation.h"
#include "../../Attacks/MeleAttack.h"


enum class SlimeState : int32_t {
	IDLE = 0,
	MOVING = 1,
	ATTACKING = 2,
	GET_HIT = 3,
	DIE = 4
};

class Slime : public Enemy {
private:
	Animations m_animations;
	SlimeState m_state;
	SlimeState m_newState;
	MeleAttack m_basicAttack;
public:
	Slime(sf::Vector2f position = { DEF_WIDTH / 2, DEF_HEIGHT / 2 }, float speed = 300, sf::Vector2f hitboxSize = { 85,42 });
	void move(sf::Time& deltaTime) override;
	void update(sf::Time& deltaTime, Room& world, std::unique_ptr<Character>& player) override;
	void draw() override;
	void move(sf::Time& deltaTime, std::unique_ptr<Character>& player);
	void move(float x, float y) override;
	bool checkIfNewState();
	void input(sf::Event& e);
	void attack(Room& room);
	bool inRange(std::unique_ptr<Character>& character);
};