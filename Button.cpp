#include <iostream>
#include "Button.h"

using namespace sf;

Button::Button(float x, float y, float width, float height, float shift, Font *font, std::string text) {
    this->buttonState = BTN_IDLE;

    this->textIdleColor = Color(100, 100, 100, 200);
    this->textHoverColor = Color(0, 0, 0, 250);
    this->textActiveColor = Color(20, 20, 20, 50);
    this->idleColor = Color(70, 70, 70, 0);
    this->hoverColor = Color(150, 150, 150, 0);
    this->activeColor = Color(20, 20, 20, 0);

    this->shape.setSize(Vector2f(width, height));
    this->shape.setPosition(x / 2 - 100, y / 4 + shift);
    this->shape.setFillColor(this->idleColor);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(this->textIdleColor);
    this->text.setCharacterSize(50);
    this->text.setPosition(
            this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );
}

Button::~Button() {

}

const bool Button::isPressed() const {
    if (this->buttonState == BTN_ACTIVE)
    {
        return true;
    } else
    {
        return false;
    }
}

void Button::update(const sf::Vector2f mousePos) {
    this->buttonState = BTN_IDLE;
    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (this->buttonState)
    {
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            this->text.setFillColor(this->textIdleColor);
            break;
        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            this->text.setFillColor(this->textHoverColor);
            break;
        case BTN_ACTIVE:
            this->shape.setFillColor(this->activeColor);
            this->text.setFillColor(this->textActiveColor);
            break;
        default:
            this->shape.setFillColor(Color::Red);
            this->text.setFillColor(Color::Blue);
            break;
    }
}

void Button::render(sf::RenderTarget *target) {
    target->draw(this->shape);
    target->draw(this->text);
}
