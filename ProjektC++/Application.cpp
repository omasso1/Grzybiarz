#include "Application.h"
#include "Display.h"
#include "States/PlayingState.h"

Application::Application()
{
	Display::init();
	m_states.push(std::make_unique<State::Playing>(this));
}

void Application::runMainLoop()
{
	while (Display::isOpen()) {
		Display::clear();
		m_deltaTime = m_clock.restart();
		Display::pollEvents(*m_states.top());

		m_states.top()->update(m_deltaTime);
		m_states.top()->draw();

		Display::update();
	}
}

void Application::popState()
{
	m_states.pop();
}

void Application::pushState(std::unique_ptr<State::BaseState> newState)
{
	m_states.emplace(std::move(newState));
}

