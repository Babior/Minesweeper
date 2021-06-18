#include "Game.h"

using namespace sf;

void Game::init_variables() {
    this->window = nullptr;
    this->dt = 0.f;
    this->fullScreen = false;
}

void Game::init_window() {
    std::ifstream ifs("../Config/window.ini");
    this->videomodes = VideoMode::getFullscreenModes();
    std::string title = "None";
    VideoMode windowBounds = VideoMode::getDesktopMode();
    bool fullScreen = false;
    unsigned framerateLimit = 120;
    bool verticalSyncEnabled = false;
    unsigned antialiasingLevel = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> windowBounds.width >> windowBounds.height;
        ifs >> fullScreen;
        ifs >> framerateLimit;
        ifs >> verticalSyncEnabled;
        ifs >> antialiasingLevel;
    }

    ifs.close();

    this->fullScreen = fullScreen;
    this->windowSettings.antialiasingLevel = antialiasingLevel;
    if (this->fullScreen)
    {
        this->window = new RenderWindow(VideoMode(windowBounds), title, Style::Fullscreen, windowSettings);
    } else
    {
        this->window = new RenderWindow(VideoMode(windowBounds), title, Style::Titlebar | Style::Close, windowSettings);

    }
    this->window->setFramerateLimit(framerateLimit);
    this->window->setVerticalSyncEnabled(verticalSyncEnabled);
}

void Game::init_keys() {
    this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
    this->supportedKeys["Up"] = sf::Keyboard::Key::Up;
    this->supportedKeys["Down"] = sf::Keyboard::Key::Down;

}

void Game::init_states() {
    this->states.push(new MenuState(this->window, &this->supportedKeys, &this->states));
}

Game::Game() {
    this->init_variables();
    this->init_window();
    this->init_keys();
    this->init_states();
}

Game::~Game() {
    delete this->window;

    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}

void Game::end_app() {
    std::cout << "ending app" << "\n";
}

void Game::update_dt() {
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::update_sfml_events() {
    while (this->window->pollEvent(this->e))
    {
        if (this->e.type == Event::Closed)
        {
            this->window->close();
        }
    }
}

void Game::update() {
    this->update_sfml_events();
    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);
        if (this->states.top()->get_quit())
        {
            this->states.top()->end_state();
            delete this->states.top();
            this->states.pop();
        }
    } else
    {
        this->end_app();
        this->window->close();
    }
}

void Game::render() {
    this->window->clear(Color::White);

    if (!this->states.empty())
    {
        this->states.top()->render(this->window);
    }

    this->window->display();
}

void Game::run() {
    while (this->window->isOpen())
    {
        this->update_dt();
        this->update();
        this->render();
    }
}

