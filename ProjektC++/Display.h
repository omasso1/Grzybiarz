#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "States/BaseState.h"
#define DEF_WIDTH 1200
#define DEF_HEIGHT 800
#define COLS 15
#define ROWS 10
#define TILE_WIDTH DEF_WIDTH/COLS
#define TILE_HEIGHT DEF_HEIGHT/ROWS



namespace Display{
	void init();
	void draw(sf::Drawable& object);
	void update();
	bool isOpen();
	void checkIfClose(sf::Event& e);
	void pollEvents(State::BaseState& state);
	void setClearColor(sf::Color& color);
	void clear();
	sf::Vector2u getSize();
	sf::Vector2f getTileSize();


};