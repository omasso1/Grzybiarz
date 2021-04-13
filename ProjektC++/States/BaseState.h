#pragma once
#include <SFML/Graphics.hpp>
class Application;

namespace State {

	class BaseState {
	public:
		Application* m_p_Application;
		
	public:
		BaseState(Application* app);
		BaseState() = delete;
		BaseState(const BaseState& src) = default;
		BaseState(BaseState&& src) = default;
		BaseState& operator=(const BaseState& other) = default;
		BaseState& operator=(BaseState&& other) = default;
		virtual ~BaseState() = default;

		virtual void update(sf::Time& deltaTime) = 0;
		virtual void draw() = 0;
		virtual void input(sf::Event e) = 0;
	};

}