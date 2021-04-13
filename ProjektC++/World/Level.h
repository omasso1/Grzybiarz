#pragma once
#include <vector>
#include "Room.h"
class Level {
private:
	uint8_t m_levelNumber;
	std::vector<std::vector<std::shared_ptr<Room>>> m_p_rooms;
	std::shared_ptr<Room> m_p_currentRoom;
	std::pair<size_t, size_t> m_currentRoomIndex;
	sf::Texture m_wallTexture;
	sf::Texture m_floorTexture;
	sf::Texture m_obstacleTexture;
public:
	Level(uint8_t levelNumber);
	void loadTextures();
	void draw();
	void update(std::unique_ptr<Character>& player, sf::Time& deltaTime);
	inline std::shared_ptr<Room> getCurrentRoom() { return m_p_currentRoom; }
	void generateLevel();
};