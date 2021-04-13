#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>
#include "States/BaseState.h"

class Application {
private:
	std::stack<std::unique_ptr<State::BaseState>> m_states;
	sf::Clock m_clock;
	sf::Time m_deltaTime;
public:
	Application();
	void runMainLoop();
	void popState();
	void pushState(std::unique_ptr<State::BaseState> newState);
};