#ifndef MINESWEEPER_GAMESTATE_H
#define MINESWEEPER_GAMESTATE_H

#include "State.h"
class State;

class GameState:public State {
private:
    sf::RenderWindow* window;
    sf::Font font;
    Field* field;
    Text flags;
    Texture buttonGame;
    Texture buttonWon;
    Texture buttonLost;
    Sprite buttonImage;
    Text time;
    int timeCounter;
    Thread *thread;

    void init_flag_counter();
    void init_button();
    void init_time_counter();
    void time_count();
    void set_time();
    void init_components();
    void init_key_binds() override;
protected:

public:
    GameState(sf::RenderWindow *window, std::map<string, int>* supportedKeys, std::stack<State*>* states, Font font, int lvl);
    virtual ~GameState();

    void new_game();
    void set_flags();

    void update_button();
    void update_field();
    void update_input(const float& dt) override;
    void update(const float& dt) override;
    void render_components(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr) override;
};


#endif //MINESWEEPER_GAMESTATE_H
