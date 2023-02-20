#include "Game.h"

//Private functions
void Game::initVariables()
{

}

void Game::initTextures()
{
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("sperm1.png");
}

void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 1080;
	this->window = new RenderWindow(this->videoMode, "Game 1!", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);

}

void Game::initPlayer()
{
	this->player = new Player();

}

void Game::initEnemies()
{
	this->spawnTimerMax = 30.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initGUI()
{
	if (!this->font.loadFromFile("SVN-Block.ttf"))
		std::cout << "ERROR::Fail to load font!";

	this->textPoints.setFont(this->font);
	this->textPoints.setCharacterSize(20);
	this->textPoints.setFillColor(Color::White);
	this->textPoints.setString("test");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(this->window->getSize().x / 2 - this->gameOverText.getGlobalBounds().width / 2, this->window->getSize().y / 2 - this->gameOverText.getGlobalBounds().height / 2);

	//Init player GUI
	this->playerHpBar.setSize(Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(Color::Green);
	this->playerHpBar.setPosition(15.f, 40.f);
	this->playerHpBar.setOutlineThickness(2.0f);
	this->playerHpBar.setOutlineColor(Color::White);

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(Color::Red);
}

void Game::initWorld()
{
	if (!this->backgroundTex.loadFromFile("background.png"))
	{
		std::cout << "ERROR::Fail to load background texture!";
	}

	this->worldBackground.setTexture(this->backgroundTex);
}

void Game::initSystem()
{
	this->points = 0;
}

//Contructors & Destructors
Game::Game() 
{
	this->initVariables();
	this->initWindow();
	this->initPlayer();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystem();
	this->initEnemies();
}
Game::~Game()
{
	delete this->window;
	delete this->player;

	//Delete textures
	for (auto& i : this->textures)
	{
		delete i.second;
	}

	for (auto* i : this->bullet)
	{
		delete i;
	}

	for (auto* i : this->enemies)
	{
		delete i;
	}
}


//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}


void Game::pollEvent()
{
	while (this->window->pollEvent(this->e))
	{
		switch (this-> e.type)
		{
		case Event::Closed:
			this-> window->close();
			break;
		case Event::KeyPressed:
			if (this->e.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

int Game::getHptoMain()
{
	return this->player->getHp();
}

void Game::playerMove()
{
	if (Keyboard::isKeyPressed(Keyboard::A))
		this->player->move(-0.2f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::D))
		this->player->move(0.2f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::W))
		this->player->move(0.f, -0.2f);
	if (Keyboard::isKeyPressed(Keyboard::S))
		this->player->move(0.f, 0.2f);

	if (Mouse::isButtonPressed(Mouse::Left) && this->player->canAttack())
	{
		this->bullet.push_back(new Bullet(this->textures["BULLET"],this->player->getPos().x+this->player->getBounds().width/2-5, this->player->getPos().y, 0.f, -3.f, 5.f));
	}
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//Left world
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world
	if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}
	//Top world
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world
	if (this->player->getBounds().top + this->player->getBounds().height > this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter=0;
	for (auto* b : this->bullet)
	{
		b->update();

		//Delete bullet out the screen
		if (b->getBounds().top + b->getBounds().height < 0.f)
		{
			delete this->bullet.at(counter);
			this->bullet.erase(this->bullet.begin() + counter);
		}

		counter++;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand()%this->window->getSize().x, -100.f));
		this->spawnTimer = 0;
	}

	//Update
	unsigned counter = 0;
	for (auto* e : this->enemies)
	{
		e->update();

		//Delete bullet out the screen
		if (e->getBounds().top  > this->window->getSize().y)
		{
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		else if (e->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}

		counter++;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullet.size() && enemy_deleted==false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullet[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullet[k];
				this->bullet.erase(this->bullet.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " << this->points;
	this->textPoints.setString(ss.str());

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));
}

//Functions
void Game::update()
{
	this->pollEvent();
	this->playerMove();
	this->player->update();
	this->updateCollision();
	this->updateBullets();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->textPoints);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	this->renderWorld();

	this->player->render(*this->window);

	for (auto* bullet : this->bullet)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);

	this->window->display();
}
