#include "World.h"

World::World(std::unique_ptr<Character>& player)
	:m_p_player(player), currentLevel(1), m_p_level(std::make_unique<Level>(currentLevel))
{
	
}

void World::update(sf::Time& deltaTime)
{
	m_p_player->update(deltaTime,*m_p_level->getCurrentRoom().get());
	m_p_level->update(m_p_player,deltaTime);
	
	
}

void World::draw() {
	m_p_level->draw();
	m_p_player->draw();
}

void World::input(sf::Event& e)
{

}
