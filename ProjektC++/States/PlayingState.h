#pragma once

#include <memory>
#include "BaseState.h"
#include "../World/World.h"
#include "../World/Player/Player.h"

namespace State {
	class Playing : public BaseState {
	protected:
		std::unique_ptr<Character> m_p_player;
		World m_world;
	public:
		Playing(Application* app);
		Playing() = delete;
		Playing(const Playing& src) = default;
		Playing(Playing&& src) = default;
		Playing& operator=(const Playing& other) = default;
		Playing& operator=(Playing&& other) = default;
		virtual ~Playing() = default;

		void update(sf::Time& deltaTime) override;
		void draw() override;
		void input(sf::Event e) override;
	};
}