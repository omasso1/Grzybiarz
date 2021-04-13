#include "Level.h"
#include <string>
#include <iostream>
#include <stack>
#include "../Display.h"
#include <iomanip>
Level::Level(uint8_t levelNumber)
	:m_levelNumber(levelNumber)
{
	loadTextures();
    generateLevel();
    m_currentRoomIndex = { 0,0 };
	m_p_currentRoom = m_p_rooms[m_currentRoomIndex.second][m_currentRoomIndex.first];
}

void Level::loadTextures()
{
	std::string path = ".\\World\\Levels\\" + std::to_string(m_levelNumber);
	if (!m_wallTexture.loadFromFile(path + "\\" + "wall.png"))		std::cerr << "Nie udalo sie zaladowac tekstury wall " << std::endl;
	if(!m_floorTexture.loadFromFile(path + "\\" + "floor.png"))		std::cerr << "Nie udalo sie zaladowac tekstury floor " << std::endl;
	if(!m_obstacleTexture.loadFromFile(path + "\\" + "obstacle.png"))	std::cerr << "Nie udalo sie zaladowac tekstury obstacle " << std::endl;

}

void Level::draw()
{
	m_p_currentRoom->draw();
    /*system("cls");
    for (int y = 0; y < m_p_rooms.size(); y++) {
        for (int x = 0; x < m_p_rooms[y].size(); x++) {
            std::cout << std::setw(2);
            std::cout << (int)m_p_rooms[y][x]->getRoomNumber()<< " ";
        }
       std::cout << std::endl;
    }*/
}

void Level::update(std::unique_ptr<Character>& player,sf::Time& deltaTime)
{
	m_p_currentRoom->update(player,deltaTime);
	if (m_p_currentRoom->isFinished()) {
        //Przejscie w prawo
		if (player->getPosition().x > Display::getSize().x) {
			player->setPosition(Display::getTileSize().x, player->getPosition().y);
            m_currentRoomIndex.first++;
			m_p_currentRoom = m_p_rooms[m_currentRoomIndex.second][m_currentRoomIndex.first];
		}
        //Przejscie w lewo
        else if (player->getPosition().x < 0 ) {
            player->setPosition(Display::getSize().x - Display::getTileSize().x, player->getPosition().y);
            m_currentRoomIndex.first--;
            m_p_currentRoom = m_p_rooms[m_currentRoomIndex.second][m_currentRoomIndex.first];
        }
        //Przejscie w gore
        else if (player->getPosition().y < 0) {
            player->setPosition(player->getPosition().x, Display::getSize().y - Display::getTileSize().y);
            m_currentRoomIndex.second--;
            m_p_currentRoom = m_p_rooms[m_currentRoomIndex.second][m_currentRoomIndex.first];
        }
        //Przejscie w dol
        else if (player->getPosition().y > Display::getSize().y) {
            player->setPosition(player->getPosition().x, Display::getTileSize().y);
            m_currentRoomIndex.second++;
            m_p_currentRoom = m_p_rooms[m_currentRoomIndex.second][m_currentRoomIndex.first];
        }
	}
}

void Level::generateLevel() {
    enum class DIRECTION : int {
        NORTH = 1,
        EAST = 2,
        SOUTH = 4,
        WEST = 8,
        VISITED = 16
    };

    srand(time(NULL));
    std::stack<std::pair<size_t, size_t>> visited_coord;
    std::vector<int> tiles;
    size_t width = 5;
    size_t height = 5;
    int size = 1;
    tiles.resize(width * height);

    auto offset = [&](size_t x, size_t y) {return (visited_coord.top().second + y) * width + visited_coord.top().first + x; };
    visited_coord.push({ 0,0 });
    tiles[0] = (int)DIRECTION::VISITED;
    //generowanie szablonu na pokoje
    while (size < width * height) {
        std::vector<DIRECTION> available_neghbours(0);
        if (visited_coord.top().second > 0 && (tiles[offset(0, -1)] & (int)DIRECTION::VISITED) == 0)
            available_neghbours.push_back(DIRECTION::NORTH);
        if (visited_coord.top().first < width - 1 && (tiles[offset(1, 0)] & (int)DIRECTION::VISITED) == 0)
            available_neghbours.push_back(DIRECTION::EAST);
        if (visited_coord.top().second < height - 1 && (tiles[offset(0, 1)] & (int)DIRECTION::VISITED) == 0)
            available_neghbours.push_back(DIRECTION::SOUTH);
        if (visited_coord.top().first > 0 && (tiles[offset(-1, 0)] & (int)DIRECTION::VISITED) == 0)
            available_neghbours.push_back(DIRECTION::WEST);


        if (available_neghbours.size()) {
            DIRECTION new_direction = available_neghbours[rand() % available_neghbours.size()];
            switch (new_direction) {
            case DIRECTION::NORTH:
                tiles[offset(0, 0)] |= (int)DIRECTION::NORTH;
                tiles[offset(0, -1)] |= (int)DIRECTION::SOUTH | (int)DIRECTION::VISITED;
                visited_coord.push({ visited_coord.top().first,visited_coord.top().second - 1 });
                break;
            case DIRECTION::EAST:
                tiles[offset(0, 0)] |= (int)DIRECTION::EAST;
                tiles[offset(1, 0)] |= (int)DIRECTION::WEST | (int)DIRECTION::VISITED;
                visited_coord.push({ visited_coord.top().first + 1,visited_coord.top().second });
                break;
            case DIRECTION::SOUTH:
                tiles[offset(0, 0)] |= (int)DIRECTION::SOUTH;
                tiles[offset(0, 1)] |= (int)DIRECTION::NORTH | (int)DIRECTION::VISITED;
                visited_coord.push({ visited_coord.top().first,visited_coord.top().second + 1 });
                break;
            case DIRECTION::WEST:
                tiles[offset(0, 0)] |= (int)DIRECTION::WEST;
                tiles[offset(-1, 0)] |= (int)DIRECTION::EAST | (int)DIRECTION::VISITED;
                visited_coord.push({ visited_coord.top().first - 1,visited_coord.top().second });
                break;
            default:
                break;
            }
            size++;

        }
        else {
            visited_coord.pop();
        }
    }
    //generowanie pokoi
    m_p_rooms.resize(height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            m_p_rooms[y].push_back(std::make_shared<Room>(m_levelNumber, (uint8_t)tiles[y * width + x] - (uint8_t)DIRECTION::VISITED, m_wallTexture, m_floorTexture, m_obstacleTexture));
        }
    }
}

