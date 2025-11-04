#include "State.h"

State::State() : currentTab_(0) {}

State::~State() = default;

void State::handleEvent(SDL_Event& e) {
    if (currentTab_ >= 0 && currentTab_ < (int)tabs_.size()) {//Handle event
        tabs_[currentTab_]->handleEvent(e);
    }
}

void State::update() {
    if (currentTab_ >= 0 && currentTab_ < (int)tabs_.size()) { //Update Tab
        tabs_[currentTab_]->update();
    }
}

void State::render(SDL_Renderer* des_, const SDL_Rect* clip) {//Render tab
    if (currentTab_ >= 0 && currentTab_ < (int)tabs_.size()) {
        tabs_[currentTab_]->render(des_, clip);
    }
}