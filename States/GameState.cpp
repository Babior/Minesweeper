#include "GameState.h"

using namespace sf;

void GameState::init_key_binds() {
    this->keyBinds["CLOSE"] = this->supportedKeys->at("Escape");
    this->keyBinds["MOVE_UP"] = this->supportedKeys->at("Up");
    this->keyBinds["MOVE_DOWN"] = this->supportedKeys->at("Down");
}

void GameState::init_flag_counter() {
    this->flags.setFont(this->font);
    this->flags.setStyle(sf::Text::Bold);
    this->flags.setFillColor(sf::Color::Black);
    this->flags.setCharacterSize(40);
    this->flags.setPosition(10, 0.0f);
}

void GameState::set_flags() {
    this->flags.setString(to_string(field->getF()));
}

void GameState::init_button() {
    if (!this->buttonGame.loadFromFile("../images/happy.png"))
        cout << "Can'texture find the button image" << endl;
    if (!this->buttonLost.loadFromFile("../images/dead.png"))
        cout << "Can'texture find the button image" << endl;
    if (!this->buttonWon.loadFromFile("../images/cool.png"))
        cout << "Can'texture find the button image" << endl;
    this->buttonImage.setPosition(this->window->getSize().x / 2, 03.0f);
    this->buttonImage.setTexture(this->buttonGame);
}

void GameState::init_time_counter() {
    this->time.setFont(this->font);
    this->time.setStyle(sf::Text::Bold);
    this->time.setFillColor(sf::Color::Black);
    this->time.setCharacterSize(40);
    this->time.setPosition(this->window->getSize().x - 100.0f, 0.0f);
}

void GameState::time_count() {
    thread = new sf::Thread([=]() {
        while (field->getIsRunning())
        {
            timeCounter++;
            if (timeCounter < 10)
            {
                time.setString("0" + to_string(timeCounter));
            } else
            {
                time.setString(to_string(timeCounter));
            }
            sleep(milliseconds(1000));
        }
    });
    thread->launch();
}

void GameState::set_time() {
    timeCounter = 0;
    time.setString("00");
    time_count();
}

void GameState::init_components() {
    init_flag_counter();
    init_button();
    init_time_counter();
}

void GameState::new_game() {
    this->field->init_variables();
    this->field->init_field();
    this->field->init_borders();
    this->field->init_mines();
    this->set_flags();
    this->set_time();
}

GameState::GameState(RenderWindow *window, std::map<string, int> *supportedKeys, std::stack<State *> *states, Font font,
                     int lvl)
        : State(window, supportedKeys, states) {
    this->window = window;
    this->font = font;
    field = new Field(lvl);
    this->init_key_binds();
    this->init_components();
    this->new_game();
}

GameState::~GameState() {
    delete this->field;
    this->thread->terminate();
}

void GameState::update_button() {
    if (buttonImage.getGlobalBounds().contains(this->mousePoseView))
    {
        buttonImage.setColor(sf::Color(250, 20, 20));
    } else
    {
        buttonImage.setColor(sf::Color(255, 255, 255));
    }
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        if (buttonImage.getGlobalBounds().contains(this->mousePoseView))
        {
            buttonImage.setTexture(buttonGame);
            this->thread->terminate();
            new_game();
        }
    }

    if (!field->getIsRunning())
    {
        if (!field->getIsWon())
        {
            buttonImage.setTexture(buttonLost);
        } else
        {
            buttonImage.setTexture(buttonWon);
        }
    }
}

void GameState::update_field() {
    int x = this->mousePoseView.y / field->getW();
    int y = this->mousePoseView.x / field->getW();
    if (Mouse::isButtonPressed(Mouse::Left))
    {
        field->open_cell(x, y);
    } else if (Mouse::isButtonPressed(Mouse::Right))
    {
        if (field->getF() > 0)
        {
            field->add_flag(x, y);
            set_flags();
        }
    }
}

void GameState::update_input(const float &dt) {
    this->update_mouse_position();

    if (Keyboard::isKeyPressed(Keyboard::Key(this->keyBinds.at("CLOSE"))))
    {
        this->end_state();
    }
}

void GameState::update(const float &dt) {
    this->update_input(dt);
    this->update_button();
    this->update_field();
}

void GameState::render_components(sf::RenderTarget *target) {
    target->draw(flags);
    target->draw(buttonImage);
    target->draw(time);
}

void GameState::render(RenderTarget *target) {
    if (!target)
    {
        target = this->window;
    }
    this->render_components(target);
    this->field->render(target);
}

