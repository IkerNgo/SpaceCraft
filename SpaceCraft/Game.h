#pragma once
#include "Player.h"
#include<map>
#include <vector>
#include "Bullet.h"
#include "Enemy.h"
#include<string>
#include<sstream>

class Game
{
private:
	//Window
	RenderWindow* window;
	VideoMode videoMode;
	Event e;

	//Resource
	std::map <std::string, Texture*> textures;
	std::vector<Bullet*> bullet;

	//Player
	Player* player;

	//PlayerGUI
	RectangleShape playerHpBar;
	RectangleShape playerHpBarBack;

	//Enemy
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;

	//GUI
	Font font;
	Text textPoints;

	Text gameOverText;

	//Background
	Sprite worldBackground;
	Texture backgroundTex;

	//System
	unsigned points;

	//Functions
	void initVariables();
	void initTextures();
	void initWindow();
	void initPlayer();
	void initEnemies();
	void initGUI();
	void initWorld();
	void initSystem();

public:
	//Contructors & Destructors
	Game();
	virtual ~Game();

	//Accessors
	const bool running() const;

	//Functions
	void pollEvent();
	int getHptoMain();
	void playerMove();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateGUI();
	void update();
	void renderGUI();
	void renderWorld();
	void render();
};

