#ifndef MINESWEEPER_STATE_H
#define MINESWEEPER_STATE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>
#include "../Field.h"

class State {
private:

protected:
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<string, int>* supportedKeys;
    std::map<string, int> keyBinds;
    bool quit;

    sf::Vector2i mousePoseScreen;
    sf::Vector2i mousePoseWindow;
    sf::Vector2f mousePoseView;

    std::vector<sf::Texture> textures;

    virtual void init_key_binds() = 0;
public:
    State(sf::RenderWindow* window, std::map<string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~State();

    const bool& get_quit() const;

    void end_state();
    virtual void update_mouse_position();
    virtual void update_input(const float& dt) = 0;

    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
};


#endif //MINESWEEPER_STATE_H
