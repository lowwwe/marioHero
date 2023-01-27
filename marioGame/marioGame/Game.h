/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


enum class Direction
{
	None,
	Down,
	Up,
	Right,
	Left
};


class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void checkDirection();
	void move();
	void changeCharacter();
	void processKeyReleases(sf::Event t_event);
	void setupFontAndText();
	void setupSprite();
	void centreText(sf::Text& t_text, float t_y);

	sf::RenderWindow m_window; // main SFML window
	
	
	sf::Font m_marioFont; // fomt for name
	sf::Text m_name; // text for name


	bool m_exitGame; // control exiting game
	Direction m_direction{ Direction::None };

	sf::Texture m_marioTexture; //texture used for mario and luigi
	sf::Sprite m_marioSprite;  // sprite for mario and luigi
	sf::Vector2f m_marioLocation; // marios location belly button
	float m_speed = 2.45f; // speed that marioo maove at
	bool m_isaMario{ false };// is the character mario
	bool m_canChange{ true };

	sf::SoundBuffer m_buffer;
	sf::Sound m_sound;
};

#endif // !GAME_HPP

