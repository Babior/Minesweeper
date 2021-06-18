#include "State.h"

using namespace sf;

State::State(RenderWindow *window, std::map<string, int> *supportedKeys, std::stack<State *> *states) {
    this->window = window;
    this->supportedKeys = supportedKeys;
    this->states = states;
    this->quit = false;
}

State::~State() {

}


const bool &State::get_quit() const {
    return this->quit;
}

void State::end_state() {
    this->quit = true;
}

void State::update_mouse_position() {
    this->mousePoseScreen = Mouse::getPosition();
    this->mousePoseWindow = Mouse::getPosition(*this->window);
    this->mousePoseView = this->window->mapPixelToCoords(Mouse::getPosition(*this->window));

}

