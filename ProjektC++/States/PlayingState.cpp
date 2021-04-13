#include "PlayingState.h"
#include "../World/World.h"
#include "../Application.h"
#include "PlayerDeathState.h"
namespace State {
	Playing::Playing(Application* app)
		:BaseState(app),m_p_player(std::make_unique<Player>(sf::Vector2f(DEF_WIDTH / 2, DEF_HEIGHT / 2))),m_world(m_p_player)
	{
	}

	void Playing::update(sf::Time& deltaTime)
	{
		m_world.update(deltaTime);
		if (m_p_player->getHealth() <= 0) {
			m_p_Application->pushState(std::make_unique<State::PlayerDeath>(m_p_Application));
		}
	}

	void Playing::draw()
	{
		m_world.draw();
	}

	void Playing::input(sf::Event e)
	{
		m_world.input(e);
	}

}