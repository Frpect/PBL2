#ifndef LOGIN_STATE_H
#define LOGIN_STATE_H
#include "State.h"
#include "Button.h"
#include"LoginTabs.h"


enum Role {// Cac hang so dai dien cho tung phase
    GUEST,       // Trang chủ
    STAFF
};

class LoginState : public State {
public:
    LoginState();
    virtual ~LoginState();
    virtual void handleEvent(SDL_Event& e) override;
    virtual void update() override;
    virtual void render(SDL_Renderer* des_, const SDL_Rect* clip = nullptr) override;    
protected:    
    Role identity_;
    int currentTab_;
    std::vector<std::unique_ptr<Tab>> tabs_; 
};
#endif