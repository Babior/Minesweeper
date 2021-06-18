#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#include "States/MenuState.h"


class Game {
private:
    sf::RenderWindow *window;
    sf::Event e;
    std::vector<sf::VideoMode> videomodes;
    ContextSettings windowSettings;
    bool fullScreen;

    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    std::map<string, int> supportedKeys;

    void init_variables();
    void init_window();
    void init_states();
    void init_keys();
public:
    Game();
    virtual ~Game();

    void end_app();

    void update_dt();
    void update_sfml_events();
    void update();

    void render();
    void run();
};


#endif //MINESWEEPER_GAME_H
