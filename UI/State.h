#ifndef STATE_H
#define STATE_H

#include"BaseObject.h"
#include"Button.h"
#include"Tab.h"

#include<vector>
class State
{
public:
    State();
    virtual ~State();
    virtual void handleEvent(SDL_Event& e) = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer* des_, const SDL_Rect* clip = nullptr);    
protected:    
    int currentTab_;
    Phase status=Phase::DOING;
    std::vector<std::unique_ptr<Tab>> tabs_; 
};
#endif