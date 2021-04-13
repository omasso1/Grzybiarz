#pragma once
#include <SFML/Graphics.hpp>
#include "../Collider.h"
#include "../Entity.h"
namespace Tile {
	enum class Type : int {
		FLOOR = 0,
		WALL = 1,
		OBSTACLE = 2,
		ENEMY_SPAWN_POINT = 3,
		DOOR = 4
	};

	class BaseTile : public Entity {
	protected:
		bool m_isObstacle;
	public:
		BaseTile(sf::Vector2f position, sf::Texture& texture, bool isObstacle);
		BaseTile() = delete;
		BaseTile(const BaseTile& src) = default;
		BaseTile(BaseTile&& src) = default;
		BaseTile& operator=(const BaseTile& src) = default;
		BaseTile& operator=(BaseTile&& src) = default;
		virtual ~BaseTile() = default;
		virtual void bindTexture(sf::Texture& texture);
		virtual void endOfRoom() { ; }
		void draw();
		inline bool isObstacle() const { return m_isObstacle; }

	};
}