#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tiles/BaseTile.h"
#include "Character.h"
#include "Attacks/Attack.h"

class Room {
private:
	std::vector<std::vector<std::unique_ptr<Tile::BaseTile>>> m_p_Tiles;
	std::vector<std::unique_ptr<Character>> m_p_enemies;
	std::vector<std::unique_ptr<Attack>> m_p_attacks;
	uint8_t m_roomNumber;
	
	sf::Texture* m_p_wallTexture;
	sf::Texture* m_p_floorTexture;
	sf::Texture* m_p_obstacleTexture;

	bool m_roomFinished;
public:
	Room(uint8_t levelNumber, uint8_t roomNumber, sf::Texture& wallTexture, sf::Texture& floorTexture, sf::Texture& obstacleTexture);
	void draw();
	void loadRoom(std::string& path,uint8_t roomNumber);
	void checkCollisionsWithTiles(std::unique_ptr<Character>& character);
	void update(std::unique_ptr<Character>& Player,sf::Time& deltaTime);
	bool checkCollision(Entity* first, Entity* second);
	bool checkCollisionAndPush(Entity* first, Entity* second);
	void endRoom();
	void inline addAttack(std::unique_ptr<Attack> attack) { m_p_attacks.emplace_back(std::move(attack)); }
	bool inline isFinished() { return m_roomFinished; }
	uint8_t inline getRoomNumber() { return m_roomNumber; }
};