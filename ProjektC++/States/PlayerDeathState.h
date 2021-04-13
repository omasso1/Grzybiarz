#pragma once
#include "BaseState.h"
#include <iostream>
namespace State {
	class PlayerDeath :public BaseState {

	protected:

	public:
		PlayerDeath(Application* app);
		PlayerDeath() = delete;
		PlayerDeath(const PlayerDeath& src) = default;
		PlayerDeath(PlayerDeath&& src) = default;
		PlayerDeath& operator=(const PlayerDeath& other) = default;
		PlayerDeath& operator=(PlayerDeath&& other) = default;
		virtual ~PlayerDeath() = default;
		virtual void update(sf::Time& deltaTime) override;
		virtual void draw() override;
		virtual void input(sf::Event e) override { std::cout << e.type << std::endl; }

	};
}
