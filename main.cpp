#include <SFML/Graphics.hpp>
#include "WelcomeWindow.h"
#include "Board.h"
#include <fstream>

using namespace std;

int main() {
    ifstream file("files/config.cfg");
    int cols = 25, rows = 16, mines = 50;

    if (file.is_open()) {
        file >> cols >> rows >> mines;
    }

    string playerName = runWelcomeWindow(cols, rows);
    if (playerName == "") return 0;

    int width = cols * 32;
    int height = rows * 32 + 100;

    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");

    Board board(cols, rows);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / 32;
                int y = event.mouseButton.y / 32;

                if (event.mouseButton.button == sf::Mouse::Left)
                    board.reveal(x, y);

                if (event.mouseButton.button == sf::Mouse::Right)
                    board.toggleFlag(x, y);
            }
        }

        window.clear();
        board.draw(window);
        window.display();
    }

    return 0;
}