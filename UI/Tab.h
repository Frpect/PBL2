#ifndef TAB_H
#define TAB_H

#include"BaseObject.h"
#include"Button.h"
#include<vector>


enum Phase {// Cac hang so dai dien cho tung phase
    DOING,
    BACK,
    DONE        
};
class Tab
{
public:
    Tab();
    ~Tab();
    virtual void handleEvent(SDL_Event& e) = 0;
    virtual void update() = 0;
    virtual void render(SDL_Renderer* des_, const SDL_Rect* clip=nullptr);
protected:
    Phase status_=DOING;
    BaseObject bG_;
    std::vector<BaseObject> texts_;
    std::vector<std::unique_ptr<Button>> buttons_;  
    friend class LoginState;  
};
#endif