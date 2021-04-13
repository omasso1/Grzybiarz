#pragma once
#include <vector>
#include <memory>
#include <string>
#include <stdint.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

class SingleAnimation {
public:
	sf::Texture m_p_texture;
	float m_actualTime;
	float m_switchTime;
	float m_animationDuration;
	sf::RectangleShape& m_texturebox;
	sf::IntRect m_textureRect;
	sf::Vector2u m_currentImage;
	uint32_t m_numerOfFrames;
	bool& m_faceRight;
	sf::Vector2f m_textureOffset;
public:
	SingleAnimation() = default;
	SingleAnimation(SingleAnimation&&) = default;
	SingleAnimation& operator=(const SingleAnimation&) = default;
	SingleAnimation& operator=(SingleAnimation&&) = default;
	~SingleAnimation() = default;
	SingleAnimation(const std::string& path, const std::string& name, sf::RectangleShape& texturebox,bool& faceRight);

	void start(sf::Vector2f& playerPosition);
	void reset();
	void draw();
	void update(sf::Time& deltaTime);
	inline float getAnimationDuration() { return m_animationDuration; }
	inline void setFaceRight(bool r) { m_faceRight = r; }
	sf::Vector2f getTextureOffset() { return m_textureOffset; }
};

class Animations {
public:
	std::vector<std::unique_ptr<SingleAnimation>> m_p_animations;
	int32_t m_actualAnimationIndex;

public:
	Animations();
	Animations(const Animations&) = default;
	Animations(Animations&&) = default;
	Animations& operator=(const Animations&) = default;
	Animations& operator=(Animations&&) = default;
	~Animations() = default;

	void addAnimation(const std::string& path, const std::string& name, int32_t index, sf::RectangleShape& texturebox, bool& playerFaceRight);
	void startAnimation(int32_t index,sf::Vector2f& playerPosition);
	void update(sf::Time& deltaTime);
	void setFaceRight(bool r);
	void draw();
	void recalculateTexturePosition(sf::Vector2f& position);
	inline std::unique_ptr<SingleAnimation>& getActualAnimation() { return m_p_animations[m_actualAnimationIndex]; }
	inline std::unique_ptr<SingleAnimation>& getAnimation(int32_t index) { return m_p_animations[index]; }
	sf::Vector2f getTextureOffset();

};


