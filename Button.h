#ifndef MINESWEEPER_BUTTON_H
#define MINESWEEPER_BUTTON_H
#include <SFML/Graphics.hpp>

enum ButtonStates {
    BTN_IDLE = 0,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button {
private:
    short unsigned buttonState;
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;

    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;


public:
    Button(float x, float y, float width, float height, float shift, sf::Font* font, std::string text);
    ~Button();

    const bool isPressed() const;

    void update(const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};


#endif //MINESWEEPER_BUTTON_H
