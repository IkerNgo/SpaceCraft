#pragma once

#include<iostream>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

using namespace sf;

class Player
{
private:
	Sprite sprite;
	Texture texture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;

	//Private function
	void initVariables();
	void initSprite();
	void initTexture();

public:
	Player();
	~Player();

	//Accessors
	const Vector2f& getPos() const;
	const FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	//Function
	void move(const float dirX, const float dirY);
	const bool canAttack();
	void updateAttack();

	void update();
	void render(RenderTarget& target);
};

