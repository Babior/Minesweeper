#include "MenuState.h"

using namespace sf;

void MenuState::init_fonts() {
    if (!font.loadFromFile("../fonts/kenvector-future.ttf"))
    {
        cerr << "MenuState: Could not find font." << endl;
    }
}

void MenuState::init_key_binds() {
    this->keyBinds["CLOSE"] = this->supportedKeys->at("Escape");
    this->keyBinds["MOVE_UP"] = this->supportedKeys->at("Up");
    this->keyBinds["MOVE_DOWN"] = this->supportedKeys->at("Down");
}

void MenuState::init_title() {
    title.setFont(font);
    title.setString("Minesweeper");
    title.setCharacterSize(80);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Black);
    title.setOrigin(title.getLocalBounds().width / 2,
                    title.getLocalBounds().height / 2);
    title.setPosition(this->background.getSize().x / 2, this->background.getSize().y / 2 - 270.f);
}

void MenuState::init_buttons() {
    this->buttons["EASY"] = new Button(this->window->getSize().x, this->window->getSize().y,
                                       200, 80, 0, &this->font, "Easy");
    this->buttons["MEDIUM"] = new Button(this->window->getSize().x, this->window->getSize().y,
                                         200, 80, 100, &this->font, "Medium");
    this->buttons["HARD"] = new Button(this->window->getSize().x, this->window->getSize().y,
                                       200, 80, 200, &this->font, "Hard");
    this->buttons["EXIT"] = new Button(this->window->getSize().x, this->window->getSize().y,
                                       200, 80, 300, &this->font, "Exit");
}

MenuState::MenuState(RenderWindow *window, std::map<string, int> *supportedKeys, std::stack<State *> *states)
        : State(window, supportedKeys, states) {
    this->background.setSize(Vector2f(window->getSize().x, window->getSize().y));
    this->background.setFillColor(Color::White);
    this->init_fonts();
    this->init_key_binds();
    this->init_title();
    this->init_buttons();
}

MenuState::~MenuState() {
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }
}

void MenuState::update_input(const float &dt) {

    if (Keyboard::isKeyPressed(Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
    {

    }
}

void MenuState::update_buttons() {
    for (auto &it : this->buttons)
    {
        it.second->update(this->mousePoseView);
    }

    if (this->buttons["EASY"]->isPressed())
    {
        Vector2u v(768, 768);
        this->window->setSize(v);
        resize_window(v);
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, font, 0));
    }
    if (this->buttons["MEDIUM"]->isPressed())
    {
        Vector2u v(1152, 1152);
        this->window->setSize(v);
        resize_window(v);
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, font, 1));
    }
    if (this->buttons["HARD"]->isPressed())
    {
        Vector2u v(1600, 1600);
        this->window->setSize(v);
        resize_window(v);
        this->states->push(new GameState(this->window, this->supportedKeys, this->states, font, 2));
    }

    if (this->buttons["EXIT"]->isPressed())
    {
        this->end_state();
    }
}

void MenuState::update(const float &dt) {
    this->update_mouse_position();
    this->update_input(dt);
    this->update_buttons();
}

void MenuState::render_buttons(sf::RenderTarget *target) {
    for (auto &it : this->buttons)
    {
        it.second->render(target);
    }
}

void MenuState::render(RenderTarget *target) {
    if (!target)
    {
        target = this->window;
    }

    target->draw(this->background);
    target->draw(title);
    this->render_buttons(target);
}

void MenuState::resize_window(Vector2u size) {
    FloatRect visibleArea(0, 0, size.x, size.y);
    this->window->setView(sf::View(visibleArea));
    this->window->setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width / 2.f - size.x / 2.f,
                                           sf::VideoMode::getDesktopMode().width / 4 - size.y / 2.f));
}


