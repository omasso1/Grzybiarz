#include "PlayerDeathState.h"

State::PlayerDeath::PlayerDeath(Application* app)
	:BaseState(app)
{
	std::cout << "Przegrales" << std::endl;
}

void State::PlayerDeath::update(sf::Time& deltaTime)
{
}

void State::PlayerDeath::draw()
{
}
