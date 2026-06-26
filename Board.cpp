#include "Board.h"
#include <cstdlib>
#include <ctime>

Board::Board(int c, int r, int m) {
    cols = c;
    rows = r;
    mines = m;

    grid.resize(rows, std::vector<Tile>(cols));

    hiddenTex.loadFromFile("files/images/tile_hidden.png");
    revealedTex.loadFromFile("files/images/tile_revealed.png");
    flagTex.loadFromFile("files/images/flag.png");

    hiddenSprite.setTexture(hiddenTex);
    revealedSprite.setTexture(revealedTex);
    flagSprite.setTexture(flagTex);

    std::srand(std::time(nullptr));

    placeMines();
    calculateNumbers();
}

void Board::placeMines() {
    int placed = 0;

    while (placed < mines) {
        int x = rand() % cols;
        int y = rand() % rows;

        if (!grid[y][x].isMine) {
            grid[y][x].isMine = true;
            placed++;
        }
    }
}

void Board::calculateNumbers() {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {

            if (grid[y][x].isMine) continue;

            int count = 0;

            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx;
                    int ny = y + dy;

                    if (nx >= 0 && nx < cols && ny >= 0 && ny < rows) {
                        if (grid[ny][nx].isMine)
                            count++;
                    }
                }
            }

            grid[y][x].adjacentMines = count;
        }
    }
}

void Board::floodFill(int x, int y) {
    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return;

    Tile &tile = grid[y][x];

    if (tile.revealed || tile.flagged)
        return;

    tile.revealed = true;

    if (tile.adjacentMines != 0)
        return;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            floodFill(x + dx, y + dy);
        }
    }
}

void Board::reveal(int x, int y) {
    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return;

    Tile &tile = grid[y][x];

    if (tile.flagged || tile.revealed)
        return;

    tile.revealed = true;

    if (tile.isMine) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (grid[i][j].isMine)
                    grid[i][j].revealed = true;
            }
        }
        return;
    }

    if (tile.adjacentMines == 0)
        floodFill(x, y);
}

void Board::toggleFlag(int x, int y) {
    if (x >= 0 && x < cols && y >= 0 && y < rows) {
        if (!grid[y][x].revealed)
            grid[y][x].flagged = !grid[y][x].flagged;
    }
}

void Board::draw(sf::RenderWindow& window) {
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            grid[y][x].draw(window, hiddenSprite, revealedSprite, flagSprite, x, y);
        }
    }
}