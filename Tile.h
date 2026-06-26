#pragma once
#include <SFML/Graphics.hpp>

class Tile {
public:
    bool revealed = false;
    bool flagged = false;
    bool isMine = false;
    int adjacentMines = 0;

    void draw(sf::RenderWindow& window, sf::Sprite& hidden,
              sf::Sprite& revealedSprite, sf::Sprite& flagSprite,
              int x, int y);
};