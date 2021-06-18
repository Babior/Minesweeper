#ifndef MINESWEEPER_MENUSTATE_H
#define MINESWEEPER_MENUSTATE_H

#include "GameState.h"
#include "../Button.h"

class MenuState : public State {
private:
    sf::RectangleShape background;
    sf::Font font;
    sf::Text title;
    map<string, Button*> buttons;

    void init_fonts();
    void init_title();
    void init_buttons();
    void init_key_binds();
public:
    MenuState(sf::RenderWindow *window, std::map<string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MenuState();

    void update_input(const float& dt) override;
    void update_buttons();
    void update(const float& dt) override;
    void render_buttons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr) override;
    void resize_window(Vector2u size);
};


#endif //MINESWEEPER_MENUSTATE_H
