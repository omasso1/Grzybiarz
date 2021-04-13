#include "Animation.h"
#include "Display.h"
#include <fstream>
#include <iostream>
SingleAnimation::SingleAnimation(const std::string& path, const std::string& name, sf::RectangleShape& texturebox,bool& faceRight)
	:m_faceRight(faceRight),m_texturebox(texturebox), m_textureRect(), m_actualTime(),m_currentImage(0,0)
{
	m_p_texture.loadFromFile(path + name + ".png");

	std::fstream file(path + name + ".data",std::ios::in);
	if (file) {
		file >> m_textureRect.width;
		file >> m_textureRect.height;
		file >> m_textureOffset.x;
		file >> m_textureOffset.y;
		file >> m_numerOfFrames;
		file >> m_animationDuration;
		m_switchTime = m_animationDuration / m_numerOfFrames;
		if(file.fail())
			throw std::runtime_error("Nie udalo sie zaladowac pliku: " + path + name+".data");
	}
	else {
		throw std::runtime_error("Nie udalo sie zaladowac pliku: " + path + name+".data");
	}
	file.close();
}



void SingleAnimation::start(sf::Vector2f& playerPosition)
{
	m_texturebox.setSize({(float)abs(m_textureRect.width),(float)abs(m_textureRect.height) });
	m_texturebox.setTexture(&m_p_texture);
	m_texturebox.setPosition(playerPosition - m_textureOffset);
}

void SingleAnimation::reset()
{
	m_actualTime = 0;
}

void SingleAnimation::draw()
{
	Display::draw(m_texturebox);
}

void SingleAnimation::update(sf::Time& deltaTime)
{
	m_actualTime += deltaTime.asSeconds();
	if (m_actualTime >= m_switchTime) {
		m_actualTime -= m_switchTime;
		m_currentImage.x++;
		if (m_currentImage.x >= m_numerOfFrames)
			m_currentImage.x = 0;
	}

	if (m_faceRight) {
		m_textureRect.width = abs(m_textureRect.width);
		m_textureRect.left = m_currentImage.x * m_textureRect.width;
	}
	else {
		m_textureRect.left = (m_currentImage.x + 1) * abs(m_textureRect.width);
		m_textureRect.width = -abs(m_textureRect.width);
	}
	m_textureRect.top = m_currentImage.y * m_textureRect.height;
	m_texturebox.setTextureRect(m_textureRect);
}

Animations::Animations()
	:m_actualAnimationIndex(-1),m_p_animations(0)
{
}

void Animations::addAnimation(const std::string& path, const std::string& name, int32_t index, sf::RectangleShape& texturebox,bool& playerFaceRight)
{

	if (m_p_animations.size() <= index)
		m_p_animations.resize((size_t)index +1);
	m_p_animations.emplace(m_p_animations.begin() + index, std::make_unique<SingleAnimation>(path, name,texturebox, playerFaceRight));
}

void Animations::startAnimation(int32_t index,sf::Vector2f& playerPosition)
{
	if (index > -1 && index < m_p_animations.size()) {	
		if (m_actualAnimationIndex != -1)
			m_p_animations[m_actualAnimationIndex]->reset();
		m_actualAnimationIndex = index;
		m_p_animations[m_actualAnimationIndex]->start(playerPosition);
	}
}

void Animations::update(sf::Time& deltaTime)
{
	if (m_actualAnimationIndex != -1) {
		m_p_animations[m_actualAnimationIndex]->update(deltaTime);
	}
}

void Animations::setFaceRight(bool r)
{
	if (m_actualAnimationIndex != -1) {
		m_p_animations[m_actualAnimationIndex]->setFaceRight(r);
	}
}

void Animations::draw()
{
	if (m_actualAnimationIndex != -1) {
		m_p_animations[m_actualAnimationIndex]->draw();
	}
}

void Animations::recalculateTexturePosition(sf::Vector2f& playerPosition)
{
	m_p_animations[m_actualAnimationIndex]->start(playerPosition);
}

sf::Vector2f Animations::getTextureOffset()
{
	if (m_actualAnimationIndex != -1) {
		return m_p_animations[m_actualAnimationIndex]->getTextureOffset();
	}
	return sf::Vector2f(0,0);
}
