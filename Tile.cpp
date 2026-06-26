#include "Tile.h"

void Tile::draw(sf::RenderWindow& window, sf::Sprite& hidden,
                sf::Sprite& revealedSprite, sf::Sprite& flagSprite,
                int x, int y) {

    if (revealed) {
        revealedSprite.setPosition(x * 32, y * 32);
        window.draw(revealedSprite);
    } else {
        hidden.setPosition(x * 32, y * 32);
        window.draw(hidden);

        if (flagged) {
            flagSprite.setPosition(x * 32, y * 32);
            window.draw(flagSprite);
        }
    }
}