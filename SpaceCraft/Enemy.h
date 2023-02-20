#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace sf;

class Enemy
{
private:
	unsigned pointCount;
	CircleShape shape;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initShape();


public:
	Enemy(float pos_x,float pos_y);
	virtual ~Enemy();

	const FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	void update();
	void render(RenderTarget* target);

};

