#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace sf;

class Bullet
{
private:
	Sprite shape;
	Texture t;
	Vector2f direction;
	float movementSpeed;

public:
	Bullet(Texture* t,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	virtual ~Bullet();

	//Accessors
	const FloatRect getBounds() const;

	void update();
	void render(RenderTarget* target);
};

