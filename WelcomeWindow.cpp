#include "WelcomeWindow.h"
#include <SFML/Graphics.hpp>
#include <cctype>

using namespace std;

string runWelcomeWindow(int cols, int rows) {
    int width = cols * 32;
    int height = rows * 32 + 100;

    sf::RenderWindow window(sf::VideoMode(width, height), "Welcome");

    sf::Font font;
    font.loadFromFile("files/font.ttf");

    sf::Text prompt("Enter your name:", font, 24);
    prompt.setPosition(width / 2 - 120, height / 2 - 50);

    sf::Text input("", font, 24);
    input.setPosition(width / 2 - 120, height / 2);

    string name = "";

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return "";
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    window.close();
                    return name;
                }
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8) {
                    if (!name.empty())
                        name.pop_back();
                }
                else if (isalpha(event.text.unicode)) {
                    name += static_cast<char>(event.text.unicode);
                }

                input.setString(name);
            }
        }

        window.clear(sf::Color::Blue);
        window.draw(prompt);
        window.draw(input);
        window.display();
    }

    return name;
}