/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	
	checkDirection();
	move();
	m_marioSprite.setPosition(m_marioLocation);
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_marioSprite);

	m_window.draw(m_name);
	
	
	m_window.display();
}

void Game::checkDirection()
{
	m_direction = Direction::None;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_direction = Direction::Up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_direction = Direction::Down;
	}
}

void Game::move()
{
	sf::Vector2f velocity{0.0f,0.0f};//movement for this frame 
	switch (m_direction)
	{
	case Direction::None:
		break;
	case Direction::Down:
		velocity.y = m_speed;
		break;
	case Direction::Up:
		velocity.y = -m_speed;
		break;
	case Direction::Right:
		break;
	case Direction::Left:
		break;
	default:
		break;
	}
	m_marioLocation += velocity;
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_marioFont.loadFromFile("ASSETS\\FONTS\\SuperMario256.ttf"))
	{
		std::cout << "error fomt";
	}
	m_name.setFont(m_marioFont);
	m_name.setString("Mario");
	m_name.setCharacterSize(70U);
	m_name.setFillColor(sf::Color::Red);
	m_name.setOutlineColor(sf::Color::Black);
	m_name.setOutlineThickness(2.0f);

	m_name.setPosition(100.0f, 100.0f);

	

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_marioTexture.loadFromFile("ASSETS\\IMAGES\\mario-luigi-64.png"))
	{
		std::cout << "problem with mario image" << std::endl;
	}
	m_marioSprite.setTexture(m_marioTexture);
	m_marioSprite.setTextureRect(sf::IntRect{ 64,0,64,148 });
	m_marioLocation =  sf::Vector2f{ 32.0f,74.0f };
	m_marioSprite.setOrigin(32.0f, 74.0f);

	
}
