#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Board {
private:
    int cols, rows, mines;
    std::vector<std::vector<Tile>> grid;

    sf::Texture hiddenTex, revealedTex, flagTex;
    sf::Sprite hiddenSprite, revealedSprite, flagSprite;

    void placeMines();
    void calculateNumbers();
    void floodFill(int x, int y);

public:
    Board(int c, int r, int m);
    void draw(sf::RenderWindow& window);
    void reveal(int x, int y);
    void toggleFlag(int x, int y);
};