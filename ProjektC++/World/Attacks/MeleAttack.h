#pragma once
#include "Attack.h"


class MeleAttack : public Attack {
protected:


public:
	MeleAttack(Character* source,const sf::RectangleShape& hitbox, const sf::Vector2f& attackOffset, float lifetime, float castTime, void (*effectFunc)(Character& target) = nullptr);
	MeleAttack() = delete;
	MeleAttack(const MeleAttack& src) = default;
	MeleAttack(MeleAttack&& src) = default;
	MeleAttack& operator=(const MeleAttack& other) = default;
	MeleAttack& operator=(MeleAttack&& other) = default;
	virtual ~MeleAttack() = default;

	virtual void draw() override;
	virtual void update(sf::Time& deltaTime) override;
	virtual inline std::unique_ptr<Attack> clone() override { return std::make_unique<MeleAttack>(*this); }

};