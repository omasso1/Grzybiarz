#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/System/Vector2.hpp>
#include "Room.h"
#include "Tiles/AllTiles.h"
#include "../Display.h"
#include "Enemies/Slime/Slime.h"

Room::Room(uint8_t levelNumber, uint8_t roomNumber, sf::Texture& wallTexture, sf::Texture& floorTexture, sf::Texture& obstacleTexture)
	:m_p_floorTexture(&floorTexture), m_p_obstacleTexture(&obstacleTexture), m_p_wallTexture(&wallTexture),m_roomNumber(roomNumber)
{
	std::string path = ".\\World\\Levels\\" + std::to_string(levelNumber);
	loadRoom(path, roomNumber);
}

void Room::draw() {
	for (auto& it1 : m_p_Tiles) {
		for (auto& it2 : it1) {
			it2->draw();
		}
	}
	for (auto& enemy : m_p_enemies) {
		enemy->draw();
	}

	for (auto& attack : m_p_attacks) {
		attack->draw();
	}
}


void Room::checkCollisionsWithTiles(std::unique_ptr<Character>& character) {
	for (auto& it1 : m_p_Tiles) {
		for (auto& it2 : it1) {
			if (it2->isObstacle()) {
				character->getCollider().checkCollisionAndPush(it2->getCollider(),0.0);
			}
		}
	}
}



void Room::update(std::unique_ptr<Character>& Player, sf::Time& deltaTime)
{
	//Zaktualizowanie pozycji obiektow nalezyacych do pokoju
	for (auto& attack : m_p_attacks) {
		attack->update(deltaTime);
	}

	//TODO!!!! Jak skoncze to zastanowic sie nad zamiana wszystkich tablicami unique_ptr, zeby moze to inaczej zorganizowac
	for (auto& enemy : m_p_enemies) {
		static_cast<Enemy*>(enemy.get())->update(deltaTime,*this,Player);
	}	

	//sprawdzenie kolizji
	checkCollisionsWithTiles(Player);
	for (auto& enemy : m_p_enemies) {
		checkCollisionsWithTiles(enemy);
		checkCollisionAndPush(Player.get(), enemy.get());

		//sprawdzenie kolizji pomiedzy przeciwnikami
		/*for (auto& e : m_p_enemies) {
			if(e !=enemy)
				checkCollisionAndPush(e.get(), enemy.get());
		}*/
	}

	//sprawdzenie czy przeciwnicy zyja
	m_p_enemies.erase(std::remove_if(m_p_enemies.begin(), m_p_enemies.end(), [](std::unique_ptr<Character>& e) {return e->getHealth() <= 0; }), m_p_enemies.end());

	//sprawdzenie atakow
	m_p_attacks.erase(std::remove_if(m_p_attacks.begin(), m_p_attacks.end(), [](std::unique_ptr<Attack>& attack) {return attack->isNotLive(); }),m_p_attacks.end());

	for (auto& attack : m_p_attacks) {
		if (attack->isCasted()) {
			//nie ma friendly fire i ranienia samego siebie, przynajmniej narazie
			//I to attack-clone() zdecydowanie da sie lepiej rozwianac TODO!!!!!!!!!
			if (attack->getSource() != Player.get() && attack->didntHitBefore(Player.get())) {
				if (checkCollision(Player.get(), attack.get())) {
					attack->hit(Player);
				}
			}
			for (auto& enemy : m_p_enemies) {
				if (attack->getSource() != enemy.get() && attack->didntHitBefore(enemy.get())) {
					if (checkCollision(enemy.get(), attack.get())) {
						attack->hit(enemy);
						std::cout << "Hit enemy" << std::endl;
					}
				}
			}
		}
	}

	if (m_p_enemies.size() == 0) {
		endRoom();
	}
}


bool Room::checkCollisionAndPush(Entity* first,Entity* second)
{
	return	first->getCollider().checkCollisionAndPush(second->getCollider(), 0.5f);
}

void Room::endRoom()
{
	for (auto& it : m_p_Tiles)
		for (auto& tile : it)
			tile->endOfRoom();
	m_roomFinished = true;
}

bool Room::checkCollision(Entity* first, Entity* second)
{
	return	first->getCollider().checkCollision(second->getCollider());
}


void Room::loadRoom(std::string& path, uint8_t roomNumber){
	std::string fullPath = path + "\\layout" + std::to_string(roomNumber) + ".txt";
	std::ifstream file(fullPath);
	if (file.good()) {
		m_p_Tiles.reserve(ROWS);
		int type;

		for (size_t i = 0; i < ROWS; i++) {
			m_p_Tiles.push_back(std::vector<std::unique_ptr<Tile::BaseTile>>());
			m_p_Tiles[i].reserve(COLS);
			for (size_t j = 0; j < COLS; j++) {
				file >> type;
				sf::Vector2f tilePosition(j * TILE_WIDTH + TILE_WIDTH/2.f, i * TILE_HEIGHT + TILE_HEIGHT/2.f);
				switch (static_cast<Tile::Type>(type)) {
					case Tile::Type::FLOOR:
						m_p_Tiles[i].emplace_back(std::make_unique<Tile::Floor>(tilePosition,*m_p_floorTexture));
						break;

					case Tile::Type::WALL:
						m_p_Tiles[i].emplace_back(std::make_unique<Tile::Wall>(tilePosition, *m_p_wallTexture));
						break;

					case Tile::Type::OBSTACLE:
						m_p_Tiles[i].emplace_back(std::make_unique<Tile::Obstacle>(tilePosition, *m_p_obstacleTexture));
						break;

					case Tile::Type::ENEMY_SPAWN_POINT:
						m_p_Tiles[i].emplace_back(std::make_unique<Tile::Floor>(tilePosition, *m_p_floorTexture));
						m_p_enemies.emplace_back(std::make_unique<Slime>(tilePosition));
						break;
					case Tile::Type::DOOR:
						m_p_Tiles[i].emplace_back(std::make_unique<Tile::Door>(tilePosition, *m_p_obstacleTexture,*m_p_floorTexture));
						break;
					default: 
						std::cerr << "Nie odpowiednia wartosc w pliku " + path + "\\layout.txt : " + std::to_string(type) << std::endl;
						exit(1);
						break;
				}

			}
		}
	}
	else {
		std::cerr << "Nie udalo sie otworzyc pliku " + fullPath << std::endl;
		exit(1);
	}
}

