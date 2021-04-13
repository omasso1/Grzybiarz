#pragma once
#include <array>
#include <memory>
#include "Player/Player.h"
#include "Level.h"

class World {
	std::unique_ptr<Character>& m_p_player;
	uint8_t currentLevel;
	std::unique_ptr<Level> m_p_level;


public:
	World(std::unique_ptr<Character>& player);
	void update(sf::Time& deltaTime);
	void draw();
	void input(sf::Event& e);
};